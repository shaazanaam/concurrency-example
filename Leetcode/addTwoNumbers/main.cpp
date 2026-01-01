#include <iostream>
#include <vector>

using namespace std;
class ListNode{
      public :
            int val;
            ListNode* next;
            ListNode(int x): val(x),next(nullptr){}

            
};

ListNode* addTwoList (const ListNode*  L1 , const ListNode*  L2){
// inside this function you  will be tracking two traversal cursors and the carry 
//dummy head +current pointer for building output
//the goal of this function is to take the heads of the reversed digit Lists and then sum the digits and then return the Linked list also reversed.
//even though the parametes are const ListNode* , you will be using the local traversal cursors:
const ListNode* current1 = L1; // this is the readonly traversal cursor
const ListNode* current2 = L2;
ListNode  dummy(0);            // dummy is a real node that exists in the memory 
ListNode* tail = &dummy;       // &dummy which is the addrtess of that node and tail is a pointer that stores that address
                               // this makes this invariant to be true which makes the last  node in the result list 
                               // at the start the last node is dummy and thus the tail points to dummy
                               // this unlocks the possibility of safely doing the tail->next = newNode and then you never need a special case for the first digit
                               // the list remains singly linked 
int carry = 0;                 // initializing the arithmethic state

while(current1!=0 || current2!=0 || carry!=0){

      int x = current1 ? current1->val:0;
      int y = current2 ? current2->val:0;
      int total = x+y+carry;
      ListNode* newNode =  new ListNode(total%10);
      tail->next = newNode;
      carry =total/10;
      tail = newNode;
      if (current1!=nullptr )current1 = current1->next;
      if (current2!=nullptr) current2= current2->next;
     
      
}
return dummy.next;

}

