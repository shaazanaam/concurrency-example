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
  .. once a valid window is found you try to shrink it from the left to find the minimum possible size.

## COMPLEXITY ANALYSIS
.. The optimal solution should be O(|S| +|T|) since each character is processed at most twice ( once  when expanding, once when contracting).

## COMBINATORICS:  Counting occurences and ensuring all the required elements are present 
Optimization Minimizing the window length 
Set theory : ENsuring all the elements of the T are covered in the current window. You will be translating the problem constraints into mathematical checks

## You made the mistake of checking the per character while looping through the T which is the target string

This is because you would try to act on the window even if one of the characters are not valid. Instead you should be acting only when the entire window of the characters contain all the charaters of T including the duplicates.
Per character expansion is not correct becasue you might miss that other required characters are still underrepresented in the window .
The window is only valid if all the S[c] >= T[c] for every c in the T simultaneously

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


Here’s a side‑by‑side mapping of your approach vs his, with the “missing leap” you didn’t think of, in coach style and visualization‑focused:

1) Frequency tracking
You: Two hash maps (T and S)
Him: One fixed array need[128]

Coach insight:
He collapses both “target” and “window” into one array.

## Counter Value:

Positive value = still need this character
Zero           = exactly satisfied
Negative       = extra in window
This removes one entire structure and cuts overhead.
2) Validity condition
You: Track matchedCount vs T.size() ( chars matched)
Him: Track required = total characters left (including duplicates)

Coach insight:
This is the big conceptual shift.
Instead of “How many unique characters are matched?”, he asks:
“How many total characters are still missing?”
This removes the duplicate complexity entirely and avoids scanning T.

3) Expand window
You: Add char → compare against T → update matchedCount
Him: Add char → if need > 0 (map[s[end++]]-->0) then required--(counter--) → need--

Coach insight:
He uses the state of the need array to decide instantly if a character was actually needed.
No map lookup + no loop. Just O(1) transition.

4) Shrink window
You: If valid, shrink; adjust matchedCount if dropping below
Him: If valid (required==0), shrink; if need++ becomes >0 then required++

Coach insight:
He uses the same “need array” to detect exactly when the window becomes invalid again.
No separate logic for duplicates—just one invariant.

5) Minimal window update
You: Update when window valid
Him: Same, but validity is O(1)

Coach insight:
You both do the right idea, but he made validity check constant time.

What You Didn’t Think Of (The Core Mental Leap)
He treats the target frequency array as a “debt ledger.”

If need[c] > 0: you still owe c
When you take a character, you pay off debt
When you give a character back (shrink), debt increases
required is the total debt remaining
Visualization:
You’re balancing a budget.
He never re-checks the full budget; he only updates the balance.

How to Train This Thinking
Ask: “Can I track a single variable instead of scanning?”
Ask: “Can I encode both target + window in one structure?”
Practice converting “validity = all conditions met” into a single scalar invariant.
If you want, I can map your current code line‑by‑line to the exact role in his solution and show you where the state compresses.

Single variable              : required (remaining total characters needed, including duplicates).
Single structure             :need[128] (starts as target counts, then is updated as the window grows/shrinks, so it represents both target and window state).
Scalar invariant for validity: required == 0 (all required characters are satisfied).

 There is a template you can use for this kind of problems and then beyond which you can see if in the problem for the subarray sum equals K if you can see it results in the value or not


 The code of solving this problem is below. It might be the shortest among all solutions provided in Discuss.

string minWindow(string s, string t) {
        vector<int> map(128,0);
        for(auto c: t) map[c]++;
        int counter=t.size(), begin=0, end=0, d=INT_MAX, head=0;
        while(end<s.size()){
            if(map[s[end++]]-->0) counter--; //in t
            while(counter==0){ //valid
                if(end-begin<d)  d=end-(head=begin);
                if(map[s[begin++]]++==0) counter++;  //make it invalid
            }  
        }
        return d==INT_MAX? "":s.substr(head, d);
    }

     this is the solution to the problem we have had and then this is the template for the proble 

int findSubstring(string s){
        vector<int> map(128,0);
        int counter; // check whether the substring is valid
        int begin=0, end=0; //two pointers, one point to tail and one  head
        int d; //the length of substring

        for() { /* initialize the hash map here */ }

        while(end<s.size()){

            if(map[s[end++]]-- ?){  /* modify counter here */ }

            while(/* counter condition */){ 
                 
                 /* update d here if finding minimum*/

                //increase begin to make it invalid/valid again
                
                if(map[s[begin++]]++ ?){ /*modify counter here*/ }
            }  

            /* update d here if finding maximum*/
        }
        return d;
  }
One thing needs to be mentioned is that when asked to find maximum substring, we should update maximum after the inner while loop to guarantee that the substring is valid. On the other hand, when asked to find minimum substring, we should update minimum inside the inner while loop.

Below is  the code for solving the Longest Substring with At Most two Distinct Characters is below 

int lenghtOfLongestSubstringTwoDistinct(string s){
  vector map<int> (128,0);
  int counter = 0, begin = 0 , end =0, d=0;
  while (end<s.size()>){
    if(map[s[end++]]++==0) counter++;
    while(counter >2) if (map[s[begin++]]--==1) counter --;
    d= max(d,end-begin);
  }
  return d;
}

int lengthOfLongestSubstring(string s) {
        vector<int> map(128,0);
        int counter=0, begin=0, end=0, d=0; 
        while(end<s.size()){
            if(map[s[end++]]++>0) counter++; 
            while(counter>0) if(map[s[begin++]]-->1) counter--;
            d=max(d, end-begin); //while valid, update d
        }
        return d;
    }


