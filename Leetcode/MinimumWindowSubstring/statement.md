76. Minimum Window Substring
Given two strings s and t of lengths m and n respectively return the minimum window substring of s such that every character in t including duplicates is included in the window . 

Problem essence : 
You are given two strings , S the source and T the target . The goal is to find the smallest substring in S that contains all the characters of the T ( including the duplicates)

Key concepts : 
Frequency counter : Track  the frequency of each character in T .
For any window in S ( the substring )  you must check if its  character counts meet or exceed those in T. 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
 

Follow up: Could you find an algorithm that runs in O(m + n) time?

## SLIDING WINDOW
Another Key concept is the sliding window  which is a two pointer approach and one pointer expands the window(right), the other contracts it (left) 
Mathematically you are moving through all the possible intervals [i,j] in S , but efficiently.

## HASH MAPS /Arrays
.. to store character frequencies you will be using the hash map or the array.
.. This  allows O(1) access to check if the current window meets the requirements

## GREEDY MINIMIZATION
  .. once a valid window is found you try to shrink it from the left to find the minimum possible size

## COMPLEXITY ANALYSIS
  .. The optimal solution should be O(|S| +|T|) since each character is processed at most twice ( once  when expanding, once when contracting).

## COMBINATORICS:  COunting occurences and ensuring all the required elements are present 
 Optimization Minimizing the window length 
 Set theory : ENsuring all the elements of the T are covered in the current window.

  You will be translating the problem constraints into mathematical checks
