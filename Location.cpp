/**
 * Filename:     Location.cpp
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

#include "Location.hpp"

Location::Location(string name, int x, int y) {
    locationName = name;
    xCoord = x;
    yCoord = y;
    dist = -1;
    heurDist = 0;
    isOptimized = false;
    from = nullptr;
    adjacent.reserve(1000);
}

int Location::getXcoord() {
    return xCoord;
}

int Location::getYCoord() {
    return yCoord;
}

string Location::getLocationName() {
    return locationName;
}

void Location::addAdj(Location *adj)
{
    adjacent.insert(pair<string, Location*>(adj->getLocationName(), adj));
}
