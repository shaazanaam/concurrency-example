#include <iostream>
#include<vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename T>
void printVector(const string& name, const vector<T>& v) {
    cout << setw(12) << left << name << ": [";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 < v.size()) {
            cout << ", ";
        }
    }
    cout << "]\n";
}

void debugMaxProductBuild(const string& s) {
    int n = static_cast<int>(s.size());
    if (n == 0) {
        cout << "Empty string. Nothing to debug.\n";
        return;
    }

    vector<int> bestStart(n, 0), bestEnd(n, 0), leftBest(n, 0), rightBest(n, 0);
    vector<int> radius(n, 0);

    cout << "Input: " << s << "\n";
    cout << "Index: ";
    for (int i = 0; i < n; ++i) cout << setw(3) << i;
    cout << "\nChars: ";
    for (char c : s) cout << setw(3) << c;
    cout << "\n\n";

    int L = 0, R = -1;
    cout << "=== Manacher (odd palindromes) ===\n";
    for (int i = 0; i < n; i++) {
        int i_mirror = -1;
        if (i <= R) {
            i_mirror = L + R - i;
            radius[i] = min(radius[i_mirror], R - i + 1);
        } else {
            radius[i] = 1;
        }

        while (i - radius[i] >= 0 && i + radius[i] < n && s[i - radius[i]] == s[i + radius[i]]) {
            radius[i]++;
        }

        int start = i - (radius[i] - 1);
        int end = i + (radius[i] - 1);
        int len = 2 * radius[i] - 1;

        if (end > R) {
            L = start;
            R = end;
        }

        bestStart[start] = max(bestStart[start], len);
        bestEnd[end] = max(bestEnd[end], len);

        cout << "i=" << setw(2) << i
             << "  char='" << s[i] << "'"
             << "  mirror=" << setw(2) << i_mirror
             << "  radius=" << setw(2) << radius[i]
             << "  start=" << setw(2) << start
             << "  end=" << setw(2) << end
             << "  len=" << setw(2) << len
             << "  [L,R]=[" << L << "," << R << "]\n";
    }
    cout << "\n";

    printVector("radius", radius);
    printVector("bestStart", bestStart);
    printVector("bestEnd", bestEnd);
    cout << "\n=== Propagation ===\n";

    for (int i = n - 1; i > 0; i--) {
        if (bestEnd[i] > 2) {
            bestEnd[i - 1] = max(bestEnd[i - 1], bestEnd[i] - 2);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        if (bestStart[i] > 2) {
            bestStart[i + 1] = max(bestStart[i + 1], bestStart[i] - 2);
        }
    }

    printVector("bestStart", bestStart);
    printVector("bestEnd", bestEnd);

    leftBest[0] = bestEnd[0];
    for (int i = 1; i < n; i++) {
        leftBest[i] = max(leftBest[i - 1], bestEnd[i]);
    }

    rightBest[n - 1] = bestStart[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        rightBest[i] = max(rightBest[i + 1], bestStart[i]);
    }

    cout << "\n=== Prefix/Suffix best arrays ===\n";
    printVector("leftBest", leftBest);
    printVector("rightBest", rightBest);

    long long answer = 0;
    cout << "\n=== Split products ===\n";
    for (int i = 0; i <= n - 2; i++) {
        long long cur = 1LL * leftBest[i] * rightBest[i + 1];
        answer = max(answer, cur);
        cout << "split after i=" << setw(2) << i
             << "  leftBest=" << setw(2) << leftBest[i]
             << "  rightBest=" << setw(2) << rightBest[i + 1]
             << "  product=" << cur << "\n";
    }
    cout << "\nFinal max product (debug pipeline): " << answer << "\n";
}

class Solution {
public:
    long long maxProduct(string s) {
        int n = static_cast<int>(s.size());
        // the palindrome length at i is being definded as the 2*n-1
        // the radius at i tells how many characters you can expand including the center
        vector<int> bestStart(n,0), bestEnd(n,0),leftBest(n,0),rightBest(n,0);
        vector<int> radius(n,0); // this is the radius array which will be computed from the manacher and be stored inside this vector
        long long answer{};
        // we will be using the radius values to fill the bestStart best end
        int L{0},R{-1};// L and R are the intervals for the current best palindrome which we will be getting by converting the radius to them
        for(int i = 0; i<n;i++){
           int i_mirror,start,end;
           if ( i<=R) {
            i_mirror=L+R-i;
            radius[i]=min(radius[i_mirror],R-i+1);
           }
           // with the inital value of the R as R=-1 this conditon takes it to the else directly 
           else radius[i]=1; 
        
           while(i-radius[i]>=0 && i+radius[i]<n && s[i-radius[i]]==s[i+radius[i]]){  
                radius[i]++;    
            }
            //convert radius to local boundaries
            start= i-(radius[i]-1);
            end=i+(radius[i]-1);
            int len =2*radius[i]-1;
            if (end>R){
                L=start;
                R=end;
            }
            // updating the boundary arrays
            bestStart[start]=max(bestStart[start],len);
            bestEnd[end]=max(bestEnd[end],len);

        }
        //adding two propogation passes for including all the radii for max radius for the odd palindrome
        // for the bestEnd sweep right to left
        //use the idea that the neighbor to the left can inherit the length minus 2
        for(int i =n-1;i>0;i--){
           if (bestEnd[i]>2){
            bestEnd[i-1]= max(bestEnd[i-1],bestEnd[i]-2);
           }
            
        }
        for (int i = 0;i<n-1;i++){
            if (bestStart[i]>2){
              bestStart[i+1]= max(bestStart[i+1],bestStart[i]-2);  
            } 
        }
        leftBest[0]=bestEnd[0];
        for(int i = 1; i<n;i++){
            
            leftBest[i]= max(leftBest[i-1],bestEnd[i]);
        }   
        rightBest[n-1]=bestStart[n-1];
        for(int i=n-2;i>=0;i--){
            rightBest[i] = max(rightBest[i+1],bestStart[i]);
        }
        for(int i = 0; i<=n-2; i++){
         answer= max(static_cast<long long>(leftBest[i])*rightBest[i+1],answer);
        }
        

     return answer;   

    
    }

    long long maxProduct2(string s) {
        int n = s.length();
        vector<int> d(n); // Manacher's array for odd palindromes
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
            d[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }

        vector<long long> left(n, 1), right(n, 1);

        // Precompute max palindrome length in prefix
        for (int i = 0, center = 0; i < n; i++) {
            while (center + d[center] - 1 < i) center++;
            left[i] = max(i > 0 ? left[i - 1] : 1LL, (long long)(i - center) * 2 + 1);
        }

        // Precompute max palindrome length in suffix
        for (int i = n - 1, center = n - 1; i >= 0; i--) {
            while (center - d[center] + 1 > i) center--;
            right[i] = max(i < n - 1 ? right[i + 1] : 1LL, (long long)(center - i) * 2 + 1);
        }

        long long ans = 0;
        for (int i = 0; i < n - 1; i++) {
            ans = max(ans, left[i] * right[i + 1]);
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cout << "Enter string (or press Enter for default): ";
    getline(cin, s);
    if (s.empty()) {
        s = "ababbb";
        cout << "Using default: " << s << "\n";
    }

    cout << "\n";
    debugMaxProductBuild(s);

    Solution sol;
    cout << "\nSolution::maxProduct result: " << sol.maxProduct(s) << "\n";
    cout << "Solution::maxProduct2 result: " << sol.maxProduct2(s) << "\n";
    return 0;
}