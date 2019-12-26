CF = -std=c++11 -O3 -Wall -pedantic

all: main.o
	g++ main.o -o program

main.o: main.cpp
	g++ -c $(CF) main.cpp -o main.o
clean:
	rm *.o program
