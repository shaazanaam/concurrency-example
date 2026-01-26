## You are give two non empty linked lists representing two non negative integers . The digits are stored in the reverse order and then each of their nodes contains a single digit. Add the two numbers and then return the sum as a linked list

 You may assume the two numbers do not contain any leading zero except the number 0 itself

  you have thge first example as a the following 

  Input L1  = [2,4,3] and then the l2 = [5,6,4]
  Output:[7,0,8]

   Explanation :342+465 = 807

    Constraints :
      the number of the nodes in each linked list is the range [1,100].

      0<=Node.val<=9
      It is guaranteed that the list represents a number that does not have the leading zeroes
      

## the way an interviewer expects you to hear this 
You are given the two non emppty linked lists
Each List represents a non negative integer 
  . digits are stored in the reverse order
  . Each node contains one digit
  . Return the  sum as a linked list  also in the reverse order

Interviewer's Hidden Intent ( important to memorize)
They are asking the following 
  1. Traversal of the linked List 
  2. Digit by digit arithmetic 
  3. Carry handling 
  4. Edge handling 
  5. Clean loop invariants
  6.  Whether you can think iteratively and not mathematically
   this is not a math problem and this is a simulation problem

Elementary school  addition but one digit at a time 
You already know how to add the numbers like 
342+463
807

I will simulate how I add the numbers columns by  column starting from the ones place 
that sentence alone solves the 50% of the problem

   Visual Mental Model ( NO COde)
   L1: 2->4->3
   L2: 5->6->4

    because the list is reversed

    2 and 5 are the ones place and 4 and 6 is in the tens  place and then the 3 and the 4 are in the hundreds place 

## memory Anchor#2

  Three things happens at every step 
  At every node your brain must remember only three things
  1. two digits form the (l1 and L2 ---or 0 if missing)
  2. Carry from the previous step 
  3. Result digit + new carry
  
  so  say this  aloud "Digit +Digit + carry forward " Repeat it and this is the heart of the problem 

  Gudied Dry Run

      Step1 
      . Digits: 2 and 5 
      . Carry :0

      Question ? 
       What is the 2+5+0 . Answer is the resulting digit ? Is there a Carry?

         Every step will be having the same question and then the resulting digit will be the carry + the L:1  and the L2

  This is the favorite FAANG question edge case and they  would be asking  what if  there is a carry left even when the list is finished 
  its pure logic :  

          You would be  needing a dummy starting node and then a current pointer that moves forward because it removes the edge cases and then it moves forward 


    Common interview pittfalls 
    .. Forgetting to carry 
    .. stopping  when one list ends
    .. Not handling the leftover carry 
    .. Overcomplicating with the math or converting to numbers and then 
    .. Trying use recurssion unnecessarily

    Say this aloud : 
    "I will never convert the list  to an integer"
      What the interviewer want you to say ?

      "I will traverse both the lists simultaneously and then add the corresponding  digits  along with the carry and then create a new node for each digit of the result and then continue until both list and the  carry are exhausted"

    
            


Memory Anchor #3
# Loop While everything  remains
 Burn this into the memory
 " I continue while L1 exists OR L2 exists OR carrry exists .. 

Conveptual Data structure Rule No code 
You cannot modify inputs list 
You must build a new list 

So mentally picture 
A dummy starting node ( placeholder)
A current pointer that moves forward

 A dummy is  helpful becasue it  removes the edge cases when the first digit is removed


 The final answer will be like the following : Ill traverse both the lists simultaneously  and then add corresponding digits along with a carry then create a new node for each digit of the result and continue until both the lists and the carry are exhausted 

  If you say this confidently you already passed

## sample questions to ask before attempting to solve the problem.

What variables to we need to track at each step?
When do i stop the loop?
what happens if one list is shorter ?
What happens if there's a carry after both the list end
Why is  a dummy node  helpful?
    A dummy is helpful because it removes the edge cases when the first digit is created ..

   Without a  dummy the logic becomes the following .

    If this is the first digit then 
      Create node 
      Set it as the head and the set the current pointer 
     Else
       Attach the node to the current.next
       Move Current

     That IF is the edge case

      At the end you might just have to skip the dumnmy and then return the dummy.next

## Mental Model#2 

 Dummy absords the awkwardness..

  the dummy node absorbs the awkwardness of starting th elist 
  You never worry about the :
   First node 
   Empty list 
   Head assignment 

   You  just append forever


## Memory Anchor #4
Repeat this aloud 
"If my algorithm needs special logic for the first iteration , I  should consider a dummy node"

This applies to the linked lists , trees queues ,Graph construction.

The dummy node lets you treat all the insertions uniformly and avoids special
handling for the head of the list 


## Linked List

A data structure that contains a head , tail and the length property
Linked List consists of the nodes and each node has a value and a pointer to another node.

