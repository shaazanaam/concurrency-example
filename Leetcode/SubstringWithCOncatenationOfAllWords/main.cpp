#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
       public:
             vector<int>  findSubstrings(string s, vector<string>& words){
                   unordered_map<string, int> need;
                   unordered_map<string,int> seen;
                  for (string w: words){
                       need[w]++;
                  }
                  // you would  basically have to  run the sliding window for every character of the string
                  // and then basically need to update the seen
             }
};

int main(){

      return 0;
}
