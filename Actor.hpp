//
// Created by djnak on 5/24/2019.
//

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
    string name;
    int dist;
    Actor* prev;
    Movie* edge;

public:

    bool wasProcessed;
    Collection movies;
    Actor(string& name);
    const string& getActorName() const;

    /** Connect actor to the movie */
    void updateCollection(Movie* movie);

    void setDist(int dist) {
        this->dist = dist;
    }

    void setPrev(Actor * prev)
    {
        this->prev = prev;
    }

    int getDist() {
        return dist;
    }

    Actor* getPrev()
    {
        return prev;
    }

    string getName()
    {
        return name;
    }

    void setEdge(Movie* mov)
    {
        this->edge = mov;
    }

    Movie* getEdge()
    {
        return edge;
    }
};


#endif //PA4_ACTOR_HPP
