#ifndef POKEMONID_HPP
#define POKEMONID_HPP


#include "Stats.hpp"
#include <string>

enum PokemonID{
    UNKWNOWN = -1,
    marcacrin,
    cochignon,
    mammochon,
    pikachu,
    raichu,
    etourmi,
    etourvol,
    etouraptor,
    mystherbe,
    galekid,
    galegon,
    galeking
};



const std::string& pokemonIDtoString(PokemonID id);

/**
 * Get the pokemon ID from a string
 * @param str a const reference to the pokemon string
 * @return the Pokemon ID
 */
PokemonID pokemonID(const std::string& str);



/**
 * Get the number of pokemons in the Pokedex
 * @return the number of different pokemons
 */
int getPokedexSize();



/**
 * Return a pointer to the base stats of a pokemon corresponding to the id
 */
Stats* baseStatsOfID(PokemonID id);

/**
 * Return a pointer to the stats of a pokemon at a given level
 */
Stats* statsAtLevel(const Stats& baseStats, int level);



#endif /* POKEMONID_HPP */

