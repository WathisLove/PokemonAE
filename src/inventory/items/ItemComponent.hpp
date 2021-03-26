/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemComponent.hpp
 * Author: Redbuzard
 *
 * Created on 14 janvier 2021, 16:50
 */

#ifndef ITEMCOMPONENT_HPP
#define ITEMCOMPONENT_HPP

#include "../../pokemons/PokemonID.hpp"
#include "../../Enums.hpp"
#include "../../pokemons/Type.hpp"
#include "../../pokemons/attacks/Attack.hpp"
#include "effects/ItemEffect.hpp"

class Pokemon;

class ItemComponent {
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    ItemComponent();
    
    //=================// Public methods //==================//
    
    /**
     * Apply changes to a stat value
     * @param statValue a reference to the stat value
     * @param stat the Stat Type
     * @param holder the Pokemon ID of the Holder
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onStat(int& statValue, StatName stat, PokemonID holder) const;
    
    /**
     * Apply a boost on damages of a certain type
     * @param damages a reference to the damage done to the defender
     * @param attackType the Attack type
     * @param attacker the Pokemon ID of the attacker
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const;
    
    /**
     * Apply an effect on a pokemon
     * @param pokemon a pointer to the Pokemon
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onPokemon(Pokemon* pokemon) const;
    
    /**
     * Modifiy an attack
     * @param attack a pointer to the Attack
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onAttack(Attack* attack) const;
    
    
    /**
     * Apply a boost on damages of a certain type
     * @param critLeve a reference to the crit level of the attack
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onCritLevel(int& critLevel) const;
    
    
    /**
     * Apply a boost on the XP Gained
     * @param xpGained a reference to the xp gained
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onXPGained(int& xpGained) const;
    
    /**
     * Apply a boost on the Money Gained
     * @param moneyGained a reference to the money gained
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onMoneyGained(int& moneyGained) const;
    
    
    /**
     * Apply a boost on the happiness gained
     * @param happinessAmount a reference to the hapinness amount
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onHappinessReceived(int& happinessAmount) const;
    
    
    /**
     * Apply a boost on the Ev gained
     * @param evAmount a reference to the Ev amount
     * @param stat the Ev StatName 
     * @return a pointer to an ItemEffect, or nullptr
     */
    virtual ItemEffect* onEvReceived(int& evAmount, StatName stat) const;
    
    
    /**
     * Check if the ItemComponent has an effect on the pokemon
     * @param pokemon a pointer to the pokemon
     * @return true if the ItemComponent has an effect on the pokemon
     */
    virtual bool hasEffectOnPokemon(Pokemon* pokemon) const;
    
    
    /**
     * Check if the ItemComponent has an effect on an Attack
     * @param attack a pointer to the Attack
     * @return true if the ItemComponent can have an effect on the attack
     */
    virtual bool hasEffectOnAttack(Attack* attack) const;
};

#endif /* ITEMCOMPONENT_HPP */

