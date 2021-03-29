/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Zone.hpp
 * Author: Redbuzard
 *
 * Created on 17 juin 2018, 14:31
 */

#ifndef ZONE_HPP
#define ZONE_HPP


#include <string>
#include <vector>
#include "ZoneLayer.hpp"
#include "CollisionLayer.hpp"
#include "../resources/TextureHolder.hpp"
#include "ZoneChanger.hpp"
#include "../Context.hpp"
#include "managers/WildPokemonManager.hpp"
#include "StoryTrigger.hpp"
#include "../entities/EntityLoader.hpp"
#include "ZoneDialogLoader.hpp"


using namespace std;


class StateStack;
class Entity;
class Character;
class Trainer;
class Npc;


/**
 * Zone class
 * Its goal is to display the zone
 */
class Zone
{
public:
//===============// Static Methods //===============//

    /**
     * Return the name of the zone as a string
     * @param id the id of the zone
     * @return the name of the zone
     */
    static string fromIDtoFilename(ZoneID id);
    
    
    /**
     * Return the ZoneID from the Filename
     * @param str the string stored in the files
     */
    static ZoneID fromFilenameToID(string str);
    
    
    /**
     * Get the zone name (in a form that can be displayed)
     * @param id the zone ID
     * @return the zone name as a string
     */
    static sf::String getZoneName(ZoneID id);
    
//===============// Public Methods //===============//
    
    Zone(ZoneID id, Context& context, StateStack* stack);
    
    ~Zone();
    
    
    /**
     * Draw the background and the background decoration
     */
    void drawBackground(sf::RenderTarget& target, sf::RenderStates states) const;
    
    /**
     * Draw the foreground and the foreground decoration
     */
    void drawForeground(sf::RenderTarget& target, sf::RenderStates states) const;


    /**
     * Draw entities below the player
     */
    void drawEntitiesBelowPlayer(sf::RenderTarget& target, sf::RenderStates states, sf::Vector2i characterPos);

    /**
     * Dra entities above the player
     */
    void drawEntitiesAbovePlayer(sf::RenderTarget& target, sf::RenderStates states, sf::Vector2i characterPos);
    
    
    /**
     * Update the zone
     * @param dt is the elapsed time
     */
    void update(float dt);
    
    
    /**
     * Check if the given position is out of the bounds of the Zone
     * @param pos given position 
     * @return true if the position is invalid
     */
    bool isOutOfBounds(sf::Vector2i pos) const;
    
    /**
     * Get the zone size
     * @return the zone size
     */
    sf::Vector2i getZoneSize() const;
    
    /**
     * Return the cordinates of the case center
     * @param index index of the case
     * @return the coordinates of the case center
     */
    sf::Vector2f getCaseCenter(sf::Vector2i index) const;
    
    
    /**
     * Check if there is an Entity on the case
     * @param index index of the case
     * @return true if an Entity is occupying the case
     */
    bool hasEntityOnCase(sf::Vector2i index);
    
    
    /**
     * Return a boolean depending on wether the entities can walk onto this case or not
     * @param index index of the case
     * @return true if it can walk on the case
     */
    bool canWalkOnCase(sf::Vector2i index) ;
    
    /**
     * Return a boolean depending on wether the entities can surf onto this case or not
     * @param index index of the case
     * @return true if it can surf on the case
     */
    bool canSurfOnCase(sf::Vector2i index) const;
    
    /**
     * Return a boolean depending on wether the entities can jump over this case or not
     * @param index index of the case
     * @param dir direction of the Entity
     * @return true if it can jump over the case
     */
    bool canJumpOverCase(sf::Vector2i index, Direction dir) const;
    
    
    /**
     * Try to trigger a wild encounter at the given case
     * @param index the case as a Vector2i
     */
    void triggerEncounter(sf::Vector2i index);
    
    
    /**
     * Load a Zone with its id
     * @param id id of the new zone
     */
    void loadZone(ZoneID id);
    
    
    /**
     * Set the Character pointer of the zone
     * @param c a pointer to the Character
     */
    void setCharacter(Character* c);
    
    
    /**
     * Return the Entity at the given index
     * Throw an exception if nothing was found at the case; 
     */
    Entity* getEntityAtCase(sf::Vector2i index);
    
    
    /**
     * Make the character return to the closest healing center
     */
    void characterBackToHeal();
    
    
    /**
     * Delete the dead entities
     */
    void deleteDeadEntities();
    
    
    /**
     * Get the zone ID
     * @return the Zone ID
     */
    ZoneID getZoneID();
    
