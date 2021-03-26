/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightEnnemyManager.hpp
 * Author: Redbuzard
 *
 * Created on 22 décembre 2019, 09:58
 */

#ifndef FIGHTENNEMYMANAGER_HPP
#define FIGHTENNEMYMANAGER_HPP

#include "../FightAction.hpp"
#include "../../pokemons/Pokemon.hpp"

// Interface used to manage the ennemy during a fight
class FightEnnemyManager {
public:
    
//=================// Abstract methods //==================//
    
    /**
     * Update the Ennemy when the fight is ended
     * @param winner true if the ennemy won the fight
     */
    virtual void endFight(bool winner) = 0;
    
    
    /**
     * Get the next ennemy Action
     * @param ennemy a pointer to the character's pokemon
     * @param canSwitch true if the current pokemon can switch out
     * @return the action as FightAction enum
     */
    virtual FightAction getNextAction(Pokemon* ennemy, bool canSwitch) = 0;
    
    
    /**
     * Get the next attack used by the ennemy
     * @return the attack index as an int
     */
    virtual int getNextAttackIndex() = 0;
    
    
    /**
     * Check if the ennemy has some pokemons not KO
     * @return true if there are pokemons not KO
     */
    virtual bool hasPokemonsNotKO() = 0;
    
    
    /**
     * Get the index of the first pokemon not KO
     * @return the index of the pokemon as an int
     */
    virtual int getFirstPokemonNotKO() = 0;
    
    
    /**
     * Get the curent fighting pokemon
     * @return a pointer to the fighting pokemon
     */
    virtual Pokemon* getCurrentPokemon() = 0;
    
    
    /**
     * Check if the player can possibly flee from this ennemy
     * @return true if the player can possibly flee
     */
    virtual bool playerCanFlee() = 0;
    
    
    /**
     * Check if the player can capture the wild pokemon
     * @return true if the player can capture the pokemon
     */
    virtual bool canBeCaptured() = 0;
    
    
    /**
     * Check if the Ennemy managed is a Trainer
     * @return true if the ennemy is a trainer
     */
    virtual bool isTrainer() = 0;
    
    
    /**
     * Get the ID of the item the trainer wish to us
     * @return the ItemID of the Item
     */
    virtual ItemID getItemToUse() const = 0;
};

#endif /* FIGHTENNEMYMANAGER_HPP */

