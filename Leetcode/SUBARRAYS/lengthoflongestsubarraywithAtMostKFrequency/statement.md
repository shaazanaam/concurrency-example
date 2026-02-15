2958. Length of Longest Subarray With at Most K Frequency

You are given an integer array nums and an integer k.

The frequency of an element x is the number of times it occurs in an array.

An array is called good if the frequency of each element in this array is less than or equal to k.

Return the length of the longest good subarray of nums.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,2,3,1,2,3,1,2], k = 2
Output: 6
Explanation: The longest possible good subarray is [1,2,3,1,2,3] since the values 1, 2, and 3 occur at most twice in this subarray. Note that the subarrays [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good.
It can be shown that there are no good subarrays with length more than 6.
Example 2:

Input: nums = [1,2,1,2,1,2,1,2], k = 1
Output: 2
Explanation: The longest possible good subarray is [1,2] since the values 1 and 2 occur at most once in this subarray. Note that the subarray [2,1] is also good.
It can be shown that there are no good subarrays with length more than 2.
Example 3:

Input: nums = [5,5,5,5,5,5,5], k = 4
Output: 4
Explanation: The longest possible good subarray is [5,5,5,5] since the value 5 occurs 4 times in this subarray.
It can be shown that there are no good subarrays with length more than 4.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= nums.length

HINT 


For each index i find the right most index j (i<=j)such that the frequency of each element in the subarray[i,j] is at most K.

my initial solution was 
int lengthOfLongestSubarray(vector<int> nums, int k ){
            unordered_map<long,long> uniqueIntegersCount;
            int L=0,distinct=0,ans=0;
            for(int R=0; R<nums.size();R++){
                if(uniqueIntegersCount[nums[R]]==0) distinct++;

                uniqueIntegersCount[nums[R]]++;

                while(distinct>k){
                    uniqueIntegersCount[nums[L]]--;
                    if(uniqueIntegersCount[nums[L]]==0) distinct--;
                    L++;
                }
                ans = max(ans,R-L+1);
                
            }
            return ans;
        }

In this logic there are conceptual errors and you use two pointers , L and R to define the window and as you iterate through the array with the R you add elements to the frequency map and then track the number of distinct elements and you use the condition check to chekc if the number of distinct elements exceeds k , you shrink the window by incrementing the L and adjusting the frequency map. 

After ensuring you  satisfy your window conditon ( distinct<=k>) you calculate the maximum length of the window ( R-L+1) then you return the maximum length of the calid subarray .

But here is the problem and the conceptual issue with the above code :
 the problem asks for the longest subarray where the frequency of each element is at most k and this means you need to track the frequency of the elements not just the count of the distinct elements. You would have to check 
each element's frequency is <=k in your logic which is the conceptual gap found above 

Frequency vs Distinct count 
the problem is about the frequency of the elements and not thenumber of distinct elements for example is nums = [1,1,2,3]  and ke = 2 the subarray [1,1,2,2] is valid becasue the  frequency  of each element is <=k

  With just the distinct you might incorrectly shrink the window when just the distinct is less than k  even  though the frequencies are valid 

  When shrinking the window  you need to correctly update the frequency map and ensure that the  condition (frequency of each element <k)  is the one that is restored

   You do need to consider the edge cases like the nums=[5,5,5,5]
 where all the elements are the same or if k is very small like = 1 and large arrays with diverse elements 

 Focus on the frequency instead of the distinct and then ensure that the logic equality checks the frequency of each element in the window .  Use the frequency map to validate the conditon and then add  pront statement to log the state of the window and the frequency map and the current ans at each step this will help you identify where the logic might deviate from the expected behavior
 Iterative refinement approach needs to be adhered to in that if you find a bug isolate the failing case and refine your logic step by step and focus on the understanding of the why the bug occurs rather than just fixing it 

 