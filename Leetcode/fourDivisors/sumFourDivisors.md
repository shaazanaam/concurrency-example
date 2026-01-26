#1390 Given an integer array nums , return the sum of the divisors of the integers in that array that have exactly four divisors. if ther is no such integer return 0.

Example 1:

Input: nums = [21,4,7]
Output: 32
Explanation: 
21 has 4 divisors: 1, 3, 7, 21
4 has 3 divisors: 1, 2, 4
7 has 2 divisors: 1, 7
The answer is the sum of divisors of 21 only.
Example 2:

Input: nums = [21,21]
Output: 64
Example 3:

Input: nums = [1,2,3,4,5]
Output: 0
 

Constraints:

1 <= nums.length <= 104
1 <= nums[i] <= 105


Hint Find the divisors of each element in the array 
You only need to loop to the square root of a number to find its divisors.


A number has exactly 4 divisors if and only if it is 
Case 1 : p3 where p is prime
Divisors 
1,p,p2,p3 -> exactly 4 
Case 2 , pxq where p and q are two distinct primes 
Divisors are 
1,p,q,pxq -> exactly 4

No other numbers can have exactly 4 divisors
 TAhis is the interview unlock ,

 Apply this insight to the examples 
 Example 1 :[21, 4 ,7]
 21 =3x7  two distinct  primes and they are valid
 Divisors are 1, 3,7 and 3X7 so the sums is 1+3+7+21= 32

 Interview strategy you can precompute the primes.
 since nums[i] <=10^5 , i can precompute the primes up to ✓10^5..
 For any number x<=100000;if x is composite then it can be written as x = a* b. If both a and b were  greater than the ✓x then a * b > x  (impossible) so at least one factor lesss than =✓x<=1000000 ≈ 316.
 To find the factors of any x<=1000000 its  enough to try dividing by primes up to 316.   Primes upto ✓max(A) are enough to factor any number A such that A <=max(A)                                                                                                                                                                               simple math fact is that if n is a composite number then it has a prime factor <=✓n  when we replace n with the max(A) we are just choosing a safe upper bound . Since every A in the array satisfies A<= max(A) primes upto ✓max(A) suffice for all of them.

 SO we will be precomputing the primes upto ✓max(A) since thats enough to factor every value in the array .. All number I procee are <=max(A) so the primes upto ✓max(A) cover every factorization and any composite <=max(A) must have a prime factor<=max(A)

 REMEMBER ONE THING
 to factor any number less than max(A) its sufficient to precomppute primes upto ✓max(A)

 Verbal White board explanation 
 I will explain this  using the  same idea as the sqrt n prime test 
 Start from the familiar ( your old method)
  when I check if a single number is a prime I only  test the divisibility up to sqrt N
Why becasue if  n= a x b and both a and b were greater than the sqrt n then the a x b would be greater than the n so at least one factor must be <= n
thats the mathematical fact you already trust

    Flip the direction 
    The sieve applies the same logic but instead of testing one number it eliminates all the numbers in the buld 
    Instead of asking 
    Does n have a divisor \sqrt{n}   we ask which numbers can be eliminated by the small divisors . Its the same math but in the opposite directions..

Why precomputing the primes upto ✓100000 actually enables us to check efficiently ?
    This is becasue  when you ask the question if this prime number has one prime factor p such that the remaining factor is also prime?
    And also if this number a perfect cube of a prime?
    And doing this wihtout recomputing the primality from scratch every time.
    We precompute the primes upto ✓1000000 not to find the primes but to factor numbers upto 10000 so we can recognize the two shapes that give exactly four divisors. That sentence is the corrrelation you need.

We are not precomputing the primes upto 100000 becasue it was unnecessary and it wastes the memory and time and we never divide by the primes larger than the ✓x anyway.



