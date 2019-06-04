/**
 * Filename:     NavigationSystem.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Main driver to get shortest distance between two locations in a graph
 *
 * Arguments: input file, u/w, pairs, output
 */

#include <iostream>
#include <fstream>
#include "LocationGraph.hpp"

using namespace std;

int main(int argc, char** argv)
{
    LocationGraph graph;
    ifstream locsFile;        // locations and their x-y cartesian coordinate, file
    ifstream adjFile;         // file of connected (neighboring) locations
    ifstream tripFile;        // file containing trips to find
    ofstream outFile;         // file to write trip path to

    // open files used to build graph
    locsFile.open(argv[1]);
    adjFile.open(argv[2]);

    graph.buildGraph(locsFile, adjFile);

    locsFile.close();
    adjFile.close();

    // open files used to get directions and output to
    tripFile.open(argv[3]);
    outFile.open(argv[4]);

    graph.writeDirections(tripFile, outFile);

    tripFile.close();
    outFile.close();
}