#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
        public: 
            vector<int> findSubstring(string s, vector<string>& words) {
            unordered_map<string, int> need;
            unordered_map<string, int> seen;
            int L = words.empty()? 0:static_cast<int> (words[0].size());
            int left , right =0;
            vector<int> results;
            // Use a sliding window to check the substrings of length L*k
            //L = length of each word inside the passed vector
            //k = total number of words 
            //create the need map from words.
            for (string w: words){
                need[w]++;
            }

            // for each off set you need to  implement the sliding window logic
            for (int offset = 0; offset <L ; ++offset){
                //sliding window logic will go here 
                left = offset, right = offset;
                seen.clear();
                int count = 0;  //number of valid words in the current window 

                // slide the right pointer  in the steps of L 
                while(right + L <=s.size()){
                    string word = s.substr(right,L);  //Extract the word of length L
                    right +=L;                        // move the right pointer 
                
                    // update the seen map 
                    if(need.count(word)){
                        seen[word]++;
                        count++;

                        while(seen[word]>need[word]){
                            string leftWord = s.substr(left,L);
                            seen[leftWord]--;
                            count--;
                            left +=L;
                        }
                        if (count ==words.size()){
                            results.push_back(left);
                        }

                    
                    }

                
                }

                

            }
            return results;
        }
};


int main(){

    return 0;
}