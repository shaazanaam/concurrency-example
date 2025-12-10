#include <random>
#include <string>
#include <functional>  // This is where std::bind lives



using namespace std;
using my_engine = default_random_engine;          //type of the engine
using my_distribution = uniform_int_distribution<>; // type of the distribution

my_engine re {};  // calls the default constructor   the engine automatically sets up the internal state arrays and default seed value and the current position in the sequence and all the math constants needed for the random generation
my_distribution one_to_six {1,6};    // distribution that maps to the ints 1..6
auto die = bind(one_to_six,re);   // make a generator

int x = die();