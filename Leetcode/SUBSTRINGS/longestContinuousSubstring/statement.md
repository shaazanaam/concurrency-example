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

## In the case of the vector that we are forming 
     Here is the notes for the same and casting a character to an unsigned char ensures that its value is always in the range of 0-255 which matches the size of the vector (256 elements). This is important because 
         The vector is used as  a frequency /count array for all the possible byte values 
         If you use a plain char which can be negative on some systems indexing the vector with a negative value will cause undefined behaviour or access the wrong index 
          By  casting to the unsigned char every character ( including those with the negative values in the signed char) maps to a valid index in the vector)

          Remember that in c++ the plain char can either be signed or unsigned depending on the compiler and the platform and if the char is signed it can be represented with the values from the -128 to the 127 . this means some characters (especially those with the ASCII codes above the 127) may be interpreted as negative values 
          Casting to the unsigned char ensures that all the character values are in the range 0-255 which is safe for the indexing arrays of the size 256.

## What does the vector last seen mean in this case conceptually
Yes in many substring or sliding window problems , a vector named last (often of the size 256 for all the possible characters) is used to record the last seen index of  each character in the string 

    .. Last seen means  the most recent position index where a particular character appeared as you iterate  through the string . The context is usually  useful when you wanna do the following 
        1. You wanna know if a character has appeared  before and if so where
        2. This helps in problems like the longest substring without the repeating characters and where you need to adjust the window start position to avoid duplicates 

    For example if you see character A at the index 5 you set last['A']= 5 and then if you see 'A'again at the index 8 last['A'] tells you its previous position so that you can update your window accordingly.

    When the value of the character at the S[R] gets evaluated then the vector last[...] uses this value as an index into the vector retrieving the last seen index for that character.

    the value store in the vector last[ascii value] is the last position (index in s) where that character was seen as you iterate through s 

    If the prev ( the last seen index of the current character ) is greater than or equal to the left window index(L) it means that this character was already seen inside the current  window . to maintain a substring with all the unique characters you need to move the left pointer (L) to one past the prev as you need to skip past the previous occurence of that character and this ensures that the window always contain only unique characters