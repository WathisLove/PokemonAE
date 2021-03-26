/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealHPComponent.hpp
 * Author: Redbuzard
 *
 * Created on 21 janvier 2021, 16:41
 */

#ifndef HEALHPCOMPONENT_HPP
#define HEALHPCOMPONENT_HPP

#include "../ItemComponent.hpp"

class HealHPComponent : public ItemComponent {
public:
    
    //=================// Constructor //==================//
    
    /**
     * Constructor for fixed amount
     * Default is for full heal
     */
    HealHPComponent(int hpAmount);
    
    
    /**
     * Constructor to heal a percentage of life
     * @param hpPercentage
     * @return 
     */
    HealHPComponent(float hpPercentage);
    
    
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
    // Heal data
    union {
        int m_hpAmount;
        float m_percentage;
    };
    
    // Percentage
    bool m_isPercentage;
};

#endif /* HEALHPCOMPONENT_HPP */

