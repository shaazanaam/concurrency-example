#include <iostream>
#include<vector>

using namespace std;

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
};