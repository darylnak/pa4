/**
 * Filename:     Movie.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Movie object (to connect actors to each other). Holds name of
 *               movie, year released, and strength of relationship between
 *               actors connected by this movie. Strength is how recently the
 *               actors worked together, with the most recent as 2019.
 *               Lower is better becuase the actors most recently
 *               worked together.
 */

#include "Movie.hpp"

/** Create a new movie with weighted or unweighted edge, depending on arg
 *  strength/weight is 1 if unweighted flag set
 */
Movie::Movie(string& name, int& year, bool useWeight) {
    this->name = name;
    this->year = year;

    // check for weighted or unweighted graph
    if(useWeight) this->strength = 1 + (2019 - year); // defined by PA guide
    else this->strength = 1;
}

/** add a new actor to the cast from imdb/input file */
void Movie::updateCast(Actor* actor)
{
    string key = actor->getName();

    // find the actor, if it exists
    auto castItr = cast.find(key);

    // reject duplicate cast member
    if(castItr != cast.end()) return;

    // If here, new actor in movie. Update cast
    cast.insert(actorVal(key, actor));
}