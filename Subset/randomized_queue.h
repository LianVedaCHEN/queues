#ifndef randomized_queue_H
#define randomized_queue_H
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void error(const char *msg)
{
    std::cerr<<"\nerror information: "<<msg<<std::endl;
    exit(0);
}
template<typename Item>
class RandomizedQueue{
public:
  class Iterator;//define  a iterator of this randomized queue
  RandomizedQueue();
  ~RandomizedQueue();
  RandomizedQueue(const RandomizedQueue& reffed);
  int size() const;
  bool isEmpty() const;
  void enqueue(Item item);
  Item dequeue();
  Item sample() const;
  Iterator iterator() const;
private:
  class Element;// a type to be used in the array
  Element** eArray;
  int elementNumber;// to indicate the number of elementNumber in the array
  int arraySize;//indicate the size of array since the array size may be different with the number of elementNumber in my design
  void arraySizeChange(int n);// use this function to expand or shrink the size of the array
};


template<typename Item>
class RandomizedQueue<Item>::Iterator {
public:
  Iterator();// default constructor
  ~Iterator();
  Iterator(const Iterator& itr1);//copy constructor
  Iterator(const RandomizedQueue& rQueue);//conversion constructor
  Iterator& operator=(const Iterator& itr1);
  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);
  Item& operator*();
  Item* operator&();
    int currentIndex; 
   Element** iArray;
private:

 // Element** iArray;// a inner array whose order of element is different with teh array of randomized queue so that it can print the element randonly
  int sizeOfArray; // the size of the inner array
  int correctIndex(int direction=0) const; 
  // this function is special. It is used to get the nearest the element with valid value . In most cases, if the user
   // use the iterator correctly, it always get the current element and return the index of itself. But if the element is broken that it has no valid value, 
   // this function will reach the next one with valid value and return its index. And the direction of its searching can be controlled by the 
  //parameter of n
  
  
};

template<typename Item>
class RandomizedQueue<Item>::Element {
public:
  Element();// default constructor
  ~Element();
  Element(const Element& elem);//copy constructor
  Element(Item item);//conversion constructor 
  Element& operator=(const Element& Element);//overload the operator =
  Item* value;// to store the infomation in this element 
};

template<typename Item>
RandomizedQueue<Item>::Element::Element():value(NULL){}

template<typename Item>
RandomizedQueue<Item>::Element::~Element(){
  if(value){
    delete value;
    value=NULL;
  }
  
}

template<typename Item>
RandomizedQueue<Item>::Element::Element(const Element& elem):value(new Item(*(elem.value))){}

template<typename Item>
RandomizedQueue<Item>::Element::Element(Item item):value(new Item(item)){}

template<typename Item>
typename RandomizedQueue<Item>::Element& RandomizedQueue<Item>::Element::operator=(const Element& elem){
   if(elem.value){
     value=new Item(*(elem.value));
     
  }
  return *this;
}

template<typename Item>
RandomizedQueue<Item>::Iterator::Iterator():iArray(NULL),currentIndex(0),sizeOfArray(0){}


template<typename Item>
RandomizedQueue<Item>::Iterator::~Iterator(){
  if(iArray){
    delete[] iArray;
    iArray=NULL;
  }
}

template<typename Item>
RandomizedQueue<Item>::Iterator::Iterator(const Iterator& itr1):iArray(new Element*[itr1.sizeOfArray] ),currentIndex(itr1.correctIndex()),sizeOfArray(itr1.sizeOfArray){
  for(int i=0;i<sizeOfArray;i++){
     iArray[i]=itr1.iArray[i];
  }  

}

template<typename Item>
RandomizedQueue<Item>::Iterator::Iterator(const RandomizedQueue& rQueue):iArray(new Element*[rQueue.elementNumber] ),currentIndex(0),sizeOfArray(rQueue.elementNumber){
  // copy the array from the randomized queue
  for(int i=0;i<sizeOfArray;i++){
     iArray[i]=rQueue.eArray[i];

  }
  //to change the order so later it can print element "randomly"
  Element* tempForRandomize;
  for(int i=0;i<sizeOfArray;i++){
     srand((unsigned)time(NULL));
     int randNum= (i+rand())%sizeOfArray;
     tempForRandomize=iArray[i];
     iArray[i]=iArray[randNum];
     iArray[randNum]=tempForRandomize;
  }

}

