What is a packaged task?
It is a wraooer that :
. Packages a function for execution in another thread
. Automatically creates a future to get the result
. Connects function execution with result retrieval

Code Breakdown:
1. Function to be Packaged:
double accum(double* beg, double* end, double init) {
    // Compute the sum of [beg:end) starting with initial value init
    return accumulate(beg, end, init);
}

This function sums the elements in a range [beg, end) starting with init


2. Type Alias for Clarity 

using Task_type = double(double* , double*, double);

This defines the function signature that the packaged_task will wrap 

3. Creating packaged Tasks:

packaged_task<Task_type> pt0{accum};   // Package the accum function
packaged_task<Task_type> pt1{accum};   // Another package of accum
packaged_task<Task_type> pt2{accum};   // Third package (unused in your code)

What this does 
    . Wraps the accum function for async execution 
    . Each packaged_task can be executed once

4. Getting Futures

future<double>  f0{pt0.get_future()};
future<double>  f1{pt1.get_future()};

Connection established 

pt0 ←→ f0   (when pt0 executes, result appears in f0)
pt1 ←→ f1   (when pt1 executes, result appears in f1)


5. Setting up Data Pointers

double* first = &v[0];

6. Launching Tasks in the Threads
thread t1{move(pt0), first, first+v.size()/2};
//        ^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^
//        move the   arguments to accum function
//        packaged
//        task

Whats happening
move(pt0): Transfer ownership of packaged task to thread
first: Start pointer ( beginning of vector)
first+v.size()/2 : End pointer ( middle of vector)

Missing 3rd arguments: Should be inital value(0)

thread t2{move(pt1), first+v.size()/2, first+v.size(), 0};
//        ^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//        move the   arguments to accum function
//        packaged
//        task

Whats happening 
. first + v.size()/2: Start pointer (middle of vector)
. first + v.size(): End pointer( end of vector)
. 0: Initial value for the accumulation 


Issues in your code 
1. Missing 3rd argument in t1:
// Current (WRONG):
thread t1{move(pt0), first, first+v.size()/2};

// Should be:
thread t1{move(pt0), first, first+v.size()/2, 0};
//                                            ^^^ missing initial value

2. missing join calls 
// Add these before return:
t1.join();
t2.join();

3. Unused pt2:
packaged_task<Task_type> pt2{accum};   // This is never used


double comp2(vector<double>& v) {
    using Task_type = double(double*, double*, double);
    
    packaged_task<Task_type> pt0{accum};
    packaged_task<Task_type> pt1{accum};
    
    future<double> f0{pt0.get_future()};
    future<double> f1{pt1.get_future()};
    
    double* first = &v[0];
    
    // Fix: Add missing 3rd argument
    thread t1{move(pt0), first, first+v.size()/2, 0};
    thread t2{move(pt1), first+v.size()/2, first+v.size(), 0};
    
    // Fix: Wait for threads to complete
    t1.join();
    t2.join();
    
    return f0.get() + f1.get();  // Get results and sum them
}

How it works

Visual Representation 
Vector: [1, 2, 3, 4, 5, 6, 7, 8]
         └─ Thread 1 ─┘└─ Thread 2 ─┘
         
Thread 1: accum([1,2,3,4], 0) → result goes to f0
Thread 2: accum([5,6,7,8], 0) → result goes to f1

Final: f0.get() + f1.get() = sum of first half + sum of second half


Complete working Example 

#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <numeric>

using namespace std;

double accum(double* beg, double* end, double init) {
    return accumulate(beg, end, init);
}

double comp2(vector<double>& v) {
    using Task_type = double(double*, double*, double);
    
    packaged_task<Task_type> pt0{accum};
    packaged_task<Task_type> pt1{accum};
    
    future<double> f0{pt0.get_future()};
    future<double> f1{pt1.get_future()};
    
    double* first = &v[0];
    
    thread t1{move(pt0), first, first+v.size()/2, 0};
    thread t2{move(pt1), first+v.size()/2, first+v.size(), 0};
    
    t1.join();
    t2.join();
    
    return f0.get() + f1.get();
}

int main() {
    vector<double> data{1, 2, 3, 4, 5, 6, 7, 8};
    double result = comp2(data);
    cout << "Sum: " << result << endl;  // Output: 36
    return 0;
}



Step By Step execution Sequence:
Step1: Create Packaged Tasks
packaged_task<Task_type> pt0{accum};  //create task wrapper for accum
packaged_task<Task_type>  pt1 {accum};  //Create another task wrapper for accum


What happens

Two packaged_task  objects created in main thread stack
Each contains a copy of the accum function 
Each has an internal promise automatically created 

Step2: Create Future Objects

