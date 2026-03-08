Dynamic programing is a problem solving technique where you :
1. Break a big problem into smaller problem 
2. store the results of the subproblems so you dont recalculate them 
3. Then you can build up to the final answer using stored results

vector<vector<int>> dp(n, vector<int>(n, 0));

This creates an nxn table representing all the possible substrings:
    .. Row i , Column j = dp[i][j] = answer for substring from index i to j 

Visual for substring "bbbab" (n=5):
      j=0  j=1  j=2  j=3  j=4
i=0   1    2    3    3    4     ← dp[0][4] is our answer!
i=1        1    2    2    3
i=2             1    1    3
i=3                  1    1
i=4                       1

Each cell stores the length of the longest palindromic subsequence in the s[i..j]

Why dp[0][n-1]?

Index 0 = start of the string 
Index n-1 = end of the string
dp[0][n-1] = longest palindrome in the entire string

The building strategy 
You fill the table bottom-up starting with small subproblems 
    1. Single characters (base case) dp[i][i]=1
    2. Length 2: dp[i][i+1] uses the length-1 results
    3. Length 3: dp[i][i+2] uses length-2 results
    4  ... and so on until 
    5. Length n: dp[0][n-1] uses all smaller results


    By the time you reach dp[0][n-1], you have already solved all the smaller problems needed !

    Real Example :"bbbab"

    . dp[0][0]=1 --> "b" is palindrome of length 1
    . dp[0][1]=2 --> "bb" is palindrome of length 2
    . dp[0][2]=3 --> "bbb" is a palindrome of length 3
    . dp[0][3]=3 --> "bbba" longest is still 3 ( cant use 'a')
    . dp[0][4]=4 --> "bbbab"-->"bbbb" (skip 'a')

Why not recalculate? because dp[0][4]  uses the dp[1][3] which you already calculated and the DP table stores the answers for all the substring ranges return the dp[0][n-1] the answe

