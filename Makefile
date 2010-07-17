# Makefile

test: bigraph.o
	g++ -O3 -lgtest -lpthread ./src/tests/test.cpp bigraph.o -o test

main: bigraph.o
	g++ -O3 ./src/main.cpp bigraph.o -o main

bigraph.o:
	gcc -O3 -c ./src/bigraph.cpp

clean:
	rm -f bigraph.o