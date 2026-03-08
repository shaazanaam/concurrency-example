## Problem number 516 Palindromic Subsequence

Given a string s , find the longest palindromic subsequence's length in s 
A subsequence is a sequence  that can be derived from  another sequence by deleting some or no elements without changing the order of the remaining elements

Example 1:

Input: s = "bbbab"
Output: 4
Explanation: One possible longest palindromic subsequence is "bbbb".
Example 2:

Input: s = "cbbd"
Output: 2
Explanation: One possible longest palindromic subsequence is "bb".

 The main difference between the substring and the subsequence is that  the substring must be adjacent and you cannot skip characters and in the "abcde" subsequence include "ace", "ad", "bce", "abde"
  You skip characters but keep them in order for the subsequence and in the longest palindromic substring you find the longest contigious palindrome like the racecar  in a string and then the longest Palindromic Subsequence you find the longest palindromic using the characters in  order but not necessarily adjacent like finding the "a_c_a" in the "aXcXa" This makes the subsequence problems typically easier since you have more flexibility you can skip characters and think of it as selecting the characters from the string while maintaining their orders versus the substring problem which requires an unbroken run of characters
  

  O(N) isnt possible in the longest palindromic subsequence case and that problem is inherently O(N^2) becasue you need to compare the character pair across the string and . However O(N) is possible for the longest palindromic substring using  the Manacher algorithm which is an optimized version of the expand from the center and achieves O(N).

  Basic version of the expand from the center 
    ## For each character expand outward checking matches 
     It is O(N^2)

     MANACHER ALGO 
     Stil expands fromt he center but uses a mirror property and skips the redundant checks by remembering previously found palindromes. More complex but much faster . if you want the O(N) then expand from the center style you need the Manachers algorithm

for(int len =2; len<=n; len++){
            for(int i = 0; i<=n-len;i++){ // i is the starting position 
                int  j = len+i-1;    // end  position
                if(s[i]==s[j]){
                  dp[i][j] = dp[i+1][j-1]+2;  
                }else{
                    dp[i][j] = max(dp[i+1][j],dp[i])
                }
            }
          }



This nested loop processes all possible substrings by length building up the DP table 
Outer loop ( len =2 to n ) iterates through substring lengths
Inner loop (i=0 to n-len) iterates through the starting positions 
The line j= len+i-1 calculates the ending position of the substring 
Start at position i 
Length is len 
End position = i+len -1

Example with the string "babad"
.. len = 2, i=0: j=2+0-1=1 --> substring s[0..1]="ba"
.. len = 2, i=1: j=2+1-1=2 --> substring s[1..2]="ab"
.. len = 3, i=0: j=3+0-1=2 --> substring s[0..2]="bab"
.. len = 5, i=0: j=5+0-1=4 --> substring s[0..4]="babad"

This way you process shorter substrings first and then use those results to solve the longer substrings which is the classic bottom -up DO 

This line handles the case when the characters at positions i and j match.

dp[i][j] = longest palindromic subsequence in substring s[i..j]

When s[i] == s[j]:

The outer characters match, so we can extend the palindrome
Take the longest palindrome from the inner substring (s[i+1..j-1])
Add +2 for the matching characters on both ends
Example with "aba":

i=0 (a), j=2 (a) → they match
Inner substring is s[1..1] = "b" → dp[1][1] = 1
Result: dp[0][2] = dp[1][1] + 2 = 1 + 2 = 3 ✓ (gives "aba")
Another example with "racecar":

When we reach i=0 (r), j=6 (r) → they match
Inner part s[1..5] = "aceca" → suppose dp[1][5] = 5
Result: dp[0][6] = 5 + 2 = 7 ✓ (gives "racecar")
The logic is: matching outer characters + longest palindrome inside = longer palindrome.

dp[i][j] = dp[i+1][j-1]+2;

This line handles the case when the characters at the positons i and j match 
 dp[i][j] = longest palindromic subsequence in the substring s[i..j]  
 when the s[i]==s[j]:
The outer characters match so we can extend the  palindrom and take the longest palindrome from the inner substring (
  s[i+1..j+1]
)


dp[i][j] is the length of the longest palindromic subsequence in the substring s[i..j] This line handles when the s[i]!= s[j] ( characters dont match ) and in this case there are only two situations :
Either the  longest paplindrome excludes the left character dp[i+1][j]
Or the longest palindrome excludes the right character dp[i][j-1] Take the maximum of both options

The dp logic ensures implicitly and gurantees its a palindrom through its logic and we are not checking if its palindromic we are building palindroms 

Base case 
dp[i][i] = 1 --> single characters are palindromes
When the s[i] == s[j]:
dp[i][j] = dp[i+1][j-1] +2

if dp[i+1][j-1] is already a palindrom ( which it is by earlier iterations) adding matching characters on both the sides keep it palindrome

When the s[i]!=s[j] : 
In that case dp[i][j] = max(dp[i+1][j], dp[i][j-1]) ..
If the outer characters dont match we exclude one end and keep only the palidnromic part from what remains 
Example in "ab" neither option with both chars is palindromic so we pick the the  longest sindle palindrome 

The recurrence relation itself prevents non palindromes from ever appearing on the DP table and we only build larger palindromes by extending existing palindromes with the matching characters OR
Keeping only parts that are already palindroms
Dynamic programing is a problem solving technique where you break a big problem into smaller subproblems and store the results of the subproblems so you dont recalcuate them build up to the final answer stored results

We are using the vector<vector<int>> dp(n, vector<int>(n,0));
this creates an nx n table representing all possible substrings and the row i and the column j = dp[i][j] = answer for substring from the index i to j 
 Visual for the string "bbbab" (n=5)  


