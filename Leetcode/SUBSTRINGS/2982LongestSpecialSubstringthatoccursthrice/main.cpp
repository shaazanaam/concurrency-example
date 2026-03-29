#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;
// using grouping and then the binary search for the largest string 
class Solution {
    public :
     int maximumLength(string s ){
        
        vector<pair<char,int>> groups;
         size_t i =0;        
         string special;
         while(i <s.size()){                    
          char c = s[i];
          size_t j = i;
          while(j<s.size() && s[j]==c) j++;
          groups.push_back({c,j-i});
          i=j;
                      
         }

         // Now for a given L 
         int low = 1, high = s.size(), answer = -1;
         while(low<=high){
            int mid = (low+high)/2;
            unordered_map<char,int> freq;
            for(auto& [ch, cnt]: groups){
               if(cnt>=mid) freq[ch]+=cnt-mid+1;
            }
            bool found = false;
            for(auto&[ch,count]:freq){
               if(count>=3) found = true;
            }
            if(found){
               answer = mid ;
               low = mid+1;
            }else{
               high = mid-1;
            }
         }
         return answer;
  
     } 
        
};

int main(){
   Solution sol;
   // string s1 = "aaaa";
   // cout<<"Test1: "<<sol.maximumLength(s1)<<endl;

   // string s2 = "abcdef";
   // cout<<"Test 2: "<<sol.maximumLength(s2)<<endl;

   // string s3 = "abcaba";
   // cout<<"Test 3: "<<sol.maximumLength(s3)<<endl;

   string s4 = "ccc";
   cout<<"Test4: "<<sol.maximumLength(s4)<<endl;

   return 0 ;
}