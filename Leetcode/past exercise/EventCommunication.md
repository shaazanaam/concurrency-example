The  basic support for the communicating using the external events is provided by condition_variables
found in the <condition_variable>

A condition variable  is a mechanism allowing one thread to wait for the another . In particular , it allows a thread to wait for some condition (Often called an event ) to occur as the result of the work done by  other threads

Consider that classical example of two threads communicating by passing messages through a queue
 For the simplicity we can declare the queue and the mechanism for avoiding race conditons on that queue global to the producer and the consumer


A conditon variable is synchronization mechanism that allows the threads to 
1. Wait for a specific condition or event to occur
2. Signal other threads when that condition becomes true

Its like a notification system between threads

The Producer Consumer Problem 
:  This is the classic concurrency problem 
    Producer creates the data and then puts it in a queue
    Consumer Takes the data from the queue and then processes it 
    Problem :   Consumer needs to know when that data is avaiblable

What does the conditonal variable do with the lck in this 
mcond.wait(lck,lambda)

1. Cheecks the condition first 
    . If(!mqueue.empty()|| finished){
        //Condiiton is True - dont wait , continue execution 
        return;  //
    }
    
2. If conditon is FALSE
    //conditon is false( Queue is empty and not finished)
    //So we need to wait
    //ATOMICALLY do these two things
    lck.unlock();   //Release the mutex
    //Put thread to sleep
    //Wait for the notification 

3. What happens when notify_one() is Called
    //Step-By-Step Process:
    mcond.notify_one();   //This wakes up the consumer  thread

4.  //1.notify_one() wakes up the sleeping thread 
    //2.The awakened consumer thread tries to reqcquire the lock3 .
    //3.Consumer thread gets the lock when it becomes available 
    //4.Consumer thread checks the conditon again

    Producer Thread          Consumer Thread
    ===============          ===============
    Lock acquired            (sleeping, no lock)
    Add to queue            
    Release lock    ──────┐  
                          │  
    notify_one()    ──────┼──→ Wake up!
                          │      ↓
                          └──→ Acquire lock (succeeds immediately)
                                 ↓
                             Check condition (TRUE)
                                 ↓
                             Continue with lock held

    // If producer did this (BAD example):
    
    
    
    {
        unique_lock<mutex> lck{mmutex};
        mqueue.push(m);
        mcond.notify_one();  // ← Notify while still holding lock
        this_thread::sleep_for(chrono::seconds(1)); // Still holding lock!
    }  // ← Lock finally released here

Now the sequence:

Time 1: Producer releases lock (end of scope ) 
Time 2: Producer calls notify_one() 
Time 3: Consumer thread wakes up 
Time 4: Consumer thread tries to acquire the lock 
Time 5: Consumer thread successfully acquires the lock (since producer released it) 
Time 6: Consumer thread checks condition !mqueue.empty() || finished 
Time 7: Condition is TRUE (queue not empty), so wait() returns 
Time 8: Consumer continues execution with lock held.

In this case:

notify_one() wakes up consumer at notification time
Consumer tries to acquire lock but blocks (producer still has it)
Consumer only gets lock when producer releases it (at })



Key Points 
    1. notify_one() only wakes up the thread - it doesnt give it the lock 
    2. The awakened thread must acquire the lock itself -- this might stay blocked if there is another thread that holds it
    3. In you code , timing works perfectly becasue the producer releases the lock before notifying 
    4. The lck in the wait() automatically handles the lock acquisiton when the thread wakes up 

    

    