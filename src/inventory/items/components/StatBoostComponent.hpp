/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatBoostComponent.hpp
 * Author: Redbuzard
 *
 * Created on 19 janvier 2021, 14:58
 */

#ifndef STATBOOSTCOMPONENT_HPP
#define STATBOOSTCOMPONENT_HPP

#include "../ItemComponent.hpp"

class StatBoostComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    
    StatBoostComponent(StatName stat, float factor, PokemonID holder = PokemonID::UNKWNOWN);
    
    
    //=================// Public methods //==================//
    
    /**
     * Apply changes to a stat value
     * @param statValue a reference to the stat value
     * @param stat the Stat Type
     * @param holder the Pokemon ID of the Holder
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onStat(int& statValue, StatName stat, PokemonID holder) const override;

    
protected:
    //=================// Attributes //==================//
    // Stat and factor
    StatName m_stat;
    float m_factor;
    
    // The holder (UNKWNON if not used)
    PokemonID m_holder;
};

#endif /* STATBOOSTCOMPONENT_HPP */

