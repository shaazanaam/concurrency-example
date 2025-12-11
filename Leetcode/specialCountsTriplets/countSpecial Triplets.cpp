#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution{
    public:
        int specialTriplets(vector<int> nums){

            unordered_map <long, long > freqPrev;
            unordered_map<long,long> freqNext;         
            
            for ( int x: nums){
                freqNext[x]++;
            }


            long long ans = 0;

            // treat each index as the middle element

            for ( int j = 0; (int)nums.size();++j){
                long long x= nums[j];

                // Move the current elment from the rightr side to the current (so k>j only)

                freqNext[x]--;

                long long target = x*2;

                long long prevCount = freqPrev[target];   //hpow many nums[i] ==2*x for i<j
                long long nextCount = freqNext[target];  //how many nums[k] ==2*x for k>j

                ans = (ans+ (prevCount*nextCount));

                freqPrev[x]++;  

                //Now nums[j] becoems the  part of the left side for the future j's
            }

        
             return ans;
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

    cout<<"ans "<<sol.specialTriplets(nums);

    //Now nums contains the user input
    //.. use nums as needed ...
    

    return 0;
}