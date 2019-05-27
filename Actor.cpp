/**
 * Filename:     Actor.cpp
 *
 * Team:         Brandon Olmos (bolmos@ucsd.edu),
 *               Daryl Nakamoto (dnakamot@ucsd.edu)
 *
 * Reference(s): cplusplus.com
 *
 * Description:  Actor object (main node in ActorGraph). Holds the name
 *               of actor, distance from a specified origin acter to this,
 *               a pointer the adjacent actor in a shortest path from origin,
 *               and the movie connecting them. Contains a collection of movies
 *               this actor starred in.
 */

#include "Actor.hpp"
#include "Movie.hpp"

/** create new actor with actor name, name */
Actor::Actor(string& name)
{
    this->name = name;
    wasProcessed = false;
    dist = -1;
    prev = nullptr;
    edge = nullptr;
}

/** Update actor's movie collection if they starred in a new movie.
*   Else, updateActor will do nothing
**/
void Actor::updateCollection(Movie* movie)
{
    // key for a movie is movie year appended to movie name
    string key = movie->getMovieName() + to_string(movie->getMovieYear());

    // find the movie, if it exists
    auto movieItr = movies.find(key);

    // reject duplicate movie (already in their collection)
    if(movieItr != movies.end()) return;

    // If here, actor starred in a new movie. Update their collection.
    movies.insert(movieVal(key, movie));
}