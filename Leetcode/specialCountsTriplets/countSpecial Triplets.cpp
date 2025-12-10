#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution{
    public:
        int specialTriplets(vector<int> nums){

            unordered_map <int, int > freqPrev;
            unordered_map<int,int> freqNext;

            int i,j,k;

            for (size_t i =0; i<nums.size();++i){
                if(freqPrev.find(nums.at(i))!= freqPrev.end()){
                    ++freqPrev[nums.at(i)];
                    
                }

            }
            for( size_t i = 0; i<nums.size();++i){
                 cout <<nums.at(i)<<" in the Vector num is "<<freqPrev[nums.at(i)]<<" times\n";
            }
                return 0;
        }
};

int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    vector<int> nums(n);
    cout<<"Enter the elements: \n";
    for(int i = 0; i <n; ++i){
        cin>>nums[i];
    }

    Solution sol;

    sol.specialTriplets(nums);

    //Now nums contains the user input
    //.. use nums as needed ...
    

    return 0;
}