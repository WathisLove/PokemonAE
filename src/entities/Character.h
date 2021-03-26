/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Character.h
 * Author: Redbuzard
 *
 * Created on 18 juin 2018, 11:36
 */

#ifndef CHARACTER_H
#define CHARACTER_H


#include <SFML/Graphics.hpp>
#include <vector>

#include "Entity.hpp"
#include "../pokemons/PokemonTeam.hpp"
#include "../Context.hpp"
#include "../pokemons/teamPreview/TeamPreview.hpp"
#include "../inventory/Inventory.hpp"
#include "../pokemons/boxes/BoxSystem.hpp"
#include "../pokemons/Pokedex.hpp"
#include "NPCId.hpp"
#include "movements/CharacterMover.hpp"
#include "character/CharacterBody.hpp"


/**
 * Structure to hold the data of the last Heal
 */
struct HealData {
    // Constructor
    HealData(sf::Vector2i pos, ZoneID zone, Direction dir);

    // Attributes
    sf::Vector2i pos;
    ZoneID zone;
    Direction dir;
};



class Character : public Entity{
public:
//=================// Public Methods //==================//
    Character(Context& context, sf::Vector2i pos, Zone* zone);
    
    virtual ~Character();

    
    /**
     * Update the character
     * @param dt elapsed time since last frame
     */
    void update(float dt);
    
    /**
     * Update the Team Preview
     */
    void updateTeamPreview();
    
    /**
     * Update the pos of the Team Preview
     */
    void updateTeamPreviewPos();
    
    /**
     * Overrided function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * Draw the TeamPreview
     */
    virtual void drawTeamPreview(sf::RenderTarget& target, sf::RenderStates states) const;
    
    /**
     * Return the index of the face that the Entity is facing
     * @param distance the distance as an int
     * @return the index of the case faced as a Vector2i
     */
    sf::Vector2i getFacedCase(int distance = 1) const;
    
    
    /**
     * Set the Character at the given position
     * @param pos new position of the Character as a Vector2i
     */
    virtual void setPosition(sf::Vector2i pos);
    
    /**
     * @return the position of the character as a Vector2i
     */
    virtual sf::Vector2i getPosition() const;
    
    /**
     * Check if the Character is occuping the given position
     * @return true if the position is occupied by the Character
     */
    virtual bool isOccupingPosition(sf::Vector2i pos) const override;    
    
    /**
     * @return a pointer to the Pokemon team
     */
    PokemonTeam* getPokemonTeam();
    
    
    /**
     * Returns a string that can be used to display infos about the character and its team
     * @return a string
     */
    virtual std::string getInfoString() const;
    
    
    /**
     * Heal the whole pokemon team
     */
    void healTeam();
    
    
    /**
     * Checks wether or not the Character has some pokemons not KO
     * @return true if a not KO pokemon was found
     */
    bool hasPokemonsLeft() const;
    
    
    /**
     * @return the number of pokemons in the team as an int
     */
    int getNbPokemon() const;
    
    /**
     * @return a pointer to the pokemon at the given index
     */
    Pokemon* getPokemonAt(int index);
    
    
    /**
     * Function called when the chaarcter leave the fight
     */
    void leaveFight();
    
    /**
     * Freeze the character or unfreeze it
     * @param value the new value : is the character frozen, or not
     */
    void freeze(bool value = true);
    
    /**
     * Returns if the character is frozen
     * @return true if the character is frozen
     */
    bool isFrozen() const;
    
    /**
     * Check if the Character is actually Moving
     * @return true if the Character is moving
     */
    bool isMoving();
    
    
    
    /**
     * Add an item to the character Inventory
     * @param item the item that will be added to the inventory
     * @param count the number of items added
     */
    void giveItem(Item* item, int count = 1);
    
