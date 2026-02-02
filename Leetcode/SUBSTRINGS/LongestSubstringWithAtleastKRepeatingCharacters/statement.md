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


## Approach 1 Vs Approach 2

Initialize the map by counting all the characters in the entire string . As you slide the window you decrement from these counts  . Then in this case the counter tracks the characters whose remaining count drops below . The problem is that this doesnt represent the window validity as it only represents how many characters are exhausted from the full string 

# Approach 2 Window only count 
 Do not initialize the map by counting the  full string but start with the empty map and then as you expand the end you increment the ocunts for the characters entering the window . and as you shring begin you decrement the couonts for the characters leaving the window . 
 Counter correctly tracks the invalid characters inside the current window .  
