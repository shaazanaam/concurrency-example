## 523 .Continuous Subarray Sum

Given an integer array nums and an integer k, return true if the nums has a good subarray or false otherwise

A good subarray is a subarray where 
1. its length is at least two 
2. and the sum of the elements of the subarray is a multiple of k

A sub array is  contiguous part of the array and then an integer x is a multiple of k if there exists an integer n such that x= n*k.
0 is always a multiple of k

Input nums =[23,2,4,6,7], k=6
Output true
Explanation : [2,4] is a continuous subarray of size 2 whose elements sum up to 6


Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
0 <= sum(nums[i]) <= 231 - 1
1 <= k <= 231 - 1


## WRONG ANSWER
 bool checkSubarraySum(vector<int>& nums , int k){
                  int counter =0, sum=0, n=0;
                  unordered_map<int,int> prefixSumCount;
                  prefixSumCount[0]=1;
                  
                  for(int i :nums){
                        sum += i;
                        //check if the prefix S                        
                        if (prefixSumCount[sum-k]>=1) {
                              counter+= prefixSumCount[sum-k];
                              
                        } 
                        prefixSumCount[sum]++;
                        if(counter>=2 && sum%k==0){
                                    return true;
                              }
                        
                  } return false;
            }

## EXPLANATION 
1. You are checking for the subarrays whose sum is exactly k and not multiples of k  and the problem wants any subarray of length >=2 whose sum is a multiple of k(sum%k ==0)
2. You are not tracking the subarray length
3. The prefix Sum logic is incorrect for this problem and you should track the remainder of the prefix sum modulo k and the earliest index where each remainder occurs
4. use a hash map to store the {remainder: index} for the sum%k and if you see the same remainder at two indices atleast 2 apart then the subarray sum between them is a multiple of k

# Concept 
 The key insight is that if two prefix sums have the same remainder when divided by k, the subarray between those two indices has a sum that is a multiple of k 

Let sum1 and sum2 be the cumulative sums at indices i and j respectively, where (j > i).
            If:
            [
            sum1 % k = sum2 % k
            ]
            Then:
            [
            sum2 - sum1 = n \cdot k
            ]
for some integer (n), meaning the subarray sum between indices (i+1) and (j) is a multiple of (k).

 You will be tracking the remainders and using the hash map to store the first index where each remainder from the sum%k occurs and if the same remainder is seen again at a later index then it means that the subarray between those indices has a sum that is a multiple of k .

 Special case for k=0
 If k=0 then check for the subarrays whose sum is exactly 0

 It uses the mathematical properties of a  remainders to determine if a subarray sum is a multiple of k.

 Example Walkthrough:
Let’s use the example nums = [23, 2, 4, 6, 7] and k = 6:

Initialization:

Start with sum = 0 and a hash map remainder = {0: -1} (to handle subarrays starting from index 0).
Iterate Through the Array:

At index 0: sum = 23, remainder = 23 % 6 = 5. Add {5: 0} to the hash map.
At index 1: sum = 25, remainder = 25 % 6 = 1. Add {1: 1} to the hash map.
At index 2: sum = 29, remainder = 29 % 6 = 5. Remainder 5 is already in the hash map at index 0. The subarray [2, 4] (from index 1 to 2) has a sum of 6, which is a multiple of 6.
Return true.
 
 The remainder(sum%k) == 0 only if the cumulative sum up to the current index is a multiple of k
 But for this problem you want to find the subarray ( not necessarily starting from index 0) whose sum is a multiple of k.

 If you check only for the sum%k==0 you will be missing the subarrays that start somewhere in the middle of the array and Instead you should check if the same remainder has occured before at a previous index.
 If so the subarray between those indices has a  sum that is a multiple of k

 Example 
if sum1%k ==sum2%k and index1-index2>=2  then the subarray from the (index1 + 1) to index2 has the sum that is a multiple of k

Summary 
Only checking the sum%k==0 finds subarrays starting at index 0. Tracking the remainder lets you find the subarrays starting anywhere


You do not need the hash map to store the count of the prefix sums
Instead you should use the hash map to store the first index where each remainder (sum%k) occurs
This is because if the same remainder appears at two different indices then the subarray between those indices has a sum that is a multiple of k
Then the hash map should be {remainder :first_index}.

do not store the counts . instead store the first index for each remainder

