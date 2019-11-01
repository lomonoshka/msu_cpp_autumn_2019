main: main.o Bigint.o
	g++ -fsanitize=address main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
allocator.o: Bigint.cpp Bigint.h
	g++ -c Bigint.cpp --std=c++14
clean:
	rm *.o
run:
	./main
test:
	python3 ./tester.py
