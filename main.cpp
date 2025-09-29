#include<thread>
#include<iostream>
#include<chrono>
#include<vector>
#include<mutex>

using namespace std;

// to make the outputs print safe serialize the wwrites

std::mutex cout_m;

void safe_print(const std::string& s){
    std::lock_guard<std::mutex> g(cout_m);
    std::cout<<s;
}


void f(){                                                   //function 
    for(int i = 0; i<3;++i){
        cout<<"f step "<<i <<" ("<<this_thread::get_id()<<")\n";
        this_thread::sleep_for(chrono::milliseconds(60));
    }

}  

struct F{               //function object
    void operator()(){
        for(int i = 0 ; i<3;++i){
            cout<<"F step "<<i <<" ("<<this_thread::get_id()<<")\n";
            this_thread::sleep_for(chrono::milliseconds(40));
        }
    };  //F's call operator 
};

void user()
{
    thread t1{f};
    thread t2 {F()};

    t1.join();
    t2.join();
}
int main()
{
    std::cout<<"Main thread id "<<std::this_thread::get_id()<<"\n";
    user();
    std::cout<<"Done\n";
}