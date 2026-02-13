#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
    public :
     int maximumLength(string s ){
        unordered_map<string,int>  u;
        vector<pair<char,int>> groups;
         int i =0;
         int L=0;
         string special;
         while(i <s.size()){                    
          char c = s[i];
          int j = i;
          while(j<s.size() && s[j]==c) j++;
          groups.push_back({c,j-i});
          i=j;
                      
         }

         // Now for a given L 
         unordered_map<string, int> u;
         for(auto& g: groups){
            if (g.second>=L){
               // each substring of length L in this group is special 
               // All are the same so use the string of ch repeated L times
               string special(L, g.first);
               u[special]+= g.second-L+1;
               if(u[special]>=3) L= 
            }
            
         }
     }    
};