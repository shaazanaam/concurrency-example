5. Longest Palindromic Substring
Medium
Topics
premium lock icon
Companies
Hint
Given a string s, return the longest palindromic substring in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.
Example 2:

Input: s = "cbbd"
Output: "bb"

Hint 1 ... How can we use a previously computed palindrome to compute a large palindrome
Hint 2 ... If aba is a palindrome is xabax a palindrome ? Similarly is xabay a palindrome?
Hint 3 ... If we brute force the check for the palindrome substring then for every start and end we have O(n^2) start-end pairs and also o(n) times the palindromic checks. can we reuse the time for the palindromic checks by reusing the previously found computation.


The naive method 
 for(size_t i = 0; i<s.size(); i++)
        {
            for(size_t j = i; j<s.size();j++){
                substrings.push_back(s.substr(i,j-i+1)); // pushed all the possible substrings inside the vector 
            }
        }
    vector<bool> isPalindrome(substrings.size(), true);
    for(size_t i = 0; i< substrings.size();i++){
        for (char c :substrings[i]){
        
            q.push(c);
            stk.push(c);
        }

        char c1{},c2{};
        while(!q.empty()){
            c1= q.front();
            q.pop();
            c2=stk.top();
            stk.pop();
            if(c1!=c2)
                isPalindrome[i]= false;
                break;  
        }
        //clear the stack and queue for the next substring

        while(!stk.empty()) stk.pop();
        while(!q.empty()) q.pop();
        
    }
    for(size_t i = 0; i< substrings.size();i++){
        if (isPalindrome[i] && substrings[i].size() > longest.size()) {
                longest = substrings[i];
            }

    }


## This method has a time complexity of O(n^3)
    1. Generating all substrings takes O(n^2)
    2. Checking if each substring is a palindrome takes O(n)
    3. Combined this results in O(n^3) for the entire solution 


The old approach generates all the possible substring for the input string and then checks each one for being a palindrome .

## New approach 

Treat each character as a Center 
    A palindrome has a center . For odd length palindromes the center is a single character . For the even length palindromes the center is between two characters..
    So we need to expand around the center .. for each center expand outwards while the characters on both sides are equal 

Track the longest Palindrome :
    Keep track  of the starting index and the length of the longest palindrome found during the expansopn
 