there is no indec in a singly linked list 
 In this case you would be needing a singly linked list and at no point will you be needing to move backward and then delete form the middle or insert  before a node  or revisit a previous digit 

 this is becasue the algorithm only requires a forward traversal and forward construction and no backward navigation is needed .... 


 Each list stores the number reversed and then so the head node is the ones place and adding will  happen left to the right  along the lists

 I will be  adding from the head because the head is the ones digit 

th eplace value will be determined by the node's positon and not by multiplying  the pointer


When the interviewer asks what pieces of state must your algorithm remember while it runs?
MEMORIZE THIS 

 you need exactly four categories of variable ?
 1. Input traversal variables ( READ state)
   you need references that let you walk  through the input lists
    conceptuallu where I am in L1 
     where I am in L2
     these move forward only and memory line: Momory Line 
     "Two pointers to read the inputs"

 2.  Carry variable ( Arithmethic state )
    You need a variable that remembers  what must be added to the next digit
    this will be starting at zero and will be updating at every iterations

    Carry lives across iterations

  3. Result construction variables ( Write State)

    You need :
     One stable anchor to the result list ( dummy)
     One moving pointer to append new digits
      
    " One pointer to rember the start , one to grow the list and these are seperate from the input pointer "

    Temporary computation variables ( Ephemeral State)

    " Inside each  loop iteration you briefly hold 
      . digit from L1 
      digit from L2 
      sum
       these do not persist between the iterations

        the final answer

        I need pointers to traverse both the input lists , a carry variable to propagate the additon a dummy head an a current pointer to construct the reasult and the  temposrary variables to hold the digit sums


         You  should not be adding the  method to add the two linked list inside the node class as this will indicate  that you are mixing the mode with the algorithm and then algorithm is not equal to the node.

so doing something like this is wrong
using namespace std;
class ListNode{
      public :
            int val;
            ListNode* next;
            ListNode(int x): val(x),next(nullptr){}

            int listSum(ListNode& L1 , ListNode& L2){
                  
            }
};


 Conceptual  mistake in this one is the reference vs the pointer 
   this means that 
    you are passing the references to the single nodes 
    You cannot reassign them 
    You cannot safely traverse by advancing them

What the algorithm needs to do :
it needs to move forward through the list 
reassign traversal pointers repeatedly

 that requires a pointer you you are allowed to move .. traversal requires movable pointers and not fixed references


Common mistake is not passing the pointer and  using the reference instead which will be  causing it to be not allowing the traversal.

Say this aloud :
" The node class defines the structure ; algorithm operates on nodes and pointers outside the class .. This is because adding the two linked lists is an operation on multiple nodes and not a responsibility of a single node . Keeping the algorithm seperate imporves the clarity and design

 in order to create the dummy node you cant just have the nullptr and then a dummy null will be creating a real ListNode object whose value doesnt matter and use it as a permanent anchor.

  the dummy node will be pointing to the dummy initially and then it moves forward as you append the nodes .
   The dummy node is the starting block and the tail pointer is my hand builing forward


    You  though that dummy means a place holder pointer but in all actuality it means a placeholder node
     this is very common confusion.

      What is a dummy node ?
       it is a real node created at the start of the list to simplify the insertion logic and avoid the special handling for the head .
       it exists in the memory and then has a next pointer ( initially null)..
       is the previous node for the first real result digit.

        A tail pointer is a variable that always points to the last node in the result list used so you can append in O{1}
This shows the udnerstanding of the  following concept 
.. pointer vs object
.. ownership vs traversal
..dummy node pattern
..O(1) list construction

final note keep this in mind :
" The dummy is a node and then the tail is the pointer and the  tail initially points to the dummy.

## difference between the tail pointer and the dummy
  the tail pointer is not the part of th list and it is just a variable and whose  job is to remember where the end of the list currently is . The tail is dynamic and it moves forward every time you append a node .  Without it you will have to traverse the entire list to add or append it .
## dummy node
   it is  responsible for acting as a real node and it is part of the output list and whose job is only to give me a stable starting point for the list . dummy.next is not enough to build the list using this becasue after the first append dummy --->[7]---> null  
   With dummy.next you can still do the dummy.next = newNode when you can accidentally overrite the [7]. In order to append the second node you  still have to do the  following [7].next =newNode but how do you get to the [7] . You would indeed have to traverse the entire list. this will be turing the algorithm into O(n^2).. the tail pointer will be preventing this exact problem. With the tail  you always know where the last node is and where to attach the next one in the O(1) time ....

## Memory anchor: 
Critical distinction (memorize this)

Say this out loud:

Nodes store structure.
Pointers store position.

dummy.next = structure

tail = position

They are not interchangeable.

## Answer
  "dummy.next give me access to the head of the result  list  but I need a separate tail pointer to track the last node so I can append new nodes in the constant time traversing the list."

