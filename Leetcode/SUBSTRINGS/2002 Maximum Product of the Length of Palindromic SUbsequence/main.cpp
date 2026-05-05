#include <iostream>
#include<vector>
#include<string>
#include<algorithm>


using namespace std;

class Solution{
      public:
            int maxProduct(string s){
                  // get n from the string length
                  // full mask will represent the state where every character in the string  is selected 
                  //totalMasks one shifted left by n 
                  int n = s.size();
                  int totalMask =1<<n;
                  int fullMask = totalMask-1;
                  vector<int>pallLen(totalMask,0);
                  vector<int> palMasks;  // to store only masks that are palindromic
                  for(int mask =1;mask<=totalMask-1;mask++){
                       
                       string subseq;
                      for (int i = 0; i<n;i++){
                          if(mask&(1<<i)){  // this is checking if the bit mask is going to include the character at that position 
                             subseq+= s[i]; 
                       }
                      }
                      string rev = subseq;
                      reverse(rev.begin(),rev.end());
                      if(subseq==rev){
                        pallLen[mask]=subseq.length();
                      }
                  }
                  int res = 0;
                  for(auto& m1 : pallLen){
                        for (auto& m2: pallLen){
                              if (m1 &m2==0){
                                    res = max(res,pallLen[m1]* pallLen[m2] );
                              }

                        }
                  }

                  
                  return res;
            }

};
int main(){
      Solution sol;
      cout<<sol.maxProduct("ababa");
}