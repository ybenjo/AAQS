# Makefile

test: bigraph.o cohits.o
	g++ -O3 -lgtest -lpthread ./src/tests/test.cpp bigraph.o cohits.o -o test

main: bigraph.o
	g++ -O3 ./src/main.cpp bigraph.o -o main

bigraph.o:
	gcc -O3 -c ./src/bigraph.cpp

cohits.o:
	gcc -O3 -c ./src/cohits.cpp

clean:
	rm -f bigraph.o cohits.o