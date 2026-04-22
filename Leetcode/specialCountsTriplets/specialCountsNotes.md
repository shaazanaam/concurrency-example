You are given an integer array nums.

A special triplet is defined as a triplet of indices (i, j, k) such that:

0 <= i < j < k < n, where n = nums.length
nums[i] == nums[j] * 2
nums[k] == nums[j] * 2
Return the total number of special triplets in the array.

Since the answer may be large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [6,3,6]

Output: 1

Explanation:

The only special triplet is (i, j, k) = (0, 1, 2), where:

nums[0] = 6, nums[1] = 3, nums[2] = 6
nums[0] = nums[1] * 2 = 3 * 2 = 6
nums[2] = nums[1] * 2 = 3 * 2 = 6
Example 2:

Input: nums = [0,1,0,0]

Output: 1

Explanation:

The only special triplet is (i, j, k) = (0, 2, 3), where:

nums[0] = 0, nums[2] = 0, nums[3] = 0
nums[0] = nums[2] * 2 = 0 * 2 = 0
nums[3] = nums[2] * 2 = 0 * 2 = 0
Example 3:

Input: nums = [8,4,2,8,4]

Output: 2

Explanation:

There are exactly two special triplets:

(i, j, k) = (0, 1, 3)
nums[0] = 8, nums[1] = 4, nums[3] = 8
nums[0] = nums[1] * 2 = 4 * 2 = 8
nums[3] = nums[1] * 2 = 4 * 2 = 8
(i, j, k) = (1, 2, 4)
nums[1] = 4, nums[2] = 2, nums[4] = 4
nums[1] = nums[2] * 2 = 2 * 2 = 4
nums[4] = nums[2] * 2 = 2 * 2 = 4
 

Constraints:

3 <= n == nums.length <= 105
0 <= nums[i] <= 105


HINT:

    Use Frequency arrays or maps, eg freqPrev and freqNext - to track how many times each value appeards before and after the current index

    For each index j in the triplet (i,j,k), compute its contribution to the answer using your freqPrev and freqNext counts.

## Genenral Discussion 
 This is not a sliding window problem   and then each iterations you would be removing the nums[j] from the right map 
 1. Query counts from both sides and then 
 2. Add combinations 
 3. Insert nums[j] into the left map

  Why this is not a sliding window problem :
  sliding window requires two pointers that define a contigious range 
  A window that expands and contracts

There is no window 
There is no shrinking 
Only counting across  partitions 
there is no shrinking 
Correct classification of this style of problem is :

" this is the frequency based  counting problem where each index is treated as a fixed 
middle , using prefix and suffix frequency maps"

## Think of j As the  divider moving left to right 
 and then you have the following structure
 [ elements before j ]   [ nums[j] ]   [ elements after j ]
       left              current             right
     freqPrev              x                freqNext


The goal is to count the triplets where the following is true:

i < j < k
nums[i] == nums[j] * 2
nums[k] == nums[j] * 2


So when then nums[j]=x , we need the target = 2*x

Then we ask 
prevCount = how many target values exist on the left?
nextCount = how many target values exist on the right?


Each left match can pair each right match , so 
ans+ = prevCount * nextCount;

## The confusing part is this order 
freqNext[x]--;  remove the current j from the right
query the left/right
freqPrev[x]++//  add current j to the left

The above order exist because while processing j , nums[j] should be in neither side 
During this  exact moment 
left side:  indices < j
current:    index j
right side: indices > j

when the execution falls through the x= nums[j] then all it does it goes through the next step and makes sure it gets removed from the freqNext and then its also not entered to the freqPrev yet .  which this is the state we then go ahead and then check for the availability of the target at both the sides and then go ahead and note it down in our answer counts.If we would not have removed the nums[j] from the freqNext then originally the freqNext contains the whole array then the right map would be incorrectly including the current middle element as if it were a future k.

then after  counting the triplets with this j we add the nums[j] into the freqPrev, because for the next iteration this current element will now be on the left .

nums = [2, 1, 2]

freqPrev = {}
freqNext = {2:2, 1:1}

At j =0, x=2

current = nums[0] = 2
Remove current from the right
freqPrev = {}
freqNext = {2:1, 1:1}

Need the target as 2*2 which is 4 

left has 4?  0
right has 4? 0
add 0 * 0

Now move the current into the left
freqPrev = {2:1}
freqNext = {2:1, 1:1}

At j=1, x=1:
Before query remove current from the right
freqPrev = {2:1}
current = 1
freqNext = {2:1, 1:0}

Need Target =2
left has 2?  1
right has 2? 1

So there is 
i = 0, j = 1, k = 2
nums[i] = 2
nums[j] = 1
nums[k] = 2
which is a valid triplet because
2 == 1 * 2
2 == 1 * 2
Then the ans += 1*1

After that move the current  to the left 
freqPrev = {2:1, 1:1}
freqNext = {2:1, 1:0}


 Then the mental picture is :

 Before loop starts:
