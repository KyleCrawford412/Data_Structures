#ifndef BET_H
#define BET_H

#include <iostream>

using namespace std;

class BET{
	
	private:
	// nested Node class
	struct BinaryNode{
		string data;
		BinaryNode *leftChild;
		BinaryNode *rightChild;

		BinaryNode(const string& d = string{}, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : data(d), leftChild(l), rightChild(r){
			
		}
		BinaryNode(string&& d, BinaryNode *l = nullptr, BinaryNode *r = nullptr) : data(std::move(d)), leftChild(l), rightChild(r){
			
		}
    };
	
	public:
	BET();
	BET(const string& postfix);
	BET(const BET&);
	~BET();
	bool buildFromPostfix(const string& postfix);
	//assignment operator
	const BET& operator =(const BET&);
	void printInfixExpression();
	void printPostfixExpression();
	size_t size();
	size_t leaf_nodes();
	bool empty();
	
	private:
	void printInfixExpression(BinaryNode *n);
	void makeEmpty(BinaryNode* &t);
	BinaryNode* clone(BinaryNode* t);
	void printPostfixExpression(BinaryNode *n);
	size_t size(BinaryNode *t);
	size_t leaf_nodes(BinaryNode *t);
	bool isOperator(const string token);
	bool checkExpression(const string& postfix);
	
	//start of tree
	BinaryNode *root;
	
	
	
};

#endif