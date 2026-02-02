/*
Longest Substring with Atleast K repeating Characters
Given a string s and an Integer K return the length of the longest substring
of s such that the frequency of each character in this substring is greater
than or equal to k  if no such substring exists , return 0 .
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution{
    public:
        int lenghtOfLongestSubstring(string s, int k){
        vector<int> map(128,0);
        int begin=0, end=0; 
        int atLeastKcount=0;
        int unique =0;
        int ans=0;

        for (int i =1 ; i <=26;i++){
            begin =0; end =0; atLeastKcount=0;map.assign(128,0);unique=0;
            while (end<s.size()){
                if(map[s[end]]==0) unique++;  // incrementing the unique
                map[s[end]]++;                 
                if(map[s[end]]==k) atLeastKcount++; // incrementing the atleastKCount
                end++;
                while(unique>i){
                    if(map[s[begin]]==k)atLeastKcount--; // decrementing the atLeastKCount when you know it was k before and then later on in the next line you would be decreasing the character's count it would be come k-1                                               
                    map[s[begin]]--;
                    if(map[s[begin]]==0)unique--;  // decrementing the unique becasue we are checking if the unique is greater than i which makes the window invalid and then we bring the unique count back to i
                    begin++;
                
                    
                }
                if(unique==i && atLeastKcount==i){
                    ans = max(ans,end-begin);
                }
                
            }
        } return ans;


    }
};

int main (){

    Solution sol;
    sol.lenghtOfLongestSubstring("aaabb",3);

    return 0;
}