left  = empty
right = whole array

For each j:
1. Take nums[j] out of right
2. Count valid left choices and right choices
3. Put nums[j] into left for future iterations


So we are not dumping it on the left map before using it for the current j and calculating for the count match and then we would be dumping it on the left only after the query  because it becomes a previous element only for future middle positions


## the compressed idea for the brain is 
For each j the current element must stand in the doorway and it cannot be inside the left room . It also cannot be inside the right room and only after we finish checking it it walks into the left room

So basically the loop is doing this 

freqNext[x]--;   // remove current from the future room
count answer     // current is now isolated as j
freqPrev[x]++;   // move current into the past room


Mental Diagram 
Imagine the array as a conveyor belt

nums = [ 2, 1, 2, 1, 2 ]


At the begining everything is still in the future 

PAST / LEFT          CURRENT          FUTURE / RIGHT

freqPrev = {}                         freqNext = {2:3, 1:2}


# Now suppose that the j is at the index 1:
nums = [ 2, 1, 2, 1, 2 ]
         ^  ^
         i  j

# Before processing the j=1 the situation should be 

PAST / LEFT          CURRENT          FUTURE / RIGHT

[ 2 ]                  [ 1 ]              [ 2, 1, 2 ]

## that means that the map must be representing the following 

freqPrev = {2:1}
freqNext = {2:2, 1:1}

For the x = nums[j] = 1, we need:

target = 2 * x = 2

How many 2s are in the past?   1
How many 2s are in the future? 2


# That gives 

1*2 = 2 triplets

# Visually 

PAST                 CURRENT              FUTURE

[ 2 ]                  [ 1 ]              [ 2, 1, 2 ]
  |                     |                   |     |
  +---------------------+-------------------+     valid
  +---------------------+------------------------- valid


(0, 1, 2)
(0, 1, 4)

# Now here is the dangerous version if you do not remove the current item from the freqNext , then when j=1, the right map still thinks that the current 1 is in the future

WRONG FUTURE MAP

PAST / LEFT          CURRENT          FUTURE / RIGHT

[ 2 ]                  [ 1 ]              [ 1, 2, 1, 2 ]
                         ^                  ^
                         same item counted as future


# the current element which is the num[j] is being counted for the two roles and num[j] is in the middle and is also pretending to be on the right side 


This breaks the rule i<j<k Because  k must be after j 
The map does not know about the positions . It only knows counts so if you leave the nums[j] inside the freqNext the map may accidentally say

"Yes I have a future value" 

Even when that value is actually the current middle element 
Tiny Example where it clearly Breaks 

nums =[1]
Initial
freqPrev = {}
freqNext = {1:1}

At j= 0 
current = 1
If you do not remove it then 

freqNext still has {1:1}
PAST          CURRENT          FUTURE

[]              [1]              [1]   <- fake future copy

But the actual array has no future index 0  so correctly removing first gives 

PAST          CURRENT          FUTURE

[]              [1]              []


That is the real world 

The Doorway Analogy

Imagine people are moving through a security checkpoint.

There are three areas:

Already checked room     Security checkpoint     Waiting room
       left                    current              right


## At the start every one is in the waiting room 

left room:     empty
checkpoint:    nobody yet
waiting room:  everyone

When the person step up to the check point then they must be remvoed from the waiting room first
Why ? because while they are being checked they are no longer waiting so the process is remove the person from the waiting room. Inspect them at the check point and after inspection move into the already checked room 

## Translated back to the code 
freqNext[x]--;   // no longer waiting in the future
query maps       // currently being inspected as nums[j]
freqPrev[x]++;   // now belongs to the past

## The compressed momory phrase 

Current j is at the checkpoint, not in either room.
Remove from future, count, then add to past.

Future -> Current -> Past


That is the whole methodology 

## WHy the query happens in between . the query must happen when the world looks like this 

left has only indices < j
right has only indices > j
current is isolated


## So the valid order is 
right removes j
count using left and right
left receives j


# Diagram

Step 0: before processing j

LEFT                  RIGHT
[0 ... j-1]           [j ... n-1]
                       ^
                       current is still wrongly inside right


Step 1: remove nums[j] from right

LEFT                  CURRENT                  RIGHT
[0 ... j-1]             [j]                    [j+1 ... n-1]


Step 2: query

Look left for nums[i] == 2 * nums[j]
Look right for nums[k] == 2 * nums[j]


Step 3: move current into left

LEFT                                  RIGHT
[0 ... j]                             [j+1 ... n-1]

Before counting for j:
freqPrev = counts of elements strictly before j
freqNext = counts of elements strictly after j


## The word strictly is the key
freqPrev: i < j
freqNext: k > j

# So the loop order exists only to maintain this truth 

freqNext[x]--;        // makes right strictly after j
// count
freqPrev[x]++;        // prepares left for next j
