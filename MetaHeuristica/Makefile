CC=g++
STDFLAGS = -std=c++11
CFLAGS=-I.

.PHONY: clean

all: MetaHeur
	$(CC)  MetaHeur.cpp -o MetaHeur $(CFLAGS)

	
tests: 
	$(CC) $(STDFLAGS) tests.cpp -o tests $(CFLAGS)

clean: 
	$(RM) MetaHeur tests


