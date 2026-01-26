30. Substring with Concatenation of All Words

Given is the string s and an array of strings words . All the string of words are of the same length.  A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

For example if words = ["ab", "cd", "ef"] then "abcdef" ,"abefcd", "cdabef","cdefab", "efabcd", and "efcdab" are all concatenated strings .
"acdbef" is not a concatenated string because it is not the concatenation of any permutation of words

Return an array of the starting indices of all the concatenated substrings in s. You can return the answer in any order.

Example 1:
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]

Explanation:

The substring starting at 0 is "barfoo". It is the concatenation of ["bar","foo"] which is a permutation of words.
The substring starting at 9 is "foobar". It is the concatenation of ["foo","bar"] which is a permutation of words.

Example 2:

Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]

Output: []

Explanation:

There is no concatenated substring.

Example 3:

Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]

Output: [6,9,12]

Explanation:

The substring starting at 6 is "foobarthe". It is the concatenation of ["foo","bar","the"].
The substring starting at 9 is "barthefoo". It is the concatenation of ["bar","the","foo"].
The substring starting at 12 is "thefoobar". It is the concatenation of ["the","foo","bar"].

Constraints:

1 <= s.length <= 10^4
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.

Create a set to keep track of all previously encountered and validated strings. During the sliding window traversal, if a string is already in the set, directly add its index to the result without performing any further checks. This approach increases memory usage but allows you to efficiently skip redundant processing, which helps in passing the 178/179 test cases.

This is basically a sliding Window on the word boundaries (aka multi-offset/modular sliding window) + HashMap frequency counting.

Since every word has the same length L you don’t slide 1 char at a time -- you slide L characters at a time and you run the window starting from each offset ..
And then you run the window starting from each offset 0....L-1.

Why your cache validated strings in a set idea is risky:
The idea that you are proposing is that you can keep track of all the previously encountered and validated strings. During the sliding window traversal, if a string is already in the set, directly add its index to the result without performing any further checks. This approach will be increasing the memory usage but will allow you to efficiently skip redundant processing which helps in passing the 178/179 test cases.

Basically your idea is that you store each of the already validated concatenation substrings in a set and then if you see it again accept it immediately.

This is more of a sliding window on window boundaries (aka multi-offset/modular sliding window) + HashMap frequency counting.
Key idea: since every word has the same length L, you don’t slide 1 character at a time -- you slide L characters at a time and you run the window starting from each offset 0...L-1.

1. Memory blow up: Validated substrings are length L*k (can be huge) and there can be O(n) of them which is a lot of memory.
Copy cost still exists to check the set you still need to create the substring (or compute a hash)--- which is most of the work.

2. Copy cost still exists: To check the set you still need to create the substring (or compute a hash) which is most of the work.

3. Doesn’t fix the real bottleneck. The correct check avoids redundant checks structurally using the word-aligned sliding window. That’s why it passes all the cases cleanly.

SO CACHING IS A BANDAID BUT THE REAL FAANG SOLUTION IS THE MULTI-OFFSET SLIDING WINDOW.

SO THIS IS THE METHODOLOGY FOR THE WORD-ALIGNED SLIDING WINDOW:

Window is [LEFT--RIGHT] moving in the steps of L.
Seen[word] counts the words inside the current window.
If the seen[word] > need[word] shrink from the left until valid again.
When the window contains exactly k words, record left.

You will be having two frequency maps:
- need[word] ---> how many times this word is allowed.
- seen[word] ----> how many times this word appears in the current window.

The invariant you enforce is that for every word: seen[word] <= need[word].

Key insight: The moment this invariant breaks your window is invalid.

Scenario is that you add a word at the right and then if you see that the seen[word] > need[word] then you don’t restart everything but instead you shrink from the left. And the mathematical beauty is that shrinking by exactly one word (+L) always removes exactly one count so the invariant can be restored deterministically.

## When do you record an answer?

This is the precise condition:
Define:

k = words.length which is the size of the given vector.
count = number of words currently in the window.

Condition: if count == k AND invariant holds --> valid concatenation.

Why does the multiple offsets are required?
If L=3 valid windows could start at the index 0, index 1, and then the index 2. You must run the sliding window L times once per offset.
This is not optional; this is the mathematical structure of the problem.

People fail because they restart the windows too often and then recompute the maps from the scratch and then use the substrings caching instead of the structural guarantees and then the FAANG wants the amortized linear movements and not the memorization hacks.

The invariant is not the seen == need all the time and that’s the goal condition when you want to record an answer and the correct way to think about it is that there are two different truths and you must keep them separate in your conceptual mind:
1. The window-valid invariant (must hold while you slide and for every word in need: seen[word] <= need[word]).
   This is what you enforce by shrinking from the left.

