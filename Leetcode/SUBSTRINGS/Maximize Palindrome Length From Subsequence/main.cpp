#include <iostream>
#include<vector>
using namespace std;
class Solution{
    public:
        int longestPalindrome(string word1, string word2){
            int ans =0;
            int n = word1.size();
            string combined = word1+word2;
            int t = combined.size();
            vector<vector<int>> dp(t, vector<int>(t,0));
            for(int i = 0 ; i< t;i++){
                dp[i][i]=1;// single char is the palindrome length 1

            }
            for(int len = 2 ; len <=t ; len++){
                for(int i = 0; i <=t-len;i++){
                    int j = len+i-1;
                    if( combined[i]==combined[j] )
                        {
                          dp[i][j] = dp[i+1][j-1]+2;      
                        }
                    else {
                        dp[i][j]= max(dp[i+1][j],dp[i][j-1]);
                    }
                    if(i<n && j>=n && combined[i]==combined[j]){
                       ans =max(ans,dp[i][j]); 
                    }
                }
            }
            return ans;
            
        }

        int longestPalindrome2(std::string word1, std::string word2) {
        int len1 = word1.length();
        int len2 = word2.length();
        int n = len1 + len2;
        
        char s[2005];
        for(int i = 0; i < len1; ++i) s[i] = word1[i];
        for(int i = 0; i < len2; ++i) s[len1 + i] = word2[i];
        
        int dp[2005] = {0};
        int max_pal = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = 1;
            int prev = 0;
            for (int j = i + 1; j < n; ++j) {
                int temp = dp[j];
                if (s[i] == s[j]) {
                    dp[j] = prev + 2;
                    if (i < len1 && j >= len1) {
                        if (dp[j] > max_pal) {
                            max_pal = dp[j];
                        }
                    }
                } else {
                    if (dp[j - 1] > dp[j]) {
                        dp[j] = dp[j - 1];
                    }
                }
                prev = temp;
            }
        }
        
        return max_pal;
    }
};