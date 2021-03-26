/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pokedex.hpp
 * Author: Redbuzard
 *
 * Created on 15 avril 2020, 18:43
 */

#ifndef POKEDEX_HPP
#define POKEDEX_HPP

#include <map>
#include <vector>

#include "PokemonID.hpp"


class Pokedex {
public:
//=================// Constructor //==================//
    
    /**
     * Default constructor
     */
    Pokedex();
    
    
//=================// Public methods //==================//
    
    /**
     * Adds a pokemon to the set of pokemon saw
     * @param id the ID of the new Pokemon
     */
    void addPokemonSaw(PokemonID id);
    
    /**
     * Adds a pokemon to the set of pokemon captured
     * @param id the ID of the new Pokemon
     */
    void addPokemonCaptured(PokemonID id);
    
    
    
    /**
     * Check if a given pokemon was already saw
     * @param id the ID of the pokemon
     * @return true if the pokemon was already saw
     */
    bool saw(PokemonID id);
    
    /**
     * Check if a given pokemon was already captured
     * @param id the ID of the pokemon
     * @return true if the pokemon was already captured
     */
    bool captured(PokemonID id);
    
    
    
    /**
     * Get the number of time we captured a pokemon
     * @param id the PokemonID of the Pokemon
     * @return the number of time the pokemon was captured
     */
    int getNumberCaptured(PokemonID id);
    

    /**
     * Get the number of time we saw a pokemon
     * @param id the PokemonID of the Pokemon
     * @return the number of time the pokemon was seen
     */
    int getNumberSaw(PokemonID id);
    
    
    /**
     * Get the total number of pokemon saw
     * @return the number of pokemon saw
     */
    int getTotalSaw();
    
    /**
     * Get the total number of pokemon captured
     * @return the number of pokemon captured
     */
    int getTotalCaptured();
    
    
//=================// Getters //==================//
    
    /**
     * Get the pokemon saw
     * @return a const reference to the map of pokemon saw
     */
    const std::map<PokemonID, int>& getPokemonSaw() const;
    
    
    /**
     * Get the pokemon captured
     * @return a const reference to the map of pokemon captured
     */
    const std::map<PokemonID, int>& getPokemonCaptured() const;
    
    
    /**
     * Get a set Containing all pokemons in order
     * @return a pointer to the set of pokemon captured 
     */
    std::vector<PokemonID>* getAllPokemons() const;
    
    
private:
//=================// Attributes //==================//

    // A set for the pokemon saw
    std::map<PokemonID, int> m_pokemonsSaw;

    // A set for the pokemon captured
    std::map<PokemonID, int> m_pokemonsCaptured;
    
};

#endif /* POKEDEX_HPP */

