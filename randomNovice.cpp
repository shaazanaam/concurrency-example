#include <functional>
#include<iostream>
#include<random>

using namespace std;

auto die = bind(uniform_int_distribution<>{1,6}, default_random_engine{});

// we can use the novice version and define a class like the Rnd_int

class Rand_int{
      
      public:
            Rand_int(int low, int high):dist{low,high}{}

      private:
            default_random_engine re;
            uniform_int_distribution<> dist;
}
