/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealConfusionComponent.hpp
 * Author: Redbuzard
 *
 * Created on 25 janvier 2021, 09:56
 */

#ifndef HEALCONFUSIONCOMPONENT_HPP
#define HEALCONFUSIONCOMPONENT_HPP

#include "../ItemComponent.hpp"

class HealConfusionComponent : public ItemComponent {
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    HealConfusionComponent() = default;
    
    
    //=================// Inherited methods //==================//
    
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

};

#endif /* HEALCONFUSIONCOMPONENT_HPP */

