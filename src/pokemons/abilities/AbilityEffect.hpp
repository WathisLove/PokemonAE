/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AbilityEffect.hpp
 * Author: Redbuzard
 *
 * Created on 29 juillet 2020, 14:21
 */

#ifndef ABILITYEFFECT_HPP
#define ABILITYEFFECT_HPP

#include "../attacks/StatsChanger.hpp"

/**
 * A class used to know the effects of an Ability when entering the fight, if it paralyses the ennemy, ...
 */
class AbilityEffect {
public:
//=================// Enum //==================//
    
    /**
     * Enum for the type of effect
     */
    enum AbilityEffectType{
        AE_NOT_DEFINED = -1,
        AE_ChangeStats = 1,
    };
    
//=================// Constructor //==================//
    
    /**
     * Default Constructor
     */
    AbilityEffect();
    
    
    /**
     * Constructor to apply a Stat Change
     * @param changer the StatChanger that will be applied
     */
    AbilityEffect(StatsChanger changer);
    
    
//=================// Setters //==================//
    
    
    /**
     * Set the AbilityEffect to change Stats of one of the pokemons
     * @param changer the StatChanger that will be applied
     */
    void setChangeStats(StatsChanger changer);
    
    
    
//=================// Getters //==================//
    
    
    /**
     * Get the Ability Effect type
     * @return the type as an enum
     */
    AbilityEffectType getType();
    
    
    /**
     * Get the stat Changer linked to the Ability Effect
     * @warnin will throw an error if the EffectType is not correct
     * @return a reference to the StatChanger
     */
    StatsChanger& getStatChanger();
    
    
private:
//=================// Attributes //==================//
    
    
    // The Effect type
    AbilityEffectType m_type;
    
//=================// Union Attributes //==================//

    // The infos related to the Ability effect
    union {
        StatsChanger m_statChanger;
    };
    
};

#endif /* ABILITYEFFECT_HPP */

