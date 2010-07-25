# Makefile

CXX=g++
CXX_FLAGS=-O3 -Wall

test: bigraph.o cohits.o hitting_time.o rwr.o
	${CXX} ${CXX_FLAGS} -lgtest -lpthread ./src/tests/test.cpp bigraph.o cohits.o hitting_time.o rwr.o -o test

main: bigraph.o cohits.o hitting_time.o rwr.o
	${CXX} ${CXX_FLAGS} ./src/main.cpp bigraph.o cohits.o hitting_time.o rwr.o -o main

bigraph.o:
	${CXX} ${CXX_FLAGS} -c ./src/bigraph.cpp

cohits.o:
	${CXX} ${CXX_FLAGS} -c ./src/cohits.cpp

hitting_time.o:
	${CXX} ${CXX_FLAGS} -c ./src/hitting_time.cpp

rwr.o:
	${CXX} ${CXX_FLAGS} -c ./src/rwr.cpp

clean:
	rm -f bigraph.o cohits.o hitting_time.o rwr.o