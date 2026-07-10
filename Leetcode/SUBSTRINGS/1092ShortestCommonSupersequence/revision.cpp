#include <iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;
class Solution{
    //building a dp table 
    string shortestCommonSupersequence2(string str1, string str2){
        int n= str1.size(), m = str2.size();
        vector<vector<int>>dp(n+1,vector<int>(m+1,0));
        //index 0 means empty prefix so the row 0 = first string prefix length 0 ( empty)
        //column 0 = second string prefix length 0(empty)
        // this lets the base case of the dp table to be  built naturally
        // ..LCS(empty, anything)= 0
        //..LCS(anything,empty) = 0
        //start the loop at 1 instead of the 0 as the row0
        //column 0 are base cases already fixed at 0 and then the DP cell(i,j) 
        // means the LCS of the first i characters of a and the first j characters of b
        for (int i = 1; i<=n;i++){
            for(int j = 1; j<=m;j++){
                if(str1[i-1]==str2[j-1]){
                    dp[i][j] = 1+dp[i-1][j-1];
                    // if the characters are common then add it once and move the diagonal
                }else{
                    dp[i][j]= max(dp[i-1][j],dp[i][j-1]);
                    // compare the top and the left DP values
                }
             
            }
        }
        // reconstruct the SCS by walking backwares
        int i = n, j= m;
        string ans;
        while(i>0 && j>0){
            if(str1[i-1]==str2[j-1]){
                ans.push_back(str1[i-1]);
                i--;j--;
            }else if (dp[i-1][j]>=dp[i][j-1]){
                //use the dp numbers to chose which actual characters to place 
                // why compare the dp[i-1][j] and dp[i][j-1] this 
                //tell you which side keeps a larger common overlap for the remaining prefixes
                //larger overlap means fewer total extra chars laterm so better for
                //shortes supersequence
                //So:
                    //if the top is bigger /equal move up and append str1[i-1]
                    //else move left and append str2[j-1]
                ans.push_back(str1[i-1]);
                i--;
            }else{
                ans.push_back(str2[j-1]);
            }
        }

        //append the leftovers
        while(i>0){
            ans.push_back(str1[i-1]);
            i--;
        }
        while(j>0){
            ans.push_back(str2[j-1]);
            j--;
        }
        reverse(ans.begin(), ans.end());
        return ans;

    
    }

};