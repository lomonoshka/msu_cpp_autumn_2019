CC=g++

all: ar_col ar_row

ar_col: array_col.o
	$(CC) -o ar_col array_col.o

array_col.o: array_col.cpp
	$(CC) -c array_col.cpp

ar_row: array_row.o
	$(CC) -o ar_row array_row.o

array_row.o: array_row.cpp
	$(CC) -c array_row.cpp

clean:
	rm -rf *.o ar_col ar_row
