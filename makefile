proj4.x: driver.o bet.o
	g++ -std=c++11 driver.o bet.o -o proj4.x

driver.o: driver.cpp bet.h
	g++ -std=c++11 -c driver.cpp
	
bet.o: bet.cpp bet.h
	g++ -std=c++11 -c bet.cpp
	
clean: 
	 rm -f *.o proj4.x
