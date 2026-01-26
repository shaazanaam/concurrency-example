2772. Apply Operations to make all  array elements equal to Zero

You are given a 0-indexed integer array nums and a positive integer k 
You can apply the following operations on the array any number of times .
      1. Choose any subarray size k from the array and decrease all its elements by 1
      2. Return true if you can make all the array elemets equal to 0 or false otherwise 

A subarray is contiguous non empty part of an array

Example 1:

Input: nums = [2,2,3,1,1,0], k = 3
Output: true
Explanation: We can do the following operations:
- Choose the subarray [2,2,3]. The resulting array will be nums = [1,1,2,1,1,0].
- Choose the subarray [2,1,1]. The resulting array will be nums = [1,1,1,0,0,0].
- Choose the subarray [1,1,1]. The resulting array will be nums = [0,0,0,0,0,0].
Example 2:

Input: nums = [1,3,1,1], k = 2
Output: false
Explanation: It is not possible to make all the array elements equal to 0.
 

Constraints:

1 <= k <= nums.length <= 105
0 <= nums[i] <= 106


## WHy this problem

It tests if you understand how local operatitons create  global constraints. FAANG  loves this because the naive simulation is too slow and you must reason about the cumulative effect and you must decide the feasibility not just compute a result
This is not about the brute force andyou must decide the feasibility not just compute a result . this is about the reasoning under constraints
It lets you decide if the array can structurraly reduce to zero becasue you cannot selectively reduce one element and every operation afffects k consecutive elements and once you move past an index you can never touch it again that last point is a killer insight

The most important idea to memorize
When you move past an index i you lose the ability to change the nums[i]. This turns this problem into a left-to-right greedy feasibility check and not an optimization or backtracking or a DP .. It just means the following ?
      Did I do enough work when I still have the chance. Greedy is forced and is not optional .
      At the index i:
         if the current value is x the only way to reduce it is to apply exactly x operations starting at i. You cannot delay it or fix it later or borrow it from another window so the greedy decison is forced and not chose and this is a Huge FAANG signal for the checking of the concept .

         This problem teaches the three elite skills 
         Skill 1: Difference array thinking (wihtout coding it )
         You are tracking how many operations are currently affecting this index and not what operations you have explicitly performed. This is the implicit prefix accumulation and not simulation.

         Skill  2: Feasibility vs construction .FAANG loves the "is it possible" problems where the final sequence doesnt matter this removes the distractions and forces the pure reasoning.
         Skill 3: One pass invariant reasoning . In this case you would be maintaining an invariant like the everything before  the index i would be guaranteed to be zero. Once that invariant would be breaking you would be returning false immediately

         GREEDY Techniques

         Take the best choice at every step . Intervals scheduling and resource optimization problems rely on this . Works when the local optimal = global optimal.  Learn when not to use is and when to actually use it. We essentially make a locally forced optimal decision at every  step without revisitng it and relying on a property that guarantees these choices compose into a valid global solution .It is not just the best choice but rather its a forced or provably safe  choice and then the decision is irreversible after this .


         Biggest question to ask if you are using the greedy and deciding  if greedy vs not greedy?

                  If I make a decison now  would I be able to reverse it later on down the line ?
                  If the answer is no then the problem is greedy and if yes then greedy is dangeorus.

## MATHEMATICAL CONCEPTS

      At the heart this problem  is about the difference constraints over the prefixes and you are not applying operations . You are solving a system of linear inequalities under prefix accumulation.

      This is like saying chose a subarray of size k and decrease all the elements by 1 which  is equivalent to saying add -1  to a range [i, i+k-1] 
      
      Mathematically that is a range update which is best understood using a difference array and you are implicitly doing 
      diff[i]-=1
      diff[i+k]+=1
      And the actual value at the index j is 
                  
            nums[j] + (t=0 to t =j) ∑ ​diff[t] where  t changes from 0 to j

      This is discrete prefix summation

      1. What must be true for a solution to exist ?
      For every index i:
                  nums[i]−(total operations covering i)=0
            so in effect this also means that the 
                  (operations covering i) = nums[i]
            This is the hard equality constraint and not an optimization.

## Why greedy is mathematicaly forced?
 When you reach index i the total number of operations that can still affect it is :
            operations started in [i-k+1,i] ( means which subarrays of size k includes index i and the answer to this is that there are i-k+1 to i number of subarrays that would can be of size k and could include the index i that is the range [i-k+1,i])

            Explaination
                   At index i which operations can touch it ?
                   Only subarrays that Start at i Or start before i but still cover it .
### Why you cant come back?
      Becasue when you are i any new subarray that you will start will be starting at index >= i+1 and so it cannot include the index  i anymore and this is the key irreversible rule.

            But once i advances :
                  Operations starting later cannot affect earlier indices

            so at the index i :
                  required operations = nums[i] - current prefix effect

            If this number is:
                  . Negative ---> over-subtracted ---> impossible 
                  . Positive but no room left ---> impossible
            This is feasibility under prefix constraints.
            

# Why prefix sum matter for this problem 
       This problem asks us to apply operations that affect many elements at once and tracking their total effect . The prefix sum lets you track how much change has happened so far without repeatedly updating every element.

# What is a difference array ?  
       In the context of prefix sum being the running total then a difference array is a record of changes and instead of saying that every element from index 2 to 4 does down by 1 you would mean in an indirect manner start subtracting 1 at index 2 and then stop subtracting after index 4.

Normal array
nums = [5, 5, 5, 5, 5]
Now suppose:
Subtract 1 from index 1 to 3
Instead of changing all:
[5, 4, 4, 4, 5]
We write a difference array:
diff = [0, -1, 0, 0, +1]

Meaning:

-1 at index 1 → “start subtracting 1 here”

+1 at index 4 → “stop subtracting after index 3”

4️⃣ How difference array becomes the real array

To get the real values, we take a prefix sum of diff.

diff:        [0, -1, 0, 0, +1]
prefix sum:  [0, -1, -1, -1, 0]


Now apply it to the original array:

nums:        [5,  5,  5,  5,  5]
final:       [5,  4,  4,  4,  5]

WHy is it important concept?
Apply many range updates and in constant time per operation and compute the final array once instead of O(n) per operation you get O(1) per operation +one prefix pass . 

When you apply a window of size k and subtract 1 you are really saying start subtracting at index i and the  stop subtracting at i+k.


