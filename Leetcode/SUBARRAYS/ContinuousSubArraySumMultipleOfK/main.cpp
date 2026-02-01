#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
      public :
            bool checkSubarraySum(vector<int>& nums , int k){
                  int counter =0, sum=0, n=0;
                  unordered_map<int,int> remainder;
                  remainder[0]=-1;
                  
                  for(int i :nums){
                        sum += i;
                        int rem = k==0 ? sum:sum%k; // handle the k=0 edge case 
                        if(remainder.count(rem)){
                              // if  you see the same remainder again and the subarray is at least length 2 you found a valid subarray
                              // check if the subarray length is atleast 2
                              if (n- remainder[rem]>=2) return true;
                        } else {
                              //store the first index where this remainder occurs
                              // this is where we are tracking the first index where each remainder occurs
                              // map keeps the earliest index because the second time the remainder occurs it gets processed by the if block
                              
                              remainder[rem]=n;
                        }
                        
                        n++;
                        
                  

                        
                  } return false;
            }
};

int main(){
      
      Solution sol;
      vector nums {23,2,4,6,7};
      sol.checkSubarraySum(nums,6);
      return 0;
}