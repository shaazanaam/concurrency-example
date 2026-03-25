## 2207  Maximize the number of subsequence in a string 
You are given a 0- indexed string text and another 0 indexed string pattern of length 2 both of which consist of only lower case english letters 
You can add either pattern[0] or pattern[1] anywhere in the text exactly once . Note that the character can be added even at the beginning or the end of the text .

Return the maximum number of times the pattern can occur as a subsequence of the modified text .
A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters




Example 1:

Input: text = "abdcdbc", pattern = "ac"
Output: 4
Explanation:
If we add pattern[0] = 'a' in between text[1] and text[2], we get "abadcdbc". Now, the number of times "ac" occurs as a subsequence is 4.
Some other strings which have 4 subsequences "ac" after adding a character to text are "aabdcdbc" and "abdacdbc".
However, strings such as "abdcadbc", "abdccdbc", and "abdcdbcc", although obtainable, have only 3 subsequences "ac" and are thus suboptimal.
It can be shown that it is not possible to get more than 4 subsequences "ac" by adding only one character.
Example 2:

Input: text = "aabb", pattern = "ab"
Output: 6
Explanation:
Some of the strings which can be obtained from text and have 6 subsequences "ab" are "aaabb", "aaabb", and "aabbb".

Constraints:

1 <= text.length <= 105
pattern.length == 2
text and pattern consist only of lowercase English letters.
 




Basic Idea for this 

1. Let a = pattern[0] and b = pattern[1]
2. You are allowed one insertion either a  or b
Count how many subsequences "ab" already exist in the text then compute how much extra you get from inserting a ( best place is at the very begining and then inserting b ) ( best place is at the very end)

Take the larger result

## WHy those insertion positons are optimal .

If you insert a it helps by pairing with every b that appears after it . Earliest position maximizes "after it" so beginning is best 

If you insert b it helps by pairing with every a before it .

You have to maintain the order ab which is a must 


## How to count the existing subsequences efficiently 

Scan left to right 
1. Keep the countA = number of 'a' seen so far 
2. When you see b , add countA to answer and this gives the existing subsequences in the O(n)


You made a mistake here with the two if statements in the following code 
   for (auto ch: text){
            if (ch==a) countA++;
            if (ch==b) ogCount +=countA;

        }

you will be running into the issue when you have the a==b you would be actually getting to increment countA first and then immediately adding that new (already incremented)value to ogCount. That means you would be counting the current character as pairing with itself which overcounts 

Hint: swap the order of the two if checks. Check b and accumulate into the ogCount before incrementing count 

  for (auto ch: text){
            
            if(ch==b) {
                ogCount +=countA;
                countB++;
            }
            if(ch==a) countA++;

        }
    }


After the loop you have:

ogCount — existing subsequences
countA — total a's in text
countB — total b's in text
Two choices:

1. Insert a at the beginning --every b in the text now has an extra a before it so you gain the countB new subsequences 

2. Insert b at the end and every a in the text now has an extra b after it so you gain countA new subsequences 

So the answer is 

ogCount + max(countA, countB)

## THink about why :
You pick whichever insertion gives the bigger gain which is just whichever count( a's or b's) is larger

Also — note your ogCount is int but the problem allows text length up to 
10
5
10 
5
 . The maximum number of subsequences can be up to 
≈
10
10
/
4
≈10 
10
 /4, which overflows int. Consider making it long long.


You do not actually need to build the new string or perform a real insertion.

That is the key simplification.

Think of “insert” as only changing the count:

Insert a at the beginning:

new subsequences added = number of existing b
total becomes ogCount + countB
Insert b at the end:

new subsequences added = number of existing a
total becomes ogCount + countA
So “how do I insert?”:

Conceptually, pretend you inserted.
Mathematically, just add the gain.
Then return the larger of the two totals.
You only need real insertion if the problem asked you to output the modified string, but it only asks for the maximum count.

One more detail:

if a == b, this same formula still works if your counting loop is in the correct order.
In that case both choices are the same character anyway, so the gain is just the number of existing a characters.
So your final reasoning is:

count existing subsequences
count total a
count total b
answer is ogCount + max(countA, countB)
If you want, I can now check your full function once you add the return line.

Why it works:

ogCount counts the existing subsequences.
countA ends as total number of pattern[0].
countB ends as total number of pattern[1].
ogCount + max(countA, countB) correctly models:
insert a at the front, gain countB
insert b at the end, gain countA
It also handles a == b correctly because you do:

add to ogCount first
then increment countA
That avoids pairing a character with itself.

Two small C++ points to clean up mentally:

The method is inside a class, so on LeetCode it usually needs to be public: or the judge cannot call it.
max needs the right header in standard C++; usually that means including the algorithm header.
Quick sanity checks:

text = "abdcdbc", pattern = "ac" gives 4
text = "aabb", pattern = "ab" gives 6
text = "aa", pattern = "aa" gives 3, which is correct after one insertion because "aaa" has $\binom{3}{2} = 3subsequences"aa"`




This is a **greedy two-character subsequence counting pattern**. Here's what it does:

**The Algorithm:**
1. **Count subsequences of pattern in text**: As you iterate through the text, whenever you see the second character `b`, add the count of first character `a` you've seen so far to `ogCount`. This counts all `a...b` subsequences.

2. **Optimize with one insertion**: At the end, add `max(countA, countB)` to the result. This represents the benefit of inserting one additional character:
   - Insert `a` before the string → creates `countB` new subsequences (since all `b`'s can now pair with it)
   - Insert `b` after the string → creates `countA` new subsequences (since all existing `a`'s can pair with it)
   - Pick whichever is better

**Example**: For `text="abdcdbc"`, `pattern="ac"`:
- See `a` → `countA=1`
- See `b` :nothing
- See `d` :nothing
- See `c` → add `1` to result, `ogCount=1` and also countB=1
- See `d` -> nothing
- See `b` -> nothing
- See `a` → `countA=2`
- See `c` → add `1` to result, `ogCount=2` `countB=2`

After the loop :
ogCount = 2( existing "ac' subsequences)
countA = 1 ( total a's)
countB = 2 ( total 'c's)

Answer 2+ max(1,2) = 2+2 = 4

Insert 'a' at the beginning : Every 'c' can now pair with it -> gain countB (2) new subsequences
Insert 'c' at the end : Every a can now pair with it ->gain countA (1) new subsequence

The pattern works by optimally choosing whether to add an extra `a` or `b` to maximize the pattern count.

It's an elegant single-pass greedy solution for maximizing subsequence occurrences.
