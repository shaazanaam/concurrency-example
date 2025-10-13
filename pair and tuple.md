PAIR and Tuple 
Often we need some data that is just data that is a colleciton of values rather than an object of a class with a well defined semanitcs and an invariant for its values . In such cases we could simply define a struct with an appropriate set of appropriately named members. Alternativly we could let the standard library define write the definition for us. For example the standard library algorithm  equal-range returns a pair of iterators specifying a subsequence meeting a predicate :


template< typenam>