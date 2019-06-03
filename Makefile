# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CXXFLAGS += -O3
    LDFLAGS += -O3
else
    CXXFLAGS += -g
    LDFLAGS += -g
endif

all: navigationsystem

# include what ever source code *.hpp files pathfinder relies on (these are merely the ones that were used in the solution)

navigationsystem: NavigationSystem.o LocationGraph.o Location.o
	$(CC) $(CXXFLAGS) -o navigationsystem NavigationSystem.o LocationGraph.o Location.o

NavigationSystem.o: NavigationSystem.cpp
	$(CC) $(CXXFLAGS) -c NavigationSystem.cpp

LocationGraph.o: LocationGraph.hpp LocationGraph.cpp
	$(CC) $(CXXFLAGS) -c LocationGraph.cpp

Location.o: Location.hpp Location.cpp
	$(CC) $(CXXFLAGS) -c Location.cpp

clean:
	rm -f navigationsystem *.o core*