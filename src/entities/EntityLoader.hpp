/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityLoader.hpp
 * Author: Redbuzard
 *
 * Created on 26 mars 2020, 20:39
 */

#ifndef ENTITYLOADER_HPP
#define ENTITYLOADER_HPP

#include <vector>

#include "NPCId.hpp"
#include "fabric/NPCFabric.hpp"
#include "BoxPC.hpp"
#include "../entities/npcs/conditions/Condition.hpp"


// Forward declarations
class Character;
class Entity;
class Trainer;
class PhysicalItem;
class BoxPC;
class Npc;
class StoryTrigger;
class Zone;



class EntityLoader{
public:
    //=================// Construtor //==================//
    
    
    /**
     * Creates the Entity Loader
     */
    EntityLoader(Context& context, Zone* zone);


    /**
     * Destructor
     */
    virtual ~EntityLoader();

    
    //=================// Public methods //==================//
    
    /**
     * Set the Character 
     * @param character a pointer to the Character
     */
    void setCharacter(Character* character);
    
    
    /**
     * Load all the Entities of the given zone
     * @param id the Zone id to load
     */
    void load(ZoneID id);
    
    
    /**
     * Get the Physical items loaded
     * @return a reference to the vector of Physical items
     */
    std::vector<PhysicalItem*>& getPhysicalItems();
    
    
    /**
     * Get the Npcs loaded
     * @return a reference to the vector of Npcs
     */
    std::vector<Npc*>& getNpcs();
    
    
    /**
     * Get the Trainers loaded
     * @return a reference to the vector of Trainers
     */
    std::vector<Trainer*>& getTrainers();
    
    
    /**
     * Get the StoryTriggers loaded
     * @return a reference to the vector of StoryTriggers
     */
    std::vector<StoryTrigger*>& getStoryTriggers();
    
    
    /**
     * Get the BoxPCs loaded
     * @return a reference to the vector of Box PCs
     */
    std::vector<BoxPC*>& getBoxPCs();
    
    
    /**
     * Delete all the dead Entities
     */
    void deleteDeadEntities();
    
    
    /**
     * Clear the vectors and delete all entities
     */
    void clearVectors();
    
    
    /**
     * Add a Npc to the zone map
     * @param zone the Zone ID
     * @param npc the Npc ID
     */
    static void addNpcZone(ZoneID zone, NpcID npc);
    
    
    /**
     * Add a span condition for a given npc
     * @param npc the Npc ID
     * @param condition a pointer to the condition
     */
    static void addNpcCondition(NpcID npc, Condition* condition);
    
protected:
    //=================// Enum //==================//
    
    /**
     * A structure for possible PhysicalItems
     */
    struct PhysicalItemData{
        int number;
        int x;
        int y;
        ItemID item;
        int count;
    };
    
    
    /**
     * A structure for 
     */
    struct StoryTriggerData{
        int x, y, width, height;
        NpcID npc;
        bool deactivates;
        Direction repulseDir;
    };

    
    //=================// Private methods : Loading Entities //==================//
    
    
    /**
     * Load the Physical Items of the current Zone
     */
    void loadPhysicalItems();
    
    
    /**
     * Load the Npcs of the Current zone
     */
    void loadNpcs();
    
    
    /**
     * Load the Story triggers
     */
    void loadStoryTriggers();
    
    
    /**
     * Load the Box PCs
     */
    void loadBoxPCs();
    
    
    
    //=================// Private methods : Load files //==================//
    
    /**
     * Load the Box PCs from files
     */
    void loadBoxPCsFiles();
    
    /**
     * Load the physical items from files
     */
    void loadPhysicalItemFiles();
    
    /**
     * Load the story trigger from files
     */
    void loadStoryTriggerFiles();
    
    
    //=================// Private methods : SpawnConditions //==================//

    /**
     * Check if a given Npc meets the conditions to spawn
     * @param npc the NPC ID of the Npc we want to spawn
     * @param character a pointer to the character
     * @return true if the Npc can spawn
     */
    bool meetsSpawnConditions(NpcID npc);
    
    
    //=================// Attributes //==================//
    
    // The Zone Id
    ZoneID m_zoneID;
    
    // A pointer to the Zone
    Zone* m_zone;
    
    // A reference to the context
    Context& m_context;
    
    // A pointer to the Character
    Character* m_character;
    
    // The Npc fabric
    NPCFabric m_fabric;
    
    // Vector of Physical Items
    std::vector<PhysicalItem*> m_physicalItems;
    
    // Vector of Npcs
    std::vector<Npc*> m_npcs;
    
    // Vector of Npcs
    std::vector<Trainer*> m_trainers;
    
    // Vector of Npcs
    std::vector<BoxPC*> m_boxPCs;
    
    // Story Triggers
    std::vector<StoryTrigger*> m_storyTriggers;
    
    
    //=================// Data maps //==================//
    
    // Boolean to know if the data were loaded
    static bool loadedFiles;
    
    // Npcs for the differents Zones
    static std::multimap<ZoneID, NpcID> zoneNpcs;

    // Map for the Npc Conditions
    static std::map<NpcID, Condition*> npcSpawnConditions;
    
    // PhysicalItems for the differents Zones 
    static std::multimap<ZoneID, PhysicalItemData> zoneItems;
    
    // PhysicalItems for the differents Zones 
    static std::multimap<ZoneID, sf::Vector2i> zoneBoxPCs;
    
    // Story Triggers for the differents Zones
    static std::multimap<ZoneID, StoryTriggerData> zoneStoryTriggers;
};


#endif /* ENTITYLOADER_HPP */
