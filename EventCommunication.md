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
    
