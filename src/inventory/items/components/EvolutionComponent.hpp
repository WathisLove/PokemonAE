/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvolutionComponent.hpp
 * Author: Redbuzard
 *
 * Created on 19 février 2021, 18:48
 */

#ifndef EVOLUTIONCOMPONENT_HPP
#define EVOLUTIONCOMPONENT_HPP

#include "../ItemComponent.hpp"


class EvolutionComponent : public ItemComponent {
public:
    
    //=================// Constructors //==================//
    
    /**
     * Constructor 
     */
    EvolutionComponent(PokemonID unevolved, PokemonID evolution);
    
    
    //=================// Inherited methods//==================//
    
    /**
     * Apply an effect on a pokemon
     * @param pokemon a pointer to the Pokemon
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onPokemon(Pokemon* pokemon) const override;
    
    
    /**
     * Check if the ItemComponent has an effect on the pokemon
     * @param pokemon a pointer to the pokemon
     * @return true if the ItemComponent has an effect on the pokemon
     */
    bool hasEffectOnPokemon(Pokemon* pokemon) const override;

    
private:
    //=================// Attributes //==================//
    // Pokemons
    PokemonID m_unevolved, m_evolution;
};

#endif /* EVOLUTIONCOMPONENT_HPP */

