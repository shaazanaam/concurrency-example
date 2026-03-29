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


    }
};

int main (){
    string s = "abacaba";
    string t = "bzaa";
    Solution sol;
    sol.minimumScore(s,t);
    
}