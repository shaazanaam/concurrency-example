## 647.. Palindromic Substrings  
Giving a string s return  the number of palindromic substrings in it and a string is a palindrome  when its reads the same backward as forward. A substring is a contiguous sequence of characters withing the string

Example 1:

Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:

Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

 Hint 1: 
 How can we reuse a previously computed palindrome to compute a larger palindrome ?
 Hint 2: If abab is a palindrome , is xabax a palindrome?
 Similarly is xabay a palindrome?
 Complexity based hint: If we use the brute force and  check whether for every start and end positon a substring is a palindrome we have O(n^2) start -end pairs and O(n). can we reduce the time for the palindromic checks to O(1) by reusing some previous computation?

 For each substring of lenght len starting at the index i and ending at index j = i +len-1
    If you check if the the substring s[i..j] is a palindrome by verifying two conditons :
        1. The substring inside the (s[i+1..j-1]) is already known to be a palindrome (dp[i+1][j-1] is true).
        2. The characters at the ends match (s[i]==s[j])

        If both are true it marks the dp[i][j] as true ( meaning s[i..j] is a palndrome and increments the count ) other wise you would be marking the dp[i][j] as false 
        In summary this code will be filing out a DP table to find and count all the palindromic substrings of length 3 or more in the string 


The vector dp is a 2D dynamic programming table used to track whether the substrings of s are palindromes 
dp is a matrix of size (n+1)xn where n is the length of the string s.
Each entry dp[i][j] is a boolean 
true means the substring from index i to j (inclusive) is a palindrome and false means it is not 

All the values are set to  false(0) initiallu . this loop sets dp[i][i] = true for all the i (single characters are palindromes )
If two consecutive charaters are equal(s[i]==s[i+1]), then the dp[i][i+1] == true ( two character palindromes )

for the s= "aba";
n=3 
dp has 4 rows and 3 colums ( indices 0..3 for the rows and 0..2 for the columns)
dp[0][0], dp[1][1], dp[2][2] are set to true ( single characters)
dp[0][1], dp[1][2] are checked for the two character palindromes and in ssummary : dp is a 2D boolean matrix marking which substrings of s are palindromes used for dynamix programing

if i and j represent the start and the end  indices of the  substrings s[i,j] then the dp[i+1][j+1] refers to the substrings s[i+1..j-1]  This is the substring inside the s[i..j] excluding the first and the last characters for  example 
if s= "racecar", i = 0, j=6 then s[i,j] ="racecar" and s[i+1..j-1] = "aceca   So the dp[i+1][j-1] checks if the inner substring is the palindrome and if it is and also s[i]==s[j] then s[i..j] is also a palindrome 