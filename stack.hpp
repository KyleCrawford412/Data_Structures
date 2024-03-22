#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"
#include <iostream>

using namespace std;
using namespace cop4530;

//------------------------------------------------------------------- Class Stack --------------------------------------------------------------------------
//default constructor no parameters
template <typename T>
Stack<T>::Stack(){
	
}

//destructor
template <typename T>
Stack<T>::~Stack(){
	v.clear();
}

//copy constructor
template <typename T>
Stack<T>::Stack(const Stack& s){
	//resize the vector
	v.resize(s.v.size());
	
	//copy the data
	for(int i = 0; i < size(); i++){
		v[i] = s.v[i];
	}
	
}

//move constructor
template <typename T>
Stack<T>::Stack(Stack&& s){
	//swap
	swap(v, s.v);
}

//copy assignment operator 
template <typename T>
Stack<T>& Stack<T>::operator =(const Stack& s){
	//clear current vector
	v.clear();
	
	//resize
	v.resize(v, s.v);
	
	//copy the data
	for(int i = 0; i < size(); i++){
		v[i] = s.v[i];
	}
	
	return *this;
}

//move assignment operator
template <typename T>
Stack<T>& Stack<T>::operator =(Stack&& s){
	//swap vectors
	swap(v, s.v);
	
	//return 
	return *this;
}

//check for empty stack
template <typename T>
bool Stack<T>::empty() const{
	return v.empty();
}

//clear the stack
template <typename T>
void Stack<T>::clear(){
	v.clear();
}

//add element to stack
template <typename T>
void Stack<T>::push(const T& x){
	v.push_back(x);
}

//add element to stack
template <typename T>
void Stack<T>::push(T&& x){
	v.push_back(x);
}

//pop element from stack
template <typename T>
void Stack<T>::pop(){
	v.pop_back();
}

//view the top element of the stack
template <typename T>
T& Stack<T>::top(){
	return v.back();
}

//view the top element of the stack
template <typename T>
const T& Stack<T>::top() const{
	return v.back();
}


//return size of stack
template <typename T>
int Stack<T>::size() const{
	return v.size();
}

//print all the elements in the stack from the bottom up
template <typename T>
void Stack<T>::print(ostream& os, char ofc) const{
	//print the stack
	for(int i = 0; i < v.size(); i++){
		os << v[i] << ofc;
	}
}

//-------------------------------------------------------------------------- non-memeber functions ---------------------------------------------------------------------------
//check for equality of two stacks
template <typename T>
bool operator ==(const Stack<T>& lhs, const Stack<T>& rhs){
	//if the sizes are different return false
	if(lhs.size() != rhs.size()){
		return false;
	}
	//if sizes are the same check the elements
	else{
		Stack<T> lhs2 = lhs;
		Stack<T> rhs2 = rhs;
		//loop through each element
		for(int i = 0; i < lhs.size(); i++){
			//return false if any elements are different
			if(lhs2.top() != rhs2.top()){
				return false;
			}
			lhs2.pop();
			rhs2.pop();
		}
		//if it made it this far all elements are the same
		return true;
	}
}

//check to see if the two stacks are different
template <typename T>
bool operator !=(const Stack<T>& lhs, const Stack<T>& rhs){
	return !(lhs == rhs);
}

//check to see if every element in left hand side is equal to or smaller than the right hand side
template <typename T>
bool operator <=(const Stack<T>& lhs, const Stack<T>& rhs){
	//if left hand side has more elements return false
	if(lhs.size() > rhs.size()){
		return false;
	}
	//if left is smaller than or equal to size of right check all elements of left hand side
	else{
		Stack<T> lhs2 = lhs;
		Stack<T> rhs2 = rhs;
		//loop through each element on left 
		for(int i = 0; i < lhs.size(); i++){
			//return false if any elements are larger than right hand side
			if(lhs2.top() > rhs2.top()){
				return false;
			}
			lhs2.pop();
			rhs2.pop();
		}
		//if it made it this far all elements are either less than or equal to the right 
		return true;
	}
}

//print all elements in the stack
template <typename T>
void operator <<(ostream& os, const Stack<T>& s){
	s.print();
	return os;
}

#endif