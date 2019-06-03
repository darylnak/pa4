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

void Location::setXcoord(int &x) {
    xCoord = x;
}

void Location::setycoord(int &y) {
    yCoord = y;
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