template<typename Item>
typename RandomizedQueue<Item>::Iterator& RandomizedQueue<Item>::Iterator::operator=(const RandomizedQueue<Item>::Iterator& itr1){
 
  sizeOfArray=itr1.sizeOfArray;
  currentIndex=itr1.correctIndex(0);

  if(iArray){
    delete[] iArray;
    iArray=NULL;
  }

  if(sizeOfArray>0){
     iArray=new Element*[sizeOfArray];
     for(int i=0;i<sizeOfArray;i++){
     iArray[i]=itr1.iArray[i];
     }  
  }
   

  return (*this);
}

template<typename Item>
typename RandomizedQueue<Item>::Iterator& RandomizedQueue<Item>::Iterator::operator++(){
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
  }
  if(sizeOfArray==0){
         error("The randomized queue is empty so the iterator don't know how to move");
       // the randomized queue is empty so that the iterator don't know how to move
  }

         
  currentIndex=correctIndex(0);
  
  if(currentIndex==sizeOfArray){
       error("the iterator has been at the end of the deque, so it can not move to the next one!");
     // the iterator has been the end of deque so it can not move to next one
  }
 
  currentIndex=correctIndex(1);

     currentIndex=correctIndex(0);
  
   if(currentIndex==sizeOfArray){
       error("the iterator has been at the end of the deque, so it can not move to the next one!");
  } 
   

  return (*this);
}

template<typename Item>
typename RandomizedQueue<Item>::Iterator RandomizedQueue<Item>::Iterator::operator++(int){
  Iterator tempForItr=*this;
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
  }
  if(sizeOfArray==0){
         error("The randomized queue is empty so the iterator don't know how to move");
        // the randomized queue is empty so that the iterator don't know how to move
  }
  currentIndex=correctIndex();
  if(currentIndex==sizeOfArray){
       error("the iterator has been at the end of the deque, so it can not move to the next one!");
      // the iterator has been the end of deque so it can not move to next one
  }
  currentIndex=correctIndex(1);
  currentIndex=correctIndex(0);
   if(currentIndex==sizeOfArray){
       error("the iterator has been at the end of the deque, so it can not move to the next one!");
  }

  return tempForItr;
}

template<typename Item>
typename RandomizedQueue<Item>::Iterator& RandomizedQueue<Item>::Iterator::operator--(){
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
  }
  if(sizeOfArray==0){
         error("The randomized queue is empty so the iterator don't know how to move");
       //   the randomized queue is empty so that the iterator don't know how to move
  }
  currentIndex=correctIndex();
 
  currentIndex=correctIndex(-1);
  if(currentIndex<-1){
       error("the iterator has been at the start of the deque, so it can not move to the previous one!");
  }
  return *this;
}

template<typename Item>
typename RandomizedQueue<Item>::Iterator RandomizedQueue<Item>::Iterator::operator--(int){
  Iterator tempForItr=*this;
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
  }
  if(sizeOfArray==0){
         error("The randomized queue is empty so the iterator don't know how to move");
         // the randomized queue is empty so that the iterator don't know how to move
  }
  currentIndex=correctIndex();
  /*if(currentIndex==0){
       error("the iterator has been at the start of the deque, so it can not move to the previous one!");
              // the iterator has been the head of deque so it can not move to next one
  }*/
  currentIndex=correctIndex(-1);
  if(currentIndex<-1){
       error("the iterator has been at the start of the deque, so it can not move to the previous one!");
  }
  return tempForItr;
}

template<typename Item>
Item& RandomizedQueue<Item>::Iterator::operator*(){
  //gain a reffrence Item from iterator
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");
  }
  int tempId=correctIndex(0);
  currentIndex=tempId;
  if(!this->iArray[0]->value){
     error("the iterator is not valid any longer! So please use a new one!");
  }
   if(tempId>=sizeOfArray){
       error("the iterator has been at the end of the deque, so it can not move to the previous one!");
  }
  
  
  return *(iArray[currentIndex]->value);
}

template<typename Item>
Item* RandomizedQueue<Item>::Iterator::operator&(){
  //gain a pointer to the value from the iterator
  if(!iArray){
      error("the iterator is not initialized so it can not find itself!");
  }
  currentIndex=correctIndex(0);
  if(!iArray[currentIndex]->value){
       error("the iterator is not valid any longer! So please use a new one!");
  }
  return iArray[currentIndex]->value;
}

