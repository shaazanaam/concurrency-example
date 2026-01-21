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

Let's assume that there is some contiguous subarray A[i:j] which sum is equal to k: sum(A[i:j]) == k

If sum(A[i:j]) == k, then we can rewrite previous equality in the following ways:

sum(A[:j]) = sum(A[:i]) + k 
sum(A[:j]) - k = sum(A[:i])
Therefore, if we already saw value of sum(A[:j]) - k as a cumulative sum sum(A[:i]) for some previous i (which we can check by looking at the hash table), then it means that sum of the subarrary A[i:j] is equal to k and we can increment the counter.
