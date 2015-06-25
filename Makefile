all: first
first:
	gcc -c -fPIC LibraryLong.c -o LibraryLong.o
	gcc -shared -o LibraryLong.so LibraryLong.o
	gcc -c main.c
	gcc main.o -L. -lLibaryLong -o TCHMK-1

second:
	g++ --c -fPIC ClassLong.cpp -o ClassLong.o LibraryLong.c -o LibraryLong.o
	g++ -shared  o ClassLong.so ClassLong.o LibraryLong.so LibraryLong.o
	g++ -c main.cpp
	g++  main.o -L. -lClassLong -lLibraryLong -o TCHMK-2
