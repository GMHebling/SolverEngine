CC=g++
CFLAGS=-std=gnu++11 -Wall -g
LDFLAGS= -lcholmod -lspqr -lsuitesparseconfig -lm -lstdc++

solver: main.o sparseSystem.h engine.h
	$(CC) $(CFLAGS) -o solver main.o $(LDFLAGS)

main.o: main.cc 
	$(CC) $(CFLAGS) -c main.cc $(LDFLAGS)