wanderable: main.o
	g++ main.o -o wanderable
main.o : main.cpp
	g++ -c main.cpp
