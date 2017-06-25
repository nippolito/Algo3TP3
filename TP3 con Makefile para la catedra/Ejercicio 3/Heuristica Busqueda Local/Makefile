TARGETS= BL
FLAGS= -std=c++11
make: $(TARGETS)

BL: funcionMainBL.cpp
	g++ $^ -o $@ $(FLAGS)

clean:
	rm -f *.o *~ $(TARGETS)
