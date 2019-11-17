main: main.o Serializer.o
	g++ main.o -o main --std=c++14
main.o: main.cpp
	g++ -c main.cpp --std=c++14
Serializer.o: Serializer.cpp Serializer.h
	g++ -c Serializer.cpp --std=c++14
Deserializer.o: Deserializer.cpp Deserializer.h
	g++ -c Deserializer.cpp --std=c++14
clean:
	rm *.o
test:
	./main
