#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution{
    public:
     int minimumScore(string s, string t){
        int n = (int)s.size();
        int m = (int)t.size();
        if (m == 0) return 0;

        vector<int> prefix (t.size(),-1);
        vector<int> suffix (t.size(),-1);
        int j = 0;
        for(int i = 0 ; i<n && j<m;i++){
            if (s[i]==t[j])
            {
             prefix[j]=i;  // t[j] matched at index i in s
             ++j;  
            }
        }
        j = m-1;
        for(int i = n-1 ; i>=0 && j>=0;i--){
            if (s[i]==t[j]){
                suffix[j]=i;  // t[j] matched at index i in s
            --j;
            }            
        }
        int ans = m; // initializing the ans as the worst case ( remove all of the t)
        //Case A  keep only the suffix ( remove a left prefix of t)
        // in this case find the first index k such that the suffix[k] is valid
        // if the suffix[k]!=-1 then the  then you can keep the t[k..m-1] so the removed length is actually k
        for(int k =0;k<m;++k){
            if(suffix[k]!=-1){
                ans = min(ans,k);
                break;
            }
        }

        // Case B Keep only the prefix ( remove a right suffix of t )
        //for every matched prefix end i , removed length is m-1-i
        for(int i =0; i<m;i++){
            if(prefix[i]!=-1){
                ans=min(ans,m-1-i);
            }
        }

        



    }
};

int main (){
    string s = "abacaba";
    string t = "bzaa";
    Solution sol;
    sol.minimumScore(s,t);
    
}