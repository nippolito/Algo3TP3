TARGETS= exacto
FLAGS= -std=c++11
make: $(TARGETS)

ej2: exacto.cpp
	g++ $^ -o $@ $(FLAGS)

clean:
	rm -f *.o *~ $(TARGETS)