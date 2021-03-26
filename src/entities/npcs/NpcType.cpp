#include <map>

#include "NpcType.hpp"
#include "../../Utilities.hpp"


std::map<std::string, NpcType> npcTypeStrings{
    {"CHAMPION", NpcType::CHAMPION},
    {"NPC", NpcType::NPC},
    {"SELLER", NpcType::SELLER},
    {"TRAINER", NpcType::TRAINER},
};

std::map<NpcID, NpcType> npcTypes {};



bool isJustNPC(NpcID id){
    if(npcTypes.find(id) == npcTypes.end())
        throw std::string("Can't find if ") + toString(static_cast<int>(id)) + " is just a Npc";
    
    return npcTypes[id] == NpcType::NPC;
}



bool isSeller(NpcID id){
    if(npcTypes.find(id) == npcTypes.end())
        throw std::string("Can't find if ") + toString(static_cast<int>(id)) + " is a Seller";
    
    return npcTypes[id] == NpcType::SELLER;
}



bool isChampion(NpcID id){
    if(npcTypes.find(id) == npcTypes.end())
        throw std::string("Can't find if ") + toString(static_cast<int>(id)) + " is a Champion";
    
    return npcTypes[id] == NpcType::CHAMPION;
}



bool isTrainer(NpcID id){
    if(npcTypes.find(id) == npcTypes.end())
        throw std::string("Can't find if ") + toString(static_cast<int>(id)) + " is a Trainer";
    
    return npcTypes[id] == NpcType::TRAINER;
}