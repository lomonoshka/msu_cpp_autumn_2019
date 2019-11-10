main: main.o matrix.o
	g++ -fsanitize=address main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
allocator.o: matrix.cpp matrix.h
	g++ -c matrix.cpp --std=c++14
clean:
	rm *.o
test:
	./main
