/*
Longest Substring with Atleast K repeating Characters
Given a string s and an Integer K return the length of the longest substring
of s such that the frequency of each character in this substring is greater
than or equal to k  if no such substring exists , return 0 .
*/
#include <iostream>
#include <vector>

using namespace std;

class Solution{
    int lenghtOfLongestSubstring(string s, int K){
        vector<int> map(128,0);
        int counter=0; //represents the number of unique characters in the window that have the freq<k ( dont meet the requirements)
        int begin=0, end=0; //two pointers one point to the tail and one to the head
        int d;      //the length of the substring

        for(char c : s) map[c]++;  // counting the frequencies of all the characters in the map
        while (end<s.size()){
            if (map[s[end++]]--==K)
            {
                counter++;
            }

            while(counter>0){
                if(map[s[begin++]]++==K-1)
                counter--;
                
            }
            d=  max(d,end-begin);
            
        }return d;


    }
};