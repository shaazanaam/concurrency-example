#include <iostream>
#include<stack>
#include<queue>
#include <cctype>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
    stack<char> stk;
    queue<char> q;
    
    vector<int> last (256,-1);
    string longest ="";
    // generate the substrings
    vector <string> substrings;
        

    for(size_t i = 0; i<s.size(); i++)
        {
            for(size_t j = i; j<s.size();j++){
                substrings.push_back(s.substr(i,j-i+1)); // pushed all the possible substrings inside the vector 
            }
        }
    vector<bool> isPalindrome(substrings.size(), true);
    for(size_t i = 0; i< substrings.size();i++){
        for (char c :substrings[i]){
        
            q.push(c);
            stk.push(c);
        }

        char c1{},c2{};
        while(!q.empty()){
            c1= q.front();
            q.pop();
            c2=stk.top();
            stk.pop();
            if(c1!=c2)
                isPalindrome[i]= false;
                break;  
        }
        //clear the stack and queue for the next substring

        while(!stk.empty()) stk.pop();
        while(!q.empty()) q.pop();
        
    }
    for(size_t i = 0; i< substrings.size();i++){
        if (isPalindrome[i] && substrings[i].size() > longest.size()) {
                longest = substrings[i];
            }

    }
            
      return longest;  
        
    }
// By expanding around a center . A palindrome has a center .
    string efficientLongestPalindrome (string s){
        
           
        string longest;
        for(int i = 0; i<s.size(); i++){
            
            
              int L=i, R=i;
              while (L>=0&& R<s.size() && s[L]==s[R]){
                
                if((R-L+1>longest.size()))    
                    longest = s.substr(L,R-L+1);

                L--;
                R++;
 
                }
            
            
               L=i; R=i+1;
              while (L>=0&& R<s.size() && s[L]==s[R]){
                
                if((R-L+1>longest.size()))    
                    longest = s.substr(L,R-L+1);

                L--;
                R++;
 
                }
          
            

        }

          
        return longest;    
        
    }
   

    
};

int main(){
    Solution solver ;
    cout<<solver.efficientLongestPalindrome("shaaz");
    return 0;
}