future<double> f0{pt0.get_future()};  // Get future linked to pt0's internal promise
future<double> f1{pt1.get_future()};  //Get future linked to pt1's internal promise


What happens

Two future objects created in the main thread's stack 
Each future is linked to its corresponding packaged_task's internal promise 
no computation started yet - just setup communication channels

Step3: Setup Data Pointer
double* first = &v[0];  //Get pointer to first element of the vector 

Step4:Create and Launch Threads

thread t1 {move(pt0), first, first+v.size()/2,0};

What happens here 

New OS thread created t1
pt0() is moved from the main thread to t1 thread
thread t1 immediately starts executing pt0 with the given arguments
pt0 call the accum(first,first+v.size()/2)


thread t2{move(pt1), first+v.size()/2, first+v.size(), 0};

What happens here:

Another new OS thread created (t2)
pt1 is moved from main thread to t2 thread
Thread t2 immediately starts executing pt1 with given arguments
pt1 calls accum(first+v.size()/2, first+v.size(), 0)



Step5 Threads Execute in Parallel
Main Thread: Continues to t1.join()
Thread t1:   Executing accum([1.0, 2.0, 3.0, 4.0], 0) → result = 10.0
Thread t2:   Executing accum([5.0, 6.0, 7.0, 8.0], 0) → result = 26.0

Step 6: Join Threads
t1.join();  // Main thread waits for t1 to complete
t2.join();  // Main thread waits for t2 to complete

What happens:
1. Main thread blocks until t1 finishes
2. When t1 finishes, its result(10.0) is stored in pt0's internal promise
3. Main thread blocks until t2 fisnishes
4. When t2 finishes its result(26.0) is stored in pt1's internal promise
5. Both threads are destroyed after completion 

Step 7: Get Results 

return f0.get() +f1.get();

What happens:
f0.get() retrieves result from pt0's promise-> 10.0
f1.get() retrieves result from pt1's promise ->26.0
Returns 36.0

Time 0: Main Thread
        ├─ Create pt0, pt1 (stack)
        ├─ Create f0, f1 (stack)
        └─ first = &v[0]

Time 1: Main Thread creates t1
        Main Thread: [continuing...]
        Thread t1:   [pt0 moved here] → executing accum(1,2,3,4)

Time 2: Main Thread creates t2  
        Main Thread: [continuing...]
        Thread t1:   [still computing...]
        Thread t2:   [pt1 moved here] → executing accum(5,6,7,8)

Time 3: Main Thread hits t1.join()
        Main Thread: [BLOCKED - waiting for t1]
        Thread t1:   [finishing...] → stores 10.0 in promise
        Thread t2:   [still computing...]

Time 4: t1 completes, t1.join() returns
        Main Thread: [continues to t2.join()]
        Thread t1:   [DESTROYED]
        Thread t2:   [finishing...] → stores 26.0 in promise

Time 5: t2 completes, t2.join() returns
        Main Thread: [continues to f0.get() + f1.get()]
        Thread t2:   [DESTROYED]

Time 6: Get results
        Main Thread: f0.get() → 10.0, f1.get() → 26.0 → return 36.0


MEMORY LAYOUT:
Main Thread Stack:

vector<double> test_vector  // [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0]
future<double> f0          // Linked to pt0's promise
future<double> f1          // Linked to pt1's promise  
double* first              // Points to test_vector[0]
thread t1                  // Handle to OS thread 1
thread t2                  // Handle to OS thread 2

Thread t1 Stack:
packaged_task pt0          // Moved from main thread
// Arguments: first, first+4, 0
// Executing: accum([1.0, 2.0, 3.0, 4.0], 0)

Thread t2 Stack:
packaged_task pt1          // Moved from main thread  
// Arguments: first+4, first+8, 0
// Executing: accum([5.0, 6.0, 7.0, 8.0], 0)



Key Points:
    Futures created BEFORE threads - setup communication first
    Threads start executing IMMEDIATELY when created
    Packaged tasks MOVED to threads (no longer in main thread)
    Threads execute in parallel while main thread continues
    join() blocks main thread until worker threads complete
    Threads destroyed after completion
    Results retrieved through futures after threads finish
Where Threads Live:
    Thread objects (t1, t2): In main thread's stack
    Actual OS threads: Managed by operating system
    Thread execution: On separate CPU cores (if available)
    Thread data: Each thread has its own stack space
    The sequence ensures parallel execution while maintaining thread safety through the promise/future mechanism!

Who Creates the Threads?
You're right - the threads are created inside the comp2 function, not directly in main.

Corrected Thread Ownership:

