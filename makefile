proj2.x: test_list.cpp List.hpp
	 g++ -std=c++11 test_list.cpp -o proj2.x

clean: 
	 rm -f *.o proj2.x
