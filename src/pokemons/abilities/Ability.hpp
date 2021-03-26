/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ability.hpp
 * Author: Redbuzard
 *
 * Created on 21 juillet 2020, 10:44
 */

#ifndef ABILITY_HPP
#define ABILITY_HPP

#include "AbilityID.hpp"
#include "../attacks/Attack.hpp"
#include "AbilityEffect.hpp"
#include <SFML/System/String.hpp>
#include <map>
#include <functional>

class Pokemon;


class Ability {
public:    
//=================// Constructor //==================//
    
    Ability(AbilityID id);
    
    
//=================// Getters //==================//
    
    
    /**
     * Get the Description string
     * @return 
     */
    sf::String& getDescription();
    
    /**
     * Get the Description string
     * @return 
     */
    sf::String& getName();
    
    
    /**
     * Get the Ability ID
     * @return the ID as an enum
     */
    AbilityID getID();
    
    
//=================// Ability Methods //==================//
    
    
    /**
     * Modifies the Damage value received by the pokemon
     * @return the new value of damages
     */
    float onDamageReceived(float damage, const Attack& attack);
    
    
    /**
     * Modifies the Damage value dealt by the pokemon
     * @return the new value of damages
     */
    float onDamageDealt(float damage, const Attack& attack);
    
    
    /**
     * Check if the Ability allow the Ennemy to switch
     * @param ennemy a pointer to the ennemy
     * @return true if the ennemy is allowed to switch
     */
    bool allowEnnemySwitch(const Pokemon& ennemy);
    
    
    /**
     * Apply an effect once the pokemon leave for an other
     * @param ennemy a pointer to the pokemon owning the Ability
     */
    void onLeavingSwitch(Pokemon* owner);
    
    
    /**
     * Do something when entering the Fight
     * @param owner a pointer to the Ability Owner
     * @param ennemy a pointer to the ennemy
     * @return a AbilityEffect corresponding to the effect when entering fight
     */
    AbilityEffect onEnteringFight(const Pokemon& owner, const Pokemon& ennemy);
    
    
private:
    
//=================// Attributes //==================//
    
    // The Ability ID
    AbilityID m_id;
    
    
//=================// Ability Maps  //==================//
    
    // A map for the Ability Names
    static std::map<AbilityID, sf::String> m_names;
    
    // A map for the Ability Descriptions
    static std::map<AbilityID, sf::String> m_descriptions;
            
            
//=================// Ability Functions Maps //==================//
    
    // A Map for abilities linked to damage received
    static std::map<AbilityID, std::function<float(float, const Attack&)> > m_onDamageReceived;

    // A Map for abilities linked to damage dealt
    static std::map<AbilityID, std::function<float(float, const Attack&)> > m_onDamageDealt;

    // A Map for abilities which allow or not ennemy switch
    static std::map<AbilityID, std::function<bool(const Pokemon&)> > m_allowEnnemySwitch;

    // A Map for abilities which apply an effect on a switched ally
    static std::map<AbilityID, std::function<void(Pokemon*)> > m_onLeavingSwitch;

    // A Map for abilities which apply when enering the fight
    static std::map<AbilityID, std::function<AbilityEffect(const Pokemon&, const Pokemon&)> > m_onEnteringFight;
};

#endif /* ABILITY_HPP */

