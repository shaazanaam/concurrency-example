1092. Shortest Common Supersequence

Given two strings str1 and the str2 return the shortest string that has both the str1 and the str2 as the subsequences . If there are multiple valid strings then return any of them 

# A string s is a subsequence of the string t if deleting some number of the characters from the t ( possibly 0) results in the string s 
 

Example 1:

Input: str1 = "abac", str2 = "cab"
Output: "cabac"
Explanation: 
str1 = "abac" is a subsequence of "cabac" because we can delete the first "c".
str2 = "cab" is a subsequence of "cabac" because we can delete the last "ac".
The answer provided is the shortest such string that satisfies these properties.
Example 2:

Input: str1 = "aaaaaaaa", str2 = "aaaaaaaa"
Output: "aaaaaaaa"
 

Constraints:

1 <= str1.length, str2.length <= 1000
str1 and str2 consist of lowercase English letters.

## Hint 1 
 We can  find the length of the longest common subsequence between the str1[i:] and the str2[j:] for all the (i,j) using the dynamic programins and then we can use this  information to recover the shortest common  supersequence.

 Optimizing tool selection...In that hint, they mean the second thing: compute LCS on smaller suffixes for every pair of positions, not just once on full strings.

When they write:

- `str1[i:]` = substring of `str1` starting at index `i` to the end
- `str2[j:]` = substring of `str2` starting at index `j` to the end
- “for all `(i, j)`” = do this for every possible starting index pair

So you build a DP table where each cell answers:

- `dp[i][j] = LCS length of str1[i:] and str2[j:]`

Why this helps for shortest common supersequence:
- You don’t just need the final LCS length.
- You need “future information” at each step to decide:
1. if characters match, take it once and move both pointers
2. if not, decide whether to take from `str1` or `str2` based on which move preserves a longer LCS ahead

So yes: it is LCS, but computed over all suffix pairs `(i, j)`, not only full `str1` vs full `str2`. That full LCS is just one cell in that table (`dp[0][0]`).

## YOU do have the pattern for finding the longest continuous subsequence but for this you only need an extra step  which is an extra idea 

SCS_length(a,b)  = |a|+ |b| -LCS(a,b).
(|a|) means length of string a.
(|b|) means length of string b.
So (|a| + |b|) is the sum of their lengths.

## DP state depends on two indices; i in first string , j in the second string 
.. So we need a 2D table 
.. rows for the prefixes of the first string
.. columns for the prefixes of the second string

## Why n+1 and m+1 
Index 0 means empty prefix 
..so the row 0 = first string prefix length 0(empty) 
..col 0 = second string prefix length 0 (empty)

This lets  the base case to be build naturally . 
..LCS(empty, anything) = 0
..LCS(anything,empty) =0

## Why loops start at 1 and not 0?
Because row 0 and col 0 are base case already fixed at 0 
Real character comparisons starts from the prefixes of length 1
At the DP cell(i,j)  you are talking about the first i chars of a and the first j chars of b

## Why compare a[i-1] and b[j-1] ?
DP index i means prefix length 1. Last character of the prefix length i is at the array indexi-1(0-based indexing in the C++)  Same for the j and the j-1

# intuition for the n+m-dp[n][m]
Imagine wrriting both the strings fully : total llength n+m
Overlap as much as possible using common subsequence( LCS) . Overlap ampunt is dp[n][m]  so the shortest merged length is n+m-dp[n][m]



Great questions. Here is the reconstruction in a short, memory-friendly way.

1. Why use `push_back` on a string?
- `std::string` is like a dynamic array of `char`.
- So it supports methods like `push_back(char)` exactly for appending one character.
- `push_back` is not only for `vector`; both `vector` and `string` have it.

2. Reconstruction steps
- Start from bottom-right of DP: `i = n`, `j = m`.
- Build answer from back to front, so you keep appending chars with `push_back`.
- At the end, reverse the built string.

3. Decision at each step
- If `str1[i-1] == str2[j-1]`:
  - This char is common in both.
  - Add it once, move diagonal: `i--, j--`.
- Else (mismatch):
  - Compare top and left DP values.
  - Top = `dp[i-1][j]`, Left = `dp[i][j-1]`.

4. Why “choose top -> push `str1[i-1]`”?
- Choosing top means you move from `(i,j)` to `(i-1,j)`, so you are consuming one char from `str1`.
- Since SCS must contain all chars, that consumed `str1[i-1]` must be included in answer.
- So you `push_back(str1[i-1])`, then `i--`.

5. Why “choose left -> push `str2[j-1]`”?
- Same logic:
- Move to `(i, j-1)` means consuming one char from `str2`.
- That char must appear in SCS, so add `str2[j-1]`, then `j--`.

6. After main loop
- If `i > 0`, append remaining chars of `str1`.
- If `j > 0`, append remaining chars of `str2`.
- Reverse final string, return.

Quick memory line:
- Match: add once, go diagonal.
- Mismatch: go to bigger LCS neighbor, add char of the side you moved from.
- End: append leftovers, reverse.

Also one correction to your wording:
- If your condition is `dp[i-1][j] >= dp[i][j-1]`, that is checking **top >= left**, not left > top.



Excellent confusion. This is the exact place most people get stuck.

Short answer: no, “consuming” during reconstruction is not the same as “computing length”.

