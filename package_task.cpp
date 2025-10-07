#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<numeric>
#include<vector>
#include<future>

using namespace std;




double accum(double* beg, double* end, double init)
{
    //compute the sum of the [beg:end)  starting with the initial value init
    return accumulate(beg, end, init);
}

double comp2(vector<double>& v){
    using Task_type = double(double*, double*, double);     //type of the task

    packaged_task<Task_type> pt0{accum};   //package the task (i.e., accum)
    packaged_task<Task_type> pt1{accum};
    packaged_task<Task_type> pt2{accum};

    future<double> f0 {pt0.get_future()};
    future<double> f1 {pt1.get_future()};

    double* first = &v[0];
    thread t1 {move(pt0),first,first+v.size()/2,0};
    thread t2 {move(pt1),first+v.size()/2,first+v.size(),0};

    t1.join();
    t2.join();


    return f0.get() +f1.get();  //get the result

}

int main(){
    // Initialize the vector with the test data 
    vector<double> test_vector{1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};

    cout<<"Vector contents: ";
    for(double val : test_vector){
        cout<<val<<" ";

    }
    cout<<endl;

    double result = comp2(test_vector);
    cout<<"Sum using parallel computation: "<<result<<endl;

    //Verify with standard accumulate

    double expected = accumulate(test_vector.begin(), test_vector.end(),0.0);
    cout<<"Expected sum: "<<expected<<endl;
    return 0 ;
}