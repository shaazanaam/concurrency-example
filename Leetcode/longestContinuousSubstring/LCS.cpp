#include <iostream>
#include <vector>

using namespace std;

class MaxSubstring {
      public:
        int maxSubstringLength(string s){
          // track the last index
          // intialize a  vector of 256 elements and then intialize each of them to -1
          vector<int> last(256,-1);
          
          int L=0;
          int best = 0;
          for( size_t R= 0 ; R<s.size();++R){
            
            int prev = last[(unsigned char) s[R]];
            if (prev>=L) {
                  L= prev+1;
                 
            }
            last[(unsigned char)s[R]]=(int)R;
            best = max(best, (int)R-L+1);

          }
           return best;
        }

        // using the previous Java Script Style programming 

        int maxSubStringJavaScriptStyle(string s){
          int L = 0;
          
          vector<int> last (256,-1);
          int longest = 0;
          
          for(size_t i= 0; i<s.size();i++){
            unsigned char ch = (unsigned char)s[i];
            int prev = last[ch];
            L = max(L,prev+1);
            last[ch] = (int)i;
            longest = max(longest, (int)i-L+1);
          }
          return longest;
        }
       
};
int main() {
  string sample = "abcabcbb"; // Example input
  MaxSubstring solver;

  int result1 = solver.maxSubstringLength(sample);
  int result2 = solver.maxSubStringJavaScriptStyle(sample);

  cout << "maxSubstringLength: " << result1 << endl;
  cout << "maxSubStringJavaScriptStyle: " << result2 << endl;

  return 0;
}

