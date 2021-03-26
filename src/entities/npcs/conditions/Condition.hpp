/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Condition.hpp
 * Author: Redbuzard
 *
 * Created on 6 décembre 2020, 14:58
 */

#ifndef CONDITION_HPP
#define CONDITION_HPP

#include <vector>
#include <string>

#include "../../NPCId.hpp"
#include "../../../zones/ZoneID.hpp"

class Character;

class Condition {
public:
    //=================// Construtor //==================//
    
    /**
     * Constructor
     */
    Condition(const std::string& str);
    
    
    //=================// Public methods //==================//
    
    
    /**
     * Check if the Npc is allowed to spawn
     * @param character a pointer to the character
     * @return true if the Npc can spawn
     */
    bool canSpawn(Character* character) const;
    
    
private:
    
    //=================// Private methods //==================//
    
    /**
     * Add a single condition
     * @param str the condition string
     */
    void addCondition(const std::string& str);
    
    
    /**
     * Add a condition for a visited zone
     * @param zone the Zone ID
     */
    void addVisited(ZoneID zone);
    
    /**
     * Add a condition for a not visited zone
     * @param zone the Zone ID
     */
    void addNotVisited(ZoneID zone);
    
    /**
     * Add a condition for a met Npc
     * @param npc the Npc ID
     */
    void addMet(NpcID npc);
    
    /**
     * Add a condition for a not met Npc
     * @param npc the Npc ID
     */
    void addNotMet(NpcID npc);
    
    
    /**
     * Add a conditon for defeating a trainer
     * @param trainerID the trainer ID
     */
    void addDefeated(NpcID trainerID);
    
    
    /**
     * Add a conditon for not defeating a trainer
     * @param trainerID the trainer ID
     */
    void addNotDefeated(NpcID trainerID);
    
   
    //=================// Structures //==================//
    
    
    /**
     * A structure for zone conditions
     */
    struct ZoneCondition{
        bool visited;
        ZoneID zone;
    };
    
    /**
     * A structure for NPC met conditions
     */
    struct NpcCondition{
        bool met;
        NpcID npc;
    };
    
    /**
     * A structure for NPC met conditions
     */
    struct TrainerCondition{
        bool defeated;
        NpcID trainer;
    };
    
    //=================// Attributes //==================//
    
    // Vector of Npc Met conditions
    std::vector<NpcCondition> m_npcConditions;
    
    // Vector of Zone visited conditions
    std::vector<ZoneCondition> m_zoneConditions;
    
    // Vector of Trainer defeated conditions
    std::vector<TrainerCondition> m_trainerConditions;
};

#endif /* CONDITION_HPP */

