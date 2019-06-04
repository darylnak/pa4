/**
 * Filename:     LocationGraph.hpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Graph which contains Location nodes to perform graph algs on.
 *               Can find shortest path from Location A to Location B (A* alg.)
 *
 * Arguments: input file, u/w, pairs, output
 */

#ifndef PA4_LOCATIONGRAPH_HPP
#define PA4_LOCATIONGRAPH_HPP

#include <iostream>
#include <stack>
#include <queue>
#include <unordered_map>
#include "Location.hpp"

using namespace std;

typedef unordered_map<string, Location*> loc_hash;
typedef pair<string, Location*> locPair;


class Compare
{
public:
    bool operator() (Location* loc1, Location* loc2)
    {
        return loc1->getHeurDist() >= loc2->getHeurDist();
    }
};

class LocationGraph {
private:
    loc_hash locations;             // locations in the graph
    loc_hash modified;              // keep track of modified locations to reeset
    stack<Location*> directions;

    // calculate heuristic for curr node (euclid dist from curr to endDest)
    int heuristic(Location* curr, Location* endDest, int c);

    // get euclid dist between two locations
    int getDistBetween(Location* curr, Location* adj);

    // write directions between two locations to outFile
    void writeDirecsToFile(ostream& outFile);

public:
    LocationGraph();

    ~LocationGraph();

    // priority queue used for A* algorithm
    priority_queue<Location*, vector<Location*>, Compare> pq;

    // build location graph from locFile and neighFile  (locations and edges)
    void buildGraph(istream& locations, istream& neighbors);

    // write directions between locations in tripFile to outFile (public call)
    void writeDirections(istream& tripFile, ostream& outFile);


};


#endif //PA4_LOCATIONGRAPH_HPP
