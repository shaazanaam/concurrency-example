Two Different Operations:

1. px.get_future() - Creates the Connection
promise<X> px;                    // Create promise
future<X> fx = px.get_future();   // Get the linked future from promise
//             ^^^^^^^^^^^^^^^^
//             This creates the promise/future pair connection


Purpose: Establishes the communication channel between promise and future.

2.fx.get()  //Get the actual value from the future
//This retrieves the values that were set in the promise

Purpose: Retrieves the actual data that was sent through the promise.


COMPLETE FLOW IN YOUR CODE

int main() {
    // Step 1: Create promise
    promise<X> px;
    
    // Step 2: Get linked future from promise
    future<X> fx = px.get_future();  // ← Author's px.get_future()
    //             ^^^^^^^^^^^^^^^^
    
    // Step 3: Launch tasks
    thread producer_thread{f, ref(px)};
    thread consumer_thread{g, ref(fx)};
    
    // Inside producer thread f():
    // px.set_value(42);  // Send value
    
    // Inside consumer thread g():
    // X v = fx.get();    // ← Author's fx.get() - receive value
    //       ^^^^^^^^
}


promise<X> px ←--get_future()--→ future<X> fx
     │                               │
     │ set_value(42)                 │ get() → returns 42
     │                               │
     └─────── value flows ───────────┘

Timeline of Operations:

Time 1: promise<X> px; - Create promise 
Time 2: future<X> fx = px.get_future(); - Link future to promise 
Time 3: px.set_value(42); - Producer sends value through promise 
Time 4: X v = fx.get(); - Consumer receives value through future

Both Are From the Author:
The author mentions both operations because they're both necessary:

Setting up the connection:
// Author's text: "you can get() a value... from future"
// But first you need to create the future from promise:
future<X> fx = px.get_future();  // ← This is also from author


Using the connection 
// Author's text: "If we have a future<X> called fx, we can get() a value"
X v = fx.get();  // ← This is what author was demonstrating

Why you need Both

promise<X> px;                    // Can't use this to receive values
future<X> fx = px.get_future();   // NOW you can receive values
X v = fx.get();                   // Get the actual value


Without the get_future()

promise<X> px; 
//XV = px.get() ; // Error : promise doesnt have the get() method


You need the future to receive values:

promise<X> px;
future<X> fx = px.get_future();   // Create the receiver
X v = fx.get();                   // Now you can receive


Summary:

Both examples are from the author and both are essential 
1. px.get_future() - Creates the communication channel(setup)
2. fx.get()  --Uses the communication channel ( actual communication )

