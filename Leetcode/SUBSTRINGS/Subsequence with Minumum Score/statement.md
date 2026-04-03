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

But for this problem of minimum score to make t a subsequence of s full LCS style DP is usually too expensive

Standard DP is O(s x t) which is too slow for large constraints 
Interval DP on t is also generally too heavy.


The basic idea to solve this problem is to know hou much of t I can match from the left and how much of t I can match from the right and then combine the left and right matches to remove one middle substring of t with the minumum length . remember that the start and the stop of the substring removed is what the formula is telling us which is the right- left +1


In this case you would be needing to Build a pref array and the the pref[i] = earliest index in s after mactching t[0...i]

Build the suffix arry :
suff[i] = latest index in s before matching t[i...m-1] from the right 

Then try splitting the t  in the following manner by keeping the prefix [0..i] and keeping the suffix t [j...m-1], remvoing the t[i+1..j-1]

Valid split condition is that the prefix match in s  ends before suffix match start 
Minimize remvoed length j-i-1

This is essentially the prefix suffix matching + two pointers or binary search and runs in about (s+t) or O(t logt ) much better than full DP 

So short answer:

Yes, your two DP patterns are absolutely useful conceptually.
For this question, convert that thinking into prefix/suffix subsequence matching, not a full 2D DP table.

## Core pattern for this problem 
1. match as much as possible from the left 
2. match as much as possible from the right 
3. Remove one middle part that casuses the conflict 

So instead of asking what is the full best subsequence you ask how far can i safely match from both sided and what is the smallest middle gap I must delete 

the longest common subsequence problem already trained you think the prefix relation in that what can be matched up to the position i and suffic remation what cn be matched from the position i to end and then combine two partial truths to buld a global truth 

Here we avoid full 2D table and use the  directional matching ( left pass +right pass)

## Understand what the score really means 

The score is the right -left +1 where the left and the right are the main indices of whatever you removed from the t

Key insight : If you are going to remove the characters at the position 2 and 7  then you might as well remove everything in between them too.--- It doesnt increase the score  which still is 7-2+1 =6  but it gives you more characters removed for free. SO in the case of our problem the optimal remove is  always the single contigious block from the t 

this will be then giving the minimum possible score 

t = [ a  b  c  d  e  f  g ]
            ↑           ↑
           left        right
score = right - left + 1

So the problem becomes : find the shortest contigous segment of t to delete so that remaining characters form a subsequence of s 

### Step 2: What does the remaining characters look like after deleting a block ?
After deleting t[i+1, j-1] you are left with the  prefix and the suffix

[ t[0]  t[1] ... t[i] ]  +  [ t[j]  t[j+1] ... t[j-1] ]
  ^^^^^ PREFIX ^^^^^           ^^^^^ SUFFIX ^^^^^

For this to be a subsequence of s the prefix must match in the left part of the s and the suffix must match in the right part of the s and critically the left part must end before the right part begins

s = [ ...prefix match ends here... | ...suffix match starts here... ]
                                   ↑
                             split point in s


### Why build a prefix array ?
The prefix array answers " if I greedily match match t[0..i] from the left to right in s where do i end up in s ?

prefix[i] = index in s where t[0..i] was matched 

in the below example of the s = "abacaba", t = "bzaa"

Greedy left-to-right matching:
t[0]='b' → found at s[1]  →  prefix[0] = 1
t[1]='z' → not found      →  prefix[1] = -1  (match broke here)
t[2]='a' → ...            →  prefix[2] = -1
t[3]='a' → ...            →  prefix[3] = -1

After the first successful match   j moves from 0 to 1 so from that point onward the algorithm keeps trying to match only the t[1]  and not t[2] or t[3]. This is exactly how subsequences matching should work.
## Why ?
This is because to match t as s subsequence you must match its characters in order which means 
1. first match t[0]
2. then match t[1]
3. then match t[2]
4. and so on and you are not allowed to try t[2]  before t[1] is matched . So if t[1] never gets matched then the t[2] and the t[3] can never be matched 

So if one required character of t is never found then everything after is also fails as they not only have to match but they have to be matched in order they are appearing in the t 

## So these lines 

t[2]='a' → ... → prefix[2] = -1
t[3]='a' → ... → prefix[3] = -1
 

do not mean the algorithm actively reached t[2] and t[3].



They only mean:

those positions were initialized as -1
and they stayed -1
because j got stuck at 1
That is the key point.

Intuition
Think of j as:

"Which character of t am I currently waiting to match?"

After matching 'b', you are waiting for 'z'.

