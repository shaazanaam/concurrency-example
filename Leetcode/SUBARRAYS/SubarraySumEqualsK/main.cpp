#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
      public:
      int subarraySum(vector<int> nums, int k){
            int counter = 0; // to check whether the sub array is valid which is the sum ==k
           
            int sum =0;
            

            //intiialize the hash map here 
            unordered_map<int, int> prefixSumCount ;
            // Initialize the Hash map which is the prefixSumCount[0] to 1
            // this accounts for the subarrays that start from the index 0
            prefixSumCount[0]=1;
            for(int i : nums){
                  sum +=i;
                  
                  // check if the prefixSun exists then you would be advancing the counter by the same amount as the prefixSumCount
                  if (prefixSumCount[sum-k]>=1) counter+= prefixSumCount[sum-k];
                  prefixSumCount[sum]++;
                  
            }
            return counter;
          
      }

      int sumArraySumBruteForce(vector<int> nums , int k){
            int count = 0;
            for(int i =0 ; i <nums.size(); i++){
                  int sum = 0;
                  for(int j=i ; j<nums.size(); j++){
                        sum +=nums[j];
                        if(sum==k) count++;
                  }
            }return count;
      }
};