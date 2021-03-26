/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RestorePPComponent.hpp
 * Author: Redbuzard
 *
 * Created on 27 janvier 2021, 11:35
 */

#ifndef RESTOREPPCOMPONENT_HPP
#define RESTOREPPCOMPONENT_HPP

#include "../ItemComponent.hpp"

class RestorePPComponent : public ItemComponent {
public:
    //=================// Constructors //==================//
    
    /**
     * Restore all PPs
     */
    RestorePPComponent();
    
    /**
     * Restore a fixed amount of PPs
     */
    RestorePPComponent(int ppRestored);
    
    
    //=================// Public methods //==================//
    
    /**
     * Restore PPs for all attacks of a pokemon
     * @param pokemon a pointer to the pokemon
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onPokemon(Pokemon* pokemon) const override;

    /**
     * Restore PPs for a single attack
     * @param attack a pointer to the Attack
     * @return a pointer to an ItemEffect, or nullptr
     */
    ItemEffect* onAttack(Attack* attack) const override;

    
    /**
     * Check if the ItemComponent has an effect on the pokemon
     * @param pokemon a pointer to the pokemon
     * @return true if the ItemComponent has an effect on the pokemon
     */
    bool hasEffectOnPokemon(Pokemon* pokemon) const override;
    
    
    /**
     * Check if the ItemComponent has an effect on an Attack
     * @param attack a pointer to the Attack
     * @return true if the ItemComponent can have an effect on the attack
     */
    bool hasEffectOnAttack(Attack* attack) const override;

    
private:
    //=================// Attribuets //==================//
    // Restore all PPs
    bool m_restoreAll;
    
    // Amount restored
    int m_ppRestored;

};

#endif /* RESTOREPPCOMPONENT_HPP */

