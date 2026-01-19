#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class Solution {
public:
    string minWindow(string s, string t) {
        
        unordered_map<char, int> T;
        unordered_map<char, int> S;
        // built the frequency table for the string t
        for(char target: t){
            T[target]++;
        }
        //run the sliding window on the given string with the two pointers

        int left=0; int  right =0;
        S.clear();
        while(right
            <s.size()){
            //EXPANDING THE RIGH POINTER TO INCLUDE CHARACTERS IN THE WINDOW AND CONTRACTING THE LEFT POINTER TO MINIMIZE THE WINDOW .



            
    
        }
    }
};