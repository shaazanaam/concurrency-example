#include <iostream>
#include <vector>
using namespace std;
class Solution{
      public:
            int sumFourDivisors(vector<int>& nums){
            
            //precompute the primes here 
            int limit = 1;
            int ans = 0;
            while ((limit+1)*(limit+1)<=100000){     // this is the code we are using number instead of the 100000 becasue we dont want to use the sqrt ....
                  limit++;
                  }

            vector<bool> isPrime(limit+1, true);
            isPrime[0] = false;
            isPrime[1] = false;
            for (int i =2 ;  i*i <=limit; i++){
                  if(isPrime[i]){
                        for(int j = i*i; j<limit; j+=i){
                              isPrime[j] = false;  // seiving out all the Js in this case 
                        }
                  }
            }

            vector<int> primes;
            for(int i = 2; i<= limit; i++){
                  if(isPrime[i]){
                        primes.push_back(i);
                  }
            }

            for(int i = 0; i< nums.size(); i++){
                  if (nums[i]<6) continue;
                  for ( int j =0; j< primes.size() &&(1LL*primes[j]*primes[j]<=nums[i]) ;j++){
                        if((nums[i]%primes[j])==0){
                              int p=primes[j];
                              if (1LL*p*p*p==nums[i]){
                                    ans +=1+p+p*p+ nums[i];
                                    break;
                              }
                              int q= (nums[i]/primes[j]);
                              if(q!=p){
                                  //dont have to worry if q is a floating point number becasue you have come
                                  //down under the check carried out before this that p is a divisor.
                                  //just check if q is prime
                                  bool qPrime = true;
                                  for(int k= 0 ; k<primes.size()&& (1LL*primes[k]*primes[k]<=q);k++){
                                    if(q%primes[k]==0){
                                          qPrime = false;
                                          break;
                                    }
                                  }
                                  if(qPrime){
                                    ans += 1+p+q+nums[i];
                                    break;
                                  }
                              }break;  // this is the break that handles the rejection path and all the earlier breaks will be the handler for the accept paths

                        
                        }
                  } 
                  
            }
            return ans;
      }
};


int main(){
      
      Solution solver;
      vector<int> num{1,2,3,4,5};
      solver.sumFourDivisors(num);
      return 0;

}