    /**
     * Add an item to the character Inventory
     * @param item the item ID that will be added to the inventory
     * @param count the number of items added
     */
    void giveItem(ItemID id, int count = 1);
    
    
    /**
     * Take an item from the character Inventory
     * @param item the item ID that will be added to the inventory
     * @warnign Throws an exception if not any item of the given ID was found in the Inventory
     */
    Item* takeItem(ItemID id);
    
    
    /**
     * Get the Character's Inventory
     * @return a pointer to the Inventory
     */
    Inventory* getInventory();
    
    
    /**
     * Get the character box system
     * @return a reference to the character box system
     */
    BoxSystem& getBoxSystem();
    
    
    /**
     * Check if the character already met an NPC
     * @param npcNum the NPC ID
     * @return true if the character already met the NPC
     */
    bool metNPC(NpcID id);
    
    
    /**
     * Check if the character already defeated a trainer
     * @param npcNum the Trainer NPC ID
     * @return true if the character already defeated the Trainer
     */
    bool defeatedTrainer(NpcID id);
    
    
    /**
     * Check if the character already picked a certain item
     * @param itemNum the item number as an int
     * @return true if the character already picked the item
     */
    bool pickedItem(int itemNum);
    
    
    /**
     * Add an Item picked
     * @param itemNum the item number as an int
     */
    void addPickedItem(int itemNum);
    
    
    /**
     * Add a NPC encoutered
     * @param npcNum the NPC ID
     */
    void addNPCEncounter(NpcID id);
    
    
    /**
     * Add a Trainer defeat 
     * @param trainerDefeat the Trainer NPC ID
     */
    void addTrainerDefeated(NpcID id);
    
    
    /**
     * Adds a badge to the Character collection
     * @param badgeNumber the badge number as an int
     */
    void addBadge(int badgeNumber);
    
    /**
     * Check if the character obtained the given badge
     * @param badgeNumber the badge number as an int
     * @return true if the character obtained the badge
     */
    bool hasBadge(int badgeNumber);
    
    
    /**
     * Adds a pokemon captured to the Character team
     * @param p a pointer to the pokemon
     */
    void addCapturedPokemon(Pokemon* p);
    
    
    /**
     * Check if the Chaarcter visited a given Zone
     * @param zone the Zone ID
     * @return true if thezone was visited
     */
    bool visited(ZoneID zone);
    
    /**
     * Add a visited zone
     * @param zone the Zone ID
     */
    void addVisitedZone(ZoneID zone);
    
    
    
    /**
     * Get the Character's pokedex
     * @return a reference to the Pokedex
     */
    Pokedex& getPokedex();
    
    
    /**
     * Get the Player money amount
     * @return the money of the Character
     */
    int getMoney();
    

    /**
     * Pay a certain amount of money
     * @param amount the amount of money that will be retrieved
     */
    void pay(int amount);
    
    
    /**
     * Give a certain amount of money to the Character
     * @param amount the amount of money that will be added
     */
    void addMoney(int amount);
    
    /**
     * Set the Character to run or not
     */
    void toggleRun();
    
    
    /**
     * Set the current time played
     * @param seconds the time played in seconds
     */
    void setTimePlayed(unsigned int seconds);
    
    /**
     * Get the Time played as a string that can be displayed
     * @return the time played as a string
     */
    std::string getTimePlayed();
    
    
    /**
     * Get the Character Name
     * @return a const reference to the name
     */
    const sf::String& getName() const;
    
    /**
     * Set the Character Name
     * @param name the new Character name 
     */
    void setName(const sf::String& name);
    
    
    /**
     * Get a reference to the characetr body
     * @return a const reference to the Character body
     */
    const CharacterBody& getBody();
    
    
    /**
     * Save the current position to know where to come back when going to a healer
     */
    void saveHealData();
    
    
    /**
     * Get the data of the last time the character was healed
     * @return the data as a HealData struct
     */
    HealData getLastHealData() const;
    
    
//=================// Inherited methods //==================//
    
    /**
     * Get the Character direction
     * @return the character direction as a Direction Enum
     */
    virtual Direction getDirection() const override;

    /**
     * Set the Character direction
     * @param dir the new Direction
     */
    virtual void setDirection(Direction dir) override;
    
private:
//=================// Private methods //==================//
    
    
//=================// Attributes //==================//
    
    // The character body
    CharacterBody m_body;
    
    // Character Team
    PokemonTeam* m_team;
    
    // Team Preview
    TeamPreview m_teamPreview;
    
    // Inventory of the player
    Inventory m_inventory;
    
    // The box system linked to the player
    BoxSystem m_boxSystem;
    
    
    // Queues for the met trainers, npcs and item picked 
    std::vector<NpcID> m_npcStoryMet;
    std::vector<NpcID> m_trainersDefeated;
    std::vector<int> m_itemsPicked;
    std::vector<ZoneID> m_zoneVisited;
    
    
    // Badges obtained
    std::vector<int> m_badges;
    
    // A pokedex
    Pokedex m_pokedex;
    
    // The money of the character
    int m_money;
    
    // The character clock
    sf::Clock m_timeClock;
    
    // The Time played before the clock started
    unsigned int m_secondsPlayed;
    
    // The last healer visited
    HealData m_lastHeal;
};

#endif /* CHARACTER_H */

