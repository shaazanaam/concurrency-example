When to Use Each:
Use lock_guard when:
Simple locking (lock at start, unlock at end)
No need for manual control
Maximum performance (slightly faster)
Use unique_lock when:
Need to unlock before function ends
Need to lock multiple mutexes safely
Working with condition variables
Need flexible lock management
Summary:
unique_lock gives you:

Automatic management (like lock_guard)
Manual control (lock(), unlock())
Deferred locking (defer_lock)
Multiple lock support (with std::lock())
Moveable (can transfer ownership)
Condition variable compatibility
It's the "Swiss Army knife" of lock management - flexible but slightly heavier than lock_guard.



mutex m;
int shared_data = 0;


Basick Locking( Most Common)

void function() {
    unique_lock<mutex> lock(m);  // ← Automatically locks mutex 'm'
    shared_data++;               // Safe to access shared data
    cout << shared_data << endl;
}  // ← Automatically unlocks when 'lock' goes out of scope


Constructor calls the m.lock() automatically 
Destructor calls the m.unlock() automatically 




Manual Lock Control ( advanced options)

void advanced_function() {
    unique_lock<mutex> lock(m);     // Lock acquired
    
    // Do some work with lock held
    shared_data++;
    
    lock.unlock();                  // ← Manually unlock early
    
    // Do work that doesn't need the lock
    cout << "Doing work without lock\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    
    lock.lock();                    // ← Manually lock again
    
    // Do more work with lock held
    shared_data++;
}  // ← Destructor still ensures unlock if locked



Deferred LOCKING

void deferred_locking() {
    unique_lock<mutex> lock(m, defer_lock);  // ← Don't lock yet
    
    // Do some setup work without holding the lock
    cout << "Preparing to acquire lock...\n";
    
    lock.lock();                    // ← Now manually acquire the lock
    shared_data++;
    // Automatic unlock when function ends
}