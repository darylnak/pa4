//
// Created by djnak on 5/31/2019.
//

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
    loc_hash locations;
    loc_hash modified;
    stack<Location*> directions;

    int heuristic(Location* curr, Location* endDest, int c);

    int getDistBetween(Location* curr, Location* adj);

    void writeDirecsToFile(ostream& outFile);

public:
    LocationGraph();

    ~LocationGraph();

    priority_queue<Location*, vector<Location*>, Compare> pq;

    void buildGraph(istream& locations, istream& neighbors);

    void writeDirections(istream& tripFile, ostream& outFile);


};


#endif //PA4_LOCATIONGRAPH_HPP
