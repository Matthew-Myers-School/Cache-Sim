all:	project2

project2:	project2.o
	g++ project2.o -o cache-sim

project2.o: project2.cpp
	g++ -c project2.cpp

clean:
	rm -f *.o cache-sim
