main: problem.o pseive.o
	g++ problem.o pseive.o -o main

problem.o: problem.cpp pseive.h
	g++ -c problem.cpp -o problem.o -O3

pseive.o: pseive.cpp pseive.h
	g++ -c pseive.cpp -o pseive.o -O3
