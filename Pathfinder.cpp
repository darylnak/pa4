#include <iostream>
#include <fstream>
#include <string.h>
#include "ActorGraph.hpp"



using namespace std;

int main(int argc, char* argv[])
{
    ActorGraph graph;
    ifstream allPairs;
    ofstream pathsFile;
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
    if(strcmp(argv[2], "u") == 0) graph.loadFromFile(argv[1], false);
    // else populate graph with weighted edges
    else graph.loadFromFile(argv[1], true);
    cout << "done" << endl;

    // loop through pairs file
    allPairs.open(argv[3]); // open file of pairs to find shortest path (third arg)
    pathsFile.open(argv[4]); // open file to write shortest paths to

    graph.writeShortestPaths(allPairs, pathsFile);

    allPairs.open(argv[3]);
    pathsFile.open(argv[4]);
    // done

    return 0;
}