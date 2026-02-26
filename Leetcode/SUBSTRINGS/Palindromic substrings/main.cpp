#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        int countSubstrings(string s){
            string Palindrome;
            int count =0;
            for (size_t i = 0 ; i< s.size(); i++){
                int L =i , R=i;
                while (L>=0 && R< (int)s.size() && s[L]==s[R]){
                    count++;
                    L--;
                    R++;
                }
                L=i, R=i+1;
                while (L>=0 && R<(int)s.size() && s[L]== s[R]){
                    count++;
                    L--;
                    R++;
                }
            }return count;
        }

    int countSubstrings2(string s) {
        

       int n = s.size();
       vector<vector<bool>> dp(s.size()+1 , vector<bool>(n , 0));
       int count = n;
       // marking all the one characters and the two characters as the palindrome in the dp string
       for(int i = 0; i<s.size(); i++){
          dp[i][i] = 1;
          if(s[i]==s[i+1]) {
            dp[i][i+1] =true;
            count++;
          }
       }

        
        for(int len = 3; len<=s.size(); len++){


            for(int i = 0; i<=n-len; i++){
                int j = len+i-1;

                if(dp[i+1][j-1] && s[i]==s[j]){
                    count++;
                    dp[i][j]= true;
                }
                else {
                    dp[i][j]= false;
                }
            }
        }


        return count;



    }
};

int main(){
    Solution solver;
    cout<<solver.countSubstrings("abc");
    cout<<solver.countSubstrings("aaa");
}