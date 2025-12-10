PAIR and Tuple 
Often we need some data that is just data that is a colleciton of values rather than an object of a class with a well defined semanitcs and an invariant for its values . In such cases we could simply define a struct with an appropriate set of appropriately named members. Alternatively we could let the standard library  write the definition for us. For example the standard library algorithm  equal-range returns a pair of iterators specifying a subsequence meeting a predicate :


template< typename Forward_iterator, typename T, typename Compare>
    pair<Forward_iterator, Forward_iterator>
    equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);

    Given a sorted sequence [first:last), equal_range() will return the pair representing the subsequence that matches the predicate cmp]

    We can use that to search in a sorted sequence of Records:
      auto req_eq = [](const Record& r1 , const Record& r2){return r1.name < r2.name;};  

      void f(const vector <Record>& v) //assume that v is sorted on its name field 
      {
        auto er = equal_range(v.begin(), v.end(), Record{"Reg"}, rec_eq);
        for (auto p = er.first; p!=er.second; ++p)
            cout<<*p;   //assume that << is defined for Record
      }