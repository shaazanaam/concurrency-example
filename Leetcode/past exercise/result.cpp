#include <iostream>
#include<thread>
#include<vector>
 using namespace std;

 void f(const vector<double>& v, double* res);  //take the input from v and the place the result in *res
 
 class F {
    public:
        F(const vector<double>& vv, double* p):v{vv}, res{p}{}
        
        void operator()(){
        //Calculate  something and then store in the *res
        *res = v.size();
        };

    private:
        const vector<double>& v;    //source of the input
        double* res;


    

 };

 void f (const vector<double>& v, double* res){
    //calculate something and then sote in the res;

    *res = v.size(); //Example store the size of the vector inside the res
 }



 int main()
 {
    vector<double> some_vec(5);
    vector<double> vec2(3,2.5);

    double res1; 
    double res2;

    thread t1{f, some_vec,&res1};
/*
Why it works:
some_vec gets copied to the thread, then passed as const vector<double>& to f()
&res1 is a pointer (not a reference), so it copies the address
*/  

    thread t2{F{vec2,&res2}};

    t1.join();
    t2.join();

    cout<<res1<<' '<<res2<<'\n';



 }