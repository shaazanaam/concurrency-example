76. Minimum Window Substring
Given two strings s and t of lengths m and n respectively return the minimum window substring of s such that every character in t including duplicates is included in the window . 

Problem essence : 
You are given two strings , S the source and T the target . The goal is to find the smallest substring in S that contains all the characters of the T ( including the duplicates)

Key concepts : 
Frequency counter : Track  the frequency of each character in T .
For any window in S ( the substring )  you must check if its  character counts meet or exceed those in T. 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.
Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

Constraints:

m == s.length
n == t.length
1 <= m, n <= 105
s and t consist of uppercase and lowercase English letters.
 

Follow up: Could you find an algorithm that runs in O(m + n) time?

## SLIDING WINDOW
Another Key concept is the sliding window  which is a two pointer approach and one pointer expands the window(right), the other contracts it (left) 
Mathematically you are moving through all the possible intervals [i,j] in S , but efficiently.

## HASH MAPS /Arrays
.. to store character frequencies you will be using the hash map or the array.
.. This  allows O(1) access to check if the current window meets the requirements

## GREEDY MINIMIZATION
  .. once a valid window is found you try to shrink it from the left to find the minimum possible size

## COMPLEXITY ANALYSIS
  .. The optimal solution should be O(|S| +|T|) since each character is processed at most twice ( once  when expanding, once when contracting).

## COMBINATORICS:  COunting occurences and ensuring all the required elements are present 
 Optimization Minimizing the window length 
 Set theory : ENsuring all the elements of the T are covered in the current window.

  You will be translating the problem constraints into mathematical checks

  ## You had the mistake of checking the per character while looping through the T which is the target string

   This is because you would try to act on the window even if one of the characters are not valid  . Instead you should be acting only 
   when the entire window of the characters contain all the charaters of T including the duplicates.
   Per character expansion is not correct becasue you might miss that other required characters are still underrepresented in the window .
   THe window is only valid if all the S[c] >= T[c] for every c in the T simultaneously

   Example :

   Suppose the T="AAB" and you window currently has S['A'] = 2 and S['B'] =0 if you check only S['A'] >= T['A'] then you might think that the window is  valid for A but its not valid for 'B' 
   You  must check all the characters in T before deciding the window is valid and can be shrunk .

   After expanding right you must check the following 
        ∀c∈T:S[c]≥T[c]
  Only if this is true you can try to shrink or expand the window 


  ## Optimized method with the O(m+n) 

   For every movement of the right or the left  pointer you have to loop through the entire T in order to check if the entire window is valid . Instead you can keep a counter of how many required characters are "fully matched" in the window. Only when  all are matched do you try to shrink the window .  This can avoid the repeated full scan of the T for every window move.

   Imagine when you move  the pointer one time what actually changed in the window . When you move a pointer only one character's count changes and then we track the effect of that change.

   As you expand the window keep a counter for how many required characters are fully matched ( WHich is also saying in a way that the  window count is equal to the target count for that character)

   Incremental Validity
   When you add a character check if it just met the requirement ( not every time ) and so when you remove a character you need to check if it lost its validity. Shrink only when valid . Only try to shrink the window  when all the requirments are met ( ie your fully matched counter equals the number of unique required characters )
   
   

6. Generalize the Pattern
This approach works for many “window contains all requirements” problems:
Use a map for requirements.
Use a map for the current window.
Use a counter for “how many requirements are met.”
Expand and shrink the window based on this counter.
7. Practice the Mindset
When solving a new problem, ask:
“Can I track requirements incrementally?”
“Can I use a counter to know when the window is valid?”
“Can I avoid full scans by updating only what changed?”
8. Think in Terms of State
The window’s state is defined by your counters and maps.
Validity is a property of the state, not of a full scan.