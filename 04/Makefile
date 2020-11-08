CC = g++ -std=c++17

main: main.o Bigint.o
	$(CC) main.o Bigint.o -o main 

main.o: main.cpp
	$(CC) -c main.cpp 

Bigint.o: Bigint.cpp Bigint.h
	$(CC) -c Bigint.cpp 

clean:
	rm *.o

test:
	./main
