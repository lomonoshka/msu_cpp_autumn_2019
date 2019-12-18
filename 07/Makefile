main: main.o pthread.o
	g++ main.o -o main -pthread --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
pthread.o: pthread.h pthread.cpp
	g++ -c pthread.cpp pthread.h --std=c++14
clean:
	rm *.o
test:
	./main