1. Use two pointers: start and end to represent a window.
2. Move end to find a valid window.
3. When a valid window is found, move start to find a smaller window.

To check if the window is valid we use a map to store the (char. count) for the chars in t . And use the counter  for the numbers of char t to be found in s.

the key part is the map[s[end]]--; we decrease the count for each char in  s . If it doesnt exist in t the  count will be negative.
To really understand this algorithm see the code below 
if(map[s[end++]]++>0)  counter++;

string minWindow(string s, string t) {
unordered_map<char, int> m;
// Statistic for count of char in t
for (auto c : t) m[c]++;
// counter represents the number of chars of t to be found in s.
size_t start = 0, end = 0, counter = t.size(), minStart = 0, minLen = INT_MAX;
size_t size = s.size();

// Move end to find a valid window.
while (end < size) {
  // If char in s exists in t, decrease counter
  if (m[s[end]] > 0)
    counter--;
  // Decrease m[s[end]]. If char does not exist in t, m[s[end]] will be negative.
  m[s[end]]--;
  end++;
  // When we found a valid window, move start to find smaller window.
  while (counter == 0) {
    if (end - start < minLen) {
      minStart = start;
      minLen = end - start;
    }
    m[s[start]]++;
    // When char exists in t, increase counter.
    if (m[s[start]] > 0)
      counter++;
    start++;
  }
}
if (minLen != INT_MAX)
  return s.substr(minStart, minLen);
return "";
}

in a dynamic sliding window there is the conditon given below 

intialize left =0;
initialize the window_state(sum, count, frequency map, etc)
initialize min_or_max_result

for right from 0 to arr.length -1:
  update window_state to include arr[right]  #expand the window

  while window_state violates the condition:
     update min_orMax_result(if needed)
     update window_state to exclude arr[left]  # Shrink the window 
     move left pointer forward

 return min_or_max_result



 while the window state is violating the condition shrink it until it violates the condition and then update the min or max result and then update the window state to exclude the arr[left]
 that is update the window state and  then the result according ly 


  For example if you are given an integer array nums and an integer k find the maximum average of any contiguous subarray of size k 

  [1,12,-5,-6,50,3] k=4

   find  the maximum average of any subarray of size k.

    the brute force in this case will be iterating through  every possible subarray of size k calculating its sum and then determining the maximum sum.
    After processing all the subarrays divide the maximum sum by k to get the maximum average

## BRUTE FORCE
    public static double findMaxAverage(int[] nums , int k ){
      int n = nums.length;
      int maxSum = Integer.Min_Value;
       //iterate through all the possible subarrays of length k 
       for(int i = 0; i<=n-k;i++){
        int sum = 0;
        //Calculate the sum of the subarray starting at index i 
          for (int j = i;j<i+k;j++>){
            sum+= nums[j];
          }
          maxSum = Math.max(maxSum, sum);
       }
       return (double) maxSum/k

    }

## SLiding window approach 

    calculate the sum of the first k elements of the window 

    and the add the elements  as you move right and then as you move left you subtract the  element and determine the maxSumn



    public static double findMaxAverage(int[] nums , int k){
      int n = nums.length;

      // compute the sum of the first k elements 
      int sum =0;
      for(int i =0; i<k ;i++){
        sum+= nums[i];
      }
      //intialize the maxSum as the sum of the first window 
      int maxSum = sum;

      //Slide the window across the array

      for(int i = k ;i<n; i++){
        sum -=num[i];;  remove elements leaving the window
        sum += nums[i-k]; // add new elements entering the window 

        // you can find the left most elements by going back k positions later
        maxSum = Math.max(maxSum, sum);   // update the maxSum 
      }

      return (double) maxSum/k;
    }

    in this case  we  get rid of each element only once which reduces the time complexity to O(n)

##  Given the string find the length of the longest substring that doesnt contain any repeating characters

we will be using a dynamic window which will expand if all the characters are unique and will shrink when the duplicate characters are found...

 Each substring fits into one of the two  categories:
 1. it contains only unique characters. in this case we should expand the  window by advancing the right pointer that also contains no duplicates
 2. it contains the duplicatess. In this case we should shrink the window by advancing the left pointer until the window no longer contains the duplicate


to efficiently check for the duplicate characters we use an uoprdered map or vector..

initialize two pointers left and right to the first character of the string but it will be representing the boundaries of the substring . Both array will be starting at the index 0.

 Use the hashset to store the contents of the current window for a quick look ups of the duplicate.
 expand the window by moving the right pointer and then add in the  current character to the hash set.
if the current character is already in the hash set then it indicates a duplicate then you would simply shrink the window by moving the left pointer forward.

 remove the character from the hash set until the duplicate is removed


this ensures that the substring remains valid containing only the unique characters

after each adjustment calculate the length of the substring  and update the maximum length if needed 

continue until the right pointer is at the end of the string

  you can use the for loop  to loop over the string with the right pointer 
  initialize the left pointer to =0 and then also initialize the maxLength =0;
for loop will be expanding the window one at a time and if duplicate is found  which means that the character already exists in the set  then shrink the window from the left by removing the left most character from the set and then incrementing the left pointer  .

After adjusting the window then add the  current character to the set. calculate the length of the current substring and the update the maxLength if necessary.
Once the right pointer reaches the end of the string  return the max length .

 The time complexity of  this approach is of the order of n O(n)., Since each character is processed at most twice once when its added to window and once when its removed from the window.
 The space complexity is of the order of k where k represents the size of the hash set and in the worst case senario the hasset stores all the unique characters of the string