## Theory for solving this problem 

If you calculate the cumulative sum upto  each index and then take the sum%k you  get a remainder which is always between 0 and k-1.

 if the same remainder appears at two different indices then it means that the sum of the elements between those indixes is a multiple of k

 Why?

 if at index i the cumulative sum modulo k is r and at the index j (j>i ) the cumulative sum modulo k is also r then the sum of the subarray from i+1 to j is a multiple of k

 At index 2 sum%k = 3
 At index 5 sum%k=3
  SO the sum from index 3 to 5 is a multiple of k

  Remainder occurs means you have seen the same value of the sum%k before
   This is special  becasue it tells you that there is a subarray whose sum is a multiple of k between those two indices

Step 1: Cumulative Sum and Remainder
As you iterate through the array, keep a running sum (sum).
At each index, compute remainder = sum % k.

Step 2: Why Track Remainders?
If you see the same remainder at two different indices,
it means the sum of the elements between those indices is a multiple of k.

Why?
Suppose at index i, the cumulative sum is sum1, and at index j, it’s sum2 (j > i).
If sum1 % k == sum2 % k, then:

So, the subarray from i+1 to j sums to a multiple of k.

Step 3: Using a Hash Map
Store the first index where each remainder occurs: {remainder: index}.
If you see the same remainder again at index j, and j - previous_index >= 2,
you found a valid subarray.
Step 4: Example
Let’s use nums = [23, 2, 4, 6, 7], k = 6.

Index	Num	Cumulative Sum	Remainder (sum % k)	Hash Map (remainder: index)
-1		0	0	{0: -1}
0	23	23	5	{0: -1, 5: 0}
1	2	25	1	{0: -1, 5: 0, 1: 1}
2	4	29	5	5 already seen at 0
At index 2, remainder 5 is seen again (previously at index 0).
Subarray from index 1 to 2 ([2, 4]) has sum 6, which is a multiple of 6.

Step 5: Why Not Just sum % k == 0?
That only finds subarrays starting at index 0.
Tracking remainders lets you find subarrays starting anywhere.

Step 6: Subarray Length
Make sure the subarray length is at least 2:
if (current_index - previous_index >= 2)

Summary:

Track cumulative sum and its remainder modulo k.
Use a hash map to remember the first index where each remainder occurs.
If you see the same remainder again and the subarray is at least length 2, you found a valid subarray.

remainder[rem] = n ; it does create or update the key value pair in the map. But in your code you only  execute line in the else block 

if(remainder.count(rem)){
      //already seen check the length
} else{
      remainder[rem] = n
; // only store if not seen before}

 This means you only store the first index where this remainder occur  and if the remainder occurs again the if branch is taken so the value is not updated and the map keeps the earliest index
   The map only stores the first index for each remainder . When the same remainder occurs again you use the stored index to check the subarray length but you do not overrite it .


Certainly! Here’s the mathematical theory behind the prefix sum + remainder approach for the "Continuous Subarray Sum" problem:

1. Cumulative (Prefix) Sum
Let’s define sum[i] as the sum of the first i elements of the array (nums[0] to nums[i-1]).

For any subarray from index i to j (inclusive), the sum is:

2. Subarray Sum is a Multiple of k
We want to find if there exists a subarray of length at least 2 such that:

Substitute the formula for subarray sum:

This can be rewritten as:

This means: If two prefix sums have the same remainder when divided by k, the subarray between them has a sum that is a multiple of k.

3. Why Does This Work?
If sum[j+1] % k == sum[i] % k, then:

sum[j+1] - sum[i] is divisible by k
So, the subarray from i to j sums to a multiple of k
4. Using a Hash Map
As you iterate, keep track of the first index where each remainder occurs.
If you see the same remainder again at index j+1, and the previous index is i, then the subarray from i to j is a multiple of k.
Ensure the subarray length is at least 2: j+1 - i >= 2
5. Special Case: k == 0
If k == 0, you want to check for a subarray of length at least 2 whose sum is exactly 0.
Summary Table
Index	Prefix Sum	Remainder (sum % k)	Hash Map (remainder: index)
-1	0	0	{0: -1}
0	...	...	...
...	...	...	...
If you see the same remainder at two indices, the subarray between them is a multiple of k.

In essence:

Two prefix sums with the same remainder modulo k guarantee that the subarray between them is a multiple of k.