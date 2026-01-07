## 992 Subarrays with K Different Integers
Given an integer array nums and an integer k, return the number of good subarrays of nums

A good array is an array where the number of different integers in that array is exactly k
.. For example [1,2,3,1,2] has 3 different integers 1,2,3..
A subarray is a contigious part of an array 

Input nums =[1,2,1,2,3], k= 2
Output: 7
Explanation : Subarrays formed with exactly 2 different integers :[1,2], [2,1] ,[1,2],[2,3],[1,2,1],[2,1,2], [1,2,1,2]

Example 2:
Input : nums =[1,2,1,3,4] k=3
Output :3
Explanation : Subarrrays formed with exactly different integers:[1,2,1,3],[2,1,3], [1,3,4]


Hint 1 
Try generating all the possible subarrays and check for the number of unique integers . Increment the count accordingly
Use a map to store the count of integers
Use the sliding window and the 2  pointer approach

## BRUTE FORCE
Generate ALL subarrays + count distinct

Start i = 0

[1] → distinct = {1} = 1 ❌

[1,2] → {1,2} = 2 ✅

[1,2,1] → {1,2} = 2 ✅

[1,2,1,2] → {1,2} = 2 ✅

[1,2,1,2,3] → {1,2,3} = 3 ❌

✅ count so far = 3

Start i = 1

[2] → {2} = 1 ❌

[2,1] → {2,1} = 2 ✅

[2,1,2] → {2,1} = 2 ✅

[2,1,2,3] → {1,2,3} = 3 ❌

✅ count so far = 3 + 2 = 5

Start i = 2

[1] → {1} = 1 ❌

[1,2] → {1,2} = 2 ✅

[1,2,3] → {1,2,3} = 3 ❌

✅ count so far = 5 + 1 = 6

Start i = 3

[2] → {2} = 1 ❌

[2,3] → {2,3} = 2 ✅

✅ count so far = 6 + 1 = 7

Start i = 4

[3] → {3} = 1 ❌

Final ✅ = 7
Matches the answer.

Brute force approach is Pick a start i then keep a set/map of counts and the extend end j from i->n-1 and then track the disctinct count  each time . If distint==k, increment answer.. the problem is that it checks upto 15 subarrays for the n=5 for n=20000 its ~ 200 million subarrays and will become too slow .so the sliding window is just a way to avoid recounting distinct elements for every subarray..

Key point to notice from the brute force pattern is that for a fixed start i as you extend j the distinct count only stays same or increases and  once it becomes 3 it will  never go back to 2 unless you move i.. that monotonic behavior is what the sliding window exploits. Monotonic behavoiur means that you have one defined boundary where the 


KEY MENTAL TAKEAWAY 
total sub arrays are counted by fixing the start index and counting how many valid end positions exist. A sub array is defined by start i and end j (i<=j)  So we generate all the pairs (i,j) and then list the subarray.
There are n(n+1)/2 sub array = 15 total subarrays


For an array of length L the number of subarrays are actually n(n+1)/2..
Key idea fix the start and then count all the possible ends
Start at 0 => 5 sub arrays
Start at 1 => 4 sub arrays
Start at 2 => 3 sub arrays
Start at 3 => 2 sub arrays
Start at 4 => 1 sub arrays


FLIP THE PERSPECTIVE:::: 
Instead of fixing th estart lets fix the end...
Same array( length 5)
index: 0 1 2 3 4 5

End at  index 0.... Possible starts 0->[0..0]-> 1 subarray
End at  index 0.... Possible starts 0->[0..1]-> 1 subarray

What does it mean checking distincts actually mean .. When wew say the number of distinct elements in the window we mean how many different values currently appear at least once in the window. 

 The sliding window works because adding can only keep or increase distinct , removing can only keep or decrease distinct. That predictable behaviour is what allows us to control the window.
 

This is **now correct for maintaining the invariant** (✅ “window has at most k distinct” after the while loop). Your `distinct++` placement is right, and your shrink logic is right.

But you’re still returning the wrong thing.

## What you’ve built so far

You’ve built a function that, after the loop ends, leaves you with:

* `L` and `R` at the end
* `distinct` = distinct count in the **final window only**

That is **not** “number of subarrays”.

So:

### ❌ `return distinct;` is wrong

Because the answer is not “how many distinct are in the last window”.

---

## What you must add (conceptually)

You need an accumulator, say `ans`.

At each `R`, once you’ve shrunk until `distinct <= k`, you can count **how many valid subarrays end at this R**:

* valid starts are `L, L+1, ..., R`
* number of them is `R - L + 1`

So after the while loop, you do:

> `ans += (R - L + 1)`

Then at the end:

> return `ans`

That’s the missing bulk counting step.

---

## One more important detail

Use a 64-bit count for `ans` (like `long long`) because subarray counts can be large.

---

## Tiny sanity test (run in your head)

`nums = [1,1,1]`, `k=1`

AtMost(1) should be 6 total subarrays.

With your current code, what would you return?

* `distinct` ends as 1
* but correct answer is 6

That shows exactly what’s missing.

---

### Next step (quick)

Add the accumulator and the `R - L + 1` counting step, and rename this helper mentally as `atMostK`.

Then you’ll compute:

* `exactlyK = atMostK(k) - atMostK(k-1)`

If you paste your next revision, I’ll only check the counting line placement and any off-by-one issues.
 
 
 
 
 
 
You *can* keep it as **one public function** and still use the **atMost(k) − atMost(k−1)** idea. The cleanest way is:

* **one public function** `subarraysWithKDistinct`
* inside it, compute two counts: `atMost(k)` and `atMost(k-1)`
* return the difference

### Should you add *another while loop with distinct > (k-1)* inside the same scan?

You *could*, but not as “another while loop after the first one” using the same `L/distinct/map`. That will tangle your invariants.

If you want “one function doing it all” *without* a separate helper function, the interview-friendly way is:

## Best single-function structure: two windows in parallel

Maintain **two sliding windows at the same time**, both moving with the same `R`:

* Window A tracks **at most k** (with `L1`, `freq1`, `distinct1`)
* Window B tracks **at most k−1** (with `L2`, `freq2`, `distinct2`)

For each `R`:

1. Add `nums[R]` to both maps + update distincts (0→1 rule)
2. While `distinct1 > k` shrink `L1`
3. While `distinct2 > k-1` shrink `L2`
4. Now:

   * subarrays ending at `R` with ≤k = `R - L1 + 1`
   * subarrays ending at `R` with ≤(k−1) = `R - L2 + 1`
   * so subarrays ending at `R` with **exactly k** =
     [
     (R-L1+1) - (R-L2+1) = L2 - L1
     ]
5. Add `L2 - L1` to your answer.

### Why this works (quick visual)

At a fixed `R`:

* starts ≥ `L1` give you **≤ k**
* starts ≥ `L2` give you **≤ k−1** (stricter, so `L2` is to the right of `L1`)
* the starts that are in `[L1 .. L2-1]` are **exactly k**

So you count that middle band by `L2 - L1`.

---

### What NOT to do

* Don’t try to reuse the same `L` and `freq` and just “change k” mid-loop.
* Don’t do one while loop and then another while loop for k−1 using the same state.

---

If you want to proceed without me writing code: tell me what variables you’d maintain for the **two windows** (names are fine), and I’ll check if your setup will correctly track both invariants.



