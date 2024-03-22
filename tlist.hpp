#ifndef TLIST_H
#define TLIST_H

#include "tnode.h"
#include <iostream>
#include <string>
#include <new>

using namespace std;

// default constructor
template<typename T>
TList<T>::TList() : first(0), last(0), size(0) { 
//empty body
}


// return pointer to newly allocated node
template<typename T>
Node<T> *TList<T>::getNewNode(const T& value){
   return new Node<T>(value);
}


// create list with num copies of val
template<typename T>
TList<T>::TList(T val, int num){
	
	//initialize private data before insertion
	first = 0;
	last = 0;
	size = 0;
	
	//create num nodes of val
	for(int i = 0; i < num; i++){
		InsertFront(val);
	}
}


// destructor
template<typename T>
TList<T>::~TList(){
	
	//if list is not empty
   if(!IsEmpty()){    

		//variables to loop through nodes
		Node<T> *currentPtr = first;
		Node<T> *tempPtr;

	    //loop through all nodes and delete
        while(currentPtr != 0){  
			tempPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete tempPtr;
        }
    }
}	


//copy first and last null
//assigment remove all
template<typename T>
TList<T>::TList(const TList& L){
	
	//delete old list
	first = 0;
	last = 0;
	size = 0;
	
	//create iterator
	TListIterator<T> itr = L.GetIterator();
	
	//loop through L and return data with iterator
	for(int i = 0; i < L.GetSize(); i++){
		InsertBack(itr.GetData());
		itr.Next();
	}
}
	
	
//assignment operator
template<typename T>
TList<T>& TList<T>::operator =(const TList& L){
	
	//delete all nodes
	while(first != 0){
		RemoveFront();
	}
	
	//create iterator
	TListIterator<T> itr = L.GetIterator();
	
	//loop through L with iterator
	for(int i = 0; i < L.GetSize(); i++){
		InsertBack(itr.GetData());
		itr.Next();
	}
	
	//return list with the new data
	return *this;
	
}


//move constructor
template<typename T>
TList<T>::TList(TList&& L){
	size = L.size;
	first = L.first;
	last = L.last;
}


//move assignment operator
template<typename T>
TList<T>& TList<T>::operator =(TList&& L){
	
	//temp variables
	int temp = size;
	Node<T> *tempPtr = 0;
	
	//swap sizes
	size = L.size;
	L.size = temp;
	
	//move first pointers
	tempPtr = first;
	first = L.first;
	L.first = tempPtr;
	
	//move last pointers
	tempPtr = last;
	last = L.last;
	L.last = tempPtr;
	
	//clean up the temp pointer
	delete tempPtr;
	
	//return copied list with copied data
	return *this;	
}


// insert node at front of list
template<typename T>
void TList<T>::InsertFront(const T& d){
	
	//make a new node
    Node<T> *newPtr = getNewNode(d);

    if(IsEmpty()){
		// List is empty
		first = last = newPtr;
    }
    else{  
	    // List is not empty
	    first->prev = newPtr;
	    newPtr->next = first;
	    first = newPtr;
    }
	size++;
} 


// insert node at back of list
template<typename T>
void TList<T>::InsertBack(const T& d){
    
	Node<T> *newPtr = getNewNode(d);
	
    if(IsEmpty()){
		//List is empty
        first = last = newPtr;
	}
    else{  
	    // List is not empty
		last->next = newPtr;
		newPtr->prev = last;
		last = newPtr;
    }
	size++;
} 


// delete node from front of list
template<typename T>
void TList<T>::RemoveFront(){
	
	//make sure list isnt empty
    if(!IsEmpty()){  		

		//temp variables
        Node<T> *tempPtr = first;

		//check for only one node in the list
        if(first == last){
			first = last = 0;
		} 
        else{
			first = first->next;
			first->prev = 0;
		}
		
		//delete the node
        delete tempPtr;
		size--;  			
	} 
} 


// delete node from back of list
template<typename T>
void TList<T>::RemoveBack(){
    
	//make sure list isnt empty
	if(!IsEmpty()){
	   //temp variable
		Node<T> *tempPtr = last;
		
		//check for only one node
        if(first == last){
			first = last = 0;
		}
        else{
			//update new last
			last = last->prev;
			last->next = 0;
        }
		
		//delete the old node
		delete tempPtr;
		size--;
    } 
} 


//check for empty list
template<typename T> 
bool TList<T>::IsEmpty() const{ 
   return first == 0; 
}


//clear the list
template<typename T>
void TList<T>::Clear(){
	
	//loop through all nodes and delete
    while(first != 0){  
		RemoveFront();
    }
}


//return the size
template<typename T>
int TList<T>::GetSize() const{
	return size;
}


//get first
template<typename T>
T& TList<T>::GetFirst() const{
	//check if list is empty
	if(IsEmpty()){
		return dummy;
	}
	else{
		return first->data;
	}
}