template<typename Item>
int RandomizedQueue<Item>::Iterator::correctIndex(int direction) const{
  if(direction==0){
    //check for it self
    if(!iArray){
      return 0;
      // the queue contains nothing so it return 0;
    }
    else if(iArray[currentIndex]->value){
      return currentIndex;
      // its value is valid so return the index of itself
    }
    else{
      // if can not find , search for the enxt one
      return correctIndex(1);
    }
    
  }
  else if(direction==1){
    // check for the validation of its next one and if the value of it is valid, return the enxt one's index
    if(currentIndex==sizeOfArray-1){
	return currentIndex;
	// if the iterator is on the end, return the index of end
    }  
 
    int i=0;
   
    for(i=currentIndex+1;!(iArray[i]->value )&& i<sizeOfArray;i++ ){};
    // search until find

    return i;
  }
  else{
     // check for the validation of its previous one and if the value of it is valid, return the previous one's index
     if(currentIndex==0){
      return currentIndex;
       // the iterator has been the head of deque , it can not move so only retur  itself
    }
    int i;
    for(i=currentIndex-1;!iArray[i]->value && i>=0;i-- );
    return i;
    
  }
}

template<typename Item>
RandomizedQueue<Item>::RandomizedQueue():eArray(new Element*[16]),elementNumber(0),arraySize(16){}

template<typename Item>
RandomizedQueue<Item>::~RandomizedQueue(){
  if(eArray){
     delete[] eArray;
    eArray=NULL;
  }
}

template<typename Item>
RandomizedQueue<Item>::RandomizedQueue(const RandomizedQueue<Item>& reffed):eArray(new Element*[reffed.arraySize]),elementNumber(reffed.elementNumber),arraySize(reffed.arraySize){
  if(reffed.eArray){
    for(int i=0;i<arraySize;i++){
      eArray[i]=reffed.eArray[i];
    }  
  }
  else{
     for(int i=0;i<arraySize;i++){
      eArray[i]=NULL;
    }
  } 
}

template<typename Item>
int RandomizedQueue<Item>::size() const {
  return elementNumber;
}

template<typename Item>
bool RandomizedQueue<Item>::isEmpty() const{
  if(elementNumber==0){
    return true;
    
  }
  return false;
}

template<typename Item>
void RandomizedQueue<Item>::arraySizeChange(int n){
    Element** tempArray; 
    if(n>arraySize){
      // if the n is larger than the array size, build a new one with larger size 
      //and copy the data from the old one to it and let eArray equals it. 
        tempArray=new Element*[n];
	int i=0;
	for(; i<arraySize;i++){
	  tempArray[i]=eArray[i];
	}
        for(;i<n;i++){
	  tempArray[i]=NULL;
	}
	delete[] eArray;
	eArray=NULL;
	eArray=tempArray;
    }
    else if(n<arraySize){
       // if the n is smaller than the array size, build a new one with smaller size 
      //and copy the valid data from the old one to it and let eArray equals it. 
       tempArray=new Element*[n];
	int i=0;
	for(; i<n;i++){
	  if(eArray[i]->value){
	  tempArray[i]=eArray[i];}
	  else{
	  tempArray[i]=NULL;  
	  }
	}
	delete[] eArray;
	eArray=NULL;
	eArray=tempArray;
    }
   arraySize=n;
}

template<typename Item>
void RandomizedQueue<Item>::enqueue(Item item){
  Element* newEle= new Element(item);
  if(arraySize==elementNumber){
    arraySizeChange(2*arraySize);
  }
  elementNumber++;
  eArray[elementNumber-1]=newEle;

}

template<typename Item>
Item RandomizedQueue<Item>::dequeue(){
  if(elementNumber<=0){
       error("You can not remove something from nothing since the queue has been empty.");
     // prevent dequeueing from an empty randomized queue
  }
  Element* tempHolder;
  int randNum =  (int)((1.0 * rand() / RAND_MAX) * elementNumber);
  tempHolder=eArray[randNum];
  eArray[randNum]=eArray[elementNumber-1];
  if(arraySize>32&&(arraySize/2)>=elementNumber){
    arraySizeChange(arraySize/2);
  }
  // if the only half of teh array is filled with elements , 
  //use the function arrayChange to change the size of array to save memory
  // but it can not smaller than 16(the minimum size);
  elementNumber--;
  Item tempValue=*(tempHolder->value);
  delete tempHolder->value;
  tempHolder->value=NULL;
  return tempValue;
}

template<typename Item>
Item RandomizedQueue<Item>::sample() const{
  Element* tempHolder;
  int randNum =  (int)((1.0 * rand() / RAND_MAX) * elementNumber);
  return *(eArray[randNum]->value);
  
  
}

template<typename Item>
typename RandomizedQueue<Item>::Iterator RandomizedQueue<Item>::iterator()const{
  if(isEmpty()){
    return Iterator();
 
  }
  return Iterator(*(this));
}

#endif