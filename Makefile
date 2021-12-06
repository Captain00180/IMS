CXX = g++
CPFLAGS = -Wall -Wextra -pedantic -g
CPLIBS = -lsimlib -lm

all: main

main: main.cpp
	$(CXX) $(CPFLAGS) main.cpp -o main $(CPLIBS)

clean:
	rm -rf main *.o
