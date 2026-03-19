## Problem 1143
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

 

Example 1:

Input: text1 = "abcde", text2 = "ace" 
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
 

Constraints:

1 <= text1.length, text2.length <= 1000
text1 and text2 consist of only lowercase English characters.

The answer for the full string it as the row n and the column 

The DP matrix rows and columns:
1. Row i means first i characters of the text 1 and then the column j means first j characters of the text2 so i = 0 or j=0 means one side is empty string and LCS with an empty string is always 0

This is why we need an extra row and extra column and then the rows run from 0..n and then the columns 0..m so the table size is the (n+1)(m+1) and not nxm . 

## What the columns do : 

Each columns is a different prefix length of the second string and moving right means you include one more character from text 2. This  lets you compare all prefix-pairs(i,j) and build answers gradually and the way this helps is clean base cases and the first row is all 0 and first column is all 0 and then the easy transitions if the characters matach use diagonal top-left+1 and if the characters dont match then use the max of top and left.

3. No negative indexes 
    you can safely access i-1 and j-1 states while filing from 1 upward and then the intuition dp[i][j] stores the best answer for the smaller versions of the problem and then the extra row/columns represent the "start from then nothing"state and that foundation is what allows all other cells to be computed correctly 

    Each cell dp[i][j] means the LCS length between the first i chars of text 1 and first j chars of text 2 and 


Take the first j characters of a string.

If second string is:
ACBD

Then its prefixes are:

Length 0 -> "" (empty)
Length 1 -> "A"
Length 2 -> "AC"
Length 3 -> "ACB"
Length 4 -> "ACBD"
So when I say “column j is prefix length j of the second string”, I mean:

Column 0 compares against empty second string
Column 1 compares against first 1 char of second string
Column 2 compares against first 2 chars
etc.
Visualization with LCS table idea

Suppose:

text1 = ABCD
text2 = ACBD
Rows = prefix length of text1 (i)
Columns = prefix length of text2 (j)


Visualization with LCS table idea

Suppose:

text1 = ABCD
text2 = ACBD
Rows = prefix length of text1 (i)
Columns = prefix length of text2 (j)

So headers conceptually are:

  j=0   j=1   j=2   j=3   j=4
  ""    A     AC    ACB   ACBD


And rows:

i=0 ""
i=1 A
i=2 AB
i=3 ABC
i=4 ABCD

Each cell dp[i][j] means:
LCS length between

first i chars of text1
and
first j chars of text2
Why this helps:

You build from smaller comparisons to bigger ones.
Base row/column are easy: anything vs empty string gives 0.
Every new cell uses already solved neighbors (top, left, top-left).
Concrete mini examples:

dp[1][2] compares A vs AC -> LCS is A -> 1
dp[2][2] compares AB vs AC -> LCS is A -> 1
dp[3][3] compares ABC vs ACB -> LCS is either AB or AC -> 2
So “prefix length” is just a clean way to index progressive pieces of each string, from empty up to full. That is why DP becomes structured and easy to compute.

"Top", "left", and "diagonal" are just directions inside the 2D table.

When you are at cell dp[i][j], your neighbors are:

dp[i-1][j-1]   dp[i-1][j]
     ↖ diagonal      ↑ top

dp[i][j-1]     dp[i][j]  ← you are here
     ← left

What each direction means:

Direction	Cell	Meaning
Top	dp[i-1][j]	same prefix of text2, but one less char of text1
Left	dp[i][j-1]	same prefix of text1, but one less char of text2
Diagonal	dp[i-1][j-1]	one less char of BOTH strings
Why diagonal when characters match:

If text1[i-1] == text2[j-1], those two characters form a new common pair.

So you look at the state before either of those characters existed → that is dp[i-1][j-1] (diagonal).

Then you add 1 for the new match:

dp[i][j] = dp[i-1][j-1] + 1


Why top or left when they don't match:

If characters don't match, you can't use both. So you try:

Drop the current char from text1 → look at dp[i-1][j] (top)
Drop the current char from text2 → look at dp[i][j-1] (left)
Take the better one
Mini example with text1="AB", text2="AC":
The headers show the prefix expanding as we move right (columns) and down (rows):
Row/column 0 = empty prefix → always 0 (base case).

Now fill each ? cell:

dp[1][1] → comparing A vs A → they match!

             j=0   j=1   j=2
              ""    "A"   "AC"
i=0   ""       0     0     0
i=1   "A"      0     ?     ?
i=2   "AB"     0     ?     ?

At dp[1][1] → A==A → diagonal dp[0][0] + 1 = 0 + 1 = 1

At dp[2][2] → B!=C → max(top dp[1][2]=1, left dp[2][1]=1) = 1

Answer: dp[2][2] = 1 → LCS is "A" ✓

  dp[0][0]=0    dp[0][1]=0
      ↖diagonal      ↑top

  dp[1][0]=0    dp[1][1]=?
      ←left

Characters match then take the diagonal +1 = 0+1 

dp[1][2] --> comparing A vs AC --> A!= C--> no match and top = dp[0][2] = 0
left = dp[1][1] = 1
max(0, 1) = 1
dp[2][1] → comparing AB vs A → B ≠ A → no match

top = dp[1][1] = 1
left = dp[2][0] = 0
max(1, 0) = 1
dp[2][2] → comparing AB vs AC → B ≠ C → no match

top = dp[1][2] = 1
left = dp[2][1] = 1
max(1, 1) = 1
Final complete table:

             j=0   j=1   j=2
              ""    "A"   "AC"
i=0   ""       0     0     0
i=1   "A"      0     1     1
i=2   "AB"     0     1     1


Answer = dp[2][2] = 1 → LCS is "A" ✓

"top-left + 1" IS the diagonal

"top-left" literally means: one step up AND one step left in the table. That cell is dp[i-1][j-1]. In your code it IS used:

dp[i][j] = 1 + dp[i-1][j-1];

dp[i-1][j-1] = diagonal = top-left. Same thing, just written as code.



