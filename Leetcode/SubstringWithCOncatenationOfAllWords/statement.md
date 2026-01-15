
30. Substring with Concatenation of All Words

Given is the string s and an array of strings words . All the string of words are of the same length.  A concatenated string is a string that exactly contains all the strings of any permutation of words concatenated.

For example if words =["ab", "cd", "ef"] then "abcdef" ,"abefcd", "cdabef","cdefab", "efabcd", and "efcdab" are all concatenated strings .
"acdbef" is not a concatenated string becasue it is not the concatenation of any permutation of words

Return an  array of the starting indices of all the concatenated substrings in s. You can  return the answer in any order 

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

1 <= s.length <= 104
1 <= words.length <= 5000
1 <= words[i].length <= 30
s and words[i] consist of lowercase English letters.


Create a set to keep track of all previously encountered and validated strings. During the sliding window traversal, if a string is already in the set, directly add its index to the result without performing any further checks. This approach increases memory usage but allows you to efficiently skip redundant processing, which helps in passing the 178/179 test cases


This is basically a sliding Window on the word boundaries (aka multi offset / modular sliding window) + HashMap frequency counting 

Since every word has the same lenght L you dont slide 1 char at a time -- you slide L characters at a time and you run the window starting from each offset ..
And then you run the window starting from each offset 0....L-1.

Why your cache validated strings in a set idea is risky..
      The idea that you are proposing is that you can  keep track of all the peviously encountered and validated strings. During the sliding window traversal , if a string is already in the set , directly add its index to the result without performing any further checks. This approach will be increasing the memory usage but will aloow you to efficiently  skip redundant processing which helps in passing the 178/179 test cases 

      Baically your idea is that you store each of the already validated  concatenation substring in a set and then if you see it again accept it immediately.
     
      This is more of a sliding window on window boundaries ( aks multio offset / modular sliding window ) + HashMap frequency counting .
      Key idea :  since every word has the same length L, you dont slide 1 character at a time -- you slide L characters at a time and you run the window starting from each offset 0...L-1.

      1. Memory blow up: Validated substrings are length L*k ( can be huge) and there can be O(n) of then wich is a lot of memory
      Copy cost still exists to chekc the set you still need to create the substring ( or compute a harsh)--- which is  most of the work.

      2.Copy cost still exists : To check the set you still need to create the substring ( or compute a hash) which is most of the work

      3. Doesnt  fix the real bottle neck .k The correct chekc avoids redundant checks structureally using the word aligned sliding window . thats why it passes all the cases cleanly..


       SO CACHING IS A BANDAID BUT THE REAL FAAANG SOLUTION IS THE MULTIOFFSET SLIDING WINDOW,

       SO THIS IS THE METHODLOGY FOR THE WORD ALIGNED SLIDING WINDOW

        window is [LEFT-- right ]  moving in the steps of L
        seen[word] counts the words inside the current window
        if the seen[word] >need[word] shrink from the left until valid again
        when the window contains exactly k words, record left


 You will be  having two frequency maps .. need[word] ---> how many times this word is allowed 
 seen[word] ----> how many times this word appears in the current window

 The invariant you enforce is that for every word :seen[word] <= need[word] ..

 Key insight : The moment this invariant breaks your window is invalid

 Senario is  that you add a word at the right and then if you see that the seen[word] > need[word]  then you dont restart everything but instead you shrink from the left . and the mathematical  beauty is that shrinking by exactly one word (+L) always remvoes exactly one count so the invariant can be restored deterministically 
 
 
 ## When do you record an answer?
  
   this is the precise condition 
   Define :

   k = words.length ( which is the number of words we have)
   count = number of words currently in the window.
   L = length of each word.

   Condition if count ==k AND  invariant holds--> valid concatenation 

    why does the  multiple offsets are required 
    If L=3 valid windows could start at the index 0 index 1 and then the index2 . You must run the sliding window L times once per offset 
    this is not optional this is the mathematical structure of the problem 
    


    People fail because they restart the windows too often and then recompute the maps from the  scratch and then use the substrings caching instead  of the structural guarantees and then the Faan wants the amortized linear movements and not the memorizxation hacks..
     The invariant is not the seen == need all the time and thats the goal conditon when you want to record an answer and the correct way to think about it is that there are two  different truths and you must keep separate and the window- valid invariant ( must hold while you slide and for every word in the need seen)

     So the seen and the need is the invariant and the seen ==need is the we found it moment.