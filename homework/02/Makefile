main: main.o allocator.o
	g++ -fsanitize=address main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
allocator.o: allocator.cpp allocator.h
	g++ -c allocator.cpp --std=c++14
clean:
	rm *.o
run:
	./main
test:
	python3 ./tester.py
