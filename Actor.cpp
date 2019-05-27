//
// Created by djnak on 5/24/2019.
//

#include "Actor.hpp"
#include "Movie.hpp"

Actor::Actor(string& name)
{
    this->name = name;
    wasProcessed = false;
    dist = -1;
    prev = nullptr;
    edge = nullptr;
}

const string& Actor::getActorName() const
{
    return name;
}

/** Update actor if they starred in a new movie.
*   Else, updateActor will do nothing
**/
void Actor::updateCollection(Movie* movie)
{
    string key = movie->getMovieName() + to_string(movie->getMovieYear());

    // find the movie, if it exists
    auto movieItr = movies.find(key);

    // reject duplicate movie (already in their collection)
    if(movieItr != movies.end()) return;

    // If here, actor starred in a new movie. Update their collection.
    movies.insert(movieVal(key, movie));
}