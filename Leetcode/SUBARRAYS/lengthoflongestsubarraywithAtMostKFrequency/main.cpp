#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
    public:
        int lengthOfLongestSubarray(vector<int> nums, int k ){
            unordered_map<long,long> uniqueIntegersCount;
            int L=0,distinct=0,ans=0;
            for(int R=0; R<nums.size();R++){
                if(uniqueIntegersCount[nums[R]]==0) distinct++;

                uniqueIntegersCount[nums[R]]++;

                while(uniqueIntegersCount[nums[R]]>k){
                    uniqueIntegersCount[nums[L]]--;
                    if(uniqueIntegersCount[nums[L]]==0) distinct--;
                    L++;
                }
                ans = max(ans,R-L+1);
                
            }
            return ans;
        }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 2, 3, 1, 2, 3, 1, 2};
    int k1 = 2;
    cout << "Example 1: " << solution.lengthOfLongestSubarray(nums1, k1) << " (Expected: 6)" << endl;

    vector<int> nums2 = {1, 2, 1, 2, 1, 2, 1, 2};
    int k2 = 1;
    cout << "Example 2: " << solution.lengthOfLongestSubarray(nums2, k2) << " (Expected: 2)" << endl;

    vector<int> nums3 = {5, 5, 5, 5, 5, 5, 5};
    int k3 = 4;
    cout << "Example 3: " << solution.lengthOfLongestSubarray(nums3, k3) << " (Expected: 4)" << endl;

    return 0;
}