/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvolutionItemEffect.hpp
 * Author: Redbuzard
 *
 * Created on 18 février 2021, 17:24
 */

#ifndef EVOLUTIONITEMEFFECT_HPP
#define EVOLUTIONITEMEFFECT_HPP

#include "ItemEffect.hpp"
#include "../../../pokemons/PokemonID.hpp"



class EvolutionItemEffect : public ItemEffect{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    EvolutionItemEffect(PokemonID evolution);
    
    
    //=================// Constructor //==================//
    
    
    /**
     * Get the Evolution ID 
     * @return the Evolution ID
     */
    PokemonID getEvolutionID() const;

    
private:
    //=================// Attributes //==================//
    
    // The evolution the item triggered
    PokemonID m_evolution;
};

#endif /* EVOLUTIONITEMEFFECT_HPP */

