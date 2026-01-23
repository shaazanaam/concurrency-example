560: given an array of integers nums and an integer k return the total number of subarrays whose sum equals to k

Sub array is a contigious non empty sequence of elements within an array

Input nums =[1,1,1], ke=2
Output : 2

Input nums =[1,2,3] k=3
OPutput 2

in this one  you would be taking the approach were we will be having the vector and the map  which will be storing  the elements we have in the window and then try to check for the counter for a window  validation and then the condition for the window to be invalidated where by we will be shrinking the window to make it valid again while keeping track of the left and the right.



Took me a bit of time to figure out, but I found this thinking is helpful, hopefully this will be helpful to someone else:

For each index i of array A we store cumulative sums sum(A[:i]) in a hash table

We know that sum(A[:j]) = sum(A[:i]) + sum(A[i:j]) for some j > i

Let's assume that there is some contiguous subarray A[i:j] whose sum is equal to k: sum(A[i:j]) == k

If sum(A[i:j]) == k, then we can rewrite previous equality in the following ways:

sum(A[:j]) = sum(A[:i]) + k 
sum(A[:j]) - k = sum(A[:i])
Therefore, if we already saw value of sum(A[:j]) - k as a cumulative sum sum(A[:i]) for some previous i (which we can check by looking at the hash table), then it means that sum of the subarrary A[i:j] is equal to k and we can increment the counter.

1. What is a prefixSum?
A prefixSum at index i is the sum of all the elements from the start up to the index i. It is the actual value of the running sum up to a certain index

For example for the nums[1,2,3] the prefix sums are :
index 0: 1
index 1: 1+2 = 3
index 2: 1+2+3 = 6

  

2. Why use the hashmap?
We want to quickly know how many times a particular prefix sum has occured as we scan through the array
This helps us find the subarrays whose sum is exactly k.
   2.1. What is a prefixSumCount?  prefixSumCount  on the other hand is a hash map that keeps track of how many times each prefix sum has occured so far.
   for example if the prefixSumCount[3] = 2 it means the sum 3 has occured twice as a prefix sum.

3. Why initialize the prefixSumCount[0]=1? 
This means that there is only one way to have a sum of 0 before we start (the empty subarray)
This is important for the cases where a subarray starting from the index 0 sums to k.
Meaning that we have seen the sum 0 once before starting the array. its not a boolean (not just true/false) but a count
If the prefixSumCount[0]=1,
it means the sum 0 has occured once so far. So the value of the SumCount to have occured once means that the prefixSumCount[0] =1 and that there is one way to have a subarray ending at the current index that sums to k.
The value like the 1 is a count and not a boolean.

4. Why Check the prefixSumCount[sum-k]?
Suppose at the current index the running sum is SUM. If there was a previous prefixSum equal to sum-k, then the elements between that previous index and the current index sum to k.
Meaning if the sum-k has occured before it means there is a subarray ending at the current index whose sum is k
The value of the prefixSumCount[sum-k] ( which is how many times that senario happened ) tells us how many such subarrays exist.

Example :

Lets say nums =[1,2,3]
and k=3
At index 0 : sum =1
At index 1 : sum =3
      ..in this case  for the index 1 .. sum-k =3-3 =0
      if prefixSumCount[0] exists then it  means there is a subarray ending here that sums to k.

5. How does it find all the subarrays?
Everytime you find that the prefixSumCount[sum-k] exists then it means there are that many subarrays ending at the current index whose sum is k.


The hash map tracks how many times each prefix sum has occured and when you reach a new sum you check if there was previous sum that would make the subarray sum to k.




Intialily you provided with the logic were you incremented the counter by one everytime the check for the prefixSumCount was found to be greater than .  But the problem with the concept was that the prefixSumCount[sum-k] could be greater than 1  which means that there could be multiple subarrays ending at the current index whose sum is k

You should increment the counter by the value of the prefixSumCount[sum-k] not just by 1.

class Solution {
      public:
      int subarraySum(vector<int> nums, int k){
            int counter = 0; // to check whether the sub array is valid which is the sum ==k
            int begin =0, end = 0;  //two pointers one point to the tail and one to the head
            int sum =0;
            

            //intiialize the hash map here 
            unordered_map<int, int> prefixSumCount ;
            // Initialize the Hash map which is the prefixSumCount[0] to 1
            // this accounts for the subarrays that start from the index 0
            prefixSumCount[0]=1;
            for(int i : nums){
                  sum +=i;
                  
                  // check if the prefixS
                  if (prefixSumCount[sum-k]>=1) counter++;   [ this is where its wrong]
                  prefixSumCount[sum]++;
                  
            }
            
       
          
      }



      replace the (prefixSumCount[sum-k]>=1) counter++ with the counter += prefixSumCount[sum-k];

      This way you count all the subarrays ending at the current index whose sum is k