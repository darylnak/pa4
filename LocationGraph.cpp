/**
 * Filename:     LocationGraph.cpp
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

#include "LocationGraph.hpp"

LocationGraph::LocationGraph()
{
    directions = stack<Location*>();
}

LocationGraph::~LocationGraph()
{
    for(locPair loc : locations)
        delete loc.second;
}

// build location graph from locFile and neighFile  (locations and edges)
void LocationGraph::buildGraph(istream& locFile, istream& neighFile)
{
    string locationName;
    string loc1Name;
    string loc2Name;
    int x;
    int y;

    // create all nodes in graph and put them in a hash table to quickly lookup specific nodes
    while(true)
    {
        locFile >> locationName;

        // check if last request for next string failed. If so, reached end of file
        if(locFile.eof())
            break;

        locFile >> x >> y;


        locations.insert(locPair(locationName, new Location(locationName, x, y)));
    }

    // connect locations to each other
    while(true)
    {
        neighFile >> loc1Name;

        if(neighFile.eof())
            break;

        neighFile >> loc2Name;

        locations.find(loc1Name)->second->addAdj(locations.find(loc2Name)->second);
        locations.find(loc2Name)->second->addAdj(locations.find(loc1Name)->second);
    }
}
// write directions between locations in tripFile to outFile (public call)
void LocationGraph::writeDirections(istream& tripFile, ostream& outFile)
{
    int mult = 1; // debugging multiplier

    // loop for all pairs in tripFile
    while(true)
    {
        string orig;
        string dest;

        tripFile >> orig;          // get origin and destination names

        if(tripFile.eof())
            break;

        tripFile >> dest;


        Location* origLoc = locations.find(orig)->second;       // get origin and dest from location hash table
        Location* destLoc = locations.find(dest)->second;
        Location* curr = nullptr;                               // current working location in graph

        int distCheck;                            // current working distance from source
        bool hasPath = false;

        // initial setup before A*; pushing origin to hash
        origLoc->setDist(0);
        origLoc->setHeurDist(heuristic(origLoc, destLoc, mult));

        pq.push(origLoc);
        modified.insert(locPair(origLoc->getLocationName(), origLoc));

        /** run A* to find shortest path from origin Location to dest Location */
        while(!pq.empty())
        {
            // get min distance node from origin
            curr = pq.top();
            pq.pop();

            // stop when dest has shortest path to orig (popped node is done node)
            if(curr == destLoc)
            {
                hasPath = true;     // set to know if path found by loop termination
                break;
            }

            // check if current location has been optimized
            if(!curr->isOptimized)
            {
                // Mark as optimized so it's not visited later. Record modification
                curr->isOptimized = true;
                modified.insert(locPair(curr->getLocationName(), curr));

                // process each adjacent Location of curr
                for(pair<string, Location*> loc : curr->adjacent)
                {
                    // check if current location been completely processed
                    if(loc.second->isOptimized) continue;

                    // get this paths distance from origin to current location
                    distCheck = curr->getDist() +
                                getDistBetween(curr, loc.second);

                    // if infinite dist or better dist found, update
                    if(loc.second->getDist() < 0 ||
                       distCheck < loc.second->getDist())
                    {
                        // remember location that got us here and record heuristic
                        loc.second->setFrom(curr);
                        loc.second->setDist(distCheck);
                        loc.second->setHeurDist(distCheck +
                                         heuristic(loc.second, destLoc, mult));

                        pq.push(loc.second);

                        // record that this node was modified
                        modified.insert(locPair(loc.second->getLocationName(), loc.second));
                    }
                }
            }
        }

        /** hasPath is a check to see if there was a path from orig to dest
         *
         */
        while(hasPath && curr != nullptr)
        {
            directions.push(curr);
            curr = curr->getFrom();
        }

        writeDirecsToFile(outFile);

        // reset processed nodes for another search
        for(locPair record : modified)
        {
            record.second->isOptimized = false;
            record.second->setDist(-1);
            record.second->setFrom(nullptr);
            record.second->setHeurDist(0);
        }

        // reset priority queue for a new call to find shortest path
        pq = priority_queue<Location*, vector<Location*>, Compare>();
        modified = unordered_map<string, Location*>();
    }
}

// calculate heuristic for curr node (euclid dist from curr to endDest)
int LocationGraph::heuristic(Location* curr, Location* endDest, int c)
{
    // NOTE: c should always be 1. was included for skewing path
    return c*(abs(curr->getXcoord() - endDest->getXcoord()) +
              abs(curr->getYCoord() - endDest->getYCoord()));
}

// get euclid dist between two locations
int LocationGraph::getDistBetween(Location* curr, Location* adj)
{
    int euclidianDist = abs(curr->getXcoord() - adj->getXcoord()) +
                        abs(curr->getYCoord() - adj->getYCoord());
    return euclidianDist;
}

// write directions between two locations to outFile
void LocationGraph::writeDirecsToFile(ostream& outFile)
{
    while(!directions.empty())
    {
        // check if last node
        if(directions.size() == 1)
        {
            outFile << "(" << directions.top()->getLocationName() << ")\n";
            directions.pop();
            break;
        }

        // copy paste nodes in between
        outFile << "(" << directions.top()->getLocationName() << ")-->";

        directions.pop();
    }
}