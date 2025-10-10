The standard library sort() takes a pair of iterators supposed to define a sequence.

Furthermore,
those iterators must offer random access to that sequence, that is, they must be randomaccess
iterators. Some containers, such as forward_list, do not offer that. In particular, a forward_
list is a singly-linked list so subscripting would be expensive and there is no reasonable way
to refer back to a previous element. However, like most containers, forward_list offers forward iterators
that can be used to traverse the sequence by algorithms and for-statements (§33.1.1).
The standard library provides a mechanism, iterator_traits that allows us to check which kind of
iterator is supported. Given that, we can improve the range sort() from §4.5.6 to accept either a
vector or a forward_list. For example:
void test(vector<string>& v, forward_list<int>& lst)
{
sort(v); // sor t the vector
sort(lst); // sor t the singly-linked list
}
The techniques needed to make that work are generally useful.
First, I write two helper functions that take an extra argument indicating whether they are to be
used for random-access iterators or forward iterators. The version taking random-access iterator
arguments is trivial:
Section 5.4.2.1 iterator_traits 125
template<typename Ran> // for random-access iterators
void sort_helper(Ran beg, Ran end, random_access_iterator_tag) // we can subscript into [beg:end)
{
sort(beg,end); // just sort it
}
The version for forward iterators is almost as simple; just copy the list into a vector, sort, and copy
back again:
template<typename For> // for forward iterators
void sort_helper(For beg, For end, forward_iterator_tag) // we can traverse [beg:end)
{
vector<decltype(∗beg)> v {beg,end}; // initialize a vector from [beg:end)
sort(v.begin(),v.end());
copy(v.begin(),v.end(),beg); // copy the elements back
}
The decltype() is a built-in type function that returns the declared type of its argument (§6.3.6.3).
Thus, v is a vector<X> where X is the element type of the input sequence.
The real ‘‘type magic’’ is in the selection of helper functions:
template<typname C>
void sort(C& c)
{
using Iter = Iterator_type<C>;
sort_helper(c.begin(),c.end(),Iterator_category<Iter>{});
}
Here, I use two type functions: Iterator_type<C> returns the iterator type of C (that is, C::iterator) and
then Iterator_category<Iter>{} constructs a ‘‘tag’’ value indicating the kind of iterator provided:
• std::random_access_iterator_tag if C’s iterator supports random access.
• std::forward_iterator_tag if C’s iterator supports forward iteration.
Given that, we can select between the two sorting algorithms at compile time. This technique,
called tag dispatch is one of several used in the standard library and elsewhere to improve flexibility
and performance.
The standard-library support for techniques for using iterators, such as tag dispatch, comes in
the form of a simple class template iterator_traits from <iterator> (§33.1.3). This allows simple definitions
of the type functions used in sort():
template<typename C>
using Iterator_type = typename C::iterator; // C’s iterator type
template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // Iter’s categor y
If you don’t want to know what kind of ‘‘compile-time type magic’’ is used to provide the standardlibrary
features, you are free to ignore facilities such as iterator_traits. But then you can’t use the
techniques they support to improve your own code.

The idea is simple and can't use standard sort() because it only has forward iterators ( cant jump around).

Solution 
1. Copy the forward list into a vector 
2. Sort the vector ( which has random access  iterators)
3. Copy back the sorted elements to the original container

How the Forward Iterator Version Works:

template<typename For> // for forward iterators
void sort_helper(For beg, For end, forward_iterator_tag)
{
    vector<decltype(*beg)> v{beg, end}; // Copy [beg:end) into vector
    sort(v.begin(), v.end());           // Sort the vector
    copy(v.begin(), v.end(), beg);      // Copy sorted elements back
}
Step-by-Step Breakdown:

// Step 1: Copy to vector
vector<decltype(*beg)> v{beg, end};
//      ^^^^^^^^^^^^^^     ^^^^^^^
//      Type of elements   Range constructor copies all elements

// Step 2: Sort the vector (fast because vector has random access)
sort(v.begin(), v.end());

// Step 3: Copy sorted elements back to original container
copy(v.begin(), v.end(), beg);
//   ^^^^^^^^^^^^^^^^^^^  ^^^
//   Sorted vector range  Start of original container


#include <iostream>
#include <algorithm>
#include <vector>
#include <forward_list>
#include <list>
#include <iterator>

using namespace std;

// Fix your random access version
template <typename Ran>
void sort_helper(Ran beg, Ran end, random_access_iterator_tag)
{
    sort(beg, end);  // Fix: was missing 'end' parameter
}

