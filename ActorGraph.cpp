/**
 * Filename:    ActorGraph.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Graph which contains Actor nodes to perform graph algs on.
 *               Can find shortest path from actor A to actor B through
 *               series of movies connecting actors.
 *
 * Arguments: input file, u/w, pairs, output
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;

/**
 * Constructor of the Actor graph
 */ 
ActorGraph::ActorGraph()
{
    pq = priority_queue<Actor*, vector<Actor*>, ActCompare>();
    processed = unordered_map<string, Actor*>();
    ordEdges = priority_queue<Movie*, vector<Movie*>, MovCompare>();
    numActors = 0;
}

/** Destroy the graph */
ActorGraph::~ActorGraph() {
    // delete all actor nodes
    for(actorVal actor : actors)
        delete actor.second;

    // delete all movies
    for(movieVal movie : movieArchive)
        delete movie.second;
}

/** Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year)
 *                      otherwise all edge weights will be 1
 *
 * return true if file was loaded successfully, false otherwise
 */
bool ActorGraph::loadFromFile(char* in_filename, bool useWeight, bool isTrav)
{

    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
    Actor* newActor;
    Movie* newMovie;
    string movieKey;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {

            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        // get actor name, their movie and movie year
        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        /** actors are inserted in an ActorCollection, a collection to
        *   hold all actors in the graph. Check if this actor has been recorded
        */
        auto actorItr = actors.find(actor_name);

        /** if the actor did not exist, add them to the ActorCollection/graph
         *  Hold a pointer to the actor to work on it later
         */
        if(actorItr == actors.end())
        {
            newActor = new Actor(actor_name);
            actors.insert(actorVal(actor_name, newActor)); // add actor to graph
            ++numActors;
        }

        // else, the actor existed, so just remember it
        else
            newActor = actorItr->second;

        /** movies are inserted in an Archive, a collection to
        *   hold all movie connecting actors.
        *   Check if this movie has been recorded
        */
        movieKey = movie_title + to_string(movie_year);
        auto movieItr = movieArchive.find(movieKey);

        /** create a new movie in the archive if it does not exist
         *  hold pointer to the movie to work on it later.
         *  Also, insert the new movie into a pq sorted, least to greatest,
         *  strength.
         */
        if(movieItr == movieArchive.end())
        {
            newMovie = new Movie(movie_title, movie_year, useWeight);
            movieArchive.insert(movieVal(movieKey, newMovie));
            ordEdges.push(newMovie);
        }

        // else, the movie existed, so just remember it
        else
            newMovie = movieItr->second;

        /** check to see if actor needs to add a new movie to their collection
         *  and also check to see if actor must be added to the cast of the
         *  movie
         */

        updateGraph(newActor, newMovie);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }

    infile.close();
    return true;
}

/** Update the actor and movie archive as necessary */
void ActorGraph::updateGraph(Actor* actor, Movie* movie)
{
    /** check if actor and/or movie must be updated */
    actor->updateCollection(movie);
    movie->updateCast(actor);
}

/** write shortest path for each pair of actors
*  in pairs file -- initial call.
**/
void ActorGraph::writeShortestPaths(istream& allPairs, ostream& pathsFile)
{
    string currLine;
    string trash;
    string originActor;
    string destinationActor;

    getline(allPairs, trash);    // go past header
    getline(allPairs, currLine); // wil be EOF if no pairs in file

    // check for no pairs input
    if(allPairs.eof()) return;

    // reset to beginning
    allPairs.clear();
    allPairs.seekg(0);
    getline(allPairs, trash);


    // write header to file
    pathsFile << "(actor)--[movie#@year]-->(actor)--..." << endl;

    // find and write shortest path for all pairs
    while(!allPairs.eof())
    {
        getOriginAndDest(originActor, destinationActor, allPairs);

        /** /*
        cout << "Finding shortest path between " << originActor << " and "
             << destinationActor << endl;
        //*/
        getShortestPath(originActor, destinationActor, pathsFile);
    }
}

