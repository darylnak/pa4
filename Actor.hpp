/**
 * Filename:     Actor.hpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Actor object (main node in ActorGraph). Holds the name
 *               of actor, distance from a specified origin actor to this,
 *               a pointer the adjacent actor in a shortest path from origin,
 *               and the movie connecting them. Contains a collection of movies
 *               this actor starred in.
 */

#ifndef PA4_ACTOR_HPP
#define PA4_ACTOR_HPP

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Movie;

typedef unordered_map<string, Movie*> Collection;
typedef pair<string, Movie*> movieVal; // key-value pair of movie

class Actor {
private:
    int dist;
    string name; // actor name
    Actor* prev;
    Movie* edge;

public:

    int numBelow; // number of nodes below this node
    bool wasProcessed;
    Collection movies; // movies this actor starred in

    /** constructor */
    Actor(string& name);

    /** Connect actor to the movie */
    void updateCollection(Movie* movie);

    /** set dist from specified origin actor to this actor */
    void setDist(int dist) {this->dist = dist;}

    /** set the incoming actor to this actor for shortest path traversal */
    void setPrev(Actor * prev) {this->prev = prev;}

    /** set the movie connecting incoming actor for shortest path travers */
    void setEdge(Movie* mov) {this->edge = mov;}

    /** get dist from specified origin actor to this actor */
    int getDist() {return dist;}

    /** get the incoming actor to this actor for shortest path traversal */
    Actor* getPrev() {return prev;}

    /** get name of this acter */
    string getName() {return name;}

    /** get movie name connecting incoming actor for shortest path travers */
    Movie* getEdge() {return edge;}
};


#endif //PA4_ACTOR_HPP
