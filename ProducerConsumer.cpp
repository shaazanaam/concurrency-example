#include <iostream>
#include <thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<string>

using namespace std;

//Message class to be communicated 

class Message {
    public: 
        string content;
        int id;
    Message() = default;
    Message(const string& msg, int identifier):content(msg),id(identifier){}

    friend ostream& operator<<(ostream& os , const Message& m){
        return os<<"Message "<<m.id<< ": "<<m.content;
    }
};

//Global shared resources

queue<Message> mqueue;     //The queue of messages
condition_variable mcond;  //the variable communcating the event
mutex mmutex;
bool finished = false;


//Consumer function reads and then processes the messages 
void consumer(){
    while(true)
    {
        unique_lock<mutex> lck{mmutex};     //Acquire mmutex

        // Wait until the queue is not empty OR the producer is finished 

        mcond.wait(lck, []{return !mqueue.empty() || finished; });

        //If the queue is empty and the producer is finished , exit
        if (mqueue.empty() && finished){
            break;
        }

        //get the message

        auto m = mqueue.front();
        mqueue.pop();
        lck.unlock();   //Release lock

        //Process the message ( outside of the lock )
        cout<<"Consumer processing: " <<m<<endl;
        this_thread::sleep_for(chrono::milliseconds(100)); //Simulate procesing time
    }

    cout<<"Consumer Finished : \n";
}


//Producer function creates and then sends messages 

void producer(){
    for (int i = 1; i <=10; ++i){
        Message m{"Hello from  the producer", i};

        //Fill the message with some data 
        this_thread::sleep_for(chrono::milliseconds(50)); //Simulate work
        {
            unique_lock<mutex> lck{mmutex};  //Protect operations
            mqueue.push(m);
            cout<<"Producer created: "<< m <<endl;
        }  //release the lock automatically

        mcond.notify_one(); //notify the waiting consumer
    }

    //Signal that production is complete 

    {
        unique_lock<mutex> lck {mmutex};
        finished = true;
    }
    mcond.notify_one();  //Wake up consumer to check finished flag

    cout<<"Producer finished .\n";
}

int main(){
    cout<<"Starting Producer-Consumer example ....\n\n";

    //Create producer and consumer threads
    thread producer_thread{producer};
    thread consumer_thread {consumer};

    //Wait for both the threads to complete 

    producer_thread.join();
    consumer_thread.join();

    cout<<"\nAll threads completed. \n";
    return 0;   
    
}

