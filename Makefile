all: first
first:
	gcc -c -fPIC LibraryLong.c -o LibraryLong.o
	gcc -shared -o LibraryLong.so LibraryLong.o
	gcc -c main.c
	gcc main.o -L. -lLibaryLong -o FirstLab

second:
	g++ -c -fPIC LibraryLong.c -o LibraryLong.o
	g++ -c -fPIC ClassLong.c -o ClassLong.o
	g++ -shared -o libClassLong.so LibraryLong.o ClassLong.o
	g++ -c main.cpp
	g++ mainsec.o -L. -lClassLong -o SecondLab
