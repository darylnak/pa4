/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in imdb_2019.tsv. Feel free to modify any/all aspects as you wish.
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
ActorGraph::ActorGraph(void) = default;

/** Destroy the graph */
ActorGraph::~ActorGraph() {
    // delete all actor nodes
    for(actorVal actor : actors)
        delete actor.second;

    // delete all movies
    for(movieVal movie : movieArchive)
        delete movie.second;
}

/** You can modify this method definition as you wish
 *
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 - movie_year),
 *                      otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename, bool useWeight) {

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

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);

        // find the actor, if it exists
        auto actorItr = actors.find(actor_name);

        // check if the actor does not exist
        if(actorItr == actors.end())
        {
            newActor = new Actor(actor_name);
            actors.insert(actorVal(actor_name, newActor)); // add actor to graph
        }

        // hold the actor, if it exists
        else
            newActor = actorItr->second;

        // check to see if movie exists in the movie archive
        movieKey = movie_title + to_string(movie_year);

        auto movieItr = movieArchive.find(movieKey);

        // create a new movie in the archive if it does not exist
        if(movieItr == movieArchive.end())
        {
            newMovie = new Movie(movie_title, movie_year, useWeight);
            movieArchive.insert(movieVal(movieKey, newMovie));
        }

        else
            newMovie = movieItr->second;

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
    /** check if actor must be updated */
    actor->updateCollection(movie);
    movie->updateCast(actor);
}

/** write shortest path for each pair of actors in file */
void ActorGraph::writeShortestPaths(istream& allPairs, ostream& pathsFile)
{
    string currLine;
    string trash;
    string originActor;
    string destinationActor;

    getline(allPairs, trash); // go past header
    getline(allPairs, currLine);

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

        cout << "Finding shortest path between " << originActor << " and "
             << destinationActor << endl;

        getShortestPath(originActor, destinationActor, pathsFile);
    }
}

void ActorGraph::getOriginAndDest(string& orig, string& dest, istream& currLine)
{
    const char DELIM = '\t';

    getline(currLine, orig, DELIM);
    getline(currLine, dest, '\n');

    if(currLine.peek() == EOF) currLine.get();
}
void ActorGraph::getShortestPath(string& origin, string& destination, ostream& pathsFile)
{
    pq = priority_queue<Actor*, vector<Actor*>, Compare>();
    processed = unordered_map<int, Actor*>();
    auto sourceCheck = actors.find(origin);
    auto destCheck = actors.find(destination);
    int recorded = 0; // number of nodes modified
    bool hasPath = false;

    // if either actor does not exist, return
    if(sourceCheck == actors.end() || destCheck == actors.end())
        return;

    Actor* source = sourceCheck->second;
    Actor* dest = destCheck->second;
    Actor* curr = nullptr;
    int distCheck; // current working distance from source

    source->setDist(0);
    pq.push(source);

    /** run dijkstras algorithm to find shortest path */
    while(!pq.empty())
    {
        curr = pq.top();
        pq.pop();

        // stop when dest has shortest path to orig
        if(curr == dest)
        {
            hasPath = true;
            break;
        }

        if(!curr->wasProcessed)
        {
            curr->wasProcessed = true;

            // go through each edge for actor (movie in collection)
            for(movieVal movieItr : curr->movies)
            {
                // for each destination from edge (cast in movie)
                for(actorVal actorItr : movieItr.second->cast)
                {
                    if(actorItr.second->wasProcessed) continue;

                    // add weight of edge to current nodes dist from source
                    distCheck = curr->getDist() + movieItr.second->getStrength();

                    // if infinite dist or better dist found, set to distCheck
                    if(actorItr.second->getDist() < 0 ||
                            distCheck < actorItr.second->getDist())
                    {
                        actorItr.second->setPrev(curr);
                        actorItr.second->setDist(distCheck);
                        actorItr.second->setEdge(movieItr.second);

                        pq.push(actorItr.second);

                        // record that this node was modified
                        processed.insert(rec(recorded++, actorItr.second));
                    }
                }
            }
        }
    }

    // hasPath is a check to see if there was a path from orig to dest
    while(hasPath && curr != nullptr)
    {
        path.push(curr);
        curr = curr->getPrev();
    }

    writePathToDest(pathsFile);

    // reset processed nodes for another search
    for(rec record : processed)
    {
        record.second->wasProcessed = false;
        record.second->setDist(-1);
        record.second->setPrev(nullptr);
    }
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