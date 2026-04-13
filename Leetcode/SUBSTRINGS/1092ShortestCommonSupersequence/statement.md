1092. Shortest Common Supersequence

Given two strings str1 and the str2 return the shortest string that has both the str1 and the str2 as the subsequences . If there are multiple valid strings then return any of them 

# A string s is a subsequence of the string t if deleting some number of the characters from the t ( possibly 0) results in the string s 
 

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

 Optimizing tool selection...In that hint, they mean the second thing: compute LCS on smaller suffixes for every pair of positions, not just once on full strings.

When they write:

- `str1[i:]` = substring of `str1` starting at index `i` to the end
- `str2[j:]` = substring of `str2` starting at index `j` to the end
- “for all `(i, j)`” = do this for every possible starting index pair

So you build a DP table where each cell answers:

- `dp[i][j] = LCS length of str1[i:] and str2[j:]`

Why this helps for shortest common supersequence:
- You don’t just need the final LCS length.
- You need “future information” at each step to decide:
1. if characters match, take it once and move both pointers
2. if not, decide whether to take from `str1` or `str2` based on which move preserves a longer LCS ahead

So yes: it is LCS, but computed over all suffix pairs `(i, j)`, not only full `str1` vs full `str2`. That full LCS is just one cell in that table (`dp[0][0]`).