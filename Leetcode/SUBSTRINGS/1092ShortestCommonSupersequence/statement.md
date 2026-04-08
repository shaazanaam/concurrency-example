1092. Shortest Common Supersequence

Given two strings str1 and the str2 return the shortest string that has both the str1 and the str2 as the subsequences . If there are multiple valid strings then return any of them 
A string s is a subsequence of the string t if deleting some number of the characters from the t ( possibly 0) results in the string s 
 
Code
Testcase
Testcase
Test Result
1092. Shortest Common Supersequence 
Hard
Topics
premium lock icon
Companies
Hint
Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them.

A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.

 

Example 1:

Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
Example 2:

Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"
 

Constraints:

1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.

## Hint 1 
 We can  find the length of the longest common subsequence between the str1[i:] and the str2[j:] for all the (i,j) using the dynamic programins and then we can use this  information to recover the shortest common  supersequence.