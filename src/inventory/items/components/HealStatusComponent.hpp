/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealStatusComponent.hpp
 * Author: Redbuzard
 *
 * Created on 23 janvier 2021, 13:02
 */

#ifndef HEALSTATUSCOMPONENT_HPP
#define HEALSTATUSCOMPONENT_HPP

#include "../ItemComponent.hpp"

class HealStatusComponent : public ItemComponent {
public:
    //=================// Constructors //==================//
    
    /**
     * Constructor to heal any status
     */
    HealStatusComponent();
    
    
    /**
     * Constructor to heal a specific status
     * @warning poison heals also poison
     */
    HealStatusComponent(MainStatusName statusCured);
    
    
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
    //=================// Private method //==================//
    
    
    /**
     * Cure the pokemon Status
     * @param p a pointer to the pokemon
     * @return the MainStatus name of the cured status
     */
    MainStatusName cure(Pokemon* p) const;
    
    
    /**
     * Get the message corresponding to the cure
     * @param p a pointer to the healed pokemon
     * @param status the Main Status Name 
     * @return a pointer to the SFML string containing the display message
     */
    sf::String* getCureMessage(Pokemon* p, MainStatusName status) const;
    
    
    
    //=================// Attributes //==================//
    // Heal any status
    bool m_healAnyStatus;
    
    // Specific status healed
    MainStatusName m_statusHealed;
};

#endif /* HEALSTATUSCOMPONENT_HPP */

