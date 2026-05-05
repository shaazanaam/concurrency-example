#include <iostream>
#include<vector>
#include<string>


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
                     

                  }
                  
                  return 0;
            }

};
int main(){
      Solution sol;
      cout<<sol.maxProduct("ababa");
}