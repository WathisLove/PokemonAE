/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoneyBoostComponent.hpp
 * Author: Redbuzard
 *
 * Created on 1 février 2021, 18:15
 */

#ifndef MONEYBOOSTCOMPONENT_HPP
#define MONEYBOOSTCOMPONENT_HPP

#include "../ItemComponent.hpp"

class MoneyBoostComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    MoneyBoostComponent(float boostFactor);
    
    
    //=================// Public methods //==================//
    
    /**
     * Apply a boost on the Money Gained
     * @param xpGained a reference to the money gained
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onMoneyGained(int& moneyGained) const override;

    
private:
    //=================// Attributes //==================//
    // The money boost fator
    float m_boostFactor;
};

#endif /* MONEYBOOSTCOMPONENT_HPP */

