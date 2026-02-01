## 395  Longest Substring with Atleast K repeating Characters

Given a string s and an Integer K return the length of the longest substring of s such that the frequency of each character in this substring is greater than or equal to k  if no such substring exists , return 0 

Example 1:

Input: s = "aaabb", k = 3
Output: 3
Explanation: The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input: s = "ababbc", k = 2
Output: 5
Explanation: The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

Constraints:

1 <= s.length <= 104
s consists of only lowercase English letters.
1 <= k <= 105

Questions to Answer (Don't code yet, just think):
Initialize hash map:

What should you count in the first for() loop?
count the frequencies of the characters in the given string
Should you count frequencies of characters in s, or something else?

What is counter?

Does it represent characters that are invalid (freq < k) or **valid** (freq >= k)?
How many unique characters are in the window that don't meet the k requirement?


Expand window ([if(map[s[end++]]-- ?)](http://vscodecontentref/2)):

When you decrement [map[s[end]]](http://vscodecontentref/3), at what value does a character become invalid?
     when we decrement the map[s[end++]--] the character becomes invalid  when the value of map[s[end]] becomes k-1

If a character had k occurrences and you decrement it, it now has k-1 → is it invalid? 
    yes
Should counter increase or decrease?
      When this happens then the counter should increase by 1 and (one more invalid character)
Counter condition (while(/* counter condition */)):

When should you shrink the window?
Should you shrink when counter > 0 (there are invalid chars) or when counter == 0 (all valid)?
    You should shrink when the counter is greater than 0 that is when the window has invalid characters
    
Shrink window ([if(map[s[begin++]]++ ?)](http://vscodecontentref/7)):

When you increment [map[s[begin]]](http://vscodecontentref/8), at what value does a character become valid again?
If a character had k-1 occurrences and you increment it, it now has k → is it valid?
Should counter increase or decrease?
Update result:

When is the window in a valid state to update d?
Should you update inside or outside the while loop?
Are you looking for maximum or minimum length?


## Key insight 

If a character appears less than k times in the whole string , it can never be part of a valid substring .So any substring containing that character is invalid. This problem solving methodology is used in recursive approach with the divide and conquer.

## Divide and conquer approach 
Find characters in s that appear less than k times and use this as split points to break the string into smaller substrings and then recursively solve the problem for each substring 

## Sliding Window /Two pointer 
For each possible number of unique characters (from 1 to 26) use a sliding window to find the longest substring with exactly that many unique characters and all of them appear atleast k times and this is the more advanced but efficient.
For each substring check if all the characters appear at least k times and this is the case then update your answer and if not then split the invalid characters and repeat  for each part .

The answer must be a substring where all characters are repeated atleast k times. If you fix the number of unique characters you can efficiently check all substrings with that property using a sliding window.

### Concept of Unique characters in a window .
     It means how many different letters are present in the current substring (window), not how many times they appear
     For example in the substring "aabb" the substring has 2 unique characters : 'a' and 'b'

#### Why do we care about the unique characters 
     The answer requires all the characters in the substring to appear atleast k times , but the number of different characters in the substring can vary. By fixing the number of unique characters (lets say t ) you can efficiently search for substrings where :
        1. There are exactly t different letters in the window 
        2. Each of those t letters appear atleast k times.

    If you try all possible t ( from 1 to 26) you guarantee you dont miss any possible answer becasue the valid substring could have any nuber of unique letters.
Here you need to keep track of the following

The count of each character in the window and the number of unique characters in the window and the number of characters that appear at least k times in the window . 

## Sliding window ..
You would be using two pointers to expand the window and the left pointer to shrink it when needed 
Keep track of the :
Count of each character in the window and the number of unique characters in the window and the number of characters that appear atleast k times in the window 
So when the window has exactly t unique characters and all of them appear atleast k times update your answer  with the windows length 


Steps for t = 1 to 26 reset your window and counts and then 
    1. expand the window with the right pointer 
    2. If the number of unique characters exceeds t move the left pointer to reduce it 
    3. Each time the window has exactly t unique characters and all of them appear at least k times check if its  the longest so far.

    This approach avoids checking all the substrings naively .


Unique Character Count:
You need a variable (let’s call it unique) to track the number of unique characters in the window.
When map[s[end]] == 0 before incrementing, increment unique.
atLeastKcount:
This should be incremented only when map[s[end]] becomes exactly k after incrementing (not before).
Similarly, when shrinking, decrement atLeastKcount if a character’s count drops from k to k-1.
Window Expansion:
Always increment map[s[end]] and then end++.
If unique > i (your target), shrink from the left:
If map[s[begin]] == k before decrementing, decrement atLeastKcount.
Decrement map[s[begin]].
If map[s[begin]] == 0 after decrementing, decrement unique.
Then increment begin.
Valid Window:
If unique == i and atLeastKcount == i, update your answer with the window’s length.
Reset:
Reset map, unique, and atLeastKcount for each i.
Return:
Return the maximum length found.
You need a variable to track the number of unique characters in the window (let’s call it unique).
You need to increment unique when map[s[end]] is 0 before incrementing.
You need to increment atLeastKcount only when map[s[end]] becomes k after incrementing.
When shrinking the window (if unique > i), you need to:
Decrement atLeastKcount if map[s[begin]] is k before decrementing.
Decrement unique if map[s[begin]] becomes 0 after decrementing.
Decrement map[s[begin]] and increment begin.
You need to check if unique == i and atLeastKcount == i, and then update your answer.
You need to reset map, unique, and atLeastKcount for each i.
You need to return the maximum length found.