#include <cassert>
#include <sstream>

#include "../utility/Logger.hpp"
#include "../utility/CSVParser.hpp"

#include "EntityLoader.hpp"

#include "Trainer.hpp"
#include "PhysicalItem.hpp"
#include "BoxPC.hpp"
#include "../zones/StoryTrigger.hpp"
#include "Character.h"
#include "fabric/NPCFabric.hpp"
#include "../zones/Zone.hpp"



bool EntityLoader::loadedFiles = false;



EntityLoader::EntityLoader(Context& context, Zone* zone) :
m_zoneID(ZoneID::undefined_zone),
m_character(nullptr),
m_fabric(context, zone),
m_zone(zone),
m_context(context){
    // Do not load if already things
    if(!loadedFiles){
        loadBoxPCsFiles();
        loadPhysicalItemFiles();
        loadStoryTriggerFiles();
        loadedFiles = true;
    }
}



EntityLoader::~EntityLoader() {
    std::cout << "Deleting Entity Loader" << std::endl;
    clearVectors();
}



void EntityLoader::setCharacter(Character* character) {
    m_character = character;
}



void EntityLoader::load(ZoneID id) {
    m_zoneID = id;
    
    // Clear
    clearVectors();
    
    // Load Entities
    loadPhysicalItems();
    loadNpcs();
    loadStoryTriggers();
    loadBoxPCs();
}



std::vector<PhysicalItem*>& EntityLoader::getPhysicalItems() {
    return m_physicalItems;
}



std::vector<Npc*>& EntityLoader::getNpcs() {
    return m_npcs;
}



std::vector<Trainer*>& EntityLoader::getTrainers() {
    return m_trainers;
}



std::vector<StoryTrigger*>& EntityLoader::getStoryTriggers() {
    return m_storyTriggers;
}



std::vector<BoxPC*>& EntityLoader::getBoxPCs() {
    return m_boxPCs;
}



void EntityLoader::deleteDeadEntities() {
    for(auto it = m_npcs.begin(); it != m_npcs.end(); it++){
        Npc* n = *it;
        
        // Delete the Npc if it is dead
        if(!n->isAlive()){
            delete n;
            it = m_npcs.erase(it) - 1;
        }
    }
    
    
    for(auto it = m_trainers.begin(); it != m_trainers.end(); it++){
        Trainer* t = *it;
        
        // Delete the Npc if it is dead
        if(!t->isAlive()){
            delete t;
            it = m_trainers.erase(it) - 1;
        }
    }
    
    
    for(auto it = m_physicalItems.begin(); it != m_physicalItems.end(); it++){
        PhysicalItem* item = *it;
        
        // Delete the Npc if it is dead
        if(!item->isAlive()){
            delete item;
            it = m_physicalItems.erase(it) - 1;
        }
    }
    
    
    for(auto it = m_boxPCs.begin(); it != m_boxPCs.end(); it++){
        BoxPC* pc = *it;
        
        // Delete the Npc if it is dead
        if(!pc->isAlive()){
            delete pc;
            it = m_boxPCs.erase(it) - 1;
        }
    }
}



void EntityLoader::clearVectors() {
    // Clear Physical Items
    for(PhysicalItem* i : m_physicalItems)
        delete i;
    m_physicalItems.clear();
    
    
    // Clear Npcs
    for(Npc* n : m_npcs)
        delete n;
    m_npcs.clear();
    
    
    // Clear Trainers
    for(Trainer* t : m_trainers)
        delete t;
    m_trainers.clear();
    
    
    // Clear BoxPCs
    for(BoxPC* b : m_boxPCs)
        delete b;
    m_boxPCs.clear();
    
    
    // Clear story triggers
    for(StoryTrigger* st : m_storyTriggers)
        delete st;
    m_storyTriggers.clear();
}



void EntityLoader::loadPhysicalItems() {
    // Find the range of items
    auto itemRange = zoneItems.equal_range(m_zoneID);
    
    // Create each item that was not found
    for(auto it = itemRange.first; it != itemRange.second; it++){
        // Get the Data
        PhysicalItemData data = it->second;
        
        // If the character didn't pick it
        if(!m_character->pickedItem(data.number)){
            // Creat the item
            PhysicalItem* item = new PhysicalItem(m_context, sf::Vector2i(data.x, data.y), 
                                                        m_zone, data.item, data.count);
            
            // Set the Item number
            item->setNumber(data.number);
            
            // Push the item
            m_physicalItems.push_back(item);
        }
    }
}



void EntityLoader::loadNpcs() {
    // Find the range of NPCs
    auto npcRange = zoneNpcs.equal_range(m_zoneID);
    
    // Create each Npc if they are allowed to spawn
    for(auto it = npcRange.first; it != npcRange.second; it++){
        // Get the Data
        NpcID id = it->second;
        
        // Check the Npc can spawn
        if(meetsSpawnConditions(id)){
            // Create the Npc
            Npc* n = m_fabric.create(id);
            
            // Push trainers in a different vector
            if(n->getType() == EntityType::Trainer_Type){
                // Convert to a trainer
                Trainer* t = (Trainer*)n;
                
                // Set it to defeated if already defeated
                if(m_character->defeatedTrainer(t->getID())){
                    t->setDefeated(true);
                }
                
                // Add the Trainer
                m_trainers.push_back((Trainer*)t);
            }
            else{
                m_npcs.push_back(n);
            }
        }
    }
}



