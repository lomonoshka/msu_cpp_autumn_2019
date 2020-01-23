main: main.o pthread.o 
	g++ main.o pthread.o -o main -pthread --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
pthread.o: pthread.cpp
	g++ -c pthread.cpp --std=c++14
clean:
	rm *.o
test:
	./main
