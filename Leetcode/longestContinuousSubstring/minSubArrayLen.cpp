// Min sub array length 
#include <iostream>
#include <vector>
#include <array>
#include <limits>

using namespace std;
class MinSubarrayLength {
      public:
      template<size_t N>
      int minSubArraylen(array<int,N>& arr , int num, int& minStart, int& minEnd) {
           if(N==0) return 0;
           int tempSum = 0;
           int start = 0;  // is the left boundary 
           int minLen =  numeric_limits<int>::max();
          
           for (int i =0; i<N;i++){   
            //i is the right boundary
            // this creates an expanded window and all the  elements to the tempSum
            tempSum+= arr[i];
            while(tempSum>=num){
                  minLen = min(minLen,i-start+1);
                  minStart = start;// storing the start index to help printing it 
                  minEnd = i;  // stroing the end to help us with the printing of the array and then pass the value so that we can identify it
                  tempSum-=arr[start];
                  start++;         // Move the start  pointer forward
            }
           }  return (minLen==numeric_limits<int>::max())?0:minLen;

       }
};

int main(){
      // Exmaple array and the target
      array<int,6> arr = {2,3,1,2,4,3};
      int target = 7;
      int minStart = -1;
      int minEnd = -1;
      MinSubarrayLength solver;
      int minLen = solver.minSubArraylen(arr,target,minStart,minEnd);

      //  Handle the no answer case 
      if(minLen ==numeric_limits<int>::max()){
            cout<<0<<endl;

      }else{
            cout<<minLen<<endl;
            cout<<"The min Sub array is {";
            for(int i = minStart; i<=minEnd;++i){
                  cout<<arr[i];
                  if (i<minEnd)cout<<" ";
            }
            cout<<"}\n";
      }


      return 0;
}