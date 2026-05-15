# 1960 Maximum product of the length of two palindromic substrings 
You are given a 0 indexed string s and are tasked with  dinsing two non intersecting palindromic substrings of the odd length such that the product of their lengths is maximized .
More formally you want to chose four integers i,j,k,l  such that 0<=i<=j<=k<=l<s.length  and both the substrings s[i...j] and s[k...l] are palindromes and have odd lengths s[i...j]  denotes a susbtring from index i to index j 
return the maximum possible product of the lengths of the two non intersecting palindromix substrings .
A palindrome is a string that is the same forward and backward . A substring is contigious sequence of characters in a string 

Input s= "ababbb"
Output =9
Explanation : Substrings "aba" and "bbb" are palindromes  with odd length.product = 3x 3 = 9

Example s = "zaaaxbbby"
Output: 9
Explanation: Substrings "aaa" and "bbb" are the palindromes 

BIT MASK is not the right approach in this case as the subsequence based case DP makes the sens and the substring based and the contigious and input size is usually large . Bitmask is exponential and so it will time out badly 

# Use the Manacher ( odd- length palindromes) in O(n)
Build leftBest array 
leftBest[i] = maximum odd palindrome length fully inside the s[0..j]
Build the rightBest array:
rightBest[i] = maximum odd palindrome length fully inside
