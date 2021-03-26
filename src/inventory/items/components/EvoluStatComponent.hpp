/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvoluStatComponent.hpp
 * Author: Redbuzard
 *
 * Created on 3 février 2021, 15:32
 */

#ifndef EVOLUSTATCOMPONENT_HPP
#define EVOLUSTATCOMPONENT_HPP

#include "StatBoostComponent.hpp"


class EvoluStatComponent : public StatBoostComponent{
public:
    
    /**
     * Constructor
     */
    EvoluStatComponent(StatName stat, float factor);

    
    //=================// Public methods //==================//
    
    /**
     * Apply changes to a stat value
     * @param statValue a reference to the stat value
     * @param stat the Stat Type
     * @param holder the Pokemon ID of the Holder
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onStat(int& statValue, StatName stat, PokemonID holder) const override;

private:

};

#endif /* EVOLUSTATCOMPONENT_HPP */

