/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightWildManager.hpp
 * Author: Redbuzard
 *
 * Created on 23 décembre 2019, 20:36
 */

#ifndef FIGHTWILDMANAGER_HPP
#define FIGHTWILDMANAGER_HPP

#include "FightEnnemyManager.hpp"

class FightWildManager : public FightEnnemyManager{
public:
    
//=================// Constructor //==================//
    
    
    /**
     * Constructor that takes the wild pokemon as a parameter
     * @param p
     */
    FightWildManager(Pokemon* p);
    
    
//=================// Inherited methods //==================//
  
    /**
     * Update the Ennemy when the fight is ended
     * @param winner true if the ennemy won the fight
     */
    virtual void endFight(bool winner);
    
    
    /**
     * Get the next ennemy Action
     * @param ennemy a pointer to the character's pokemon
     * @param canSwitch true if the current pokemon can switch out
     * @return the action as FightAction enum
     */
    virtual FightAction getNextAction(Pokemon* ennemy, bool canSwitch);
    
    
    /**
     * Get the next attack used by the ennemy
     * @return the attack index as an int
     */
    virtual int getNextAttackIndex();
    
    
    /**
     * Check if the ennemy has some pokemons not KO
     * @return true if there are pokemons not KO
     */
    virtual bool hasPokemonsNotKO();
    
    
    /**
     * Get the index of the first pokemon not KO
     * @return the index of the pokemon as an int
     */
    virtual int getFirstPokemonNotKO();
    
    
    /**
     * Get the curent fighting pokemon
     * @return a pointer to the fighting pokemon
     */
    virtual Pokemon* getCurrentPokemon();
    
    
    /**
     * Check if the player can possibly flee from this ennemy
     * @return true if the player can possibly flee
     */
    virtual bool playerCanFlee();
    
    
    /**
     * Check if the player can capture the wild pokemon
     * @return true if the player can capture the pokemon
     */
    virtual bool canBeCaptured();
    
    
    /**
     * Check if the Ennemy managed is a Trainer
     * @return true if the ennemy is a trainer
     */
    virtual bool isTrainer();
    
    
    /**
     * Get the ID of the item the trainer wish to us
     * @return the ItemID of the Item
     */
    virtual ItemID getItemToUse() const;

    
//=================// Public methdos //==================//
    
    /**
     * Get the capture rate of the pokemon
     * @param ballRate the ball rate as a float
     */
    int captureRate(float ballRate);
    
    
    /**
     * Get the number of bounces for the pokeball thrown
     * Returns 4 if the capture is a success
     * @param captureRate the capture rate calculated
     * @return the number of bounces as an int
     */
    int bouncesNumber(int captureRate);
    
private:
//=================// Attributes //==================//
    
    // A pointer to the wild pokemon
    Pokemon* m_pokemon;
};

#endif /* FIGHTWILDMANAGER_HPP */

