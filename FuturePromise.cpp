#include <iostream>
#include <future>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int expensive_task(int id, int seconds) {
    cout << "Task " << id << " starting (" << seconds << " seconds)\n";
    this_thread::sleep_for(chrono::seconds(seconds));
    cout << "Task " << id << " completed!\n";
    return id * 100;
}

int main() {
    cout << "=== Sequential Execution ===\n";
    auto start = high_resolution_clock::now();
    
    int result1 = expensive_task(1, 3);  // 3 seconds
    int result2 = expensive_task(2, 2);  // 2 seconds  
    int result3 = expensive_task(3, 4);  // 4 seconds
    
    auto sequential_time = duration_cast<seconds>(high_resolution_clock::now() - start);
    cout << "Sequential results: " << result1 << ", " << result2 << ", " << result3 << "\n";
    cout << "Sequential total: " << sequential_time.count() << " seconds\n\n";
    
    cout << "=== Concurrent Execution ===\n";
    start = high_resolution_clock::now();
    
    // Start all tasks simultaneously
    auto future1 = async(launch::async, expensive_task, 1, 3);  // 3 sec
    auto future2 = async(launch::async, expensive_task, 2, 2);  // 2 sec
    auto future3 = async(launch::async, expensive_task, 3, 4);  // 4 sec
    
    cout << "All tasks started, doing other work...\n";
    this_thread::sleep_for(chrono::seconds(1));  // Simulate other work
    
    // Get results (block only if necessary)
    int concurrent_result1 = future1.get();  // Might block
    cout << "Result 1 received: " << concurrent_result1 << endl;
    int concurrent_result2 = future2.get();  // Probably ready
    cout << "Result 2 received: " << concurrent_result2 << endl;
    int concurrent_result3 = future3.get();  // Might block
    cout << "Result 3 received: " << concurrent_result3 << endl;
    cout << "Result 3 received: " << concurrent_result3 << endl;
    auto concurrent_time = duration_cast<seconds>(high_resolution_clock::now() - start);
    cout << "Concurrent results: " << concurrent_result1 << ", " << concurrent_result2 << ", " << concurrent_result3 << "\n";
    cout << "Concurrent total: " << concurrent_time.count() << " seconds\n";
    cout << "Concurrent total: " << concurrent_time.count() << " seconds\n";
    
    return 0;
}