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
                  for(int m1 =0; m1<totalMask;m1++){
                        for (int m2=0;m2< totalMask;m2++){
                              if ((m1 &m2)==0){
                                    res = max(res,pallLen[m1]* pallLen[m2] );
                              }

                        }
                  }

                  
                  return res;
            }

           
            int maxProduct2(string s) {
            int n = s.length();
            int total_masks = 1 << n;
            // is_pal[mask] "stores the length if it's a palindrome, otherwise 0"
            vector<int> pal_len(total_masks, 0);

            //DP over masks to find all palindromes
            // A mask with 0 or 1 bit set is always a palindrome
            pal_len[0] = 0;
            for (int mask = 1; mask < total_masks; ++mask) {
                  int first = -1, last = -1;
                  for (int i = 0; i < n; ++i) {
                  if ((mask >> i) & 1) {
                        if (first == -1) first = i;
                        last = i;
                  }
                  }

                  if (first == last) {
                  pal_len[mask] = 1;
                  } else if (s[first] == s[last]) {
                  // "If the outer characters are equal, check the 'inner' mask"
                  int inner_mask = mask ^ (1 << first) ^ (1 << last);
                  if (inner_mask == 0 || pal_len[inner_mask] > 0) {
                        pal_len[mask] = pal_len[inner_mask] + 2;
                  }
                  }
            }

            // 2. Collect only valid pairs (mask, length)
            vector<pair<int, int>> valid;
            for (int i = 1; i < total_masks; ++i) {
                  if (pal_len[i] > 0) valid.push_back({i, pal_len[i]});
            }

            // 3."Final iteration over non-overlapping masks"
            int max_prod = 0;
            int m = valid.size();
            for (int i = 0; i < m; ++i) {
                  int m1 = valid[i].first;
                  int l1 = valid[i].second;
                  // Optimization: if l1 * n (max possible) is less than max_prod, we can skip searching"
                  if (l1 * (n - l1) <= max_prod) continue; 
                  
                  for (int j = i + 1; j < m; ++j) {
                  if ((m1 & valid[j].first) == 0) {
                        max_prod = max(max_prod, l1 * valid[j].second);
                  }
                  }
            }

            return max_prod;
    }
};


int main(){
      Solution sol;
      cout<<sol.maxProduct("ababa");
}