    /**
     * Check if we must show the Zone Name
     * @return true if we must show the zone name
     */
    bool mustShowZoneName();
    
    
    /**
     * Check if a Story Trigger was triggered
     * @return true if the character is in one of the story triggers
     */
    bool hasTriggeredStory();
    
    /**
     * Get the StoryTrigger that was triggered
     * @return a pointer to the StoryTrigger
     */
    StoryTrigger* getStoryTriggered();
    
    /**
     * Get the Npc Triggered by the Story Trigger
     * @return a pointer to the Npc triggered
     */
    Npc* getTriggeredNpc();
    
    
    /**
     * Try to push a ZoneDialog
     * @param pos the position of the faced case
     */
    void tryPushZoneDialog(sf::Vector2i pos);
    
    
    
//===============// Loading data methods //===============//
    
    /**
     * Load each of the zone Changer files
     */
    void loadZoneChangerFiles();
    
    
//===============// Public maps //===============//
    
    // Map for the filenames
    static const std::map<ZoneID, std::string> zoneFileNames;
    
    
private:
//===============// Private Methods //===============//
    
    /**
     * Load the zoneChangers correspongind to the ID
     * @param id id of the new zone
     */
    void loadZoneChangers(ZoneID id);
    
    
    /**
     * Delete all the entities of m_entities,
     * and clear the vector
     */
    void clearEntities();

    /**
     * Delete all the ZoneChangers of m_zoneChangers,
     * and clear the vector
     */
    void clearZoneChangers();
    
    
    /**
     * Check the ZoneChangers, and change zone if needed
     */
    void checkZoneChangers();
    
    
    /**
     * Check if one of the Trainer see the Character
     */
    void checkTrainerSight();
    
    
    /**
     * Delete all the ZoneLayers
     */
    void deleteZoneLayers() const;
    
    
    /**
     * Check if the is a path between th positions without 
     */
    bool hasBlockBetween(sf::Vector2i startPos, sf::Vector2i endPos);
    
    
    /**
     * Apply the awaiting zone change (after the transition State)
     */
    void applyZoneChange();
    
    
//===============// Private Attributes //===============//
    
    // Map for the filenames
    static const std::map<ZoneID, sf::String> zoneNames;
    
    // Multimap of Zone Changers
    static std::multimap<ZoneID, ZoneChanger*> zoneChangersStorage;
    
    
//===============// Private Attributes //===============//
    // ID of the actual zone
    ZoneID m_id;
    
    // Reference to the textures used by the Zone
    const sf::Texture& m_texture;
    
    // Pointer to the textureHolder
    const TextureHolder* m_textureHolder;
    // reference to th context
    Context& m_context;
    
    // The Entity Loader
    EntityLoader m_entityLoader;
    
    // Vector of ZoneChangers
    std::vector<ZoneChanger*> m_zoneChangers;
    
    // Pointer to the actual player
    Character* m_character;
    
    // Layers
    ZoneLayer* m_background;
    ZoneLayer* m_backgroundDeco;
    ZoneLayer* m_foreground;
    ZoneLayer* m_foregroundDeco;
    CollisionLayer* m_collisionLayer;
    
    // Variables to keep in memory if the zone must load a new zone at the next update
    bool m_mustLoadZone;
    ZoneChanger* m_activatedZoneChanger;
    
    
    // The WildPokemon Manager
    WildPokemonManager m_wildManager;
    
    // A loader for the DialogObjects
    ZoneDialogLoader m_zoneDialogLoader;
    
    
    // Pointer to the stateStack, to push Transition States for example
    StateStack* m_stack;
};

#endif /* ZONE_HPP */