//get last
template<typename T>
T& TList<T>::GetLast() const{
	//check if list is empty
	if(IsEmpty()){
		return dummy;
	}
	else{
		return last->data;
	}
}


//set iterator to first
template<typename T>
TListIterator<T> TList<T>::GetIterator() const{
	
	//make new iterator
	TListIterator<T> i;
	i.ptr = first;
	return i;
}


//set iterator to first
template<typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const{
	
	//make new iterator
	TListIterator<T> i;
	i.ptr = last;
	return i;
}


//insert element
template<typename T>
void TList<T>::Insert(TListIterator<T> pos, const T& d){
	
	
	//create node for data
	Node<T> *newPtr = getNewNode(d);
	
	//temp pointer
	Node<T> *tempPtr;
	
	//if list isnt empty
	if(!IsEmpty()){
		//check for first position
		if(!pos.HasPrevious()){
			InsertFront(d);
		}
		//middle positions
		else{
			//store the previous position
			tempPtr = pos.ptr->prev;
			
			//update temp
			tempPtr->next = newPtr;
			
			//update new node
			newPtr->prev = tempPtr;
			newPtr->next = pos.ptr;
			
			//update pos
			pos.ptr->prev = newPtr;
			
			//increase size
			size++;
		}
		
	}
}


//remove element
template<typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos){
	
	//temp pointer
	Node<T> *prevPtr;
	Node<T> *nextPtr;
	Node<T> *killPtr;
	
	//if list isnt empty
	if(!IsEmpty()){
		//check for first position
		cout << "It is not empty" << endl;
		if(!pos.HasPrevious()){
			//cout << "It does not have previous" << endl;
			RemoveFront();
			//cout << "Does it Remove Front" << endl;
			if(pos.HasNext()){
				//cout << "Has next?" << endl;
				pos.Next();
			}
			//only node
			else{
				pos.ptr = 0;
			}
			//cout << "Does it Return?" << endl;
			return pos;
		}
		//check for last
		else if(!pos.HasNext()){
			pos.ptr = 0;
			RemoveBack();
			return pos;
		}
		else{
			//pointer to delete
			killPtr = pos.ptr;
			
			//surrounding nodes
			prevPtr = pos.ptr->prev;
			nextPtr = pos.ptr->next;
			
			//update surrouding nodes
			prevPtr->next = nextPtr;
			nextPtr->prev = prevPtr;
			
			//delete node
			delete killPtr;
			pos.Next();
			size--;
			return pos;
		}
		
	}
}


//print the list
template<typename T>
void TList<T>::Print(std::ostream& os, char delim) const{
	
	//print the list if it isnt empty
	if(!IsEmpty()){
		//create iterator
		TListIterator<T> i = GetIterator();
		
		//loop through the list
		for(int j = 0; j < size; j++){
			//print the data followed by the delimiter
			os << i.GetData() << delim;
			i.Next();
		}
	}
	//end the line
	os << endl;
}


//add lists together operator + overload
template<typename T>
TList<T> operator +(const TList<T>& t1, const TList<T>& t2){
	
	//create a temp list and store t1
	TList<T> tempList = t1;
	
	//create iterator to traverse the second list
	TListIterator<T> i = t2.GetIterator();
	
	//if list isnt empty
	if(!t2.IsEmpty()){
		//add each element of t2 to the back of the list
		for(int j = 0; j < t2.GetSize(); j++){
			tempList.InsertBack(i.GetData());
			i.Next();
		}
		//return the list
		return tempList;
	}
	//if second list is empty just return the first one
	else{
		return tempList;
	}
}


//******************************************** TListIterator Class **********************************************

//default constructor
template<typename T>
TListIterator<T>::TListIterator(){
	ptr = 0;
}


//has next function
template<typename T>
bool TListIterator<T>::HasNext() const{
	//return true if there is another element in the list
	return ptr->next != 0;
}


//has previous element in list
template<typename T>
bool TListIterator<T>::HasPrevious() const{
	//return true if there is an element behind in the list
	return ptr->prev != 0;
} 


//next -- advance to next element
template<typename T>
TListIterator<T> TListIterator<T>::Next(){
	
	//check to see if there is data 
	if(HasNext()){
		ptr = ptr->next;
		return *this;
	}
	//return null if there is no next 
	else{
		ptr = 0;
		return *this;
	}
}


//previous -- move to previous element
template<typename T>
TListIterator<T> TListIterator<T>::Previous(){
	
	//check for previous data
	if(HasPrevious()){
		ptr = ptr->prev;
		return *this;
	}
	else{
		ptr = 0;
		return *this;
	}
}


//return data at the pointer
template<typename T>
T& TListIterator<T>::GetData() const{
	
	if(ptr != 0){
		return ptr->data;
	}
	else{
		return TList<T>::dummy;
	}
}


#endif