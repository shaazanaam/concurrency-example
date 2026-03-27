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

        int answer = m;
        int rightStart = 0;

        // i is the last kept index in the left part of t.
        // i == -1 means we keep no left part.
        for (int i = -1; i < m; ++i) {
            int leftEnd = -1;

            if (i >= 0) {
                if (prefix[i] == -1) break;
                leftEnd = prefix[i];
                if (rightStart < i + 1) rightStart = i + 1;
            }

            while (rightStart < m && (suffix[rightStart] == -1 || suffix[rightStart] <= leftEnd)) {
                ++rightStart;
            }

            if (rightStart == m) {
                answer = min(answer, m - (i + 1));
            } else {
                answer = min(answer, rightStart - i - 1);
            }
        }

        return answer;
    }
};