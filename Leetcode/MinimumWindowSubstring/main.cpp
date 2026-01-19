
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

        int left = 0;
        int right = 0;
        int start =0;
        int minLen=s.size()+1;
        S.clear();
        while (right < s.size())
        {

            // check the validity of the window and then increas the window
            // validity of the window is that you have to check if all the characters in the  T are in the s atleast with the required frequency
            //  creating the window here and then going  in to check the validity for all the characters in the

            S[s[right]]++;
            bool isValid =true;
            for (auto &pair : T)
            {
                if(S[pair.first]<pair.second) {
                    isValid = false;
                    break;
                }
            }
            // now you shrink when valid is true
            while(isValid){
                start = left;
                minLen = min(right-left+1,minLen);
                S[s[left]]--;
                left++;
                isValid=true;
                for(auto& pair :T){
                    if(S[pair.first]<pair.second){
                        isValid = false;
                        break;
                    }
                }
            }

            right++;
        }
        return s.substr(start, minLen);
    }

    string minWindowOptimized(string s , string t){
        unordered_map<char, int> T;
        unordered_map<char, int> S;
        // built the frequency table for the string t
        for (char target : t)
        {
            T[target]++;
        }

        // run the sliding window on the given string with the two pointers

        int left = 0;
        int right = 0;
         
        // variables needed to track the minimum window found
        int start =0, minLen=s.size()+1;
        //now expand the window 
        int matchedCount=0;
        while(right <s.size()){
            S[s[right]]++;
            
            //update the count to find if the required characters are fully matched with the tagret window
            if(T.count(s[right])&&S[s[right]]==T[s[right]]){
                matchedCount++;
            }
            while(matchedCount==T.size()){
                if(right-left+1 <minLen){
                    start = left;
                    minLen = right-left +1;
                }
                if(T.count(s[left]) && S[s[left]] == T[s[left]]){
                    matchedCount--;
                }
                S[s[left]]--;
                left++;
            }

            right++;
        }
        if(minLen>s.size()) return "";
        return s.substr(start, minLen);

    } 

    string minWindow1ms(string s , string t){
        vector<int> need(128,0);
        for (char c : t) need[(unsigned char)c]++;
        int required =(int)t.size(),bestLen =INT_MAX, bestL=0,l=0;
        for(int r =0; r<(int)s.size();r++) {
            unsigned char cr = s[r];
            if(need[cr]>0) --required;  // required = the total characters left and this says how many total characters are still missing
            --need[cr];
            while(required==0){
                if(r-l+1<bestLen){
                    bestLen = r-l+1;
                    bestL=l;
                }
                unsigned char cl =(unsigned char) s[l];
                ++need[cl];
                if(need[cl]>0) ++required;
                ++l;
            }
        }
        return bestLen==INT_MAX?"":s.substr(bestL,bestLen);  
    }

};


int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    Solution sol;
    string result = sol.minWindow1ms(s, t);
    cout << "Input: s = \"" << s << "\", t = \"" << t << "\"" << endl;
    cout << "Output: \"" << result << "\"" << endl;
    cout << "Expected: \"BANC\"" << endl;
    return 0;
}