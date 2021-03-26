/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HappinessBoostComponent.hpp
 * Author: Redbuzard
 *
 * Created on 5 février 2021, 12:11
 */

#ifndef HAPPINESSBOOSTCOMPONENT_HPP
#define HAPPINESSBOOSTCOMPONENT_HPP

#include "../ItemComponent.hpp"

class HappinessBoostComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    HappinessBoostComponent(float factor);
    
    
    //=================// Public methods //==================//
    
    /**
     * Apply a boost on the happiness gained
     * @param happinessAmount a reference to the hapinness amount
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onHappinessReceived(int& happinessAmount) const override;

    
private:
    //=================// Attributes //==================//
    // The boost factor
    float m_boostFactor;
};

#endif /* HAPPINESSBOOSTCOMPONENT_HPP */

