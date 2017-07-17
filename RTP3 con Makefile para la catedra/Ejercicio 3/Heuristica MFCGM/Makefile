TARGETS= MFCGM
FLAGS= -std=c++11
make: $(TARGETS)

ej2: MFCGM.cpp
	g++ $^ -o $@ $(FLAGS)

clean:
	rm -f *.o *~ $(TARGETS)