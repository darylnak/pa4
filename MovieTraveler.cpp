/**
 * Filename:    MovieTraveler.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Main driver to find a minimum-spanning tree of the ActorGraph graph.
 *               Writes the MST to a file, listing its edges connecting actors,
 *               as well as the total number of actors, edges, and total weight of the
 *               edges in the MST. The ActorGraph graph is strictly weighted and undirected.
 *
 * Arguments: input file, output file
 */

#include <iostream>
#include <fstream>
#include "ActorGraph.hpp"

using namespace std;

/** Main driver of MovieTraveler implementation. */
int main(int argc, char** argv)
{
    ActorGraph graph;
    ofstream mstOutFile;  // output file to write shortest paths for pairs
    const int NUM_ARGS = 3;  // correct number of args

    // check for correct # of args
    if(argc != NUM_ARGS)
    {
        cout << "./movietraveler called with incorrect arguments." << endl
             << "Usage: ./movietraveler movie_cast_tsv_file "
                "output_paths_tsv_file" << endl;

        return 0;
    }

    // populate graph with unweighted/weighted edges. (u = unweight, w = weight)
    graph.loadFromFile(argv[1], true, true);

    // open file to write minimum spanning tree of graph
    mstOutFile.open(argv[2]);

    // write minimum spanning tree to file
    graph.writeMST(mstOutFile);

    // close all i/o files
    mstOutFile.close();
    // done

    return 0;
}