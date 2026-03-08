#include <iostream>
#include<vector>
using namespace std;

class Solution{
    public:
        int longestPalindromeSubseq(string s){
          int n= s.size();
          vector<vector<int>> dp(s.size()+1, vector<int>(n,0));
          // marking all the one characters and the two characetes as palindromes
          for (int i= 0 ; i <s.size(); i++ ){
            dp[i][i]=1;        
            }
          for(int len =2; len<=n; len++){
            for(int i = 0; i<=n-len;i++){ // i is the starting position 
                int  j = len+i-1;         // end  position
                if(s[i]==s[j]){
                  dp[i][j] = dp[i+1][j-1]+2;  // taking the longest palindrome from the inner substring and adding +2 
                }else{
                    dp[i][j] = max(dp[i+1][j],dp[i][j-1]);
                }
            }
          }
          return dp[0][n-1];
        }

        
};

int main() {
    Solution sol;
    
    // Test cases
    cout << "Test 1: \"bbbab\"" << endl;
    cout << "Expected: 4 (bbbb)" << endl;
    cout << "Result: " << sol.longestPalindromeSubseq("bbbab") << endl << endl;
    
    cout << "Test 2: \"cbbd\"" << endl;
    cout << "Expected: 2 (bb)" << endl;
    cout << "Result: " << sol.longestPalindromeSubseq("cbbd") << endl << endl;
    
    cout << "Test 3: \"racecar\"" << endl;
    cout << "Expected: 7 (racecar)" << endl;
    cout << "Result: " << sol.longestPalindromeSubseq("racecar") << endl << endl;
    
    cout << "Test 4: \"a\"" << endl;
    cout << "Expected: 1" << endl;
    cout << "Result: " << sol.longestPalindromeSubseq("a") << endl << endl;
    
    cout << "Test 5: \"abcda\"" << endl;
    cout << "Expected: 3 (aca)" << endl;
    cout << "Result: " << sol.longestPalindromeSubseq("abcda") << endl << endl;
    
    return 0;
}

int main
