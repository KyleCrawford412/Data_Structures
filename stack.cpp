#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

int main(){
	
	//declare stack
	stack<char> s;
	
	string check;
	
	
	while(cin){
		
		getline(cin, check);
		for(int i = 0; i < check.size(); i++){
		
			switch(check[i]){
				case '{': {
					s.push('{');
					break;
				}
				case '}': {
					if(!s.empty()){
						if(s.top() != '{'){
							cout << "Error, expecting: '{'" << endl;
							return 0;
						}
						else{
							s.pop();
						}
					}
					else{
						cout << "Error, missing '{'" << endl;
						return 0;
					}
					break;
				}
				case '[': {
					s.push('[');
					break;
				}
				case ']': {
					if(!s.empty()){
						if(s.top() != '['){
							cout << "Error, expecting: '['" << endl;
							return 0;
						}
						else{
							s.pop();
						}
					}
					else{
						cout << "Error, missing '[' characters" << endl;
						return 0;
					}
					break;
				}
				case '(': {
					s.push('(');
					break;
				}
				case ')': {
					if(!s.empty()){
						if(s.top() != '('){
							cout << "Error, expecting: '('" << endl;
							return 0;
						}
						else{
							s.pop();
						}
					}
					else{
						cout << "Error, missing '(' characters" << endl;
						return 0;
					}
					break;
				}
			}
		}
	}
	
	if(!s.empty()){
		cout << "Error, expecting closing characters ')', '}' or ']'" << endl;
		return 0;
	}
	else{
		cout << "All symbols are appropriately balanced" << endl;
	}
	
}