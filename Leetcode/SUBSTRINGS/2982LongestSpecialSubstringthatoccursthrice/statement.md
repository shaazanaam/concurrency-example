2982 Find the longgest Special substring that occures thrice II
You are given a string s that consists of lower case english letters and a string is called special if it is made up of only a single character for example the string abc is not special and whereas the strings ddd zzz and f are special. Return the length of the longest special substring of s which occurs at least thrice  or -1 if no special substring occurs atleast thrice 
A substring is a contiguous non empty sequence of characters within a string.

Example 1:

Input: s = "aaaa"
Output: 2
Explanation: The longest special substring which occurs thrice is "aa": substrings "aaaa", "aaaa", and "aaaa".
It can be shown that the maximum length achievable is 2.
Example 2:

Input: s = "abcdef"
Output: -1
Explanation: There exists no special substring which occurs at least thrice. Hence return -1.
Example 3:

Input: s = "abcaba"
Output: 1
Explanation: The longest special substring which occurs thrice is "a": substrings "abcaba", "abcaba", and "abcaba".
It can be shown that the maximum length achievable is 1.


Constraints:

3 <= s.length <= 5 * 105
s consists of only lowercase English letters.

You can group consecutive characters together since the substrings consist of only one character for example 
"aaabbbaaa"---> Groups:["aaa","bbb","aaa"] Binary search for length . The problem asks for the longest substring and this suggests you can use the binary search on the possible lengths of the substring
To check if a substring of a certain length occurs atleast three times you can use a sliding window or a hashmap to count occurrences efficiently

You can group the consecutive characters together to identify the potential special substrings . "aaabbbaaa" -->[(a,3),(b,3),(a,3)] 

The way the grouping works is that for each group you know all the substrings of length L within that group are special and if a group has length cnt it contains cnt-L+1 special substrings of length L ( for L<= cnt)

Store each group as a pair and then for each possible length L , count how many times each special substring of length L appears across all groups.
for example for the group (a,3) you got the following
a--> 3-1+1= 3  special substring for L=1
aa--> 3-2+1=2  special substring for L=2
aaa--> 3-3+1=1 special substring for L=3

each group like the (a,3) means there are 3 consecutive 'a' s . so for (a,3), cnt = 3 and you only consider substrings within that group and you process each group individually.


You also  use  a map to count the total occurences for each character and length.

You only process each group once 
No nested loop over everysubstring
Works well with binary search for the maximum L 



For each group if the count >=L then that group contributes (count-L+1) substrings of length L

The length refers to the  length of the special substring you are searching for . The problem asks what is the largest L such that there exists a special substring of length L that appears at least three times in the string? so you want to try all the possible values of L ( from 1 upto the  length of the string ) and find the maximum one that works. You need to essentially check for every possible length if there is a special substring of that length that appears at least three times . You would be using binary search to find the largest valid L



How does the grouping help ...
When you group the string you get the runs of the same character example aaabbbaaa --->[(a,3),(b,3),(a,3)]

for each group (char,count) you can form a special substrung of length L if cnt >=L
For example in the (a,3) you can form 3-L+1  substrings of length L(all are the same character)

If L= 2 then the 3-2 +1 = 2 substrings :"aa" and "aa"( overlapping) 
You count for each character and length , how many times such substrings appear in the whole string( across all groups)

## WHY DOES THIS GIVE YOU THE RIGHT ANSWER
Because you are counting all the possible special substrings of Length L ( for each character) in the string.
If for any character the total count of its special substrings of length L is atleast 3 then  L is the valid answer. You repeat this for all possible L using binary search for efficiency an return the largest valid L

## Summary Table 
Summary Table Example
For "aaabbbaaa" and L = 2:

Groups: (a,3), (b,3), (a,3)
For (a,3): 3 - 2 + 1 = 2 substrings "aa"
For (b,3): 2 substrings "bb"
For (a,3): 2 substrings "aa"
Total "aa" substrings: 2 + 2 = 4
Since "aa" appears 4 times (≥ 3), L = 2 is valid.

You try each possible length count how many times each special substring of that length appears and pick the largest length where any special substring appears at least three times .

## How do you combine the grouping approach with the binary search setup . 
You want to find the maximum length L such that a special substring of length L appears atleast three times 
... Set low = 1 , high = s.size() and answer = -1

For each midlength use the grouping approach for this check 
for each mid = (low+high)/2 check if there exists a special substring of length mid that appears atleast three times

## Grouping check fundtion 
For each group (char, cnt) if cnt>=mid , count how many substrings of length mid you can form :cnt -mid+1
Sum these count for each character across all groups 
If any character's total count for length  mid is atleast 3 then mid is valid

## Binary Search Logic 
if mid is valid then set the answer = mid and try a larger length low = mid +1 . if not then try a smaller length (high = mid -1)
