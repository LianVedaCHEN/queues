/**********************************************************************
 *  Randomized Queues and Deques
 **********************************************************************/

Name:CHEN,Lian
ID:20328991
Login:lchenbk
Hours to complete assignment (optional):


/**********************************************************************
 *  Explain briefly how you implemented the randomized queue and deque.
 *  Which data structure did you choose (array, linked list, etc.)
 *  and why?
 **********************************************************************/
I use array to implement the randomized queue and linked list to implement 
the deque. The reason I choose the array for the randomized queue is that I 
think array which can be assessed by operator[] is easier for me to choose 
one element from it to implement the “random” later. For the deque, it should be operated by addFirst/Last removeFirst/Last, in other words, it requires flexibility on add or remove element. So I choose to use linked list where it is easier to modify its elements to implement the deque.


/**********************************************************************
 *  Briefly describe why any sequence of N randomized queue operations,
 *  starting from an empty randomized queue, takes O(N) time.
 **********************************************************************/
In order to avoid too much unused space after removing and avoid the lack of space when adding new elements, my function of enqueue() and dequeue() are involved with the operation of changing the size of array. This time this process take is averagely  O(1) since before it start to enlarge(shrink) the size, it must have experienced several times enqueue(dequeue)operation.

For isEmpty()/size(), they just access and return a number, which are not involved with any manipulation, so they cost O(1).




/**********************************************************************
 *  Briefly describe why each Deque operation takes O(1) time.
 **********************************************************************/
In order to solve a problem I meet when I program, I gave the the Deque’s data member *first and *last one empty Element respectively. And all adding operation or deleting operation is to add after the Element stored by 
*first(or before the Element stored by *last if removeFirst/Last is called).
The time to access these two “marked” element is O(1), so the operation of addFirst/Last or removeFirst/Last take O(1).

For isEmpty()/size(), they just access and return a number, which are not involved with any manipulation, so they cost O(1).



/**********************************************************************
 *  How much memory (in bytes) does your data type use to store N items.
 *  Use tilde notation to simplify your answer. Use the memory requirements
 *  for a "typical machine" given in Lecture. In your analysis, don't include
 *  the memory for the items themselves (as this memory is allocated by
 *  the client and depends on the item type.
 *  For a typical machine, refer to page 11 of 
 *  http://www.cs.princeton.edu/courses/archive/spring10/cos226/lectures/02-14Analysis-2x2.pdf 
 **********************************************************************/

RandomizedQueue:
object overhead: 8 bytes
eArray Element**(a pointer) 4bytes(in a computer with 32-bit processor) or 8bytes(in a computer with 64-bit processor)
elementNumber int 4 bytes
arraySize int 4bytes
total:20bytes(in a computer with 32-bit processor) or 24bytes(in a computer with 64-bit processor)


Dequeue:
object overhead: 8 bytes
first Elements* (a pointer) 4bytes(in a computer with 32-bit processor) or 8bytes(in a computer with 64-bit processor)
last Elements* (a pointer) 4bytes(in a computer with 32-bit processor) or 8bytes(in a computer with 64-bit processor)
elementNumber int 4 bytes
total: 20bytes(in a computer with 32-bit processor) or 28bytes(in a computer with 64-bit processor)





/**********************************************************************
 *  Known bugs / limitations.
 **********************************************************************/
I debugged all the bugs I found so I think probably it don’t remain(at least too much) bugs.


/**********************************************************************
 *  List whatever help (if any) that you received and from whom,
 *  including help from staff members or lab TAs.
 **********************************************************************/
I discussed some small issues with my friends.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
In the beginning, I want to let the first directly equals the first element
I added and my function of iterator() is to return a iterator with the information of the firstly added element. So I create a object of iterator when there is nothing in the deque, it may cause some problems that the there is nothing in the first. Later I put one empty elements into *first
and *last and later operate between them, and then I solved this problem.




/**********************************************************************
 *  List any other comments here. Feel free to provide any feedback   
 *  on how much you learned from doing the assignment, and whether    
 *  you enjoyed doing it.                                             
 **********************************************************************/
I write a function error(char* msg) to handle the error. If some station 
happen, my program will handle it and use this function to print the error
message in the format”error information:”+the illegal operation causing the 
error. I also write two program for testing deque and randomized queue respectively.
They include the test provided by professor and TA and also some tests designed by
me. 

I put the Subset.cpp with a randomized_queue.h, Palindrome with a deque.h, testForDeque.cpp 
with deque.h and testForRandomizedQueue.cpp with randomized_queue.h into four 
sub folders. I also put makefile and .pro corresponding to each folder into the folders.


