#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    if (words.empty() || s.empty()) return result;

    int wordLength = words[0].size();
    int wordCount = words.size();
    int totalLength = wordLength * wordCount;

    unordered_map<string, int> need;
    for (const string& word : words) {
        need[word]++;
    }

    for (int offset = 0; offset < wordLength; ++offset) {
        unordered_map<string, int> seen;
        int left = offset, count = 0;

        for (int right = offset; right + wordLength <= s.size(); right += wordLength) {
            string word = s.substr(right, wordLength);

            if (need.find(word) != need.end()) {
                seen[word]++;
                count++;

                while (seen[word] > need[word]) {
                    string leftWord = s.substr(left, wordLength);
                    seen[leftWord]--;
                    count--;
                    left += wordLength;
                }

                if (count == wordCount) {
                    result.push_back(left);
                }
            } else {
                seen.clear();
                count = 0;
                left = right + wordLength;
            }
        }
    }

    return result;
}

int main() {
    string s = "barfoothefoobarman";
    vector<string> words = {"foo", "bar"};

    vector<int> indices = findSubstring(s, words);

    for (int index : indices) {
        cout << index << " ";
    }

    return 0;
}