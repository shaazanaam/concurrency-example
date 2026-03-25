## 2565 Subsequence with the minimum Score

You are given two strings s and t.

You are allowed to remove any number of characters from the string t.

The score of the string is 0 if no characters are removed from the string t, otherwise:

Let left be the minimum index among all removed characters.
Let right be the maximum index among all removed characters.
Then the score of the string is right - left + 1.

Return the minimum possible score to make t a subsequence of s.

A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

 

Example 1:

Input: s = "abacaba", t = "bzaa"
Output: 1
Explanation: In this example, we remove the character "z" at index 1 (0-indexed).
The string t becomes "baa" which is a subsequence of the string "abacaba" and the score is 1 - 1 + 1 = 1.
It can be proven that 1 is the minimum score that we can achieve.
Example 2:

Input: s = "cde", t = "xyz"
Output: 3
Explanation: In this example, we remove characters "x", "y" and "z" at indices 0, 1, and 2 (0-indexed).
The string t becomes "" which is a subsequence of the string "cde" and the score is 2 - 0 + 1 = 3.
It can be proven that 3 is the minimum score that we can achieve.
 

Constraints:

1 <= s.length, t.length <= 105
s and t consist of only lowercase English letters.


Can we use the patterns studied in the previous solutions where we are checking for the longest palindromic subsequence and then also the problem where we were given two strings and the  other string was a pattern with two characters where we could have used the pattern[0] or pattern[1]  and we could have used it either in the front or the back and then maximise the length of the subsequence .
we can get either using the pattern[0] or the patttern[1] in the front or the back of the subsequence.

But for this problem minimum score to make t a subsequence of s full LCS style DP is usually too expensive

Standard DP is O(s x t) which is too slow for large constrains 
Interval DP on t is also generally too heavy.


The basic idea to solve this problem is to know hou much of t I can match from the left and how much of t I can match from the right and combine the left and right matches and then remove the one middle substring of t with the minumum length . remember that the start and the stop of the substring remvoed is what the formula is telling us which is the right- left +1


In this case you would be needing to Build a pref array and the the pref[i] = earliest index in s after mactching t[0...i]

Build the suff arry :
suff[i] = latest index in s before matching t[i...m-1] from the right 

Then try splitting the t  in the following manner by keeping the prefix [0..i] and keeping the suffix t [j...m-1], remvoing the t[i+1..j-1]

Valid split condition is that th prefix match in s  ends before suffix match start 
Minimize remvoed length j-i-1

This is essentially the prefix suffix matching + two pointers or binary search and runs in about (s+t) or O(t logt ) much better than full DP 

So short answer:

Yes, your two DP patterns are absolutely useful conceptually.
For this question, convert that thinking into prefix/suffix subsequence matching, not a full 2D DP table.
