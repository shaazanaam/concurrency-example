#include <iostream>


using namespace std;
class Solution{
    public:
        long long maximumsubsequence2 (string text, string pattern){
            //count h ow many subsequences "ab" already exist in the text and then 
            //compute how much extra you get from inserting 
            //a ( best place is at the very begining and then inserting b)
            //b ( best place is at the very end) then you take the larger result
            //if you insert a it helps by pairing with every b that appears after it .
            //Earlier position maximizes after it so the beginning is the best .
            //if you insert b at the end it helps by pairing with the every a before it .

            //scan left to right and count the existing efficiently 
            char a = pattern[0];
            char b = pattern[1];
            int countA = 0, countB=0;
            long long ogcount = 0;
            for ( auto ch: text){
                if(ch==b){
                    ogcount +=countA;
                    countB++;

                }
                if(ch==a){
                    countA++;
                }
            } return ogcount + max(countA, countB);
            // when you insert a at the begining -- every b in the text now has an extra a before it so you 
            //gain the count B new subsequences
            //When you insert b at the end and every a in the text now has an extra b 
            //after it so you gain countA new subsequences
            
        }
};