// Forward iterator version (copy to vector, sort, copy back)
template<typename For>
void sort_helper(For beg, For end, forward_iterator_tag)
{
    vector<decltype(*beg)> v{beg, end}; // Copy [beg:end) into vector
    sort(v.begin(), v.end());           // Sort the vector
    copy(v.begin(), v.end(), beg);      // Copy sorted elements back
}

// Bidirectional iterator version (same as forward - copy to vector)
template<typename Bi>
void sort_helper(Bi beg, Bi end, bidirectional_iterator_tag)
{
    vector<decltype(*beg)> v{beg, end}; // Copy to vector
    sort(v.begin(), v.end());           // Sort the vector
    copy(v.begin(), v.end(), beg);      // Copy back
}

// Main sort function that dispatches based on iterator type
template<typename Iterator>
void smart_sort(Iterator beg, Iterator end)
{
    // Get the iterator category and dispatch to appropriate helper
    sort_helper(beg, end, typename iterator_traits<Iterator>::iterator_category{});
}

// Convenience function for containers
template<typename Container>
void smart_sort(Container& c)
{
    smart_sort(c.begin(), c.end());
}

// Helper function to print containers
template<typename Container>
void print(const Container& c, const string& name)
{
    cout << name << ": ";
    for (const auto& item : c) {
        cout << item << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "=== Testing Smart Sort with Different Container Types ===\n\n";

    // Test with vector (random access iterators)
    cout << "1. Vector (Random Access Iterators):\n";
    vector<int> v = {5, 2, 8, 1, 9, 3};
    print(v, "Before sorting");
    smart_sort(v);
    print(v, "After sorting");
    cout << "Strategy: Direct sort() on vector\n\n";

    // Test with forward_list (forward iterators)
    cout << "2. Forward List (Forward Iterators):\n";
    forward_list<int> fl = {5, 2, 8, 1, 9, 3};
    print(fl, "Before sorting");
    smart_sort(fl);
    print(fl, "After sorting");
    cout << "Strategy: Copy to vector -> sort -> copy back\n\n";

    // Test with list (bidirectional iterators)
    cout << "3. List (Bidirectional Iterators):\n";
    list<int> lst = {5, 2, 8, 1, 9, 3};
    print(lst, "Before sorting");
    smart_sort(lst);
    print(lst, "After sorting");
    cout << "Strategy: Copy to vector -> sort -> copy back\n\n";

    return 0;
}

Visual Example with Forward List:
Original forward_list:

[5] -> [2] -> [8] -> [1] -> [9] -> [3] -> null


Step 1: Copy to vector

vector<int> v{beg, end};  // v = [5, 2, 8, 1, 9, 3]

Step 2: Sort the vector

sort(v.begin(), v.end());  // v = [1, 2, 3, 5, 8, 9]

Step 3: Copy back to forward_list
copy(v.begin(), v.end(), beg);

Result:

[1] -> [2] -> [3] -> [5] -> [8] -> [9] -> null

Why This Strategy Works:
For Random Access (vector, array, deque):
sort(beg, end);  // Direct sort - very fast

For Forward/Bidirectional (forward_list, list):

vector<T> temp{beg, end};    // O(n) copy
sort(temp.begin(), temp.end()); // O(n log n) sort  
copy(temp.begin(), temp.end(), beg); // O(n) copy back
// Total: O(n log n) - same complexity, just more memory


Key Points:

decltype(*beg) automatically deduces the element type
Vector constructor {beg, end} copies all elements from the range
copy() writes sorted elements back to original positions
Same time complexity O(n log n), but uses extra O(n) memory
Iterator traits automatically choose the right strategy

Expected Output:

=== Testing Smart Sort with Different Container Types ===

1. Vector (Random Access Iterators):
Before sorting: 5 2 8 1 9 3 
After sorting: 1 2 3 5 8 9 
Strategy: Direct sort() on vector

2. Forward List (Forward Iterators):
Before sorting: 5 2 8 1 9 3 
After sorting: 1 2 3 5 8 9 
Strategy: Copy to vector -> sort -> copy back

3. List (Bidirectional Iterators):
Before sorting: 5 2 8 1 9 3 
After sorting: 1 2 3 5 8 9 
Strategy: Copy to vector -> sort -> copy back

Compile and Run:

g++ -std=c++20 -Wall -Wextra iterator_traits.cpp -o iterator_traits.exe
./iterator_traits.exe


This demonstrates the power of template specialization and iterator traits - one smart_sort() function that automatically chooses the best strategy for any container type!