If 'z' never appears in s, then progress stops there.

That is why later entries remain -1.

Short rule to remember
In subsequence matching:

i scans s
j scans t
j moves forward only on a successful match
if one required character of t is never found, everything after it also fails
So yes, your reading of the loop is right.

If you want, next I can explain why this same logic makes the suffix array work from the right side too.


### Why build the suffix array ?
The suffix array answers : If I greedily match the t[j..m-1] from the right to left in the s where do I start in s?

Example: s = "abacaba", t = "bzaa"

Greedy right-to-left matching:
t[3]='a' → found at s[6]  →  suffix[3] = 6
t[2]='a' → found at s[4]  →  suffix[2] = 4
t[1]='z' → not found      →  suffix[1] = -1
t[0]='b' → ...            →  suffix[0] = -1

###### SPLIT 
## SPLIT .. which is the combining step and the key insight for the combining step

Now you try every possible split

Keep t[0..i] + Keep t[j..m-1]   →   Remove t[i+1 .. j-1]
score = j - (i+1) = j - i - 1

For this split to be valid ( valid means that the two halves can actually be matched in s without overlapping)

The conditon shoudl be the following  prefix[i]< suffix[j]

The prefix match in s must end before the suffix match begins.. You want to minimize the j-i-1 which means maximize the i and minimize the j 

### The two pointer slide 

You iterate the j from 0 to m and for each j you want the largest valid i (  where the prefix[i]< suffix[j]). .This is done with the two pointer approach 

for j = 0 to m :
    while i>=0 and prefix[i] >= suffix[j]:
        i--  // shrink the prefix until it fits before suffix 

score = min ( score, j-i-1)


## The complete picture

t:   [ 0  1  2  3  4  5  6  7  8  9 ]
                  ↑           ↑
              keep up to i   keep from j
              (prefix)        (suffix)
              
              DELETE: t[i+1 .. j-1]
              score = j - i - 1

s:   [==prefix match==][==suffix match==]
                      ↑
               prefix[i] < suffix[j]  ← VALID CONDITION



## Special cases to handle is the following 

1. t is already a subsequence of s which means you should delete nothing and then the score would actually be zero
2. Delete only a prefix of t which means that keep only the t [i..m-1] only in that case the score is j

3. Delete only a suffix of t which means keep the [0...j] only in that case the score is m-1-i

4. Delete all of t and in this case you would be keeping nothing in which case the score should be m.


# How to build syntax from the semantics 


Removing a contiguous block is always optimal — the score formula rewards contiguity.
The prefix array tells you "how far right in s did I consume while matching the left part of t."
The suffix array tells you "how far left in s did I start while matching the right part of t."
A valid combination requires the left part's match to finish before the right part's match begins in s.
You slide a two-pointer over all splits to find the shortest removable middle block.
This is essentially a greedy + two-pointer pattern that replaces the expensive O(n×m) DP by precomputing what the best possible left-match and right-match look like independently, then combining them in O(n+m).



**Core Pattern (in plain words)**  
For this problem type, think in 3 parts:

1. Match as much as possible from the left.
2. Match as much as possible from the right.
3. Remove one middle part that causes conflict.

So instead of asking  
“What is the full best subsequence?”  
you ask  
“How far can I safely match from both sides, and what is the smallest middle gap I must delete?”

That is the pattern.Becasue any set of characters you remove from t the worst case is always captured and by removing everything in one contigious block you never gain by remvoing scattered chaars vs a block of the same length so the question becomes you need to keep some prefix t[0..i]  and some suffix t[j..m-1]
Remove everything in between t[i+1..j-1]  the score cost is the length of what you removed j-i-1



---

**Why your LCS background helps**
Your LCS practice already trained you to think:

1. Prefix relation: what can be matched up to position i.
2. Suffix relation: what can be matched from position i to end.
3. Combine two partial truths to build a global truth.

That is exactly what is happening here.  
Difference: here we avoid full 2D table and use directional matching (left pass + right pass).

---

**How to build syntax from semantics (very important)**

You asked about building “syntactical semantics.”  
A practical way is: meaning first, syntax second.

Use this 5-step method every time.

1. Write one sentence meaning for each array/variable.
Example:
- leftMatch[k] means: where the first k+1 chars of target can finish in source.
- rightMatch[k] means: where chars from k to end can start from the right side.

2. Write loop purpose before loop syntax.
Example:
- First loop purpose: fill leftMatch by scanning source left to right.
- Second loop purpose: fill rightMatch by scanning source right to left.
- Third loop purpose: try split points and measure deleted middle length.

