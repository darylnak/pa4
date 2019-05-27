/*
 * ActorGraph.hpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined imdb_2019.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <stack>
#include <unordered_map>
#include <queue>
#include "Actor.hpp"

// Maybe include some data structures here


using namespace std;

typedef unordered_map<string, Movie*> MovieArchive;
typedef unordered_map<string, Actor*> ActorCollection;
typedef pair<string, Actor*> actor; // <actor_name, Actor*>
typedef pair<int, Actor*> rec; // pair for record keeping

class Compare {
public:
    bool operator() (Actor* act1, Actor* act2)
    {
        if(act1->getDist() != act2->getDist())
            return act1->getDist() > act2->getDist();
        else
            return false;
    }
};


/**
 * TODO: add class header
 */
class ActorGraph {
protected:
  
     // Maybe add class data structure(s) here
     ActorCollection actors;  // collection of Actor* nodes (name, node)
     unordered_map<int, Actor*> processed; // hold processed Actors to reset for next iter
     MovieArchive movieArchive;
     priority_queue<Actor*, vector<Actor*>, Compare> pq;
     stack<Actor*> path;

    /** Update the actor anc movie archive as necessary */
    void updateGraph(Actor* actor, Movie* movie);

    /** set origin and destination for actors */
    void getOriginAndDest(string& origin, string& dest, istream& currLine);

    void getShortestPath(string& origin, string& destination, ostream& pathsFile);

    void writePathToDest(ostream & out);


public:

    /**
     * Constuctor of the Actor graph
     */
    ActorGraph(void);
    ~ActorGraph(); // TODO

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year), 
     *                      otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool useWeight);
    void writeShortestPaths(istream& allPairs, ostream& pathsFile);
  
};


#endif // ACTORGRAPH_HPP
