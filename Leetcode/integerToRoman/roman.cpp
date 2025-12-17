#include <iostream>
#include <iterator>
#include <vector>
#include <unordered_map>

using namespace std;

class Roman {
    public:
        string convertedRoman(int nums){
            vector<pair<int, string>> romanMap ={
                {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
                {100, "C"},  {90,  "XC"}, {50,  "L"}, {40,  "XL"},
                {10,  "X"},  {9,   "IX"}, {5,   "V"}, {4,   "IV"},
                {1,   "I"}
            };

            string res;
            for(auto &p : romanMap){
                while(nums>=p.first){
                    res += p.second;
                    nums -= p.first;
                }
            }
            return res;
            
        }
};

int main(){

    int nums =56;

    Roman rom;

    cout<<"converted roman number for the "<<nums<<" is "<<rom.convertedRoman(nums);
    
    return 0;
}