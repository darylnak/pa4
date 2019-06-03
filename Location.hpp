//
// Created by djnak on 5/31/2019.
//

#ifndef PA4_LOCATION_HPP
#define PA4_LOCATION_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


// some geological location with a name, x & y cartesian coordinate,
class Location {
    string locationName;
    int xCoord;
    int yCoord;
    int dist;         // current best distance from the source node
    int heurDist;
    Location* from;   //neighbor which gave current best distance from source

public:
    bool isOptimized;
    unordered_map<string, Location*> adjacent; // adjacent locations

       /////////////////
      /// Functions ///
     /////////////////

    Location(string name, int x, int y);

    void setXcoord(int& x);
    void setycoord(int& y);

    int getXcoord();
    int getYCoord();

    int getDist() {return dist;}
    void setDist(int d) {dist = d;}

    Location* getFrom() {return from;}
    void setFrom(Location* loc) {from = loc;}

    string getLocationName();

    void addAdj(Location* adj);

    void setHeurDist(int hdist) {heurDist = hdist;}
    int getHeurDist() {return heurDist;}
};


#endif //PA4_LOCATION_HPP
