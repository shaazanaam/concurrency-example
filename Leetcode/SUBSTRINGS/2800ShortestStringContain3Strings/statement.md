Problem 2800.  ## Shortest String that contains three Strings 

Given the threee strings a,b,c your task is to finda string that has the minumum lenght and contains all three string as the substrings and if there are multuple such strings return the lexicographically smallest one.

## Return a string denoting the answer to the problem

A string a is lexicographically smaller than a string b ( of the same length ) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the correspoinding letter in b.

A substring is a contigious sequence of characters within a string .

Example 1:

Input: a = "abc", b = "bca", c = "aaa"
Output: "aaabca"
Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
Example 2:

Input: a = "ab", b = "ba", c = "aba"
Output: "aba"
Explanation: We show that the string "aba" contains all the given strings: a = ans[0..1], b = ans[1..2], c = ans[0..2]. Since the length of c is 3, the length of the resulting string would be at least 3. It can be shown that "aba" is the lexicographically smallest one.
 

Constraints:

1 <= a.length, b.length, c.length <= 100
a, b, c consist only of lowercase English letters.

## you need to return the shortest string that contains all the three substrings if the multiple answers have the same shortest lenght then return the lexicographically smallest one 
SO the ranking rule is Smaller length wins and if they are of the same length then the  the alphabetically smaller one wins.


The problem is about combining the strings with the maximum overlap and then the "abc"+"bca" = "abcbca"  but you do not need that and because "abca"

because "abc" ends with "bc" and "bca" starts with "bc"


## You would have to think about how you can generate all the possible strings that contain all the  three input strings as substrings

a -> b -> c

You want to merge a and b with the maximum overlap and then merge that result with c for example a = "abc"
b= "bca"

You are not asking to build the string character by character , instead  you are actually asking how much you can overlap each next strign with what you already have?

Brute force over all the order are going to work just fine in this case as  there are only three strings and hence it will be providing a clean solution 

## For each permutations begin by appending some  letters to the end of the first word to frm the second word then proceed to add more letters to generate the third word

The steps are going to be like this 
1. put the a,b,c into a list and then 
2. Generate all 6 permutations/ordered triplets
3. For each triplet , merge first with second then merge that with the third
4. Keep the shortest result and then 
5. if the result is tied then use the lexicographicall information to determine the smallest result.


 