2. Match the condition (only when you output an index):
   That the window has exactly k words and the invariant holds which is when the effectively seen == need across all the words in the window.

So seen <= need is the invariant.
Seen == need is the "we found it" moment.

You just can’t have the seen == need as the only invariant as you can have some partial builds while traversing through the window and then you would end up rejecting every one of them.
For example, when you are building the window you will often have partial matches like the words = ["foo", "bar"] and then your need is the foo = 1 and the bar = 1.
As you scan you see the bar first and then your seen is only bar and the seen dictionary will be looking like the bar = 1 and the foo = 0. This window is potentially correct and you just haven’t collected all the words yet. So if your invariant required seen == need you’d be forced to reject every partial build which kills sliding window.

Think of the window as the bag you are filling and you are allowed to put a word in the bag up to the limit and if you exceed the limit you remove from the left until the bag is legal again.
When the bag contains exactly k items it must be the right multiset and then you would be recording it.

Training-wheels dry run (just conceptually):

s = "barfoothefoobarman"
words = ["foo","bar"]
L=3, k=2, totalLen=6

Offset 0 scan words as blocks:
bar | foo | the | foo | bar | man

need: bar=1 foo=1

Start:

take "bar" → seen(bar)=1 ✅ (≤ need) count=1
take "foo" → seen(foo)=1 ✅ count=2 → count==k → output left

next word "the" not in need → reset window
take "foo" → count=1
take "bar" → count=2 → output

Notice: most of the time you’re in a partial state where seen != need, but still valid.

When do you shrink the window?
Only when the seen[word] > need[word] you would be moving left at a time by (L) reducing the counts until the seen[word] <= need[word] again.

In the case when you read a word w that is not in the need then in that case you would be resetting the window. Meaning you would be setting the seen[word] = 0 and the count = 0; and also the left = right + L (your next window starts after the bad word). If you don’t move the left you can accidentally keep the left boundary.

In the case when you reach a word w that is in the need, but now seen[w] becomes 2 while need[w] is 1, you would shrink the window by moving the left counter by one word length at a time which is the L reducing the counts as well until seen[w] <= need[w] again and shrinking works by repeatedly removing the word at the left and then the:
seen[leftWord]--
count--
left += L

This is the key: you always remove from the left one whole word at a time.

In the case when your window has exactly k words you would do the following:
1. Record left as the valid starting index.
2. What you do next to keep sliding. You do not increase the counts further because that would it k+1 and break your bookkeeping. Instead, you advance the window by one word to look for the next possible start:
   1. Remove the word at the left.
   2. Decrement its seen count.
   3. Decrement count.
   4. Move left += L.

Think of it like you found the valid window and now you would slide it forward by one word to search for the next.

Let’s do a quick mental run on this tricky case:

s = "barfoofoo"
words = ["bar","foo"]
Tell me, in words (no code), what happens when you hit the second "foo" (the duplicate) and how left moves.

When the second foo is arrived you would have found a valid window in this case you would be removing the word at the left and then decrement the seen count of the word at the left and then decrement the count and then move left += L by L. And then you would have the seen window as the seen["foo"] = 2 which is actually then invalid as you would be counting up the newly added foo even though the count becomes 2 and then the invariant breaks as the seen(foo) = 2 > need(foo) = 1.

Ok so in the above case you were wrong and you would not be record + slide you would be shrinking to fix the invariant and then step through.
Shrink from left until valid.

Left word is then foo which is the first foo then remove it and then the seen[foo] becomes = 1 and the count becomes 1 which makes the window valid again and then the left moves forward by L again which is how the invariant gets restored.

In short the record step happens when the count = k and the window is valid and then the shrink step happens when the seen[w] > need[w] after adding a word. Both can happen in one scan but the shrink is triggered only the overflow and it happens after the overflow occurs.

Why one offset is NOT enough (this is the trap):

Imagine this string:

s = "xbarfoo"
words = ["bar","foo"]

Valid concatenation starts at index 1.

If you only scan starting at index 0, you will never see it.

The key realization (this is the invariant upgrade):

For a fixed offset:

Every word boundary is aligned.

The window always contains whole words.

Sliding by +L preserves alignment.

But alignment depends on where you start.

There are exactly L possible alignments:

offset 0 → 0, L, 2L, ...
offset 1 → 1, 1+L, 1+2L, ...
...
offset L-1 → L-1, 2L-1, ...

This is NOT extra work because each offset processes disjoint word-boundary paths and the total work across all the offsets is still O(n) and this is the amortized analysis and interviewers love hearing that term.

Mental model that locks it in forever. Think of the string as having L transparent overlays, like this.

