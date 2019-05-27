//
// Created by djnak on 5/24/2019.
//

#ifndef PA4_MOVIE_HPP
#define PA4_MOVIE_HPP

#include <iostream>
#include <unordered_map>
#include "Actor.hpp"

typedef unordered_map<string, Actor*> Cast;
typedef pair<string, Actor*> actorVal;

using namespace std;

class Movie{
private:
    string name;
    int year;
    int strength;

public:
    Movie(string& name, int& year, bool useWeight);
    string& getMovieName();
    const int& getMovieYear() const;
    void updateCast(Actor* actor);
    Cast cast;

    int getStrength() {
        return strength;
    }
};


#endif //PA4_MOVIE_HPP
