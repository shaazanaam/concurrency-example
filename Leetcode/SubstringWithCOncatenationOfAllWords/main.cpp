#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
       public:
             vector<int>  findSubstrings(string s, vector<string>& words){
                   unordered_map<string, int> need;
                   unordered_map<string,int> seen;
                   vector<int> result;
                   int offset = !words.empty()? static_cast<int>(words[0].size()):0;
                   int left, right, count =0;
                   int L = words.size();  //  this is the length of the list  of the words
                  for (string w: words){
                       need[w]++;
                  }
                  // you would  basically have to  run the sliding window for every character of the string
                  // and then basically need to update the seen as we move through the string 

                  // loop  through  the offset 
                  for (int i = 0; i<offset; i++){
                        left ,right =i;
                        seen.clear();
                        count =0;
                        while (right +L < s.size()){
                              string word = s.substr(right,L);  // extract the right most section which we then test against the words item
                              right+=L;
                              
                              if(need.count(word)){
                                    seen[word]++;
                                    count++;
                                    
                                    while (seen[word]>need[word]){
                                    // then you   would be shrinking 

                                    string leftWord = s.substr(left,L);
                                    left+=L;
                                    count--;
                                    seen[word]--;

                              }
                                    if(count == words.size()){
                                          result.push_back(left);
                                    }
                              }else {
                                    seen.clear();
                                    left = right;
                                    count =0;

                              }

                              

                               
                        }
                        
                  }
                  return result;
             }
};

int main(){

      return 0;
}
