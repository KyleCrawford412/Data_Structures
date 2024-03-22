in2post.x: in2post.cpp stack.hpp
	 g++ -std=c++11 in2post.cpp -o in2post.x

clean: 
	 rm -f *.o in2post.x
