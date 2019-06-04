/**
 * Filename:     Location.hpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Location object with name, x-y coord, adjacent location, and values
 *               used to perform shortest path algs on.
 *
 */

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
