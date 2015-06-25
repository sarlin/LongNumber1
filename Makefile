all: first
first:
	gcc main.c LibraryLong.c -o TCHMK-1.exe

second:
	g++ -c ClassLong.cpp LibraryLong.c
	g++ -shared -o ClassLong.dll ClassLong.o LibraryLong.o
	g++ main.cpp ClassLong.dll -I. -Wl,-rpath,. -L. -o TCHMK-2.exe
	rm -rf *.o
