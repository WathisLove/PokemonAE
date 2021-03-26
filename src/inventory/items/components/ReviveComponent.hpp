/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReviveComponent.hpp
 * Author: Redbuzard
 *
 * Created on 22 janvier 2021, 14:09
 */

#ifndef REVIVECOMPONENT_HPP
#define REVIVECOMPONENT_HPP

#include "../ItemComponent.hpp"

class ReviveComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    ReviveComponent(float hpPercentage);
    
    
    //=================// Public methods //==================//
    
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
    // Percentage of health restored
    float m_healthPercentage;
};

#endif /* REVIVECOMPONENT_HPP */

