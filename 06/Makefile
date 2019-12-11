main: main.o format.o
	g++ main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
format.o: format.h
	g++ -c format.h --std=c++14
clean:
	rm *.o
test:
	./main