void EntityLoader::loadBoxPCs() {
    // Find the range of items
    auto boxRange = zoneBoxPCs.equal_range(m_zoneID);
    
    // Create each item that was not found
    for(auto it = boxRange.first; it != boxRange.second; it++){
        // Get the Data
        sf::Vector2i pos = it->second;
        
        m_boxPCs.push_back(new BoxPC(m_context, pos, m_zone));
    }
}



void EntityLoader::loadStoryTriggers(){
    // Find the Triggers in the zone
    auto triggerRange = zoneStoryTriggers.equal_range(m_zoneID);
    
    // Create the StoryTrigger
    for(auto it = triggerRange.first; it != triggerRange.second; it++){
        // Get the data
        StoryTriggerData data = it->second;
        sf::IntRect rect = sf::IntRect(data.x, data.y, data.width, data.height);
        
        // Add the Trigger
        m_storyTriggers.push_back(new StoryTrigger(rect, data.npc, data.deactivates, data.repulseDir));
    }
}



bool EntityLoader::meetsSpawnConditions(NpcID npc){
    // Check if the Npc is in the map
    auto npcCond = npcSpawnConditions.find(npc);
    
    // If there are spawn condition
    if(npcCond != npcSpawnConditions.end()){
        return npcCond->second->canSpawn(m_character);
    }

    // Else return true
    return true;
}



void EntityLoader::addNpcZone(ZoneID zone, NpcID npc) {
    zoneNpcs.emplace(zone, npc);
}



void EntityLoader::addNpcCondition(NpcID npc, Condition* condition) {
    npcSpawnConditions.emplace(npc, condition);
}



void EntityLoader::loadBoxPCsFiles() {
    // Open the file
    CSVParser parser("../data/entities/box_pcs.csv");
    
    // Ignore first line
    parser.readLine();
    
    while(parser.readLine()){
        // Get the elements 
        auto elements = parser.getLineElements();
        
        // Get the Zone name
        ZoneID zone = Zone::fromFilenameToID(elements.at(0));
        
        // Get the coords
        sf::Vector2i pos;
        std::istringstream streamX(elements.at(1));
        std::istringstream streamY(elements.at(2));
        
        // If the coords were extracted
        if(streamX >> pos.x && streamY >> pos.y){
            Log("Loaded a box pc in " + elements.at(0), Logger::FILE_INFO);
            zoneBoxPCs.emplace(zone, pos);
        }
    }
}



void EntityLoader::loadPhysicalItemFiles() {
    // For each file
    for(auto it : Zone::zoneFileNames){
        std::string path = "../data/entities/physical_items/" + it.second + ".csv";
        
        // Open the file
        CSVParser parser(path);

        // Ignore first line
        parser.readLine();

        while(parser.readLine()){
            // Get the elements 
            auto elements = parser.getLineElements();

            // Data storage
            PhysicalItemData data;

            // Get the Item Num
            std::istringstream numStream(elements.at(0));

            // Get the coords
            std::istringstream coordStream(elements.at(1));

            // Get the Item ID
            data.item = Item::getID(elements.at(2));

            // Get the Item Count
            std::istringstream countStream(elements.at(0));

            // If the data was extracted
            if(numStream >> data.number && coordStream >> data.x && coordStream >> data.y && countStream >> data.count){
                Log("Loaded item " + elements.at(2) + " in " + it.second, Logger::FILE_INFO);
                zoneItems.emplace(it.first, data);
            }
            else{
                Log("Could not load data for item " + elements.at(2) + " in " + it.second, Logger::FILE_ERROR);
            }
        }
    }
}



void EntityLoader::loadStoryTriggerFiles() {
    // For each file
    for(auto it : Zone::zoneFileNames){
        std::string path = "../data/entities/story_triggers/" + it.second + ".csv";
        
        // Open the file
        CSVParser parser(path);

        // Ignore first line
        parser.readLine();

        while(parser.readLine()){
            // Get the elements 
            auto elements = parser.getLineElements();

            // Data storage
            StoryTriggerData data;

            // Get the rect coords
            std::istringstream rectStream(elements.at(0));

            // Get the Npc ID
            std::istringstream npcStream(elements.at(1));
            int npcID;

            // Get the deactivate boolean value
            std::istringstream deactivateStream(elements.at(2));
            int deactivates;

            // If the data was extracted
            if(npcStream >> npcID && deactivateStream >> deactivates && rectStream >> data.x && 
                rectStream >> data.y && rectStream >> data.width && rectStream >> data.height){
                
                // Cast the values
                data.deactivates = static_cast<bool>(deactivates);
                data.npc = static_cast<NpcID>(npcID);
                
                // Get repulse direction
                if(!elements.at(3).empty())
                    data.repulseDir = directionStrings.at(elements.at(3));
                
                Log("Loaded story trigger for " + elements.at(1) + " in " + it.second, Logger::FILE_INFO);
                zoneStoryTriggers.emplace(it.first, data);
            }
            else{
                Log("Could not load data for story trigger for " + elements.at(1) + " in " + it.second, Logger::FILE_ERROR);
            }
        }
    }
}