Why the outer loop stops at i*i<= limit? 

     When I am processing i I am asking which numbers need i as their smallest divisor?
     Any number of the form i x k where k< i already has a smaller divisor k so it would have been eliminated when k was processed.

     So the first number that actually needs i is i x i.
     SO if i x i > limit there are no numbers left that require i to eliminate them. thats why the outer loop stops at i^2 <=limit.
     i^2 is the first place where i becomes necessary.

     So why the inner loop starts at i square 
     "I start crossing at i square  becasue all the smaller multiples already have smaller factors...
      example with the i = 5
      10 -->eliminated by 2
      15 eliminated by 2 20 eliminated by 2

      the check if(isPrime[i]) is required to make sure that only primes eliminate numbers and if i is already known to be composite then it was already eliminated and it doesnt get to eliminate others and this mirrors the sqrtn prime test

      The inner Loop start
      for(int j= i x i ; j< limit ; j+= i )......
      Why do we have the first number as the ix i .. this where the explanation applies and this is becauise when I start crossing at i square because all the smaller multiples already have smaller factors.
      That is correct 
      Example i = 5 give us 25 to be  the first number whose smallest divisor is 5 and everything before that which is 10, 15,20 are already eliminated becasue the 2,3,4, were the factors which would have eliminated that\.
      So starting earlier would be redundant ::: Thats why j=ixi

      Smaller multiples dont need me and isquare is the first one that does need i ...

      j+=i means that you would be walking through all the multiples of i 
       This generates  i*i, i*(i+1), i*(i+2), i*(i+3)...
which are  exactly the numbers that contain i as the factor and need to be marked as composite....
isPrime[j] is false because j is composite becasue it has factor i and no math mystery here and this is the final act..


This is the memorization trick ??

I run i while i*i  <=limit becasue i*i is the first number that needs i as its smallest factor and any multiple of i*k with k<i  already has a smaller factor and was eliminated earlier . So I start  the inner loop at i*i and mark the multiples by stepping  j+=i.
Once i *i exceeds the limit no new composites can be formed


i*i <= limit   → i still useful
j = i*i        → first new composite
j += i         → walk multiples


So how would you use the sieve you created  in the above.
SIEVE---->primes vector

For each x in the nums:
  try diving x by primes
  if p found:
    q= x/p
    check if q is prime (using primes)
    if valid ->sum divisors
  else :
    check the cube case

##  My first approach
      for(int i = 0; i< nums.size(); i++){
                  if (nums[i]<6) continue;
                  for ( int j =0; j< sqrt(nums[i]) ;j++){
                        if((nums[i]%primes[j])==0){
                              int p= nums[i]/primes[j];
                              if ((p%primes[j])==0){
                                    int q = p/primes[j];
                                    ans += 1+p+q;
                              }
                              
                        }
                  } 
                  
            }

The above structure will have some structural bugs which will be giving the wrong answer /crash./...
1.. the inner loop condition is wrong.
    J is an index into the primes and not a candidate divisor value 
    sqrt(nums[i]) is ~ 316 max , but j doesnt represent numbers 0....316 ; it represents primes[0], primes[1], primes[2]
     this can go out of bounds if primes.size() <sqrt(nums[i]) ..

     Instead of using the inner loop you should be using the looping   through the prime values until the primes exceeds sqrt(x). This is going to be creating the problem of being out of bounds when the j increments and greater than the array bounds of the primes as you are using j to index through the primes you must make sure that this is within the bounds


     You should be using the primes list like a divisor generator...
     for(int idx = 0 ; idx<primes.size() && 1LL*primes[idx]*primes[idx]<=x; idx ++)


2..  the next issue is that you are mixing up two valid "4 divisor " shapes
     exactly 4 divisors happen only when 
      x=p^3 ( p prime)
      x = p*q( p and q distinct primes)
      int p = nums[i]/primes[j];

      in your case with the x = p^3 after dividing twice you get the q=x/p^2 and you must check the q==p or equivalently that x = p*p*p otherwise numbers like 12 can fit your checks and still be wrong

      Problem B : It completely misses the p*q case 
      For x= p*q you should do 
        find a prime divisor p
        set q = x/p
        check q is prime and q!=p

       Your current second if(p% primes[j]==0 ) is not the right check for that

      Problem C:
       for valid numbers 
         if x = p^3 --> sum is 1+p+p^2+p^3
         if x = p*q -->sum is 1+p+q+x

         but the code does ans+=1+p+q

