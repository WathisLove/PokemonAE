/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPCFabric.hpp
 * Author: Redbuzard
 *
 * Created on 3 octobre 2020, 11:36
 */

#ifndef NPCFABRIC_HPP
#define NPCFABRIC_HPP


#include "../../zones/ZoneID.hpp"
#include "../NPC.hpp"
#include "../Trainer.hpp"
#include "../Seller.hpp"
#include "../../pokemons/creators/StrategicPokemonFabric.hpp"
#include "MoverFabric.hpp"

class Zone;

class NPCFabric {
public:
    
    
    /**
     * NPC Fabric constructor
     */
    NPCFabric(Context& context, Zone* zone);
    
    
    //=================// Public methods //==================//
    
    
    /**
     * Create a Npc
     * @param id the Npc id
     * @return a pointer to the Created Npc
     */
    Npc* create(NpcID id);
    
    
    
private:
    //=================// Private methods //==================//
    

    /**
     * Create a Standard Npc
     * @param id the Npc ID
     * @return a pointer to the Npc
     */
    Npc* createNPC(NpcID id);



    /**
     * Create a Seller
     * @param id the NPC Id
     * @return a pointer to a Npc containing the Seller
     */
    Npc* createSeller(NpcID id);



    /**
     * Create a Champion
     * @param id the NPC Id
     * @return a pointer to a Npc containing the Seller
     */
    Npc* createChampion(NpcID id);



    /**
     * Create a Trainer
     * @param id the Trainer Id
     * @return a pointer to a Npc containing the Trainer
     */
    Npc* createTrainer(NpcID id);
    
    
    //=================// Utility methods //==================//
    
    
    /**
     * Get the TExture for the given Npc
     * @param id the NpcID
     * @return a const reference to the texture
     */
    const sf::Texture& texture(NpcID id) const;
    
    
    /**
     * Get the Npc position in the zone
     * @param id the Npc ID
     * @return the Npc position as a Vector2i
     */
    sf::Vector2i position(NpcID id) const;
    
    
    /**
     * Get the trainer name
     * @param id the Npc ID
     * @return a const reference to the TrainerName
     */
    const sf::String& name(NpcID id) const;
    
    
    /**
     * Setup a trainer money, items, pokemons once it has been created
     * @param t a pointer to the Trainer
     */
    void setupTrainer(Trainer* t);
    
    
    /**
     * Create the Team for the given trainer
     * @param id the Npc ID
     * @return a pointer to the Pokemon team
     */
    PokemonTeam* createTeam(NpcID id);
    
    
    /**
     * Give the Items to the trainer
     * @param trainer a pointer to the Trainer
     */
    void giveItems(Trainer* trainer);
    
    
    /**
     * Set the items sold by a seller
     * @param s a pointer to the Seller
     */
    void setItemsSold(Seller* s);
    
    
    /**
     * Load the Npc Files
     */
    void loadNpcFiles();
    
    /**
     * Load the Items for the sellers
     */
    void loadSellerItemsFiles();
    
    /**
     * Load a single Npc File
     * @param filePath a const reference to the file path
     * @param zone the current zone loading
     */
    void loadNpcFile(const std::string& filePath, ZoneID zone);
    
    
    /**
     * Load a Npc from a file line and add the data to the Map
     * @param elements a const reference to the vector of elements
     * @param zone the current zone loading
     */
    void loadNpc(const std::vector<std::string>& elements, ZoneID zone);
    
    
    /**
     * Load a Trainer from the remaining elements
     * @param elements a const reference to the vector of elements
     * @param trainerID the Trainer ID
     */
    void loadTrainer(const std::vector<std::string>& elements, NpcID trainerID);
    
    
    /**
     * Add items for a specific trainer
     * @param itemStr the string containing the item data
     * @param trainerID the Trainer ID
     */
    void addItems(const std::string& itemStr, NpcID trainerID);
    
    /**
     * Adds the data for a trainer team
     * @param teamStr a const reference to the string str
     * @param trainerID the Trainer ID
     */
    void addTeam(const std::string& teamStr, NpcID trainerID);
    
    /**
     * Adds the data for a strategic trainer team
     * @param teamStr a const reference to the string str
     * @param trainerID the Trainer ID
     */
    void addStrategicTeam(const std::string& teamStr, NpcID trainerID);
    
    
    //=================// Struct //==================//
    
    /**
     * A structure for the 
     */
    struct Position {
        int x;
        int y;
        Position(int x, int y);
    };
    
    /**
     * A sold Item 
     */
    struct SoldItem{
        ItemID item;
        unsigned int price;
    };
    
    /**
     * A standard pokemon 
     */
    struct StandardPokemon{
        PokemonID poke;
        unsigned int level;
    };
    
    /**
     * A strategic pokemon 
     */
    struct StrategicPokemon{
        StrategicPokemonID poke;
        unsigned int level;
    };
    
    /**
     * Possible item for a trainer
     */
    struct TrainerItem{
        ItemID id;
        unsigned int num;
    };
    
    
    
    //=================// Attributes //==================//
    
    
    // A reference to the context
    Context& m_context;
    
    
    // A pointer to the zone
    Zone* m_zone;
    
    // A mover fabric
    MoverFabric m_moverFabric;    
    
    
    //=================// Static Attributes //==================//
    
    // Boolean to know if the Files were already loaded
    static bool filesLoaded;
    
    
    //=================// Static Maps //==================//
    
    //// All NPCs
    
    // Localisation of the NPCs
    static std::map<NpcID, Position> positions;
    
    // NPC Textures ID
    static std::map<NpcID, TextureHolder::textureID> textures;
    
    // NPC Movers
    static std::map<NpcID, EntityMover*> movers;
    
    // NPC Directions
    static std::map<NpcID, Direction> directions;
    
    // NPC Speeds
    static std::map<NpcID, float> speeds;
    
    
    //// Sellers
    
    // Items sold by the differents sellers at default price
    static std::multimap<NpcID, ItemID> itemsSoldDefaultPrice;
    
    // Items sold by the differents sellers at different price
    static std::multimap<NpcID, SoldItem> itemsSold;
    
    
    //// Trainers
    
    // Trainer names
    static std::map<NpcID, sf::String> trainersNames;
    
    // Money given by trainers when defeated
    static std::map<NpcID, unsigned int> trainersMoney;
    
    // Trainers sight
    static std::map<NpcID, unsigned int> trainersSights;
    
    // Trainer Items
    static std::multimap<NpcID, NPCFabric::TrainerItem> trainersItems;
    
    
    // Pokemons
    static std::multimap<NpcID, StandardPokemon> trainerPokemons;
    
    // Strategic Pokemons
    static std::multimap<NpcID, StrategicPokemon> trainerStratPokemons;
};

#endif /* NPCFABRIC_HPP */

