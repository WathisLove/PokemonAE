#include "Condition.hpp"

#include "../../Character.h"
#include "../../../Utilities.hpp"
#include "../../../utility/Logger.hpp"

#include <sstream>


Condition::Condition(const std::string& str) {
    if(str.size() > 0){
        std::vector<std::string>* splitted= new std::vector<std::string>();
        
        // Split each condition string
        split(splitted, str, '+');
        
        // Add each condition
        for(const std::string& str : *splitted)
            addCondition(str);
        
        delete splitted;
    }
}



bool Condition::canSpawn(Character* character) const{
    
    // Npc met Conditions
    for(const NpcCondition& cond : m_npcConditions){
        // If a met condition is not met
        if(cond.met != character->metNPC(cond.npc))
            return false;
    }
    
    // Zone visited conditions
    for(const ZoneCondition& cond : m_zoneConditions){
        // If a visited condition is not met
        if(cond.visited != character->visited(cond.zone))
            return false;
    }
    
    // Trainer defeated conditions
    for(const TrainerCondition& cond : m_trainerConditions){
        // If a visited condition is not met
        if(cond.defeated != character->defeatedTrainer(cond.trainer))
            return false;
    }
    
    return true;
}



void Condition::addCondition(const std::string& str) {
    // Find the separator
    int sepPos = str.find(':');
    
    // If the separator was found
    if(sepPos != str.npos){
        // Get the condition type
        std::string condType = str.substr(0, sepPos);
        
        // Get the associated data
        std::string data = str.substr(sepPos+1);
        
        std::istringstream stream(data);
        int dataInt;
        
        // If we found data to extract
        if(stream >> dataInt){
            if(condType == "VISITED")
                addVisited(static_cast<ZoneID>(dataInt));
            else if(condType == "NOT_VISITED")
                addNotVisited(static_cast<ZoneID>(dataInt));
            else if(condType == "MET")
                addMet(static_cast<NpcID>(dataInt));
            else if(condType == "NOT_MET")
                addNotMet(static_cast<NpcID>(dataInt));
            else if(condType == "DEFEATED")
                addDefeated(static_cast<NpcID>(dataInt));
            else if(condType == "NOT_DEFEATED")
                addNotDefeated(static_cast<NpcID>(dataInt));
            else
                Log("Unknwon condition " + condType, Logger::FILE_ERROR);
        }
    }
}



void Condition::addVisited(ZoneID zone) {
    ZoneCondition zc;
    zc.visited = true;
    zc.zone = zone;
    
    m_zoneConditions.push_back(zc);
}



void Condition::addNotVisited(ZoneID zone) {
    ZoneCondition zc;
    zc.visited = false;
    zc.zone = zone;
    
    m_zoneConditions.push_back(zc);
}



void Condition::addMet(NpcID npc) {
    NpcCondition nc;
    nc.met = true;
    nc.npc = npc;
    
    m_npcConditions.push_back(nc);
}



void Condition::addNotMet(NpcID npc) {
    NpcCondition nc;
    nc.met = false;
    nc.npc = npc;
    
    m_npcConditions.push_back(nc);
}



void Condition::addDefeated(NpcID trainerID) {
    TrainerCondition tc;
    tc.defeated = true;
    tc.trainer = trainerID;
    
    m_trainerConditions.push_back(tc);
}



void Condition::addNotDefeated(NpcID trainerID) {
    TrainerCondition tc;
    tc.defeated = false;
    tc.trainer = trainerID;
    
    m_trainerConditions.push_back(tc);
}
