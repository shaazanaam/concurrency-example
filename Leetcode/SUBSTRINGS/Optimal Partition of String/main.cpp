#include <iostream>
#include<vector>
#include<string>
#include<unordered_set>

using namespace std;

class Solution {
public: 
    // User version: track last index and split when duplicate appears in window.
    int partitionString(string s){
        if (s.empty()) return 0;

        vector<int> last (256,-1);
        int L = 0;
        int partitions = 1;
        for (size_t R = 0; R < s.size(); ++R){
            int prev = last[(unsigned char)s[R]];
            if (prev >=L){
                L=(int)R;
                partitions++;

            }
            last[(unsigned char) s[R]] = (int) R;
                        
        }
        return partitions;
    }

    // Copilot version: set-based current partition tracking.
    int partitionStringC(string s) {
        if (s.empty()) return 0;

        unordered_set<char> seen;
        int partitions = 1;

        for (char c : s) {
            if (seen.count(c)) {
                partitions++;
                seen.clear();
            }
            seen.insert(c);
        }

        return partitions;
    }

    // partitionString2: O(n) using partition id marker table (no set clear cost).
    int partitionString2(string s) {
        if (s.empty()) return 0;

        vector<int> seenInPartition(256, 0);
        int partitionId = 1;
        int partitions = 1;

        for (unsigned char c : s) {
            if (seenInPartition[c] == partitionId) {
                partitions++;
                partitionId++;
            }
            seenInPartition[c] = partitionId;
        }

        return partitions;
    }
};

int main() {
    Solution sol;

    vector<string> tests = {
        "abacaba",
        "ssssss",
        "world",
        "hdklqkcssgxlvehva",
        ""
    };

    for (const string& s : tests) {
        cout << "s = \"" << s << "\"\n";
        cout << "partitionString      : " << sol.partitionString(s) << "\n";
        cout << "partitionStringCopilot: " << sol.partitionStringC(s) << "\n";
        cout << "partitionString2     : " << sol.partitionString2(s) << "\n";
        cout << "-----------------------------\n";
    }

    return 0;
}