/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvolutionCondition.hpp
 * Author: Redbuzard
 *
 * Created on 27 février 2020, 17:16
 */

#ifndef EVOLUTIONCONDITION_HPP
#define EVOLUTIONCONDITION_HPP

#include <vector>

#include "../pokemons/PokemonID.hpp"
#include "attacks/AttackID.hpp"
#include "../ItemEnums.hpp"

class Pokemon;

class EvolutionCondition {
public:
    
//=================// Constructor //==================//
    
    EvolutionCondition(PokemonID evolutionID);
    
    
//=================// Public methods //==================//
    
    /**
     * Add a level condition to the vector
     * @param level the minimal level at which the pokemon can evolve
     */
    void addLevelCondition(int level);
    
    /**
     * Add a Item use condition to the vector
     * @param itemID the ItemID of the item we must use on the Pokemon to evolve
     */
    void addItemUseCondition(ItemID itemID);
    
    /**
     * Add a Item wear condition to the vector
     * @param itemID the ItemID of the item the Pokemon must wear to evolve
     */
    void addItemWearCondition(ItemID itemID);
    
    /**
     * Add a Attack learned condition to the vector
     * @param attackID the AttackID of the attack the pokemon needs to know to evolve
     */
    void addAttackLearnedCondition(AttackID attackID);
    
    /**
     * Check if a pokemon fulfills the conditions to evolve
     * @param pokemon a pointer to the pokemon that we want to check
     * @return true if the pokemon can evolve
     */
    bool completesConditions(Pokemon* pokemon);
    
    
//=================// Getters //==================//
    
    
    /**
     * Return the ID of the pokemon the child one can evolve into
     * @return the Evolved PokemonID
     */
    PokemonID getEvolutionID();
    
private:
//=================// Conditions //==================//
    
    
    enum EvolveConditionType{
        LevelUp_C,
        ItemUse_C,
        ItemWear_C,
        AttackLearned_C,
    };
    
    struct EvolveCond{
        EvolveConditionType type;
        int value;
    };
    
    
//=================// Private methods //==================//
    
    /**
     * Checked if a single condition is fulfilled
     * @param cond a reference to the condition
     * @param pokemon a pointer to the pokemon
     * @return true if the pokemon fulfills the conditionA
     */
    bool checkSingleCondition(EvolveCond& cond, Pokemon* pokemon);
    
    
//=================// Attributes //==================//
    
    // The Evolution ID
    PokemonID m_evolutionID;
    
    // A vector of conditions for the evolution
    std::vector<EvolveCond> m_conditions;
};

#endif /* EVOLUTIONCONDITION_HPP */

