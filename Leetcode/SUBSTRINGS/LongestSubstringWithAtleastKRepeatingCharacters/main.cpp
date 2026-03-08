/*
Longest Substring with Atleast K repeating Characters
Given a string s and an Integer K return the length of the longest substring
of s such that the frequency of each character in this substring is greater
than or equal to k  if no such substring exists , return 0 .
*/
#include <iostream>
#include <vector>
#include <unordered_map>

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
                if(map[s[end]]==0) unique++;  // incrementing the unique. 
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

    int longestSubstring(string s, int k) {
        unordered_map<char, pair<int, pair<int, int>>> u;
        for(int i=0;i<s.size();i++) {
            if(u.count(s[i])) {
                u[s[i]].first += 1;    // character count
                u[s[i]].second.second = i;  // last seen
            } else {
                u[s[i]] = {1, {i, i}}; // so the first int of the pair is incremented when the element is first found
            }
        }
        int ans = 0;
        for(int unique=1;unique<=u.size();unique++) {   // finds the valid substring for that target unique
            int start = 0, end = 0, curr = 0;
            unordered_map<char,int> w;
            while(end < s.size()) {
                w[s[end]] += 1;
                while(w.size() > unique && start < end) {  //sliding window is to check for the longest string for that target
                    w[s[start]] -= 1;
                    if(w[s[start]] == 0) w.erase(s[start]);  //shrink the non targetter character out
                    start++;
                }
                int kCount = 0;
                for(auto z: w) {
                    if(z.second >= k) kCount += 1;
                }
                if(kCount == unique)
                    ans = max(ans, end - start + 1);
                end++;
            }
        }
        return ans;
    }
};

int main (){

    Solution sol;
    sol.lenghtOfLongestSubstring("aaabb",3);

    return 0;
}