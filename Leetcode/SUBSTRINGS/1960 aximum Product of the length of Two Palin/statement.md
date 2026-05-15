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

# Split Point :
It means you will be chosing one boundary in the string where the left palindrome must end before it and the right palindrome must start after it . Think of the string as being cut into two parts 

s="abacdcaba"
split at i = 3 
left side : s[0..3] "abac"   right side : s[4..n-1] "dcaba"

and now the problem becomes for every split i you would be finding the best palindrome completely on the left of i and then multiply it with the best palindrome on the right of the i . Instead of chekcing every possible pair of palindromes directly you ask 
What is the longest odd palindrome available up to this position ?
What is the lingest odd palindrome available after this position?

Then you would be trying every cut .
s="ababbb" split after the index 2:
left side = "aba"
right side ="bbb"
left best odd palindrome length =3 
right best odd palindrome length = 3
product = 3x3 = 9

The reason the split system simplifies everything is because the two palindromes are non intersecting and that means there is always some boundary between them
So you can evaluate each possible boundary and then combine the best left answer with the best right answer
The key mental shift is 
do not first chose palindrome A and palindrome B instead choose a split and then ask what is the best palindrome on each side 


# Whats a prefix and the suffix

It means that for every index i there is an array element prefix[i] which store the length of the best that comes before i or inside the s[0...i] from the begining of the string  up to the index i 

s= "abacdc"
i = 0   "a"         best = 1
i = 1   "ab"        best = 1
i = 2   "aba"       best = 3
i = 3   "abac"      best = 3
i = 4   "abacd"     best = 3
i = 5   "abacdc"    best = 3

so in this case the prefix is [1,1,3,3,3,3]
Similarly the suffix[i] is the same thing meaning the best odd palindrome fully inside the s[i...n-1]

We would be needing the prefix and the suffix becasue of the split idea.
Suppose split is after index i . Then we have 
left palindrome  must be inside  [0..i]
right palindrome must be inside  [i+1..n-1]
so the answwer at the split i = prefix[i]* suffix [i+1]

# Where does the Manacher comes in ?

Manacher gives the longest palindrome centered at every index and s = "abacaba" at the center index 3 = 'c'
where the radius becomes 3 becasue abacaba extenda 3 left and 3 right so the manacher produces something line p[i] = palindrome radius at center i and for the odd palindromes length = 2*p[i]-1

# Line sweep from the center to the left/right mean
This the transformation of the palindrome at the center c into information about which intervals are covered suppose center = 5 and  radius - 3 then the palindrom spans from the left = 5-3+1 = and then right = 5+3-1

You want the infromation like the bestEndingAt[i]
and the bestStartingAt[i] meaning Largest palindrome ending at i and then the largest palindrome starting at i and from those you can build prefix maximums and suffix maximums. Why is the farthest center language confusing 