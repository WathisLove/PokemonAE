/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPBooster.hpp
 * Author: Redbuzard
 *
 * Created on 31 janvier 2021, 15:39
 */

#ifndef XPBOOSTER_HPP
#define XPBOOSTER_HPP

#include "../ItemComponent.hpp"

class XPBoostComponent : public ItemComponent{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    XPBoostComponent(float boostFactor);
    
    
    //=================// Public methods //==================//
    
    /**
     * Apply a boost on the XP Gained
     * @param xpGained a reference to the xp gained
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onXPGained(int& xpGained) const override;

    
private:
    //=================// Attributes //==================//
    
    // Factor of boost ( > to 1)
    float m_boostFactor;

};

#endif /* XPBOOSTER_HPP */

