Given an integer array nums , return the sum of the divisors of the integers in that array that have exactly four divisors. if ther is no such integer return 0.

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
 since nums[i] <=10^5 , i can precompute the primes up to sqrt 10^5