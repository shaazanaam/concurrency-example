
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class Solution
{
public:
    string minWindowNaive(string s, string t)
    {

        unordered_map<char, int> T;
        unordered_map<char, int> S;
        // built the frequency table for the string t
        for (char target : t)
        {
            T[target]++;
        }

        // run the sliding window on the given string with the two pointers

        int left, right =0, start = 0, minLen = s.size()+1,matchedCount=0;
        
        while(right<s.size()){
            S[s[right]]++;
            
            if(T.count(s[right])&&S[s[right]]==T[s[right]]){
                matchedCount++;   
            }
            while(matchedCount==T.size()){
                if(right-left+1<minLen){
                    start = left;
                    minLen= right-left+1;
                }
                if(T.count(s[left])&&S[s[left]]==T[s[left]]){
                    matchedCount--;
                }
                S[s[left]]--;
                left++;
            }
            right++;
            
                
                
        }
        if(minLen>s.size()) return"";
        return s.substr(start,minLen);
   
    }

    string minWindow(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }  
        }
        return d==INT_MAX? "":s.substr(head, d);
    }
};