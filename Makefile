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

all: pathfinder



# include what ever source code *.hpp files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o Actor.o Movie.o Pathfinder.o
	$(CC) $(CXXFLAGS) -o pathfinder ActorGraph.o Actor.o Movie.o Pathfinder.o

ActorGraph.o: ActorGraph.hpp ActorGraph.cpp Actor.hpp
	$(CC) $(CXXFLAGS) -c ActorGraph.cpp

Actor.o: Actor.hpp ActorGraph.cpp
	$(CC) $(CXXFLAGS) -c Actor.cpp

Movie.o: Movie.hpp Movie.cpp Actor.hpp
	$(CC) $(CXXFLAGS) -c Movie.cpp

Pathfinder.o: Pathfinder.cpp ActorGraph.hpp
	$(CC) $(CXXFLAGS) -c Pathfinder.cpp

clean:
	rm -f pathfinder *.o core*

