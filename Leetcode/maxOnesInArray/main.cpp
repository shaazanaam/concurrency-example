#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
       
        int L=0;
        int longest = 0;

        for (size_t i = 0; i<nums.size(); i++){
            
            
            
            if (nums[i]==1){
                ++L;
                longest = max(longest, L);
            }else L=0;
            

        }
        return longest;

    
    }
};

int main(){
    vector<int> nums = {1,1,0,1,1,1};
    Solution solver;
    int  resultl = solver.findMaxConsecutiveOnes(nums);
    cout<<"Result1= "<<resultl;
}