/** parse line from pairs file. Get origin actor and destination actor */
void ActorGraph::getOriginAndDest(string& orig, string& dest, istream& currLine)
{
    const char DELIM = '\t'; // delimiter

    getline(currLine, orig, DELIM); // get actor before tab
    getline(currLine, dest, '\n');  // get actor after tab

    // to stop the loop if currLine is the last line in file
    if(currLine.peek() == EOF) currLine.get();
}

/** find shortest path from actor A to B. Writes a formatted path to a file */
void ActorGraph::getShortestPath(string& orig, string& dest, ostream& pathsFile)
{
    Actor* origAct = actors.find(orig)->second;
    Actor* destAct = actors.find(dest)->second;
    Actor* curr = nullptr; // current working actor in graph
    int recorded = 0; // number of nodes modified
    int distCheck; // current working distance from source
    bool hasPath = false;

    // initial setup before Dijkstras; pushing origin to queue
    origAct->setDist(0);
    pq.push(origAct);
    processed.insert(actor(origAct->getName(), origAct));

    /** run Dijkstras to find shortest path from origin actor to dest actor */
    while(!pq.empty())
    {
        // get min distance actor (node) from origin
        curr = pq.top();
        pq.pop();

        // stop when dest has shortest path to orig (popped node is done node)
        if(curr == destAct)
        {
            hasPath = true; // set to know if path found by loop termination
            break;
        }

        // check if current actor has been completely processed
        if(!curr->wasProcessed)
        {
            // Mark as processed so it's not visited later. Record modification
            curr->wasProcessed = true;
            processed.insert(actor(curr->getName(), curr));

            // travel through each edge for actor (movie in collection)
            for(movieVal movieItr : curr->movies)
            {
                // for each destination from edge (cast in movie)
                for(actorVal actorItr : movieItr.second->cast)
                {
                    // check if current actor has been completely processed
                    if(actorItr.second->wasProcessed) continue;

                    // get this paths distance from origin to current actor
                    distCheck = curr->getDist() + movieItr.second->getStrength();

                    // if infinite dist or better dist found, update
                    if(actorItr.second->getDist() < 0 ||
                            distCheck < actorItr.second->getDist())
                    {
                        // remember actor that got us here
                        actorItr.second->setPrev(curr);
                        actorItr.second->setDist(distCheck);
                        // dest actor remembers movie connecting them
                        actorItr.second->setEdge(movieItr.second);

                        pq.push(actorItr.second);

                        // record that this node was modified
                        processed.insert(actor(actorItr.second->getName(),
                                          actorItr.second));
                    }
                }
            }
        }
    }

    /** hasPath is a check to see if there was a path from orig to dest
     *
     */
    while(hasPath && curr != nullptr)
    {
        path.push(curr);
        curr = curr->getPrev();
    }

    writePathToDest(pathsFile);

    // reset processed nodes for another search
    for(actor record : processed)
    {
        record.second->wasProcessed = false;
        record.second->setDist(-1);
        record.second->setPrev(nullptr);
    }

    // reset priority queue for a new call to find shortest path
    pq = priority_queue<Actor*, vector<Actor*>, ActCompare>();
    processed = unordered_map<string, Actor*>();
}

/** write shortest path from origin to destination to output file */
void ActorGraph::writePathToDest(ostream & out)
{
    while(!path.empty())
    {
        // check if last node
        if(path.size() == 1)
        {
            out << "(" << path.top()->getName() << ")\n";
            path.pop();
            break;
        }

        // copy paste nodes in between
        out << "(" << path.top()->getName() << ")--[";

        path.pop();

        out << path.top()->getEdge()->getMovieName()
            << "#@" << path.top()->getEdge()->getMovieYear()
            << "]-->";
    }

}

/** Write a Minimum Spanning Tree to mstOutFile, including header, shortest weighted paths, num of actors and movies
 *  and total edge weight.
 */
