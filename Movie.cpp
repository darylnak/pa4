//
// Created by djnak on 5/24/2019.
//

#include "Movie.hpp"

/** Create a new movie */
Movie::Movie(string& name, int& year, bool useWeight) {
    this->name = name;
    this->year = year;

    // check for weighted or unweighted graph
    if(useWeight) this->strength = 1 + (2019 - year); // defined by PA guide
    else this->strength = 1;
}

string& Movie::getMovieName()
{
    return this->name;
}

const int& Movie::getMovieYear() const
{
    return this->year;
}

void Movie::updateCast(Actor* actor)
{
    string key = actor->getActorName();

    // find the actor, if it exists
    auto castItr = cast.find(key);

    // reject duplicate cast member
    if(castItr != cast.end()) return;

    // If here, new actor in movie. Update cast
    cast.insert(actorVal(key, actor));
}