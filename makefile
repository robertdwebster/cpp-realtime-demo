main: listener.cpp main.cpp
	g++ -o main.out -std=c++11 -pthread data.h listener.h listener.cpp main.cpp

.PHONY: clean

clean:
	rm -f *.out *.o *.h.gch