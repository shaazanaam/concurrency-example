Future and promise for returning a value from a task spawned on a separate thread
packaged_task to help launch tasks and connect up  the mechanisms for returning a result 
async() for launching of a task in manner very similar to calling a function 

1. When a task wants to pass a value to another it puts the value into the promise. 
2. Somehow the implementation makes that value appear in the corresponding future from which it can be read

The Key Difference: Concurrent Work vs Sequential Work
Sequential Execution (What you're thinking of):

        // Everything happens one after another - NO PARALLELISM
        int task1_result = expensive_task1();      // Wait 5 seconds
        int task2_result = expensive_task2();      // Wait another 3 seconds  
        int final_result = task1_result + task2_result;
        // Total time: 8 seconds

        // Both tasks run SIMULTANEOUSLY - PARALLELISM!
        auto future1 = async(expensive_task1);     // Start task1 (5 seconds)
        auto future2 = async(expensive_task2);     // Start task2 (3 seconds) - RUNS AT SAME TIME

        // Both tasks are running in parallel now...

        int task1_result = future1.get();          // Wait for task1 (might block)
        int task2_result = future2.get();          // Wait for task2 (might block)
        int final_result = task1_result + task2_result;
        // Total time: 5 seconds (max of both, not sum!)


        SEQUENTIAL
        Time: 0----1----2----3----4----5----6----7----8
        Main: [----Task1----][----Task2----][Done]

        CONCURRENT

        Time: 0----1----2----3----4----5
        Main: [Start both tasks...........][get()][Done]
        Task1:[--------5 seconds--------]
        Task2:[--3 sec--]


        void process_files_sequential() {
        auto start = high_resolution_clock::now();
        
        auto data1 = process_large_file("file1.txt");    // 3 seconds
        auto data2 = process_large_file("file2.txt");    // 2 seconds  
        auto data3 = process_large_file("file3.txt");    // 4 seconds
        
        auto result = combine(data1, data2, data3);
        
        auto end = high_resolution_clock::now();
        // Total time: 9 seconds
        }

                void process_files_concurrent() {
            auto start = high_resolution_clock::now();
            
            // Start all tasks simultaneously
            auto future1 = async(process_large_file, "file1.txt");  // 3 sec
            auto future2 = async(process_large_file, "file2.txt");  // 2 sec
            auto future3 = async(process_large_file, "file3.txt");  // 4 sec
            
            // All three files are being processed in parallel now!
            
            // Get results (block only if not ready yet)
            auto data1 = future1.get();  // Might not block (could be done)
            auto data2 = future2.get();  // Probably already done (2 sec < 4 sec)
            auto data3 = future3.get();  // Might block briefly (4 sec task)
            
            auto result = combine(data1, data2, data3);
            
            auto end = high_resolution_clock::now();
            // Total time: 4 seconds (max of all three, not sum!)
        }


        Why Blocking with get() is Still Beneficial:
        1. Work happens in parallel:
        
                auto future1 = async([]{ return expensive_calculation1(); });  // Starts immediately
                auto future2 = async([]{ return expensive_calculation2(); });  // Starts immediately
                
                // Both calculations running simultaneously in background threads
                
                do_other_work();  // You can do other things while they run!
                
                // Only block when you actually need the results
                int result1 = future1.get();  // Block only if still calculating
                int result2 = future2.get();  // Block only if still calculating

        2. Optimal resource utilization:

                                // 4-core CPU example
                auto f1 = async(task_for_core1);  // Uses core 1
                auto f2 = async(task_for_core2);  // Uses core 2  
                auto f3 = async(task_for_core3);  // Uses core 3
                auto f4 = async(task_for_core4);  // Uses core 4
                
                // All 4 cores working simultaneously!
                // Sequential would only use 1 core at a time

