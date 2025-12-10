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
    
    vector<double>& v;
    F(vector<double>& vv):v{vv}{}
    
    void operator()(){
        for(int i = 0 ; i<3;++i){
            cout<<"F step "<<i <<" ("<<this_thread::get_id()<<")\n";
            this_thread::sleep_for(chrono::milliseconds(40));
        }
    };  //F's call operator 
};
void f2 (vector<double>& v)   //function do something with the vector v
{
    for(size_t i = 0 ; i <v.size(); ++i){
        safe_print("f2 processing element " + to_string(i) + ": " + to_string(v[i]) + "\n");
        this_thread::sleep_for(chrono::milliseconds(50));
        
    }
}

void user()
{
    vector<double> some_vec{1,2,3,4,5,6,7,8,9};
    vector<double> vec2 {10,11,12,13,14};
    
    thread t1{f2,std::ref(some_vec)};
    thread t2 {F{vec2}};

    t1.join();
    t2.join();
}
int main()
{
    std::cout<<"Main thread id "<<std::this_thread::get_id()<<"\n";
    user();
    std::cout<<"Done\n";
}