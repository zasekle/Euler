main: pseive.o problem.o
	g++ pseive.o problem.o -o main

problem.o: problem.cpp pseive.h
	g++ -c problem.cpp -o problem.o

pseive.o: pseive.cpp pseive.h
	g++ -c pseive.cpp -o pseive.o -O3
