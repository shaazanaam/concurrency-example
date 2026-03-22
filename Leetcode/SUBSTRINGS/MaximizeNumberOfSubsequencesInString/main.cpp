#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
class Solution{
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        char a = pattern[0];
        char b = pattern[1];
        int countA=0,countB=0;
        long long ogCount=0; // existing subsequence inside the text
        // countA = number of  times we have seen a 
        for (auto ch: text){
            
            if(ch==b) {
                ogCount +=countA;
                countB++;
            }
            if(ch==a) countA++;

        } return ogCount +max(countA,countB);
    }
};

int main() {
    Solution sol;

    vector<tuple<string, string, long long>> tests = {
        {"abdcdbc", "ac", 4},
        {"aabb", "ab", 6},
        {"aaaa", "aa", 10},
        {"zzzz", "zy", 4}
    };

    for (const auto& [text, pattern, expected] : tests) {
        long long actual = sol.maximumSubsequenceCount(text, pattern);
        cout << "text=\"" << text << "\", pattern=\"" << pattern
             << "\" -> " << actual
             << " (expected " << expected << ")"
             << (actual == expected ? " [PASS]" : " [FAIL]") << '\n';
    }

    return 0;
}