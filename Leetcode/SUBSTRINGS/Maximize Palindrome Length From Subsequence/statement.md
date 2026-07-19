1771 Maximize Palindrome Length from Subsequence


You are given two strings, word1 and word2. You want to construct a string in the following manner:

Choose some non-empty subsequence subsequence1 from word1.
Choose some non-empty subsequence subsequence2 from word2.
Concatenate the subsequences: subsequence1 + subsequence2, to make the string.
Return the length of the longest palindrome that can be constructed in the described manner. If no palindromes can be constructed, return 0.

A subsequence of a string s is a string that can be made by deleting some (possibly none) characters from s without changing the order of the remaining characters.

A palindrome is a string that reads the same forward as well as backward.

 Example 1:

Input: word1 = "cacb", word2 = "cbba"
Output: 5
Explanation: Choose "ab" from word1 and "cba" from word2 to make "abcba", which is a palindrome.
Example 2:

Input: word1 = "ab", word2 = "ab"
Output: 3
Explanation: Choose "ab" from word1 and "a" from word2 to make "aba", which is a palindrome.
Example 3:

Input: word1 = "aa", word2 = "bb"
Output: 0
Explanation: You cannot construct a palindrome from the described method, so return 0.
 

Constraints:

1 <= word1.length, word2.length <= 1000
word1 and word2 consist of lowercase English letters.


## PROCESS

Exactly. The statement means this:

1. Pick any non-empty subsequence from word1.
2. Pick any non-empty subsequence from word2.
3. Join them in this order: from word1 first, then from word2.
4. The joined string must be a palindrome.
5. Among all valid choices, return the maximum length.

Important detail:
- You are not choosing a subsequence from a subsequence.
- You choose directly from word1 and directly from word2.
- Both picks must be non-empty, so the palindrome must use at least one char from each word.

Tiny example:
- word1 = ab, word2 = ab
- pick ab from word1, pick a from word2
- joined string = aba, which is palindrome, length 3

Why this is tricky:
- You cannot try all subsequences because each word has too many possibilities.
- Real solution uses dynamic programming to find longest palindrome while forcing it to cross the boundary between word1 and word2.

If you want, next I can explain that DP idea in the same simple style, step by step without code.



## SO how do we create the subsequnece and then add the two 

A subsequence is made by picking letters in order with the skips allowed and for example from word1 = cacb:

. pick position 1 and 3 gives ab
. pick positions 0,2,3 gives cab
. pick position 2 only gives c

From word2 = cbba:
. pick positions 0,2,3 gives cba
. pick positions 1,2 gives bb

Then add them by concetenation 
. subsequence1+ subsequence2
. example ab+cba = abcba

This is exactly what the problem means

## How to think while building one subsequence 
1. Start with empty string.
2. Go left to right through the word
3. For each character either take it or skip it 
4. Taken chars( in the same order ) form one subsequence

Important for this problem:

1. Both subsequences must be non-empty
2. first part must come from word 1
3. second part must come from word 2
4. joined result should be a palindrome

One warning 

Generating all the subsequence from both words and checking all the pairs is only for understanding and not efficient for length up to 1000 for the real solution use the DP.

# what is the dp?
1. State dp[i][j] = length of the longest  palindromic subsequence in the combined[i..j] , where combined = word1 + word2
# valid answer condition os the condition where you update the answer  when both  the subsequence are used 
if(i<n ** j>=n && combined[i]==combined[j])..

this guarantee comes from the two facts working together 
1. Boundary split condition 
i<n means that the index i is inside the word1. j>=n means that the index j is inside the word 2 . so the two ends of the candidate palindrome are taken from different words

2. End point match condition 
COmbined[i] = combined[j] is required befre updating the ans . when this is true then the DP transition used is the dp[i][j] = dp[i+1][j-1] +2  that +2 explicitly includes both the endpoints i and j in the palindrome length 
Because i is from the word 1 and j is from the word2, those +2 characters force the palindrome to use at least one character from each word
the outside boundary is not infered from the len and it is enforced  by the condition j>=n



## Second Approach 
In the second approach the outer loop is there  because this is a space optimized dynamic programming sokution and each state depends on the values from the next row.

 In the full 2 D version the recurrence is basically using the information from the substrings that start later in the string . So when the code processes the i from n-1 down to 0 , it guarantees that all the subproblems for a later start index are already available

 Inside the 1 D version the dependencies are ..
      1. dp[j] before the overwrite represents the values from the previous outer iteration meaning the subproblem for the i+1
      2. dp[j-1] represents the current rows left neighbor.
      3. prev stores the old diagonal values which is the old dp[j-1] from the previous row

# the code is using a 1D DP array instead of a 2D table .
That means that the dp[j] initially represents the old value from the next row meaning dp[i+1][j]
After updating the dp[j] becomes the current row value dp