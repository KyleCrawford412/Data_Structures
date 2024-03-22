#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <ctype.h>
#include "stack.h"

using namespace std;
using namespace cop4530;


int findOrder(const string token);
bool order(const string lhs, const string rhs);
bool isOperator(const string token);
bool isOperand(const string token);
bool checkParentheses(const string str);
bool validFormat(const string str);
void convert(const vector<string> &infix, bool eval);
void evaluate(const string post);

int main(){

	//initialize variables
    bool onlyNums;
    bool balanced;
	bool correctFormat;
	bool running = true;	
	vector<string> exp;
	string expression;
	string token;
    string quit = "quit";
	
    while(running){
		
		//reset the data
        expression = "";
        token = "";
        onlyNums = true;
        balanced = true;
		exp.clear();
		
		//get the expression from user and use stringstream
        cout << "Enter 'q/Q' to end the program, or enter an expression to evaluate: ";
        getline(cin, expression);
		stringstream str(expression);
		
		//check for termination
		if((expression == "Q") || (expression == "q")){
			cout << "Exiting the program." << endl;
			running = false;
			return 0;
		}
		
		//check for errors in the expression
		balanced  = checkParentheses(expression);
		correctFormat = validFormat(expression);
		
		//if expression is balanced
		if(balanced && correctFormat){
			//read all the tokens from input
			for(int i = 0; i < expression.size(); i++){
				if(isalpha(expression[i])){
					onlyNums = false;
				}
			}
			while(str >> token){
				exp.push_back(token);
			}
			//convert expression to postfix and then evaluate
			convert(exp, onlyNums);
		}
		//expression isnt balanced
		else{
			cout << "Error, enter a new expression." << endl;
		}
	
    }    
}

//check for precedence
bool order(string lhs,string rhs){
    return (findOrder(lhs) >= findOrder(rhs));
}

//get numeric precedence of operator
int findOrder(string token){
    int opOrder;
	if(token == "("){
		opOrder = 3;
	}
    else if(token == "*" || token == "/"){ 
		opOrder = 2;
	}
    else if(token == "+" || token == "-"){ 
		opOrder = 1;
	}
    return opOrder;
}

//check to see if token is an operator
bool isOperator(string token){
    return (token == "*" || token == "/" || token == "+" || token == "-" || token == "(");
}

//check to see if token is an operand
bool isOperand(string token){
    if(token == ")"){
		return false;
	}
	else{
		return !(isOperator(token));
	}
}

//check for balanced parentheses
bool checkParentheses(const string expression){
	stringstream str(expression);
	string token;
	int numOpen = 0;
	int numClosed = 0;
	
	while(str >> token){
		if(token == "("){
			numOpen++;
		}
		else if(token == ")"){
			numClosed++;
		}
	}
	
	if(numOpen == numClosed){
		return true;
	}
	else{
		cout << "Error: mismatched parentheses." << endl;
		return false;
	}
	
}

//convert infix to postfix
void convert(const vector<string> &infix, bool canEvaluate){
	//use stack of tokens
	Stack<string> s;
	string post;
	
	//loop through all tokens in vector
	for(int i = 0; i < infix.size(); i++){
		//print out operands
		if(isOperand(infix[i])){ 
			cout << infix[i] << " ";
			post = post + infix[i] + " ";
		}
		//print out previous operators of greater precedence then push new operator
		else if(isOperator(infix[i])){
			while (!(s.empty()) && (s.top() != "(") && (order(s.top(), infix[i]))){
				cout << s.top() << " "; 
				post = post + s.top() + " ";
				s.pop();
			}
			s.push(infix[i]);
		}
		//print out anything inside parentheses
		else if(infix[i] == ")"){
			while(s.top() != "("){
				cout << s.top() << " "; 
				post = post + s.top() + " ";
				s.pop();
			}
			s.pop(); 
		}	
	}
	
	//print remaining operators
	while(!s.empty()){ 
		cout << s.top() << " "; 
		post = post + s.top() + " ";
		s.pop(); 
	}
	
	cout << endl;
	
	//if expression can be evaluated
	if(canEvaluate){
		evaluate(post);
	}
	//if it can't be evaluated print conversion
	else{
		cout << "Solution: " << post << endl;
	} 
	
	
}

//evaluate postfix expressions
void evaluate(const string expression){
	//use stack of tokens and stringstream 
	Stack<double> tokens;
	stringstream str(expression);
	string token;
	
	//variables for evaluation
	double a, b, temp;
	std::string::size_type sz;
	
	while(str >> token){
		if(isOperand(token)){
			temp = stod(token, &sz);
			tokens.push(temp);
		}
		else{
			a = tokens.top();
			tokens.pop();
			b = tokens.top();
			tokens.pop();
			if(token == "*"){
				tokens.push(a*b);
			}
			else if(token == "/"){
				tokens.push(b/a);
			}
			else if(token == "+"){
				tokens.push(a+b);
			}
			else{
				tokens.push(b-a);
			}
		}
	}
	
	//print solution from top of stack
	cout << "Solution: " << tokens.top();
}

//check to make sure there are a correct number of operators and operands
bool validFormat(const string expression){
	stringstream str(expression);
	string token;
	
	int numOperators = 0;
	int numOperands = 0;
	
	//count the number of operators and operands
	while(str >> token){
	if((isOperand(token)) && (token != "(") && (token != ")")){
			numOperands++;
		}
		else if((isOperator(token)) && (token != "(")){
			numOperators++;
		}
	}
	
	//should be one less operator than operand
	if(numOperands % numOperators == 1){
		return true;
	}
	else{
		cout << "Error: missing operators or operands" << endl;
		return false;
	}
}