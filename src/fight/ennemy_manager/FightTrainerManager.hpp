/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightTrainerManager.hpp
 * Author: Redbuzard
 *
 * Created on 22 décembr19
 */

#ifndef FIGHTTRAINERMANAGER_HPP
#define FIGHTTRAINERMANAGER_HPP

#include "FightEnnemyManager.hpp"
#include "../../entities/Trainer.hpp"
#include "../../entities/Champion.hpp"


class FightTrainerManager : public FightEnnemyManager {
public:
    
//=================// Constructor //==================//
    
    
    /**
     * Constructor that takes a pointer to the managed trainer
     */
    FightTrainerManager(Trainer* trainer);
    
    
//=================// Public methods //==================//
    
    
    /**
     * Switch two pokemons in the Trainer team
     * @param index1 the index of the first pokemon to switch (normally the current one)
     * @param index2 the index of the second pokemon to switch
     */
    void switchPokes(int index1, int index2);
    
    
    /**
     * Get the ID of the item the trainer wish to us
     * @return the ItemID of the Item
     */
    virtual ItemID getItemToUse() const;
    
    
    /**
     * Take off a single item of a given ID from the trainer inventory
     * @param id the ItemID that will be taken off
     */
    void useItem(ItemID id);
    
    
    /**
     * Send the next pokemon to the fight
     */
    void sendBetterPokemon(Pokemon* ennemy);
    
    
//=================// Getters //==================//
    
    
    /**
     * Get the Trainer name
     * @return the name as a const reference to a string
     */
    const sf::String& getTrainerName();
    
    
    /**
     * Get the trainer
     * @return a pointer to the trainer
     */
    Trainer* getTrainer();
    
    
//=================// Inherited methods //==================//
  
    /**
     * Update the Ennemy when the fight is ended
     * @param winner true if the ennemy won the fight
     */
    virtual void endFight(bool winner);
    
    
    /**
     * Get the next ennemy Action
     * @param ennemy the Player's pokemon 
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
    
    
private:
    
//=================// Private methods //==================//
    
    
    /**
     * Check if the Trainer should switch its pokemon
     * @param ennemy the Player's pokemon 
     * @return truf if the trainer should switch
     */
    bool shouldSwitch(Pokemon* ennemy);
    
    
    /**
     * Check if the Trainer should use an item
     * @param ennemy a pointer to the Ennemy
     * @return true if the trainer should use an item
     */
    bool shouldUseItem(Pokemon* ennemy);
    
    /**
     * Check if the Trainer should heal one of its pokemons
     * @return true if the trainer should use a healing item
     */
    bool shouldHeal();
    
    /**
     * Check if the Trainer should cure the status of one of its pokemons
     * @return true if the trainer should use an item
     */
    bool shouldCureStatus();
    
    
    /**
     * Get the best pokemon against a given ennemy
     * @param ennemy a pointer to the ennemy
     * @return a pointer to the best pokemon in the team
     */
    Pokemon* getBestPokemonAgainst(Pokemon* ennemy);
    
    
    /**
     * Calculates the index of the attack that is best against the ennemy
     * @param ennemy a pointer to the ennemy
     */
    void calculateBestAttack(Pokemon* ennemy);
    
    
//=================// Attributes //==================//
    
    // A pointer to the Trainer
    Trainer* m_trainer;
    
    // The best option for the switch
    Pokemon* m_bestOption;
    
    // The item the trainer might want to use
    ItemID m_itemOption;
    
    // The best attack option for the trainer 
    int m_attackOption;
};

#endif /* FIGHTTRAINERMANAGER_HPP */

