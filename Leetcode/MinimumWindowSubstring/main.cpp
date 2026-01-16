#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        
        unordered_map<char, int> T;
        unordered_map<char, int> S;
        // built the frequency table for the string t
        for(char target: t){
            T[target]++;
        }
        //run the sliding window on the given string with the two pointers

        int left, right =0;
        S.clear();
        while(right-left+1<s.size()){
            
            

            if(T.count(s[right])){
                S[right]++;
                
            }
            right++;
            for (auto &pair: T){
                while(S[right]>pair.second){
                    left = right;
                    left++;
                    S[s[left]]--;
                }
                
                
            }
    
        }
    }
};