#include <iostream>
#include <vector>
#include <list>
#include <forward_list>
#include <iterator>
#include <type_traits>

using namespace std;

// DEFINITION 1: Get iterator type from container
template<typename C>
using Iterator_type = typename C::iterator;
//    ^^^^^^^^^^^^^ = ^^^^^^^^^^^^^^^^^^^
//    What you call   What you get

// DEFINITION 2: Get iterator category from iterator
template<typename Iter>
using Iterator_category = typename iterator_traits<Iter>::iterator_category;
//    ^^^^^^^^^^^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//    What you call       What you get

int main() {
    cout << "=== Understanding Iterator Type Aliases ===\n\n";
    
    // ====================================
    // Part 1: Iterator_type<C>
    // ====================================
    cout << "1. Iterator_type<C> - Gets container's iterator type\n\n";
    
    vector<int> v = {1, 2, 3};
    
    // Long way (without alias):
    cout << "   Long way:\n";
    vector<int>::iterator it1 = v.begin();
    cout << "   vector<int>::iterator it1 = v.begin();\n";
    cout << "   Value: " << *it1 << "\n\n";
    
    // Short way (with alias):
    cout << "   Short way (using Iterator_type):\n";
    Iterator_type<vector<int>> it2 = v.begin();
    //            ^^^^^^^^^^^
    //            C = vector<int>
    //            Returns: vector<int>::iterator
    cout << "   Iterator_type<vector<int>> it2 = v.begin();\n";
    cout << "   Value: " << *it2 << "\n\n";
    
    cout << "   Both are the same type!\n\n";
    
    // ====================================
    // Part 2: Iterator_category<Iter>
    // ====================================
    cout << "2. Iterator_category<Iter> - Gets iterator's category tag\n\n";
    
    // Get iterator type first
    using VecIter = Iterator_type<vector<int>>;  // vector<int>::iterator
    
    // Long way (without alias):
    cout << "   Long way:\n";
    using tag1 = typename iterator_traits<VecIter>::iterator_category;
    cout << "   typename iterator_traits<VecIter>::iterator_category\n";
    cout << "   Is random_access? " 
         << is_same<tag1, random_access_iterator_tag>::value << "\n\n";
    
    // Short way (with alias):
    cout << "   Short way (using Iterator_category):\n";
    using tag2 = Iterator_category<VecIter>;
    //                             ^^^^^^^
    //                             Iter = VecIter (vector<int>::iterator)
    //                             Returns: random_access_iterator_tag
    cout << "   Iterator_category<VecIter>\n";
    cout << "   Is random_access? " 
         << is_same<tag2, random_access_iterator_tag>::value << "\n\n";
    
    cout << "   Both are the same type!\n\n";
    
    // ====================================
    // Part 3: Using them together
    // ====================================
    cout << "3. Using both together:\n\n";
    
    // Step 1: Get iterator type from container
    using MyIterator = Iterator_type<list<int>>;
    //                 ^^^^^^^^^^^^^ ^^^^^^^^^^
    //                 Template      C = list<int>
    //                 Returns: list<int>::iterator
    cout << "   Step 1: Iterator_type<list<int>> = list<int>::iterator\n";
    
    // Step 2: Get category from iterator type
    using MyCategory = Iterator_category<MyIterator>;
    //                 ^^^^^^^^^^^^^^^^^ ^^^^^^^^^^
    //                 Template          Iter = list<int>::iterator
    //                 Returns: bidirectional_iterator_tag
    cout << "   Step 2: Iterator_category<list<int>::iterator>\n";
    cout << "           = bidirectional_iterator_tag\n";
    cout << "   Is bidirectional? " 
         << is_same<MyCategory, bidirectional_iterator_tag>::value << "\n\n";
    
    // ====================================
    // Part 4: Different containers
    // ====================================
    cout << "4. Testing with different containers:\n\n";
    
    // Vector
    using VecCategory = Iterator_category<Iterator_type<vector<int>>>;
    cout << "   vector: random_access? " 
         << is_same<VecCategory, random_access_iterator_tag>::value << "\n";
    
    // List
    using ListCategory = Iterator_category<Iterator_type<list<int>>>;
    cout << "   list: bidirectional? " 
         << is_same<ListCategory, bidirectional_iterator_tag>::value << "\n";
    
    // Forward list
    using FListCategory = Iterator_category<Iterator_type<forward_list<int>>>;
    cout << "   forward_list: forward? " 
         << is_same<FListCategory, forward_iterator_tag>::value << "\n";
    
    return 0;
}