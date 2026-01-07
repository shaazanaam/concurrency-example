#include <iostream>
#include <vector>
using namespace std;
class Solution{
      public:
            int sumFourDivisors(vector<int>& nums){
            
            //precompute the primes here 
            int limit = 1;
            while ((limit+1)*(limit+1)<=100000){
                  limit++;
                  }

            vector<bool> isPrime(limit+1, true);
            isPrime[0] = false;
            isPrime[1] = false;
            for (int i =2 ;  i*i <=limit; i++){
                  if(isPrime[i]){
                        for(int j = i*i; j<limit; j+=i){
                              isPrime[j] = false;
                        }
                  }
            }

            vector<int> primes;
            for(int i = 2; i<= limit; i++){
                  if(isPrime[i]){
                        primes.push_back(i);
                  }
            }
      }
};


int main(){
      
      
      return 0;

}