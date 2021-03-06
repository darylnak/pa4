/**
 * Filename:    ActorGraph.hpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Graph which contains Actor nodes to perform graph algs on.
 *               Can find shortest path from actor A to actor B through
 *               series of movies connecting actors.
 *
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <stack>
#include <unordered_map>
#include <queue>
#include "Actor.hpp"

using namespace std;

/** use with priority queue for dijkstra. key is dist from orig to curr actor */
class ActCompare {
public:
    bool operator() (Actor* act1, Actor* act2)
    {
        if(act1->getDist() != act2->getDist())
            return act1->getDist() > act2->getDist();
        else
            return false;
    }
};

/** Comparator for priority queue to sort movies from most recent to least recent. */
class MovCompare {
public:
    bool operator() (Movie* mov1, Movie* mov2);
};

typedef unordered_map<string, Movie*> movie_archive;
typedef unordered_map<string, Actor*> actor_collection;
typedef pair<string, Actor*> actor; // <actor_name, Actor*>
typedef unordered_map<string, Actor*> hash_table;
typedef priority_queue<Actor*, vector<Actor*>, ActCompare> actor_pq;
typedef priority_queue<Movie*, vector<Movie*>, MovCompare> movie_pq;

/**
 * Class to hold Actor nodes which are connected to other nodes by movies
 * performs Dijkstras algorithm to find shortest path (chain of relationships)
 * from actor A to actor B in the graph.
 */
class ActorGraph {
protected:
     actor_collection actors;  // collection of Actor* nodes (name, node)
     hash_table processed;     // to hold processed Actors to reset for next iter
     movie_archive movieArchive; // collection of all movies amongst actors
     actor_pq pq;                // queue to use in dijkstras
     stack<Actor*> path;         // to record shortest path from actor A to B
     movie_pq ordEdges;          // ordered edges (movies ordered by strength)
     int numActors;              // total number of nodes in graph

    /** Update the actor anc movie archive as necessary */
    void updateGraph(Actor* actor, Movie* movie);

    /** set origin and destination for actors */
    void getOriginAndDest(string& origin, string& dest, istream& currLine);

    /** find shortest path from actor A to B. Writes a formatted path to a file */
    void getShortestPath(string& origin, string& destination, ostream& pathsFile);

    /** Write a formatted path to a file from shortest path func */
    void writePathToDest(ostream & out);

    /** Finds sentinel value of actor in the disjoint set (up-tree). Includes path compression logic. */
    Actor* setFind(Actor* actor);

    /** Unions two disjoint sets to form a new disjoint set (up-tree) of actors. */
    void setUnion(Actor* act1, Actor* act2);

public:
    ActorGraph();
    ~ActorGraph();

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
    bool loadFromFile(char* in_filename, bool useWeight, bool isTrav);

    /** write shortest path for each pair of actors
     *  in pairs file -- initial call.
     **/
    void writeShortestPaths(istream& allPairs, ostream& pathsFile);

    /** Write a Minimum Spanning Tree to mstOutFile, including header, shortest weighted paths, num of actors and movies
     *  and total edge weight.
     */
    void writeMST(ostream& mstOutFile);
  
};


#endif // ACTORGRAPH_HPP
