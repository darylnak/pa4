/**
 * Filename:     Pathfinder.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Main driver to find the shortest path between acter in an
 *               ActorGraph. Reads actors and movies they starred in from an
 *               input file, creates a weighted/unweighted graph as specified
 *               by user, read a file containing origin, destination actor pairs
 *               to find a shortest path between, and writes each path
 *               between pairs to an output file.
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include "ActorGraph.hpp"

using namespace std;

/** ssee Description. Initiates the process */
int main(int argc, char* argv[])
{
    ActorGraph graph;
    ifstream allPairs;   // to read all origin, destination pairs
    ofstream pathsFile;  // output file to write shortest paths for pairs
    const int NUM_ARGS = 5;  // correct number of args

    // check for correct # of args
    if(argc != NUM_ARGS)
    {
        cout << "./pathfinder called with incorrect arguments." << endl
             << "Usage: ./refpathfinder movie_cast_tsv_file u/w pairs_tsv_file "
                "output_paths_tsv_file" << endl;

        return 0;
    }

    cout << "Reading imdb_2019.tsv ..." << endl;
    // populate graph with unweighted edges if arg is 'u' (unweighted)
    if(*argv[2] == 'u') graph.loadFromFile(argv[1], false);
    // else populate graph with weighted edges
    else graph.loadFromFile(argv[1], true);
    cout << "done" << endl;

    // loop through pairs file
    allPairs.open(argv[3]); // open file of pairs to find shortest path (arg 3)
    pathsFile.open(argv[4]); // open file to write shortest paths to

    // write shortest path between all pairs in pairs file
    graph.writeShortestPaths(allPairs, pathsFile);

    // close all i/o files
    allPairs.open(argv[3]);
    pathsFile.open(argv[4]);
    // done

    return 0;
}