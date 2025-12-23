#include <iostream>
#include <unordered_map>

using namespace std;

class RomanToInteger{
    public:
        
        
    
        int romanToInt(const string &s){
            
            unordered_map<char,int> val={{'I',1},{'V',5},{'X',10},
                                          {'L',50},{'C',100},{'D',500},{'M',1000}};

            int res=0;

            for (size_t i = 0; i<s.size();++i){
                int v = val[s[i]];
                if(i+1< s.size() && v< val[s[i+1]])
                    res -=v;
                else    
                    res+=v;
            }
            return res;
        };

        int parseRoman(const string &s){
             unordered_map<string,int> rev = {
                {"M",1000},{"CM",900},{"D",500},{"CD",400},
                {"C",100},{"XC",90},{"L",50},{"XL",40},
                {"X",10},{"IX",9},{"V",5},{"IV",4},{"I",1}
            };
            
            int i=0, n= s.size(), res=0;

            while(i<n){
                if (i+1<n){
                    string two = s.substr(i,2);
                    auto it = rev.find(two);
                    if(it!= rev.end()){ 
                        res+= it->second;
                        i+=2;
                        continue;
                    }
                }       
                res +=rev[string(1,s[i])];  // th single char ones
                i+=1;
   
            }
            return res;
        }

};

int main(){

    
    string testRoman ="III";
    
    RomanToInteger ans;

    cout <<"The answers is "<<ans.parseRoman(testRoman);
    cout <<"The answers is "<<ans.romanToInt(testRoman);
}