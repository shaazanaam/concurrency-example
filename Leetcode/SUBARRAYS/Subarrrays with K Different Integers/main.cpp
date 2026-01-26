#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution{
      public:
      long long subarrayWithDistinct(vector<int>& nums , int k){
            unordered_map<long, long> uniqueIntegersCounts1;
            unordered_map<long, long> uniqueIntegersCounts2;

            // find the number of sub arrays that have at most K distinct
            
            int L1=0;
            int L2=0;
            int distinct1 =0;
            int distinct2 =0;
            long long atMost1 =0;
            long long atMost2 =0;
            if (k<=0) return 0;
            int k2 = k-1;
            for(int R=0;R<nums.size();R++){
                  if(uniqueIntegersCounts1[nums[R]]==0){        // this step first checks if there is no count then only add the distinct otherwise dont add distinct
                        distinct1++;                             // you never do distinct++ after the increment unless you test became 1 
                  }
                  if(uniqueIntegersCounts2[nums[R]]==0){
                        distinct2++;
                  }
                  uniqueIntegersCounts1[nums[R]]++;
                  uniqueIntegersCounts2[nums[R]]++;
                  
                 while(distinct1>k){
                     uniqueIntegersCounts1[nums[L1]]--;
                      
                      if(uniqueIntegersCounts1[nums[L1]]==0){
                        distinct1-- ;
                      }
                      L1++;
                      
                  }
                  atMost1 +=(R-L1+1);   // at each R once you have shrunk until distint<=k , you can count how many valid subarrays end at this R

                 while(distinct2>k2){
                     uniqueIntegersCounts2[nums[L2]]--;
                      
                      if(uniqueIntegersCounts2[nums[L2]]==0){
                        distinct2-- ;
                      }
                      L2++;
                      
                  } 
                  atMost2 +=(R-L2+1);
            }
            return atMost1-atMost2;
            // there is also an equivalent form which you are doing when we  can use the add L2 -L1
      }
};

int main(){
      vector<int> nums = {1, 2, 1, 2, 3}; // Example vector
      int k = 2; // Example value for k
      Solution sol;
      int result = sol.subarrayWithDistinct(nums, k);
      cout << "Result: " << result << endl;
      return 0;
}



