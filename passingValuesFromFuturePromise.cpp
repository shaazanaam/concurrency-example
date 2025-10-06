#include <iostream>
#include<future>
#include<thread>
#include<exception>
#include<stdexcept>
#include<chrono>


using namespace std;

//Define X as a simple type for this example

using X= int;

//Task function that puts the result into promise

void f(promise<X>& px) {
    cout<<"Task f() starting....\n";

    try{
        X res;

        //Simulate some computation that might fail
        this_thread::sleep_for(chrono::seconds(2));

        //Simulate computation( could throw exception)

        bool computation_succeeds = true; //Change to false to test exception

        if(computation_succeeds){
            res = 42;   //compute a value for the res
            cout<<"Task f() computed result: "<<res<<"\n";
            px.set_value(res);  //Sends the value to the future
        } else {
            throw runtime_error("Computation failed!");
        }
    }
    catch(...){
        //oops:couldnt compute res
        cout<<"Task f() caught an exception forwarding to the future\n";
        //pass the exception to the futures thread
        px.set_exception(current_exception());

    }

    cout<<"Task f() completed\n";
}



//Task function that gets the result from the future

void g(future<X>& fx){
    cout<<"Task g() starting, waiting for the result....\n";

    try{
        X v= fx.get(); //if necessary wait for the value to get completed // blocks until the value arrives
        cout<<"Task g() received the value: "<<v <<"\n";
        //....handle error...
    }
    catch(...){
        //oops: someone couldn't compute v
        cout<<"Task g() caught exception from future\n";
        //...handle error ...
    }

    cout<<"Task g() completed\n";
}

int main(){
    cout<<"===Promise/Future Example ====\n";

    //Create promise/ future pair 
    promise<X> px;
    future<X> fx = px.get_future();

    //Launch tasks
    thread producer_thread{f, ref(px)}; //pass promise by reference
    thread consumer_thread{g, ref(fx)}; //Pass future by reference

    //Wait for both tasks to complete 
    producer_thread.join();
    consumer_thread.join();

    cout<<"All tasks completed!\n";
    return 0;
}
