/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeBoostComponent.hpp
 * Author: Redbuzard
 *
 * Created on 20 janvier 2021, 15:24
 */

#ifndef TYPEBOOSTCOMPONENT_HPP
#define TYPEBOOSTCOMPONENT_HPP

#include "../ItemComponent.hpp"

class TypeBoostComponent : public ItemComponent {
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    TypeBoostComponent(float factor, Type type, PokemonID attacker = PokemonID::UNKWNOWN);
    
    //=================// Public methods //==================//
    
    /**
     * Apply a boost on damages of a certain type
     * @param damages a reference to the damage done to the defender
     * @param attackType the Attack type
     * @param attacker the Pokemon ID of the attacker
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const override;
    
    
private:
    //=================// Attributes //==================//
    // Factor and type
    Type m_type;
    float m_factor;
    
    // Specific pokemon
    PokemonID m_poke;
};

#endif /* TYPEBOOSTCOMPONENT_HPP */

