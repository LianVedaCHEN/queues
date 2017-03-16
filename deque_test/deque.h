#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void error(const char *msg)
{
    std::cerr<<"\nerror information: "<<msg<<std::endl;
    exit(0);
}
template <typename Item>

class Deque{
public:
    Deque();
    ~Deque();
    class Iterator;//define  a iterator of this deque
    bool isEmpty();
    int size() const;
    void addFirst(Item item);
    void addLast(Item item);
    Item removeFirst();
    Item removeLast();
    Iterator iterator();
private:
    class Element;//used as a element in  a linked list
    Element* first;
    Element* last;
    int elementNumber;
};
template <typename Item>
class Deque<Item>::Element{
public:
    Element();// default constructor
    Element(const Item& i); //conversion constructor
    Element(const Element& node1); //copy constructor
    ~Element();
    Element& operator=(const Element& node2); //overload the operator =
    Item* value;// to store the infomation in this element 
    Element* nextOne; // connect to the nect one
    Element* preOne;// connect to the previous one
};

template <typename Item>
class Deque<Item>::Iterator{
public:
    Iterator();// default constructor
    Iterator( Element& node1);//conversion constructor
    Iterator(const Deque& deque);//copy constructor
    ~Iterator();
    Iterator& operator=(const Iterator& itr);
    Iterator& operator++(); 
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    bool operator==(Iterator& itr);
    bool operator!=(Iterator& itr);
    Item& operator*(); // dereference
    Item* operator&();
    
    
private:
    Element* correctElement() const; 
    // this function is special. It is used to get the nearest the element with valid value . In most cases, if the user
    // use the iterator correctly. it always get the current element. But if the element is broken that it has no valid value, 
    // this function will reach the next one with valid value
    void move(Deque<Item>::Element& node);
    // move to the element. actually it works with the function of correctElement() so it can skip the broken element 
    Element* currentElement;
};

template <typename Item>
Deque<Item>::Element::Element():value(NULL),preOne(NULL),nextOne(NULL){
    
}

template <typename Item>
Deque<Item>::Element::Element(const Item& i):value(new Item(i)),preOne(NULL),nextOne(NULL){
    
}

template <typename Item>
Deque<Item>::Element::Element(const Deque<Item>::Element& node1):value(new Item(*(node1.value))),preOne(NULL),nextOne(NULL){
    
}

template <typename Item>
Deque<Item>::Element::~Element(){
    if(!value){
        delete value;
    }
}

template <typename Item>
Deque<Item>::Iterator::Iterator():currentElement(NULL){
}

template <typename Item>
Deque<Item>::Iterator::Iterator( Deque<Item>::Element& node1):currentElement(&node1){
    
}

template <typename Item>
Deque<Item>::Iterator::Iterator(const Deque<Item>& deque2):currentElement(deque2.Iterator().currentElement){
    
}

template <typename Item>
Deque<Item>::Iterator::~Iterator(){
}

template <typename Item>
typename Deque<Item>::Iterator& Deque<Item>::Iterator::operator=(const Iterator& itr){
    currentElement=itr.correctElement();
    return *this;
    
    
}

template <typename Item>
typename Deque<Item>::Iterator& Deque<Item>::Iterator::operator++(){
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!"); // no current elements means it is not initialized so it can not be used
    }
    Element* temp = correctElement();
    move(*temp);
    if(!temp){
          error("The deque has broken so the iterator don't know how to move");
	// the correctElement() search for the whole list and can not find a valid element so the deque is broken
    }
    if(!temp->nextOne&&temp->preOne){
          error("the iterator has been at the end of the deque, so it can not move to the next one!");
	// the iterator has been the end of deque so it can not move to next one
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    move(*(temp->nextOne));
    return *this;
}

template <typename Item>
typename Deque<Item>::Iterator Deque<Item>::Iterator::operator++(int){
    Iterator tempItr =*this;// store the information to a temp Itr and later return this one
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
    }
    Element* temp = correctElement();
    move(*temp);
    if(!temp){
          error("The deque has broken so the iterator don't know how to move");
	// the correctElement() search for the whole list and can not find a valid element so the deque is broken
    }
    if(!temp->nextOne&&temp->preOne){
          error("the iterator has been at the head of the deque, so it can not move to the next one!");
	// the iterator has been the end of deque so it can not move to next one
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    move(*(temp->nextOne));
    return tempItr;
}

template <typename Item>
typename Deque<Item>::Iterator& Deque<Item>::Iterator::operator--(){
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
    }
    Element* temp = correctElement();
    move(*temp);
    if(!temp){
          error("The deque has broken so the iterator don't know how to move");
	// the correctElement() search for the whole list and can not find a valid element so the deque is broken
    }
    if(!temp->preOne&&temp->nextOne){
          error("the iterator has been at the head of the deque, so it can not move to the previous one!");
      // the iterator has been the head  of deque so it can not move to next one
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    move(*(temp->preOne));
    return *this;
}

template <typename Item>
typename Deque<Item>::Iterator Deque<Item>::Iterator::operator--(int){
    Iterator tempItr =*this;
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
    }
    Element* temp = correctElement();
    move(*temp);
    if(!temp){
          error("The deque has broken so the iterator don't know how to move");
	// the correctElement() search for the whole list and can not find a valid element so the deque is broken
    }
    if(!temp->preOne&&temp->nextOne){
          error("the iterator has been at the head of the deque, so it can not move to the previous one!");
       // the iterator has been the head  of deque so it can not move to next one
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    move(*(temp->preOne));
    return tempItr;
}

