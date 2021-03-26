/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvBoostComponent.hpp
 * Author: Redbuzard
 *
 * Created on 20 mars 2021, 10:28
 */

#ifndef EVBOOSTCOMPONENT_HPP
#define EVBOOSTCOMPONENT_HPP

#include "../ItemComponent.hpp"
#include "../../../Enums.hpp"

class EvBoostComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    /**
     * Constructor
     */
    EvBoostComponent(int boost, StatName stat, BonusType bonusType);
    
    
    /**
     * Apply a boost on the Ev gained
     * @param evAmount a reference to the Ev amount
     * @param stat the Ev StatName 
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onEvReceived(int& evAmount, StatName stat) const override;

    
private:
    //=================// Attributes //==================//
    
    // The boost amount
    int m_boost;
    
    // The stat concerned
    StatName m_stat;
    
    // Type of bonus
    BonusType m_bonusType;
};

#endif /* EVBOOSTCOMPONENT_HPP */

