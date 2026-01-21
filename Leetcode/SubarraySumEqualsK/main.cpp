#include <vector>

using namespace std;

class Solution {
      public:
      int subarraySum(vector<int> nums, int k){
            int counter = 0, begin=0, end=0, sum=0, tempSum=0, minLen=INT_MAX;
            for(int i = 0; i<nums.size(); i++){
                  sum +=nums[i];

                  while (sum!=k){
                  minLen = min(minLen,i-begin+1); 
            }
            }
          
      }
};