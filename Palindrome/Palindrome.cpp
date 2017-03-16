#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include "deque.h"
using namespace std;
// a function to check whether the inputs from user is  the {A, C, T, G}-sequence
// and whethr it can be Watson-Crick complemented palindrome.
bool check(char a, char b){
  if((a=='A'&&b=='T')||(a=='T'&&b=='A')||(a=='C'&&b=='G')||(a=='G'&&b=='C')){
    return true;
  }
  return false;
}
int main(int argc, char *argv[]) {
     int inputSize;
     //define a deque and its iterator
     Deque<char> rq;
     Deque<char>::Iterator itr;
     char charTemp;
     bool result=true;
     // using a while loop to collect the sequence from the user 
     while((charTemp=getchar())!='\n'){
	rq.addFirst(charTemp);
     }
       inputSize=rq.size();
     //if it is empty, return true
     if(rq.isEmpty()){
       result=true;
     }
     else if(rq.size()%2==1){
       result=false;
     }
     else{
       // if the number of sequence is even, now use a loop and function check() to check whether
       // it is a Watson-Crick complemented palindrome
       for(int i=0;i<inputSize/2;i++){
	 if(!check(rq.removeFirst(),rq.removeLast())){
	    result = false;
	     
	 }
       }
       
    }
      
    if(result){
      cout<<"true"<<endl;
    }
    else{
      cout<<"false"<<endl;
    }
    exit(0);
    return 0;
}
