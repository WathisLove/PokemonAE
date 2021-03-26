/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonCreator.hpp
 * Author: Redbuzard
 *
 * Created on 21 décembre 2019, 15:23
 */

#ifndef POKEMONCREATOR_HPP
#define POKEMONCREATOR_HPP

#include "PokemonID.hpp"
#include "Pokemon.hpp"


/**
 * Create a pokemon
 * @param id the Pokemon ID
 * @param level the pokemon Level
 * @return a pointer to the pokemon created
 */
Pokemon* createPokemon(PokemonID id, int level);
    

/**
 * Create a pokemon
 * @param id the Pokemon ID
 * @param level the pokemon Level
 * @param actualHealth the health of the pokemon
 * @return a pointer to the pokemon created
 */
Pokemon* createPokemon(PokemonID id, int level, int actualHealth);


/**
 * Create a pokemon
 * @param id the Pokemon ID
 * @param level the pokemon Level
 * @param actualHealth the health of the pokemon
 * @param metadata the pokemon Metadata
 * @return a pointer to the pokemon created
 */
Pokemon* createPokemon(PokemonID id, int level, int actualHealth, PokemonMetadata metadata);



#endif /* POKEMONCREATOR_HPP */