Two phases:
1. DP fill phase: only computes numbers (lengths), no characters are placed in answer.
2. Reconstruction phase: uses those numbers to choose which actual characters to place.

What “consume one char” means:
- You are at state `(i, j)` meaning:
  - remaining prefixes are `str1[0..i-1]` and `str2[0..j-1]`
- If you move to `(i-1, j)`, you reduced `i` by 1.
- That means char `str1[i-1]` is now left behind, so you must put it into SCS now (push it), otherwise it disappears.
- That is “consuming” in reconstruction: moving index and adding that char to answer.

Why compare `dp[i-1][j]` and `dp[i][j-1]` in mismatch:
- These two cells tell you which side keeps a larger common overlap (LCS) for the remaining prefixes.
- Larger overlap means fewer total extra chars later, so better for shortest supersequence.
- So:
  - if top is bigger/equal, move up and append `str1[i-1]`
  - else move left and append `str2[j-1]`

Tiny visualization (mismatch case):
- Current chars: `str1[i-1] = X`, `str2[j-1] = Y`, and `X != Y`
- You cannot merge `X` and `Y` as one char
- You must place one of them now and postpone the other path:
  - move up: place `X`
  - move left: place `Y`
- DP tells which choice preserves better overlap ahead.

Memory line:
- DP values decide direction.
- Direction decides which char you append.
- Decremented index = consumed string = append its char.

If you want, I can do one full dry run on your sample `str1="abac", str2="cab"` with `(i,j)` updates line by line.


Perfect question. You are stuck on the most important abstraction.

You are right: in the DP table we do not literally store prefixes as strings.
We store only lengths.
But each cell index represents a prefix subproblem.

Think of it like this:

1. Meaning of a cell
- dp[i][j] means:
- LCS length between:
- first i characters of str1
- first j characters of str2

So prefixes are hidden inside i and j.

2. Why prefixes are “invisible”
- You never store the substring text in DP.
- You only store the answer for that prefix pair.
- Index i is shorthand for prefix str1[0 ... i-1]
- Index j is shorthand for prefix str2[0 ... j-1]

3. What moving to (i-1, j) means
- You go from using first i chars of str1 to first i-1 chars.
- So you dropped the last considered char of that prefix, which is str1[i-1].
- str2 side stays same (first j chars).

4. Why this appears in reconstruction
At mismatch:
- Current chars str1[i-1] and str2[j-1] are different.
- You choose either:
- up: (i-1, j)
- left: (i, j-1)

If you choose up:
- you are saying “continue with the problem that ignores str1[i-1] for LCS matching”
- but for SCS, that ignored char still must exist somewhere
- so you append str1[i-1] to answer and then do i = i - 1

So “consume” means:
- move index backward in reconstruction
- append that dropped character into SCS output

It does not mean “we changed LCS length formula”.
It means “we moved to a smaller subproblem and handled the char we left behind”.

Tiny concrete snapshot:
- Suppose i = 4, j = 3
- Cell (4,3) represents prefixes:
- str1[0..3], str2[0..2]
- Move to (3,3):
- now it is str1[0..2], str2[0..2]
- char str1[3] got dropped from active subproblem
- so for SCS reconstruction, append str1[3]

One memory line:
- Indices are the prefixes.
- Moving index back drops one char.
- Dropped char must be appended to SCS unless it was a match step (diagonal).

If you want, I can do one exact 5-step trace with your sample and only show i, j, chosen move, and appended character.


# Why are we checking the dp[i-1][j]>=dp[i][j-1]  

dp[i-1][j] = how much LCS overlap remains if you drop the str1[i-1]
dp[i][j-1] = how much LCS overlap remains if you drop the str2[j-1] 
You want to keep the path with bigger remaining overlap becasue bigger overlap = more shared characters and that is = shorter final SCS

So if the dp[i-1][j]   is bigger or equal then dropping the str1 is better or same --> move up

# Why push the str1[i-1] when moving up?

Moving up means : Your next subproblem is the (i-1,j) str1[i-1] just left the active window and the SCS must contain every character from both the strings  so you must place the str1[j-1 ] into the answer now before you lose it and then the 

# Memory rule 
You move away from a cell --> the char at that index gets left behind --> append it immediately and moving up leaves behind str1[i-1] moving left leaves being str2[j-1]

Moving diagonal : both chars are the same and append once leave both behind together. The two characters are equal in the case of the diagonal move . So the single character which is the common one is also the str1[j-1] specifically . You could appeand str2[j-1] instead , it is the same character in this case we usually pick one consistently (often str1[i-1]) just for coding simplpicity and the diagonal means that the match is found and the match found means add once and move both pointers


int i = n , j= m
while(i>0&&j>0){
  if(str1[i-1]==str2[j-1]){
    ans.push_back(str1[i-1]);
    i--;j--;
  }else if (dp[i-1][j]>=dp[i][j-1]){
    ans.push_back(str1[i-1]);
    i--
  } else {
    ans.push_back(str2[j-1]);
    j--;
  }

  while(i>0){
    ans.push_back(str[i-1]);
    i--;
  }
  while(j>0){
    ans.push_back(str2[j-1]);
    j--;
  }

  reverse(ans.begin(), ans.end());
  return ans;
}