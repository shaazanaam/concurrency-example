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


