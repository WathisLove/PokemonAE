/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CritBoosterComponent.hpp
 * Author: Redbuzard
 *
 * Created on 29 janvier 2021, 16:31
 */

#ifndef CRITBOOSTERCOMPONENT_HPP
#define CRITBOOSTERCOMPONENT_HPP

#include "../ItemComponent.hpp"

class CritBoosterComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    CritBoosterComponent(int boostLevel);
    
    
    //=================// Public methods //==================//
    
    /**
     * Apply a boost on damages of a certain type
     * @param critLeve a reference to the crit level of the attack
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onCritLevel(int& critLevel) const override;
    
private:
    //=================// Attributes //==================//
    
    // Boost to crit level
    int m_critBoost;
};

#endif /* CRITBOOSTERCOMPONENT_HPP */