3. Write invariants (truth that stays true).
Example:
- left pointer never moves backward.
- right pointer never moves forward (in reverse scan).
- split is valid only if left side finishes before right side begins.

4. Dry-run on tiny strings by hand.
Use very small examples (length 4 to 6).  
If hand run is clear, coding is easy.

5. Only then write language syntax.
Now choose:
- variable types
- loop forms
- boundary checks

This order prevents “syntax confusion.”

---

**Mental template you can memorize**
When problem says “make X a subsequence of Y with minimum removal”:

1. Can I match from left greedily?
2. Can I match from right greedily?
3. If I keep left part and right part, what middle must be removed?
4. Minimize that removed middle length.

If you can say these 4 lines clearly, you understand the algorithm before coding.

---

**Beginner practice plan (short and strong)**

1. Take one tiny example and compute leftMatch manually.
2. Compute rightMatch manually on same example.
3. Pick 3 different split points and compute deletion length.
4. Check which split gives minimum.
5. After that, write pseudocode only (not full C++).
6. Then convert pseudocode to C++.

Do this 2-3 times and this pattern becomes natural.

---
## What does it mean by matching characters with the prefix and the suffix and so what if they match does matching mean i am getting subsequence 

Great question.  
“Matching” in prefix/suffix passes means: you found one next required character of t in s while keeping order.

It does not mean full subsequence yet. It means partial progress.

Think like this:

- Prefix matching:
1. Start from left of s and left of t.
2. Every time s[i] == t[j], you lock that match and move j forward.
3. You are proving how much of the beginning of t can be formed in order.

- Suffix matching:
1. Start from right of s and right of t.
2. Every time s[i] == t[j], you lock that match and move j backward.
3. You are proving how much of the end of t can be formed in order.

What does a match tell you?
- One match means one character can be part of a subsequence.
- Many ordered matches mean a longer subsequence segment.
- If you match all characters of t, then yes, t is a subsequence of s.
- If you match only some, then only that part is subsequence, not whole t.

Tiny example:
- s = axbycz
- t = abc

Prefix pass:
- a matched, then b matched, then c matched -> all matched -> t is subsequence.

Another:
- s = acx
- t = abc

Prefix pass:
- a matched, c matched cannot stand in for b, so only partial.
- Not full subsequence.

So your understanding should be:
- Matching = progress toward subsequence.
- Full subsequence only when every character of t is matched in order.


## so for combining them and for making sure that the prefix matched part ends before the suffix part starts we need to have another vector filled or just use the condition where the last index of prefix is actually less than the first index of the suffix like find the index j when prefix[i]!=-1


You do not need another vector.  
Two vectors are enough: prefix and suffix.

Use this validity rule when combining:

1. Pick how many chars you keep from the left side of t (index i in prefix).
2. Pick where the kept right side starts in t (index j in suffix).
3. Valid only if prefix[i] < suffix[j].

That single condition means:
- left kept part finishes earlier in s
- right kept part starts later in s
- so order is safe

Also include edge cases:

1. Keep only suffix (no prefix kept): always allowed if suffix part is matchable.
2. Keep only prefix (no suffix kept): always allowed if prefix part is matchable.
3. If prefix entry or suffix entry is -1, that split is not usable.

Your sentence is basically correct:
- yes, compare end index of chosen prefix with start index of chosen suffix
- yes, you find usable i and j where entries are not -1
- and enforce prefix end < suffix start

If you want, next we can do one tiny table example with concrete i, j checks so this condition becomes fully intuitive.






## Wrong approach 
is this what you mean
for(int i = 0 ; i<s.size();i++){
if (s[i]==t[i])
prefix[s[i]]++;
}

1. you should not compare the s[i] agains t[i] because t needs its own pointer j

2. you should not do prefix[s[i]]++ becasue s[i] is a character and not the target position index 


Use this for the prefix matching 

vector<int> prefix(t.size(), -1);

int j = 0; // pointer for t
for (int i = 0; i < (int)s.size() && j < (int)t.size(); ++i) {
    if (s[i] == t[j]) {
        prefix[j] = i; // t[j] matched at index i in s
        ++j;
    }
}

Meaning:

prefix[0] = where first char of t got matched in s
prefix[1] = where second char of t got matched
and so on



## Next build the suffix array
## Next build the suffix array

Suffix tells you if you keep the t[j..m-1] where in s does that suffix start.
For a valid  split at (i,j) the prefix part must finish before the suffix part begins in s . prefix[i]< suffix[j]

