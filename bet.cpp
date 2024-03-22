#ifndef BET_CPP
#define BET_CPP

#include "bet.h"
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

//-------------------------------------------------- public functions --------------------------------------------------
BET::BET(){
	root = 0;
}

BET::BET(const string& postfix){
	buildFromPostfix(postfix);
}

//copy constructor
BET::BET(const BET& rhs){
	root = 0;
	root = clone(rhs.root);
}

BET::~BET(){
	makeEmpty(root);
}

bool BET::buildFromPostfix(const string& postfix){
	
	bool check = checkExpression(postfix);
	if(check){
		string token;
		
		stack<BinaryNode*> s;
		
		int operators = 0;
		int operands = 0;
		
		BinaryNode* op;
		
		stringstream str(postfix);
		while(str >> token){
			if(!isOperator(token)){
				op = new BinaryNode(token);
				s.push(op);
				operands++;
			}
			else if(isOperator(token)){
				op = new BinaryNode(token);
				op->rightChild = s.top();
				s.pop();
				op->leftChild = s.top();
				s.pop();
				operators++;
				s.push(op);
			}
		}
		
		root = s.top();	
	}
	else{
		return false;
	}
	
}

bool BET::checkExpression(const string& postfix){
	string token;
	stringstream str(postfix);
	
	int operators = 0;
	int operands = 0;
	
	while(str >> token){
		if(isOperator(token)){
			operators++;
		}
		else{
			operands++;
		}
	}
	
	if(operators + 1 == operands){
		return true;
	}
	else{
		return false;
	}
}

//assignment operator
const BET& BET::operator =(const BET& rhs){
	makeEmpty(root);
	root = clone(rhs.root);
	return *this;
}

void BET::printInfixExpression(){
	printInfixExpression(root);
}

void BET::printPostfixExpression(){
	printPostfixExpression(root);
}

size_t BET::size(){
	return size(root);
}

size_t BET::leaf_nodes(){
	return leaf_nodes(root);
}

bool BET::empty(){
	return (root == 0);
}

//-------------------------------------------------- private functions --------------------------------------------------

void BET::printPostfixExpression(BinaryNode* n){
	if(n != 0){
		printPostfixExpression(n->leftChild);
		printPostfixExpression(n->rightChild);
		cout << n->data << " ";
	}
}

void BET::printInfixExpression(BinaryNode* n){
	//if expression needs closting parentheses
	bool needsClosing = false;
	
	//check for empty node
	if(n != 0){
		
		if((n->leftChild != 0) && (isOperator(n->leftChild->data))){
			cout << "( ";
			needsClosing = true;
		}
		
		//recursively call left child
		printInfixExpression(n->leftChild);
		
		//close parentheses
		while(needsClosing){
			cout << ") ";
			needsClosing = false;
		}
		
		//print out the data
		cout << n->data << " ";
		
		if((n->rightChild != 0) && (isOperator(n->rightChild->data))){
			cout << "( ";
			needsClosing = true;
		}
		
		//recursively call right child
		printInfixExpression(n->rightChild);
		
		//close parentheses
		if(needsClosing){
			cout << ") ";
		}
	}
	
}

void BET::makeEmpty(BinaryNode* &t){
	//check for empty tree
	if(t != 0){
		//recursively call for children
		makeEmpty(t->leftChild);
		makeEmpty(t->rightChild);
		delete t;
	}
	t = 0;
}

BET::BinaryNode* BET::clone(BinaryNode* t){
	if(t == 0){
		return 0;
	}
	else{
		return new BinaryNode(t->data, clone(t->leftChild), clone(t->rightChild));
	}
}

size_t BET::size(BinaryNode* t){
	//return zero for empty tree
	if(t == 0){
		return 0;
	}
	//else recursively count nodes
	else{
		return size(t->leftChild) + size(t->rightChild) + 1;
	}
}

size_t BET::leaf_nodes(BinaryNode* t){
	int leaves = 0;
	if(t == 0){
		return 0;
	}
	else{
		if((t->leftChild != 0) || (t->rightChild != 0)){
			return leaf_nodes(t->leftChild) + leaf_nodes(t->rightChild) + 0;
		}
		else{
			return 1;
		}
	}	
}

//check if string passed in is an operand
bool BET::isOperator(const string token){
	return (token == "(" || token == "*" || token == "/" || token == "+" || token == "-");
}
#endif