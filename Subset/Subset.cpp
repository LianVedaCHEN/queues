#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include "randomized_queue.h"
using namespace std;
int main(int argc, char *argv[]) {
     // test the input to check whether the user input the size of subset
  srand(time(NULL));
     if (argc < 2) {
      fprintf(stderr,"Please specify an output number k!\n", argv[0]);
      exit(0);
     }
     int subsetSize=atoi(argv[1]);
     int setSize;
     string strTemp;
     // define a randomized queue called rq and its iterator
     RandomizedQueue<string> rq;
     RandomizedQueue<string>::Iterator itr;
     
     //deal with the situation that the user input 0 as the size of subset
     if(subsetSize==0){
       cout<<"Invalid output number k!"<<endl;
       exit(0);
     }
     else{
       //a loop to collect user's element 
       while(cin>>strTemp){
	 if(strTemp.empty()) break;
	 rq.enqueue(strTemp);
	 
       }
       setSize=rq.size();
       itr=rq.iterator();
       // print the result from the randomized queue according to the subset size
       if(setSize<subsetSize){
	 for(int i=0; i< setSize;i++){
	   cout<<*itr<<endl;
	   ++itr;
	  }
	 cout<<"The number you input is less than the size of subset!!!"<<endl;
       }
       else{
	 for(int i=0; i< subsetSize;i++){
	   cout<<*itr<<endl;
	   ++itr;
	  }
       }
    }
}

