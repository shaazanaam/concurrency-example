#include <iostream>
#include <algorithm>
#include<vector>
#include<forward_list>
#include<iterator>
#include<list>
#include<type_traits>  //Add this for the removing of the references

using namespace std;



//Random iterator access version
template <typename Ran>
void sort_helper(Ran beg, Ran end, random_access_iterator_tag)
{
    sort(beg,end);
}

//Forward iterator version (copy to vector, sort, copy ack )

template<typename For>
void sort_helper( For beg, For end, forward_iterator_tag)
{
    
    using value_type = typename remove_reference<decltype(*beg)>::type;
    vector <value_type> v{beg, end}; //Copy [beg:end) into vector
    sort(v.begin(), v.end());            //sort the vector
    copy( v.begin(), v.end(),beg);       // copy sorted elements back 
}

//Bidirectional iterator version ( same as forward - copy to vector)

template<typename Bi>
void sort_helper( Bi beg, Bi end, bidirectional_iterator_tag)
{
    
    using value_type = typename remove_reference<decltype(*beg)>::type;
    vector<value_type> v{beg, end}; //copy the [beg:end) into vector
    sort( v.begin(), v.end());
    copy (v.begin(), v.end(), beg);    //copy the sorted elements back 
}

//Main sort function that dispatches based on the iterator type 

template< typename Iterator>
void smart_sort( Iterator beg, Iterator end)
{
    //Get the iterator category and dispatch to appropriate helper 
    sort_helper(beg, end, typename iterator_traits<Iterator>::iterator_category{});
}


//convenience functions for the containers

template<typename Container>
void smart_sort(Container& c)
{
    smart_sort(c.begin(), c.end());
}

//helper function to  print containers

template<typename Container>


void print(const Container& c, const string& name)
{
    cout<<name<<": ";
    for(const auto& item : c){
        cout<<item<<" ";
    }
    cout<<"\n";
}


int main()
{
    cout<<"===Testing Smart Sort with Different Container types ===\n\n";

    //Test with vector( random access iterators)
    cout<<"1. Vector( Random Access Iterators): \n";
    vector<int>v = {5,2,8,1,9,3};
    print(v, "Befor sorting ");
    smart_sort(v);
    print(v, "After sorting ");
    cout<<"Stratedy: Direct sort() on vector\n\n";

    //Test with the forward list (forward iterators)
    cout<<"2. Forward List (Forward iterators):\n";
    forward_list<int> fl = {5,2,8,1,9,3};
    print(fl, "Befor sorting");
    smart_sort(fl);
    print(fl," After sorting");
    cout<<"Strategy: Copy to vector -> sort -> copy back \n\n";

    //Test with  list ( bidirectional iterators)

    cout<<"3. List ( Bidirectional Iterators): \n";

    list<int> lst {5,2,8,1,9,3};
    print(lst, "Befor Sorting");
    smart_sort(lst);
    print(lst, "After sorting");
    cout<<"Strategy: Copy to vector -> sort 0 copy back \n\n";

    return 0;


}