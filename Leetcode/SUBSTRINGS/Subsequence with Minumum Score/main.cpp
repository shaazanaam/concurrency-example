#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumScore(string s, string t) {
        int n = (int)s.size();
        int m = (int)t.size();
        if (m == 0) return 0;

        vector<int> prefix(m, -1);
        vector<int> suffix(m, -1);

        // prefix[i] = position in s where t[i] was matched (left to right)
        int j = 0;
        for (int i = 0; i < n && j < m; ++i) {
            if (s[i] == t[j]) { prefix[j] = i; ++j; }
        }

        if (j == m) return 0; // t is already a subsequence of s

        // suffix[i] = position in s where t[i] was matched (right to left)
        j = m - 1;
        for (int i = n - 1; i >= 0 && j >= 0; --i) {
            if (s[i] == t[j]) { suffix[j] = i; --j; }
        }
        int ans = m; // taking ans as the worst case as this is the case where the entire string t is the subsequence
        

        int ans = m; // worst case: remove all of t

        // Case A: keep only suffix (remove left part of t)
        for (int k = 0; k < m; ++k) {
            if (suffix[k] != -1) { ans = min(ans, k); break; }
        }

        // Case B: keep only prefix (remove right part of t)
        for (int i = 0; i < m; ++i) {
            if (prefix[i] != -1) { ans = min(ans, m - 1 - i); }
        }

        // Case C: keep prefix[0..i] + suffix[j2..m-1], remove middle
        // Fix i, move j2 forward (two-pointer)
        int j2 = 0;
        for(int i = 0; i<m;i++){
            if (prefix[i]==-1) break; // this prefix length not matchable 
            j2= max(j2,i+1); //suffix must start after i in t
            while(j2<m && (suffix[j2]==-1||suffix[j2]<=prefix[i])){
                ++j2;
            }
            if(j2<m){
                ans= min(ans, j2-i-1);//removed middle length
            }
        }

        return ans;
    }
};

int main() {
    string s = "abcaacb";
    string t = "aaabc";

    int n = (int)s.size();
    int m = (int)t.size();

    vector<int> prefix(m, -1);
    vector<int> suffix(m, -1);

    int j = 0;
    for (int i = 0; i < n && j < m; ++i)
        if (s[i] == t[j]) { prefix[j] = i; ++j; }

    j = m - 1;
    for (int i = n - 1; i >= 0 && j >= 0; --i)
        if (s[i] == t[j]) { suffix[j] = i; --j; }

    cout << "s = " << s << "\n";
    cout << "t = " << t << "\n\n";

    cout << "idx:    ";
    for (int i = 0; i < m; ++i) cout << i << "    ";
    cout << "\n";
    cout << "t  :    ";
    for (int i = 0; i < m; ++i) cout << t[i] << "    ";
    cout << "\n";
    cout << "prefix: ";
    for (int i = 0; i < m; ++i) cout << prefix[i] << "    ";
    cout << "  <- position in s matched left-to-right\n";
    cout << "suffix: ";
    for (int i = 0; i < m; ++i) cout << suffix[i] << "    ";
    cout << "  <- position in s matched right-to-left\n\n";

    // two-pointer trace
    cout << "Two-pointer (fix i, advance j2):\n";
    cout << "Keep t[0..i] + t[j2..m-1], remove middle (length = j2-i-1)\n";
    cout << "Rule: need prefix[i] < suffix[j2] so matches do not overlap in s\n\n";

    int j2 = 0;
    for (int i = 0; i < m; ++i) {
        if (prefix[i] == -1) { cout << "i=" << i << ": prefix[i]=-1. Stop.\n"; break; }
        j2 = max(j2, i + 1);
        cout << "i=" << i << "  prefix[i]=" << prefix[i] << "  j2 starts at " << j2 << "\n";
        while (j2 < m && (suffix[j2] == -1 || suffix[j2] <= prefix[i])) {
            cout << "  skip j2=" << j2 << " suffix[j2]=" << suffix[j2]
                 << "  (need > " << prefix[i] << ")\n";
            ++j2;
        }
        if (j2 < m)
            cout << "  ACCEPT j2=" << j2 << " suffix[j2]=" << suffix[j2]
                 << " > prefix[i]=" << prefix[i]
                 << "  => removed=" << j2 - i - 1 << "\n";
        else
            cout << "  no valid j2\n";
    }

    cout << "\nAnswer = " << Solution().minimumScore(s, t) << "\n";
    return 0;
}
