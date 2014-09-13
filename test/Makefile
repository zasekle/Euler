CC=g++
FLAGS=--std=c++11 -O3

main: test.o pseive.o
	${CC} test.o pseive.o -o main

test.o: test.cpp pseive.h
	${CC} -c test.cpp -o test.o ${FLAGS}

pseive.o: pseive.cpp pseive.h
	${CC} -c pseive.cpp -o pseive.o ${FLAGS}

clean:
	rm test.o main
