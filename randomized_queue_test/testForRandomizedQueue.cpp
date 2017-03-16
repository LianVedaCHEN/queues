#include <iostream>
#include "randomized_queue.h"

/*
This main program only checks your class, functions' signatures correct or not.
To check the correctness of your program, you may need to use more complicated examples.
*/

using namespace std;

int main(int argc, char ** argv){

	srand(time(NULL));
	RandomizedQueue<char> rq;

	cout << "Empty? " << rq.isEmpty() << endl;
	cout << "Size? " << rq.size() << endl;
	rq.enqueue('a');
	rq.enqueue('b');
	rq.enqueue('c');
	rq.enqueue('d');
	cout << "Empty? " << rq.isEmpty() << endl;
	cout << "Size? " << rq.size() << endl;

	int i;
	RandomizedQueue<char>::Iterator itr = rq.iterator();
	cout << "queue : ";
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;

	cout << "sampling : " ;
	for(i = 0; i < rq.size()*2;i++){
		cout << rq.sample() << " ";
	}
	cout << endl;

	cout << "dequeue :  " << rq.dequeue() << endl;
	itr = rq.iterator();
	cout << "queue : ";
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;
	//above this line, all tests are provided by professor and TAs. After this line, it is designed by me.
	itr = rq.iterator();
	cout<<"\ntest for itr++ after it has been the end."<<endl;
	cout<< "In my design, if the iterator has been the end, it will stay there instaed of moving backward.So beyond the size, all result is the same as the last in the deque.\n"<<endl;
	for(i = 0; i < 20;i++){
		cout << *itr << " ";
		++itr;
	}
	cout << endl;	
	/*
	this for loop is to test iterator's reaction when it has been the end but the ++itr is still called
.       In my design, if the iterator has been the end, it will stay there instaed of moving forward.
       
	 
	*/
	
	cout<<"\ntest for --itr after it has been the head."<<endl;
	cout<< "In my design, if the iterator has been the head, it will stay there instaed of moving backward.So beyond the size, all result is the same as the first in the deque.\n"<<endl;
        for(i = 20; i >0;i--){
		cout << *itr << " ";
		--itr;
	}
	cout << endl;
        /*
	this for loop is to test iterator's reaction when it has been the head but the --itr is still called
.       In my design, if the iterator has been the head, it will stay there instaed of moving backward.
       
	 
	*/itr = rq.iterator();
	cout<<"\ntest for itr++ after it has been the end."<<endl;
	cout<< "In my design, if the iterator has been the end, it will stay there instaed of moving backward.So beyond the size, all result is the same as the end in the deque.\n"<<endl;
	for(i = 0; i < 20;i++){
		cout << *itr << " ";
		itr++;
	}
	cout << endl;	
	/*
	this for loop is to test iterator's reaction when it has been the end but the itr++ is still called
.       In my design, if the iterator has been the end, it will stay there instaed of moving forward.
       
	 
	*/
	
	cout<<"\ntest for itr-- after it has been the head."<<endl;
	cout<< "In my design, if the iterator has been the head, it will stay there instaed of moving backward.So beyond the size, all result is the same as the first in the deque.\n"<<endl;
        for(i = 20; i >0;i--){
		cout << *itr << " ";
		itr--;
	}
	cout << endl;
        /*
	this for loop is to test iterator's reaction when it has been the head but the itr-- is still called
.       In my design, if the iterator has been the head, it will stay there instaed of moving backward.
       
	 
	*/		
        
       cout<<"\nthe program can also test the situation when there is nothing in dequq but removeFirst/Last is still called. But I hide them. If you want to test, you can delete my commet in the testforDeque.cpp"<<endl;
	/*cout<<"deque: " ;
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout<<endl;
	cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue()<< endl;
	cout<<"\nnow all elements in deque has been deleted. So next operation of removing will cause the error and print the error information:"<<endl;
	cout << "dequeue: " << rq.dequeue() << endl;*/
	
	/*cout<<"\nthe program can also test the situation when there is nothing in dequq but removeLast is still called. But I hide them. If you want to test, you can delete my commet in the testforDeque.cpp"<<endl;
        cout<<"deque: " ;
	for(i = 0; i < rq.size();i++){
		cout << (*itr) << " ";
		++itr;
	}
	cout<<endl; 
        cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue()<< endl;
	cout<<"\nnow all elements in deque has been deleted. So next operation of removing will cause the error and print the error information:"<<endl;
	cout << "dequeue: " << rq.dequeue() << endl;*/
	//bekow is to test when the randomized queue is empty whether it can provide some erro information
	cout<<"\nbekow is to test when the randomized queue is empty whether it can provide some erro information"<<endl;
	cout<<"deque: " ;
	for(i = 0; i < rq.size();i++){
		cout << *itr << " ";
		++itr;
	}
	cout<<endl;
	cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue() << endl;
	cout << "dequeue: " << rq.dequeue()<< endl;
	//now the rq is an empty randomized queue
	itr=rq.iterator();
	cout<<(*itr)<<endl;
	

	return 0;
}