void ActorGraph::writeMST(ostream& mstOutFile)
{
    // Initializing variables to hold edges, actors, and total weight/actors/edges.
    Movie* currEdge;
    Actor* act1;
    Actor* act2;
    int numEdges = 0;
    int numActs = 0;
    int weightTotal = 0;

    // TODO: single node case

    // write header of mst file
    mstOutFile << "(actor)<--[movie#@year]-->(actor)\n";

    // While loop to connect actors until we have a connected path with no cycles.
    while(numEdges != numActors - 1)
    {
        // Getting the minimum-weight movie.
        currEdge = ordEdges.top();
        ordEdges.pop();

        // check each actor for currEdge movie
        auto itr = currEdge->cast.begin();
        while(true)                          //the magic happens past this point//
        {
            //Get the (itr)th actor in the cast
            act1 = itr++->second;

            // if reached last actor, get out
            if(itr == currEdge->cast.end())
                break;

            //Get the (itr+1)th actor in the cast
            act2 = itr->second;

            // keep track of number of nodes inserted
            if(!act1->wasProcessed) ++numActs;
            if(!act2->wasProcessed) ++numActs;

            // if actors are in the same set, go to next actor in cast. Prevents cycle.
            if(setFind(act1) == setFind(act2))
                continue;

            // Union the disjoint sets.
            setUnion(act1, act2);

            // We mark both actors as processed. Prevents counting actors twice.
            act1->wasProcessed = act2->wasProcessed = true;

            // At this point, we connected two actors, so increase edge and weight total.
            ++numEdges;
            weightTotal += currEdge->getStrength();

            // write edge to mstOutFile
            mstOutFile << "(" << act1->getName() << ")<--["
                       << currEdge->getMovieName() << "#@"
                       << currEdge->getMovieYear() << "]-->("
                       << act2->getName() << ")\n";
        }
    }
    // Write total number of actors, edges, and total weight to mstOutfile.
    mstOutFile << "#NODE CONNECTED: " << numActs << endl
               << "#EDGE CHOSEN: " << numEdges << endl
               << "TOTAL EDGE WEIGHTS: " << weightTotal << endl;
}

/** Finds sentinel value of actor in the disjoint set (up-tree). Includes path compression logic. */
Actor* ActorGraph::setFind(Actor* actor)
{
    Actor* curr = actor;  // Hold current actor to later get path to sentinel.
    Actor* child;   // node to attach to sentinel for compression
    stack<Actor*> children = stack<Actor*>(); // saves new children of sentinel node

    // get sentinel node of actor and push nodes in path to stack for later compression
    while(curr->getPrev())
    {
        children.push(curr);
        curr = curr->getPrev();
    }

    // attach these nodes to sentinel to complete compression
    while(!children.empty())
    {
        child = children.top();
        child->setPrev(curr);
        children.pop();
    }

    return curr;
}

/** Unions two disjoint sets to form a new disjoint set (up-tree) of actors. */
void ActorGraph::setUnion(Actor* act1, Actor* act2)
{
    // Getting sentinel nodes for union of sets. One node will be child of the other.
    Actor* foundAct1 = setFind(act1);
    Actor* foundAct2 = setFind(act2);

    // If the size of act1's set is smaller or equal to act2's set, sentinel of act1 is attached to sentinel of act2.
    if(foundAct1->numBelow <= foundAct2->numBelow)
    {
        foundAct1->setPrev(foundAct2);
        foundAct2->numBelow += foundAct1->numBelow + 1;
    }

    // Otherwise, sentinel of act 2 is now a child of act1's sentinel.
    else
    {
        foundAct2->setPrev(foundAct1);
        foundAct1->numBelow += foundAct2->numBelow + 1;
    }
}

/** Comparator for priority queue to sort movies from most recent to least recent. */
bool MovCompare::operator()(Movie* mov1, Movie* mov2)
{
    if(mov1->getStrength() != mov2->getStrength())
        return mov1->getStrength() > mov2->getStrength();
    else
        return false;
}