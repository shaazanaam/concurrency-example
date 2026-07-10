#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
class Solution {
    public :
       int  LengthOfLongestSubstring2(string s, int k ){
        vector <int> map(128,0);
        int begin{}, end{}, altleastKcount{}, unique{}, ans{};
        for (int i = 1; i<=26;i++){
            begin=end=altleastKcount=unique=0; // equality if left to right associative 
            map.assign(128,0);
            // we are resetting these because each iteration of i is a fresh search for the substrings with exactly 
            //i unique characters .
            while(end<s.size()){
                if (map[s[end]]==0) unique++;
                map[s[end]]++;
                if (map[s[end]]==k) altleastKcount++;
                end++;
                while(unique>i){
                    //If left character count is exactly k before decrement, it will become k-1, so atLeastKcount must decrease.
                    if(map[s[begin]]==k) altleastKcount--;
                    map[s[begin]]--;
                    
                    //If left character count becomes 0 after decrement, unique must decrease.
                    if(map[s[begin]]==0) unique--;
                    begin++;

                }
                if(unique==i && altleastKcount==i){
                    ans = max(ans,end-begin);
                }
            }

        } return ans;


    }
};