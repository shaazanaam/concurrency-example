#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Solution{
      public:
            string minimumString(string a , string b, string c){
               string tempAns1;
               string tempAns2;
               string globalAns;
               vector<vector<string>> orders = {
                  {a, b, c},
                  {a, c, b},
                  {b, a, c},
                  {b, c, a},
                  {c, a, b},
                  {c, b, a}
                  };
               
               for(auto& order :orders){
                  //check if order[1] is contained inside the order[0] in that case you can return order[0]
                  if (order[0].find(order[1])!=string::npos){
                     tempAns1 =order[0];
                  }
                  else if (order[1].find(order[0])!=string::npos){
                     tempAns1 =order[1];
                  }
                  else {
                     int overlap_length1 = min(order[0].length(),order[1].length());
                     while(overlap_length1>=1){
                        if (order[0].substr(order[0].length()-overlap_length1)
                            == order[1].substr(0,overlap_length1)){
                           tempAns1 = order[0]+order[1].substr(overlap_length1, order[1].length()-overlap_length1);
                           break;
                        } overlap_length1--;
                     }
                        if(overlap_length1==0){
                           tempAns1 =order[0]+order[1];
                        }
                  }
                


                  if (tempAns1.find(order[2])!=string::npos){
                     tempAns2 =tempAns1;
                  }
                  else if (order[2].find(tempAns1)!=string::npos){
                     tempAns2 =order[2];
                  }
                  else {
                     int overlap_length2 = min(tempAns1.length(),order[2].length());
                     while(overlap_length2>=1){
                        if (tempAns1.substr(tempAns1.length()-overlap_length2)
                            == order[2].substr(0,overlap_length2)){
                           tempAns2 = tempAns1+order[2].substr(overlap_length2, order[2].length()-overlap_length2);
                           break;
                        } overlap_length2--;
                     } 
                        if (overlap_length2==0){
                           tempAns2 = tempAns1 +order[2];
                        }
                  }
                  if(globalAns.length()>tempAns2.length() || globalAns.empty()){
                     globalAns = tempAns2;
                  } else if(globalAns.length()==tempAns2.length()){
                     globalAns= min(globalAns,tempAns2);
                  }   
  
               }

               return globalAns;
            }

            string getMergedString(const string& a, const string& b){
               int n = a.size(), m = b.size();
               for (int i{}; i<n;i++){
                  int k{i},j{};
                  for(;j<m&&k<n;j++){
                     if(a[k]==b[j]) ++k;
                     else break;
                  }
                  if(j==m) return a;
                  if(k==n) return a+b.substr(j);
               }
               return a+b;
            }
            string evaluateSequence(const string& a , const string& b, const string& c){
               string res{getMergedString(getMergedString(a,b),c)};
               return res;
            }
            string minimumString2(string a , string b, string c){
               string res;
               size_t minLen{std::numeric_limits<int>::max()};
               vector<string> vec;
               vec.push_back(evaluateSequence(a,b,c));
               vec.push_back(evaluateSequence(a,c,b));
               vec.push_back(evaluateSequence(b,a,c));
               vec.push_back(evaluateSequence(b,c,a));
               vec.push_back(evaluateSequence(c,a,b));
               vec.push_back(evaluateSequence(c,b,a));   
            for(const string& s: vec){
               if((s.size()<minLen)){
                  minLen=s.size();
                  res=s;
               }else if (minLen=s.size() && res>s){
                  res=s;
               }
            } return res;
            }

            

};

int main(){
   Solution sol;
   string finalAnswer{sol.minimumString("abc","bca","aaa")};
   string finalAnswer{sol.minimumString2("abc","bca","aaa")};
}