template <typename Item>
bool Deque<Item>::Iterator::operator==(Deque<Item>::Iterator& itr){
    move(*correctElement());
    itr.move(*correctElement());
    if(!currentElement&&!itr.currentElement&&currentElement==itr.currentElement){
        return true;
    }
    return false;
}

template <typename Item>
bool Deque<Item>::Iterator::operator!=(Deque<Item>::Iterator& itr){
    move(*correctElement());
    itr.move(*correctElement());
    if(!currentElement&&!itr.currentElement&&currentElement!=itr.currentElement){
        return true;
    }
    return false;
}


template <typename Item>
Item& Deque<Item>::Iterator::operator*(){
    //gain a reffrence Item from iterator
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!");// no current elements means it is not initialized so it can not be used
    }
    Element* temp = correctElement();
    move(*temp);
    if(!currentElement){
          error("The deque has broken so the iterator don't know how to move");
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    return *(currentElement->value);
}

template <typename Item>
Item* Deque<Item>::Iterator::operator&(){
     //gain a pointer to the value from the iterator
    if(!currentElement){
          error("the iterator is not initialized so it can not find itself!");
    }
    Element* temp = correctElement();
    move(temp);
    if(!currentElement){
          error("The deque has broken so the iterator don't know how to move");
    }
    if(!currentElement->value){
          error("the deque is empty!");
    }
    return currentElement->value;
}


template <typename Item>
typename Deque<Item>::Element* Deque<Item>::Iterator::correctElement() const{
    if(currentElement->value)
        return currentElement;
    //it has valid value so return itself
    if(!currentElement->nextOne&&currentElement->preOne)
        return currentElement->preOne;
    Element* testElement =currentElement;
    for(;!testElement->value&&testElement->nextOne;testElement=testElement->nextOne);
    // searching for the next element with valid value
    if(testElement->value)
        return testElement;
    if(!testElement->preOne){
        return NULL;
    }
    // can not find on its next one so it have to return those before it
    return currentElement->preOne;
}

template <typename Item>
void Deque<Item>::Iterator::move(Deque<Item>::Element& node){
  //work with function correctElement() to move it to the element with valid value
    if(&node){
        currentElement=&node;
    }
    else
        currentElement=NULL;
}


template <typename Item>
typename Deque<Item>::Element& Deque<Item>::Element::operator=(const Deque<Item>::Element& node2){
    delete value;
    value = new Item(*(node2.value));
    return (*this);
}


template <typename Item>
Deque<Item>::Deque():first(new Element()),last(new Element()),elementNumber(0){
first->nextOne=last;
last->preOne=first;
}

template <typename Item>
Deque<Item>::~Deque<Item>(){
    Element* checkElement=first;
    for(;checkElement->nextOne;checkElement->nextOne){
        if(checkElement!=first){
            checkElement->preOne->nextOne=NULL;}
        checkElement->preOne=NULL;
        if(checkElement->value){
            delete checkElement->value;
            checkElement->value=NULL;
        }
        
    }
    first=NULL;
    last=NULL;
    
}

template <typename Item>
bool Deque<Item>::isEmpty(){
    if(elementNumber==0){
        return true;
        
    }
    return false;
}

template <typename Item>
int Deque<Item>::size()const{return elementNumber;}

template <typename Item>
void Deque<Item>::addFirst(Item item){
    Element* temp;
    Element* newElement=new Element(item);
    temp=first->nextOne;
    temp->preOne=newElement;
    newElement->nextOne=temp;
    newElement->preOne=first;
    first->nextOne=newElement;
    elementNumber++;
    
}
template <typename Item>
void Deque<Item>::addLast(Item item){
    Element* temp;
    Element* newElement=new Element(item);
    temp=last->preOne;
    temp->nextOne=newElement;
    newElement->preOne=temp;
    newElement->nextOne=last;
    last->preOne=newElement;
    elementNumber++;
}

template <typename Item>
Item Deque<Item>::removeFirst(){

    if(isEmpty()){
     
          error("You are removing from an empty deque! Stop!!!");}//prevent removing from empty deque
    else {
        Element* temp;
        Item returnItem;
        temp=first->nextOne;
          
        first->nextOne=temp->nextOne;
	temp->nextOne->preOne=first;

       
        temp->nextOne=NULL;
        temp->preOne=NULL;
        returnItem = *(temp->value);
        delete temp->value;
        temp->value=NULL;
        elementNumber--;
        return returnItem;
    }
}
template <typename Item>
Item Deque<Item>::removeLast(){
    if(isEmpty()){
      
          error("You are removing from an empty deque! Stop!!!");}//prevent removing from empty deque
    else {
        Element* temp;
        Item returnItem;
        temp=last->preOne;
          
        last->preOne=temp->preOne;
	temp->preOne->nextOne=last;

       
        temp->nextOne=NULL;
        temp->preOne=NULL;
        returnItem = *(temp->value);
        delete temp->value;
        temp->value=NULL;
        elementNumber--;
        return returnItem;
    }
    
}

template <typename Item>
typename Deque<Item>::Iterator Deque<Item>::iterator(){
   if(isEmpty()) {
        return Iterator(*first);
    }
   return Deque<Item>::Iterator(*(first->nextOne));
}

