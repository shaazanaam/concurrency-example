#include <random>
#include <iostream>
#include <typeinfo>

int main() {
    // Let's see what default_random_engine actually is
    std::cout << "default_random_engine type: " << typeid(std::default_random_engine).name() << std::endl;
    
    // Compare with known engines
    std::cout << "mt19937 type: " << typeid(std::mt19937).name() << std::endl;
    std::cout << "minstd_rand type: " << typeid(std::minstd_rand).name() << std::endl;
    
    // Check if they're the same type
    std::cout << "Is default_random_engine same as mt19937? " 
              << std::boolalpha 
              << std::is_same_v<std::default_random_engine, std::mt19937> << std::endl;
    
    std::cout << "Is default_random_engine same as minstd_rand? " 
              << std::boolalpha 
              << std::is_same_v<std::default_random_engine, std::minstd_rand> << std::endl;
    
    return 0;
}