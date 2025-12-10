Simple Summary Table:
Template	        Input	                        Output	                                Purpose

Iterator_type<C>	Container type (vector<int>)	Iterator type (vector<int>::iterator)	Get the     iterator from container

Iterator_category<Iter>	Iterator type (vector<int>::iterator)	Tag type (random_access_iterator_tag)	

Get the category of iterator


In Your Code:

template<typename Iterator>
void smart_sort(Iterator beg, Iterator end)
{
    // Using Iterator_category to get the tag
    sort_helper(beg, end, Iterator_category<Iterator>{});
    //                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //                    1. Iterator_category<Iterator> gives tag TYPE
    //                    2. {} creates instance of that tag
}

template<typename Container>
void smart_sort(Container& c)
{
    // Using Iterator_type to get iterator from container
    smart_sort(c.begin(), c.end());
    
    // Could also write it like this:
    // using Iter = Iterator_type<Container>;
    // Iter beg = c.begin();
    // Iter end = c.end();
    // smart_sort(beg, end);
}



Iterator_type<C>
Input: Container(vector<int>)
Output:its iterator type (vector<int::iterator>)
Purpose:Shortcut instead of writing C::iterator


Iterator_category<Iter>
Input: Iteratory type( vector<int>::iterator)
Output: Tag type (random_access_iterator_tag)
Purpose: tells you what kind of  iterator it is 