Final Presentation 

 for(int i = 0; i< nums.size(); i++){
                  if (nums[i]<6) continue;
                  for ( int j =0; j< primes.size() &&(1LL*primes[j]*primes[j]<=nums[i]) ;j++){
                        if((nums[i]%primes[j])==0){
                              int p=primes[j];
                              if (1LL*p*p*p==nums[i]){
                                    ans +=1+p+p*p+ nums[i];
                                    break;
                              }
                              int q= (nums[i]/primes[j]);
                              if(q!=p){
                                  //dont have to worry if q is a floating point number becasue you have come
                                  //down under the check carried out before this that p is a divisor.
                                  //just check if q is prime
                                  bool qPrime = true;
                                  for(int k = 2;1LL*k*k<=q;k++){
                                    if(q%k==0){
                                          qPrime = false;
                                          break;
                                    }
                                  }
                                  if(qPrime){
                                    ans += 1+p+q+nums[i];
                                    break;
                                  }
                              }break;
                        
                        }
                  } 
                  
            }

The first break statement 

BREAK A :: the break inside the K loop ( primality test )..  This break stops testing more divisors of q once you have proven q is composite.
It does not exit the j  loop and the i loop and the divisor block 
It does saves us from wasting time after finding one divisor of q.

Break B  after the if (qPrime){ans+= .....; break }
      this break exits the j loop which is iterating over the candidate prime factors of x.  Since  you dont exit the outer i loop you still 
       move to the next number afterward
       .,.it saves  you from double counting once you have accepted the number 

Break C in the cube case

if (1LL*p*p*p == nums[i]) {
    ans += ...
    break;
}

      
      This also exits the j loop ( same as the Break B) this is becasue it sits inside the j loop body. it saves us form testing other primes after you have already confirmend its a prime cude and added the sum

Break D .. The unconditonal break at the end of the divisor block 
This is the most  important one and this is the one which saves us from keeping on scanning for other primes .
It triggers whenever you found a divisor and entered the divisor block even if q==p --> square case or qPrime = false where q is composite or the number did not qualify     ..

 The idea is that once you have found the smallest prime factor p the numbers fate is basically decided and if x is p*q with prime q ---> accept else reject ..
 There is not value in trying p=3,5,7..... after finding the p=2 and it can confuse the logic so this unconditional break is your stop after the first divisor safety net


 | Break location                          | Exits loop | Purpose                                    |
| --------------------------------------- | ---------- | ------------------------------------------ |
| Inside `for(k...)` when `q%k==0`        | `k` loop   | stop prime-check early                     |
| Inside `if(qPrime)`                     | `j` loop   | stop after accepting                       |
| Inside cube case                        | `j` loop   | stop after accepting                       |
| Unconditional break after divisor block | `j` loop   | stop after first divisor even if rejecting |

None of the breaks exit the i loop 


All the breaks exit the same j loop 
cube break 
qPrime break 
unconditonal break

You have  the option to decide where to add to the answer and then break once  at the end .. this is going to give you the straight exit idea..

 Repalicng the final primality loop ..

You can use the sieve to check for the primality of the q by the following check.
If q is composite then 
q = a*b
at least one of a or b is <=sqrt q
and since sqrt q <=100000 ~ 316 then if q is composite it must have a prime divisor in the primes vector. This means the if none of the sieve primes divide q (upto p*p <= q) then q is prime. New tool reuse sieve doing the following :
loop through the primes and then stop when the prime*prime >q check q% prime same logic fewer checks and cleaner reasoning . This way you are checking if  q exists inside the primes list becasue primes only goes up to 316 and q might be much larger 
Instead you are using the primes as possible divisors not as a lookup table and this matches your mental model perfectly.
ONE SENTENCE HOOK 
if q were composite one of the sieve primes would divide it . Instead of trial dividing q by all the integers I need to reuse the precomputed primes and then test the divisibility only by the primes up to sqrt q

