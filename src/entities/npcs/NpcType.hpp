/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NpcType.hpp
 * Author: Redbuzard
 *
 * Created on 24 novembre 2020, 16:29
 */

#ifndef NPCTYPE_HPP
#define NPCTYPE_HPP

#include "../NPCId.hpp"


enum class NpcType{
    NPC,
    SELLER,
    CHAMPION,
    TRAINER,
    
};


// Maps for the Npc Types
extern std::map<std::string, NpcType> npcTypeStrings;

extern std::map<NpcID, NpcType> npcTypes;


//// Useful methods to know the NPC Type


/**
 * Check if a NPC is just a NPC
 * @param id the Npc ID
 * @return true if the Npc is only a Npc
 */
bool isJustNPC(NpcID id);



/**
 * Check if a NPC id is the one of a Healer
 * @param id the NPC Id
 * @return true if the Npc is a healer
 */
bool isHealer(NpcID id);



/**
 * Check if a Npc is a Seller
 * @param id the Npc ID
 * @return true if the Npc is a seller
 */
bool isSeller(NpcID id);



/**
 * Check if a Npc is a Champion
 * @param id the Npc ID
 * @return true if the Npc is a champion
 */
bool isChampion(NpcID id);



/**
 * Check if a NPC ID is one of a trainer
 * @param id the NPC Id
 * @return true if the NPC is a Trainer
 */
bool isTrainer(NpcID id);


#endif /* NPCTYPE_HPP */
