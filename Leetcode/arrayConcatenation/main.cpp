#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
      vector<int> getConcatenation(vector<int>& nums) {
        vector<int> v(2*nums.size());

        for (int i = 0; i<nums.size();i++){
            v.at(i)=nums[i];
            v.at(i+nums.size())=nums.at(i);
        }
        return v;

    }
};