int main() {
    vector<double> test_vector{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    
    double result = comp2(test_vector);  // ← Main calls comp2
    //              ^^^^^^^^^^^^^^^^^^^
    //              Main thread executes comp2 function
    
    cout << "Sum: " << result << endl;
    return 0;
}

Inside comp2 (still running on Main Thread):

double comp2(vector<double>& v) {
    // All this code runs on the MAIN THREAD
    packaged_task<Task_type> pt0{accum};
    packaged_task<Task_type> pt1{accum};
    
    future<double> f0{pt0.get_future()};
    future<double> f1{pt1.get_future()};
    
    double* first = &v[0];
    
    // MAIN THREAD creates worker threads t1 and t2
    thread t1{move(pt0), first, first+v.size()/2, 0};  // ← t1 created by comp2
    thread t2{move(pt1), first+v.size()/2, first+v.size(), 0};  // ← t2 created by comp2
    
    // MAIN THREAD waits here
    t1.join();
    t2.join();
    
    return f0.get() + f1.get();
}


Visual Thread Hierarchy:
Main Thread (starts in main())
    │
    ├─ Executes main()
    │   └─ Calls comp2(test_vector)
    │
    ├─ Executes comp2() function
    │   ├─ Creates pt0, pt1, f0, f1
    │   │
    │   ├─ Creates Thread t1 ───────→ Worker Thread t1
    │   │                              │
    │   │                              └─ Executes pt0(accum)
    │   │
    │   ├─ Creates Thread t2 ───────→ Worker Thread t2
    │   │                              │
    │   │                              └─ Executes pt1(accum)
    │   │
    │   ├─ Waits at t1.join() ◄──────── t1 finishes
    │   ├─ Waits at t2.join() ◄──────── t2 finishes
    │   │
    │   └─ Returns result
    │
    └─ Continues in main() with result


 Detailed Execution Flow:
Step 1: Program starts
Main Thread: Enters main()   

Step 2: Main thread calls comp2Main Thread: Executing comp2() function
             ├─ Create pt0, pt1 (on main thread's stack)
             ├─ Create f0, f1 (on main thread's stack)
             └─ Create first pointer

Step 3: Main thread creates worker threads

Main Thread: Creates t1
             │
             └──────────→ Worker Thread t1 spawns
                          └─ Starts executing pt0(accum)

Main Thread: Creates t2
             │
             └──────────→ Worker Thread t2 spawns
                          └─ Starts executing pt1(accum)

Main Thread: Continues to t1.join()
Worker Thread t1: Executing accum([1,2,3,4], 0)
Worker Thread t2: Executing accum([5,6,7,8], 0)


Step 4: Main thread waits

Main Thread: BLOCKED at t1.join() - waiting for t1
Worker Thread t1: Computing sum...
Worker Thread t2: Computing sum...


Step 5: Threads complete
Worker Thread t1: Finished → stores 10.0 in promise
Main Thread: t1.join() returns
Main Thread: BLOCKED at t2.join() - waiting for t2
Worker Thread t2: Finished → stores 26.0 in promise

Step 6: Main thread gets results

Main Thread: t2.join() returns
Main Thread: f0.get() + f1.get() = 36.0
Main Thread: Returns to main()
Main Thread: Prints result and exits


Thread Creation Summary:

Thread	Created By	        Created Where	                Purpose

Main Thread	OS/Runtime	    main() entry	                Orchestrates program
Worker Thread t1	        Main thread	Inside comp2()	    Compute first half
Worker Thread t2	        Main thread	Inside comp2()	    Compute second half

Key Points:

Main thread executes comp2() - it's just a regular function call
Inside comp2(), the main thread creates worker threads - t1 and t2
Worker threads are children of main thread - spawned by main
Main thread waits for workers - using join()
Workers execute in parallel - on different CPU cores if available

Stack Frames:
Main Thread Stack:
┌─────────────────────────┐
│ main() frame            │
│  ├─ test_vector         │
│  ├─ result (after comp2)│
│  └─ expected            │
├─────────────────────────┤
│ comp2() frame           │  ← Main thread is HERE executing comp2
│  ├─ pt0, pt1 (moved out)│
│  ├─ f0, f1              │
│  ├─ first               │
│  ├─ t1 (thread handle)  │
│  └─ t2 (thread handle)  │
└─────────────────────────┘

Worker Thread t1 Stack:
┌─────────────────────────┐
│ pt0 operator() frame    │
│  ├─ beg, end, init      │
│  └─ accum() execution   │
└─────────────────────────┘

Worker Thread t2 Stack:
┌─────────────────────────┐
│ pt1 operator() frame    │
│  ├─ beg, end, init      │
│  └─ accum() execution   │
└─────────────────────────┘