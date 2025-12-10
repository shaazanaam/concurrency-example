#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
#include<numeric>
#include<vector>
#include<future>

using namespace std;
using namespace std::chrono;

// Make the work more computationally intensive
double heavy_accum(double* beg, double* end, double init) {
    double sum = init;
    for (double* it = beg; it != end; ++it) {
        // Add some computational work to make the difference more visible
        sum += *it;
        for (int i = 0; i < 100; ++i) {  // Artificial work
            sum += 0.0001 * (*it);
            sum -= 0.0001 * (*it);  // Net effect is zero, but takes time
        }
    }
    return sum;
}

// Simple accum for comparison
double accum(double* beg, double* end, double init) {
    return accumulate(beg, end, init);
}

double comp2(vector<double>& v) {
    using Task_type = double(double*, double*, double);

    packaged_task<Task_type> pt0{heavy_accum};  // Use heavy_accum
    packaged_task<Task_type> pt1{heavy_accum};

    future<double> f0{pt0.get_future()};
    future<double> f1{pt1.get_future()};

    double* first = &v[0];
    thread t1{move(pt0), first, first+v.size()/2, 0.0};
    thread t2{move(pt1), first+v.size()/2, first+v.size(), 0.0};

    t1.join();
    t2.join();

    return f0.get() + f1.get();
}

double comp4(vector<double>& v) {
    if (v.size() < 1000) 
        return heavy_accum(&v[0], &v[0] + v.size(), 0.0);
    
    auto v0 = &v[0];
    auto sz = v.size();
    
    // Force asynchronous execution with launch::async
    auto f0 = async(launch::async, heavy_accum, v0, v0+sz/4, 0.0);
    auto f1 = async(launch::async, heavy_accum, v0+sz/4, v0+sz/2, 0.0);
    auto f2 = async(launch::async, heavy_accum, v0+sz/2, v0+sz*3/4, 0.0);
    auto f3 = async(launch::async, heavy_accum, v0+sz*3/4, v0+sz, 0.0);
    
    return f0.get() + f1.get() + f2.get() + f3.get();
}

// Sequential version for comparison
double comp_sequential(vector<double>& v) {
    return heavy_accum(&v[0], &v[0] + v.size(), 0.0);
}

int main() {
    // Use a more reasonable vector size
    vector<double> data(50000);  // 50,000 elements
    iota(data.begin(), data.end(), 1.0);
    
    cout << "Vector size: " << data.size() << "\n";
    cout << "Number of CPU cores: " << thread::hardware_concurrency() << "\n\n";
    
    // Test sequential version
    cout << "=== Sequential Version ===\n";
    auto start0 = high_resolution_clock::now();
    double result0 = comp_sequential(data);
    auto end0 = high_resolution_clock::now();
    auto time0 = duration_cast<milliseconds>(end0 - start0);
    
    cout << "Sequential result: " << result0 << "\n";
    cout << "Sequential time: " << time0.count() << " ms\n\n";
    
    // Test packaged_task (2 threads)
    cout << "=== Packaged Task (2 threads) ===\n";
    auto start1 = high_resolution_clock::now();
    double result1 = comp2(data);
    auto end1 = high_resolution_clock::now();
    auto time1 = duration_cast<milliseconds>(end1 - start1);
    
    cout << "Packaged_task result: " << result1 << "\n";
    cout << "Packaged_task time: " << time1.count() << " ms\n";
    cout << "Speedup: " << (double)time0.count() / time1.count() << "x\n\n";
    
    // Test async (4 threads)
    cout << "=== Async (4 threads) ===\n";
    auto start2 = high_resolution_clock::now();
    double result2 = comp4(data);
    auto end2 = high_resolution_clock::now();
    auto time2 = duration_cast<milliseconds>(end2 - start2);
    
    cout << "Async result: " << result2 << "\n";
    cout << "Async time: " << time2.count() << " ms\n";
    cout << "Speedup: " << (double)time0.count() / time2.count() << "x\n\n";
    
    // Verify results are the same
    cout << "Results match: " << (abs(result0 - result1) < 1e-6 && abs(result1 - result2) < 1e-6 ? "Yes" : "No") << "\n";
    
    return 0;
}