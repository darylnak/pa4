/**
 * Filename:     Movie.hpp
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

#ifndef PA4_MOVIE_HPP
#define PA4_MOVIE_HPP

#include <iostream>
#include <unordered_map>
#include "Actor.hpp"

typedef unordered_map<string, Actor*> Cast;
typedef pair<string, Actor*> actorVal;

using namespace std;

/** Movie object (to connect actors to each other). Holds name of
 *  movie, year released, and strength of relationship between
 *  actors connected by this movie. Strength is how recently the
 *  actors worked together, with the most recent as 2019.
 *  Lower is better because the actors most recently
 *  worked together
 */
class Movie{
private:
    string name;
    int year;
    int strength;

public:
    Cast cast; // movie cast

    /** Create a new movie with weighted or unweighted edge, depending on arg
     *  strength/weight is 1 if unweighted flag set
     */
    Movie(string& name, int& year, bool useWeight);

    /** return string reference to this movie's name */
    string& getMovieName() {return this->name;}

    /** return const int reference to the year movie was released */
    const int& getMovieYear() const {return this->year;}

    /** return int to strength connecting cast members */
    int getStrength() {return strength;}

    /** add a new actor to the cast from imdb/input file */
    void updateCast(Actor* actor);
};

#endif //PA4_MOVIE_HPP
