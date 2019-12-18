main: main.o calculator.o
	g++ -fsanitize=address main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
calculator.o: calculator.cpp calculator.h
	g++ -c calculator.cpp --std=c++14
clean:
	rm *.o
test:
	./main
