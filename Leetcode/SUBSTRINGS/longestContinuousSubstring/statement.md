Given a string s, find the length of the longest substring without duplicate characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104



# GOAL 
    Find the  longest contigiuos substring with all the unique characters ; return its length.
# Complexity target 
    aim for O(n) time and O(min(n,alphabet)) extra space.
# key pattern
    sliding window ( two pointers: left , right)  that expands right and shrinks left when you see a duplicate
# Data structures
    use a hash map or array to record character occurences:
        # map of char -> last-seen index, or
        # set of characters currently in window (then remove as you move left)