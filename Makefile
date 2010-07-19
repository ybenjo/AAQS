# Makefile

test: bigraph.o cohits.o
	g++ -O3 -Wall -lgtest -lpthread ./src/tests/test.cpp bigraph.o cohits.o -o test

main: bigraph.o cohits.o
	g++ -O3 -Wall ./src/main.cpp bigraph.o cohits.o -o main

bigraph.o:
	gcc -O3 -Wall -c ./src/bigraph.cpp

cohits.o:
	gcc -O3 -Wall -c ./src/cohits.cpp

clean:
	rm -f bigraph.o cohits.o