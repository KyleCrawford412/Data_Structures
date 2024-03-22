#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"
#include <iostream>
#include <string>
#include <new>

using namespace cop4530;

//------------------------------------------------ const_iterator Class ------------------------------------------------------------------------------------

//default iterator constructor, set current to null
template <typename T>
List<T>::const_iterator::const_iterator(){
	current = 0;
}

//return reference to element in list
template <typename T>
const T& List<T>::const_iterator::operator *() const{
	return retrieve();
}

//increment the iterator (prefix)
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator ++(){
	current = current->next;
	return *this;
}

//increment the iterator (postfix)
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator ++(int){
	const_iterator temp = *this;
	++(*this);
	return temp;
}

//decrement the operator
template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator --(){
	current = current->prev;
	return *this;
}

//decrement the operator
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator --(int){
	const_iterator temp = *this;
	--(*this);
	return temp;
}

//comparison operator for equals
template <typename T>
bool List<T>::const_iterator::operator ==(const const_iterator& rhs) const{
	return current == rhs.current;
}

//comparison operator for not equals
template <typename T>
bool List<T>::const_iterator::operator !=(const const_iterator& rhs) const{
	return !(*this == rhs);
}

//return reference to corresponding element in the list
template <typename T>
T& List<T>::const_iterator::retrieve() const{
	return current->data;
}

//one parameter constructor to set current to given pointer
template <typename T>
List<T>::const_iterator::const_iterator(Node *p){
	current = p;
}

//------------------------------------------------ iterator Class ------------------------------------------------------------------------------------------

//default constructor
template <typename T>
List<T>::iterator::iterator(){
	
}

//returns a reference to the corresponding element in the list by calling retrieve()
template <typename T>
T& List<T>::iterator::operator *(){
	return const_iterator::retrieve();
}

//returns a reference to the corresponding element in the list
template <typename T>
const T& List<T>::iterator::operator *() const{
	return const_iterator::operator *();
}

//increment the iterator, prefix
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++(){
	this->current = this->current->next;
	return *this;
}

//increment operator, postfix
template <typename T>
typename List<T>::iterator List<T>::iterator::operator ++(int){
	iterator temp = *this;
	++(*this);
	return temp;
}

//decrement operator, prefix
template <typename T>
typename List<T>::iterator& List<T>::iterator::operator --(){
	this->current = this->current->prev;
	return *this;
}

//decrement operator, postfix
template <typename T>
typename List<T>::iterator List<T>::iterator::operator --(int){
	iterator temp = *this;
	--(*this);
	return temp;
}

//one parameter contructor
template <typename T>
List<T>::iterator::iterator(Node *p): const_iterator(p){
}

//------------------------------------------------ List Class ----------------------------------------------------------------------------------------------

template <typename T>
void List<T>::init(){
	//set up dummy nodes
	head = new Node;
	tail = new Node;
	
	//set dummy node pointers
	head->next = tail;
	tail->prev = head;
	
	theSize = 0;
} 

//default contructor, no params
template <typename T>
List<T>::List(){
	init();
}

//copy constructor
template <typename T>
List<T>::List(const List& rhs){
	//set up the list
	init();
	
	//copy data
	for(auto& x : rhs){
		push_back(x);
	}
}

//move contructor
template <typename T>
List<T>::List(List&& rhs){
	//set up the list
	init();
	
	//swap the data
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
}

//create a list with num Nodes of val
template <typename T>
List<T>::List(int num, const T& val){
	//set up the list
	init();
	
	//create num Nodes of val
	for(int i = 0; i < num; i++){
		push_front(val);
	}
}

//constructs with elements start and end
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
	//set up the list
	init();
	
	//traverse elements in list until reaching end position
	auto itr = start;
	while(itr != end){
		//insert element
		push_back(*itr);
		itr++;
	}
}

//constructs with a copy of each of the elements in the initializer list
template <typename T>
List<T>::List(std::initializer_list<T> iList){
	//construct list
	init();
	
	//create iterator and copy elements
	for(auto itr = iList.begin(); itr != iList.end(); itr++){
		//add elements to back of list
		push_back(*itr);
	}
}

//destructor
template <typename T>
List<T>::~List(){
	//delete all the nodes
	clear();
	delete head;
	delete tail;
}

//copy assignement operator
template <typename T>
const List<T>& List<T>::operator =(const List& rhs){
	
	//delete all the current nodes
	clear();
	
	//swap the data
	List temp = rhs;
	std::swap(*this, temp);
	return *this;
	
}

//move assignment operator
template <typename T>
List<T>& List<T>::operator =(List&& rhs){
	
	//swap values
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);
	
	return *this;
}

//sets list to the elements of the initializer_list
template <typename T>
List<T>& List<T>::operator =(std::initializer_list<T> iList){
	//clear the list
	clear();
	
	//create iterator and copy all elements from iList
	for(auto itr = iList.begin(); itr != iList.end(); itr++){
		push_back(*itr);
	}
	
}

//returns the size
template <typename T>
int List<T>::size() const{
	return theSize;
}