## The split loop - 
You want to try all the possible split points . you need to go through every valid combination of :
"how much prefix to keep " ( i from -1 to m-1 where -1 means keep nothing )  
"how much suffix to keep"( j from 0 to m where m means keep nothing)

Key edge case to think about:
1. Keep nothing from prefix , keep all the suffix from the index 0: score = j-0 = number of chars dropped from the left 
2. Keep the whole prefix up to m-1 drop no siffix : score =0 if fully matched
3. Keep prefix and suffic where j=i+2 onward score = j-i-1


Optimizing tool selection...Perfect, let’s slow it down with one small example.

Take:
- t = "b z a a"
- indices: 0 1 2 3
- m = 4

If you remove a middle block t[L..R], score is its length:
        score = R - L + 1$$

Another equivalent way:
- keep prefix ending at i (t[0..i])
- keep suffix starting at j (t[j..m-1])
- removed block is t[i+1..j-1]
- score:
        score = j - i - 1

Now the edge cases are just special values of i/j.

1. Keep nothing from prefix  
That means i = -1.

Then removed block becomes t[0..j-1] (drop from left side), and keep t[j..m-1].

Score: j - (-1) - 1 = j

So this means: drop first j characters from t.

Example: j = 2  
- drop t[0], t[1]
- keep t[2..]
- score = 2

That is what “keep nothing from prefix, keep suffix” means.

2. Keep whole prefix, keep no suffix  
“Keep whole prefix” means i = m-1.  
“Keep no suffix” means j = m.

Score:
m - (m-1) - 1 = 0

So score 0 means you removed nothing.  
This is only valid if full t is already a subsequence of s.

3. General split in middle  
Choose i and j with j > i.  
You keep left part t[0..i] and right part t[j..m-1].  
Removed part is between them: t[i+1..j-1].  
Length is:
j - i - 1

## Keep prefix[i] and suffix[j] where j = i+2 onward: score = j-i-1
- if j = i+1, removed length is 0 (nothing removed between them)
- if j = i+2, removed length is 1 (one char removed)
- etc.

The only extra rule: the kept prefix match in s must end before kept suffix match in s starts:
    prefixPos[i] < suffixPos[j]

That condition is what makes the split valid in order.

## Code 
Do this in order inside your function after building prefix and suffix.

Initialize answer as worst case (remove all of t)

int ans = m;

Case A: keep only suffix (remove a left prefix of t)
Find the first index k such that suffix[k] is valid.
If suffix[k] != -1, then you can keep t[k..m-1], so removed length is k.

for (int k = 0; k < m; ++k) {
if (suffix[k] != -1) {
ans = min(ans, k);
break;
}
}

Case B: keep only prefix (remove a right suffix of t)
For every matched prefix end i, removed length is m - 1 - i.

for (int i = 0; i < m; ++i) {
if (prefix[i] != -1) {
ans = min(ans, m - 1 - i);
}
}

Case C: keep prefix and suffix together ( middle removal) Use two pointers 
1. i for the prefix end 
2. j for the suffix start
Move j only forward so total is linear 
int j2 = 0;
for(int i = 0; i< m; ++i>){
    if prefix[i] ==-1 break; // this prefix length is not matchable 
    j2= max(j2,i+1); //suffix must start after i in t 
    while (j2 < m &&( suffix[j2]==-1 || suffix[j2]<= prefix[i])){
        ++j2;
    }
}
For a valid split 
1. in t the suffix must start after the prefix : j>i
2. In s suffux start must be to the right of the prefix end . suffix[j]>prefix[i]

j2= max(j2, i+1);

i+1 enforces the j2>i in t ( no overlap in the kept parts)
max(j2,..)  keeps j2 monotonic( never moves backward) giving linear time overall

While ( j2< m && (suffix[j2]<= prefix[i])) {++j2;}

skip invalid suffix starts 
1. suffix[j2] ==-1 means that the suffix cannot be matched in s 
2. suffix[j2]<=prefix[i] means suffix begins too early ( or some place) , violating order in s

keep moving j2 until first valid j2 starts

if (j2 < m) { ans = min(ans, j2 - i - 1); }

if such a suffix exists then we can split at the (i,j2)
and then in this case the remvoed middle is the t[i+1..j2-1] length is the j2-i-1 and then we also minilmize the answer 

Keep left part t[0..i]
Keep right part t[j2..m-1]
Delete middle t[i+1..j2-1]

So the loop is 
" for each left kept part find the the earliest right kept part that is valid in both strings and then compute the deleted middle length
