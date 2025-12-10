the random number generators are used widespread in the field of simulation, security , games , testing etc..
and one of  the most efficient one in the stl libraries is the <random> and which consists of two parts:
      1. an engine that produces a sequence of random or pseudo-random values.
      2. A distribution that maps those values into a mathematical distribution in a range.

      Example of the distribution are the uniform_int_distribution ( where all integers produced are equaly likely),
                                          normal_distribution 
                                          exponential distribution 
                              each for the specified range 

                              rember that the distribution will ensure that the roandom numbers have the mathematical properties your application needs , rather than just being any old random number .

                              Why do you need a distribution along with the random number generator . The engine by itself just gives you numbers and not what you expect 

                              you might not get the number you are targeting to be in a certain range . It might happen that you might be getting large numbers and then you will be looking at billions always just because its random  
                              Distribution takes those numbers and then converts them to what you want actually.
                                                            3499211612, 581869302, 3890346734... (useless for most purposes)
                                                            With distribution you might get 
                                                            3, 1, 5, 2, 6, 4... (perfect for dice rolls!)

Bottom Line
You always need a distribution because:

Range control     - Get numbers in the range you want
Proper scaling    - Convert giant numbers to your desired size
Fair distribution - Ensure equal probability (uniform) or other patterns
Even for "just a random number," you're implicitly asking for a uniform distribution in a specific range!