//checks for empty list
template <typename T>
bool List<T>::empty() const{
	return (head->next == tail);
}

//delete all non dummy nodes
template <typename T>
void List<T>::clear(){
	//delete nodes until empty
	while(!empty()){
		pop_front();
	}
}

//reverse the list 
template <typename T>
void List<T>::reverse(){
	//create temp list
	List temp;
	
	//create iterator
	iterator itr = begin();
	
	//traverse list using iterator
	while(itr != end()){
		//push element to the front, reverse the order
		temp.push_front(itr.retrieve());
		itr++;
	}
	
	std::swap(head, temp.head);
	std::swap(tail, temp.tail);
}

//return reference to first element in the list
template <typename T>
T& List<T>::front(){
	return *begin();
}

//return reference to first element in the list
template <typename T>
const T& List<T>::front() const{
	return *begin();
}

//return reference to last element in the list
template <typename T>
T& List<T>::back(){
	return *--end();
}

//return reference to last element in the list
template <typename T>
const T& List<T>::back() const{
	return *--end();
}

//add element to the front of the list
template <typename T>
void List<T>::push_front(const T& val){
	insert(begin(), val);
}

//add element to the front of the list
template <typename T>
void List<T>::push_front(T&& val){
	insert(begin(), std::move(val));
}

//add element to back of the list
template <typename T>
void List<T>::push_back(const T& val){
	insert(end(), val);
}

//add element to back of the list
template <typename T>
void List<T>::push_back(T&& val){
	insert(end(), std::move(val));
}

//remove first element of the list
template <typename T>
void List<T>::pop_front(){
	erase(begin());
}

//remove last element in the list
template <typename T>
void List<T>::pop_back(){
	erase(--end());
}

//remove all elements with the same value
template <typename T>
void List<T>::remove(const T& val){
	//create iterator
	iterator itr = begin();
	
	//traverse list with iterator
	while(itr != end()){
		//check for target value
		if(itr.retrieve() == val){
			//remove element
			itr = erase(itr);
		}
		else{
			itr++;
		}
	}
}

//remove all elements for pred returns true
template <typename T>
template <typename PREDICATE>
void List<T>::remove_if(PREDICATE pred){
	//create iterator
	iterator itr = begin();
	//traverse list
	while(itr != end()){
		//check if pred returns true on element
		if(pred(*itr)){
			//erase element
			itr = erase(itr);
		}
		else{
			itr++;
		}
	}
	
}

//print all elements in the list
template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
	//check for empty list
	if(!empty()){
		//create iterator
		const_iterator itr = begin();
		//traverse list
		while(itr != end()){
			os << itr.retrieve() << ofc;
			itr++;
		}
	}
}

//return iterator to first element in the list
template <typename T>
typename List<T>::iterator List<T>::begin(){
	return iterator(head->next);
}

//return const_iterator to first element in the list
template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
	return const_iterator(head->next);
}

//return iterator to last element in the list
template <typename T>
typename List<T>::iterator List<T>::end(){
	return iterator(tail);
}

//return const_iterator to last element in the list
template <typename T>
typename List<T>::const_iterator List<T>::end() const{
	return const_iterator(tail);
}

//insert value ahead of iterator
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){
	//temp pointer
	Node *p = itr.current;
	
	//increase the size
	theSize++;
	
	//insert new node into the list
	return iterator(p->prev = p->prev->next = new Node(val, p->prev, p));
}

//insert value ahead of iterator
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val){
	//temp pointer
	Node *p = itr.current;
	
	//increase the size
	theSize++;
	
	//insert new node into the list
	return iterator(p->prev = p->prev->next = new Node(std::move(val), p->prev, p));
}

//erase the element at the iterator
template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
	//temp pointer
	Node *p = itr.current;
	
	//delete the list element
	iterator retVal(p->next);
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	
	//update size
	theSize--;
	
	//return the iterator
	return retVal;
}

//erase a range of elements in the list
template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
	//traverse elements in list until reaching end position
	while(start != end){
		//delete element
		start = erase(start);
	}
	return end;
}

//equals comparison operator
template <typename T>
bool operator ==(const List<T>& lhs, const List<T>& rhs){
	//create iterators
	auto left = lhs.begin();
	auto right = rhs.begin();
	
	//check for empty lists
	if(lhs.size() != rhs.size()){
		return false;
	}
	//lists are not empty
	else if(!(lhs.empty()) && !(rhs.empty())){
		//loop both sides
		while((left != lhs.end()) && (right != rhs.end())){
			//check for inequality
			if(*left != *right){
				return false;
			}
			//update iterators
			left++;
			right++;
		}
		//check for both lists at the end
		if((left == lhs.end()) && (right == rhs.end())){
			return true;
		}
	}
}

//not equals comparison operator
template <typename T>
bool operator !=(const List<T>& lhs, const List<T>& rhs){
	return !(lhs == rhs);
}

//operator out
template <typename T>
std::ostream& operator <<(std::ostream& os, const List<T>& L){
	//print the list
	L.print(os);
	return os;
} 

#endif