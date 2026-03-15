2405. Optimal Partition of String

Given a string s, partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once.

Return the minimum number of substrings in such a partition.

Note that each character should belong to exactly one substring in a partition.

 

Example 1:

Input: s = "abacaba"
Output: 4
Explanation:
Two possible partitions are ("a","ba","cab","a") and ("ab","a","ca","ba").
It can be shown that 4 is the minimum number of substrings needed.
Example 2:

Input: s = "ssssss"
Output: 6
Explanation:
The only valid partition is ("s","s","s","s","s","s").
 

Constraints:

1 <= s.length <= 105
s consists of only English lowercase letters.


Hint 1 
Try to come up with a greedy approach
Hint 2 
From left to right extend every substring in the partition as much as possible 

## You are finding the duplicate when the prev>=L 

And  in this case you would  be wanting to create a new partition and then the duplicate is found . You would be starting a new partition at the current character so it should be 
start =R and partitions++

 if you update the L=prev+1 if wont reset the partition at the current character.

 Initial method you were adding a substring to ans on every iteration  . But you should only need to start a new partition when   you find a duplicate character in the current substring .

 Wrong sliding window update when the prev>=L you just move L forward but instead you should actually complete the current partition and start a new one at that point .
 You were also building actual substrings with the s.substr() but you only need to count partitions

 ## Correct Approach 

 The algorithm should track the characters in the current partition using a set/bitset

 When  you find a duplicate iincrement the partiton count and reset the tracking and then start a new partition and here is what it should look like 

int partitionString(string s){
vector<int> last (256,-1);
int L = 0;
vector<string> ans;
for (size_t R =0; R,s.size(); ++R){
int prev = last[(unsigned char)s[R]];
if (prev >=L){
L=prev+1;


 You would be counting the partition only when you found the duplicates and then use the unordered_set to track the characters in the current partition and then remove the unnecessary substring operations O((n)) time , O(1) space excluding the set 

 Start with the 1 partition and for each character check if its already in the current partition and if yes increment 

 unordered_set<int> seen;
 int partitiono = 1;
 for (char c :s){
    if(seen.count(c)){
        partitions++;
        seen.clear();  // when you are finding the duplicate you are ressetting the tracking and then start a new partition and this is how this looks. If a character is in the current partition then increment the partition count and clear the set (start new partition)
        If no then add it to the current partition

        If no then add it to the current partiton 

        seen.insert(c)
    }
 }

or s = "abacaba", valid minimum is 4, for example:

"ab" | "ac" | "ab" | "a"
or
"a" | "ba" | "cab" | "a"

## The issues with this code 

int partitionString(string s){
vector<int> last (256,-1);
int L = 0;
vector<string> ans;
for (size_t R =0; R,s.size(); ++R){
int prev = last[(unsigned char)s[R]];
if (prev >=L){
L=prev+1;


This is behaving like a sliding window length algorithm so it can over split and instead you would need to have the duplicates start a new partition at the current index which matches the problem rule .

You did L= prev+1 upon finding a duplicate and that was for the sliging window longest substring logic and not for the minimum partition count. In this problem when a duplicate is found  in the current partition you must start a new partition at the current character so it should be 

L =R and partitions++


## What  happens on the example "shkqbyutdvknyrpjof"

Indexes :
0:s 1:h 2:k 3:q 4:b 5:y 6:u 7:t 8:d 9:v 10:k 11:n 12:y 13:r 14:p 15:j 16:o 17:f


### Correct partition behavior 
Goal when the duplicate appears in the current partition cut before the current char and then start a new partition at current char

1. Start partition 1 at index 0 
[s h k q b y u t d v]

2. At index 10 char k repeats (k was at the index 2 in the same partition so cut:)

Partition 1 = shkqbyutdv

3. Start partition 2 at index 10:
[k n y r p j o f] (no duplicates)


Result 2 partitions.

## Why the old logic gave 3

Old code used sliding window update:
L= prev +1 when duplicate is found 

At R=10(k):
    1. prev=2 so L=3 and partitions =2

At R=12(y):
    1. prev=5
    2. Since 5>=L(3) old code thinks y is still in the current window so it increments again and then L=6 , partitions =3

That is the over counting of the isse and then the L=prev +1 means that shrink the window to remvoe the old duplciate which is good for the longest substring problems and then the start =R means close the current partition begin fresh at this char which is the correct approach for this partitioning problem ..


## GREEDY APPROACH 

This approach is greedy because this is looking  for the locally optimal choice and if the character is not in the current partition keep extending the current partitiona and if its already present you cut immediately and then start a new partition at this character .


## Why this gives the minumum number of partitions 
1. this is becasue you only cut when forces as the cut happens only when adding the current char would violate the uniqueness and so every cut is necessary.
2. Delaying a forced cut is impossible 
     If s[i] already exists in the current partiton any partiton that includes both occurences is invalid so a boundary must appear  at or before i .

3. Extending each partition maximally cant hurt.
     Making the partition longer while valid cannot increase future options ; it only avoids extra early cuts .Any solution that cuts earlier without necessity can be transformed into one with no more cuts by merging that unnecessary split 

So the algorithm is optimal by cut only when required and that is exactly the greedy choice property for this problem 


Think of each partition as pack as many unique chars as possible and if you ever split earlier than needed you are spending one extra partion for no reason adn there for the minimum is achieved by maximal valid segments