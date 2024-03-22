#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>

using namespace std;
namespace cop4530 {

 template <typename T>
    class Stack {
		
		
		public:
			//zero param constructor 
			Stack();
			//destructor 
			~Stack();
			//copy constructor
			Stack(const Stack&);
			//move constructor
			Stack(Stack&&);
			//copy assignment operator =
			Stack<T>& operator =(const Stack&);
			//move assignment operator =
			Stack<T>& operator =(Stack&&);
			
			bool empty() const;
			void clear();
			void push(const T&);
			void push(T&&);
			void pop();
			T& top();
			const T& top() const;
			int size() const;
			void print(ostream& os, char ofc = ' ') const;
			
			
		private:
			vector<T> v;
			
    };

   // overloading comparison operators
   template <typename T>
      bool operator ==(const Stack<T>& lhs, const Stack<T>& rhs);

   template <typename T>
      bool operator !=(const Stack<T>& lhs, const Stack<T>& rhs);
	  
   template <typename T>
	  bool operator <=(const Stack<T>& lhs, const Stack<T>& rhs);

   // overloading output operator
   template <typename T>
      ostream& operator <<(ostream &os, const Stack<T> &s);

   // include the implementation file here

#include "stack.hpp"

} // end of namespace 4530

#endif