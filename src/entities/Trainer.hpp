/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Trainer.hpp
 * Author: Redbuzard
 *
 * Created on 12 août 2018, 18:45
 */

#ifndef TRAINER_HPP
#define TRAINER_HPP

#include "NPC.hpp"
#include "../pokemons/PokemonTeam.hpp"
#include "../pokemons/Pokemon.hpp"
#include "../inventory/Inventory.hpp"
#include <string>

class Trainer : public Npc{
public:
    Trainer(const sf::String& name, const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone, NpcID id);
    
    
    virtual ~Trainer();

    
//=================// Public functions //==================//
    
    
    /**
     * Checks wether or not the trainer has some pokemons not KO
     * @return true if a not KO pokemon was found
     */
    bool hasPokemonsLeft() const;
    
    
    /**
     * Heal the whole pokemon team
     */
    void healTeam();
    
    
    /**
     * Overriden Update method
     */
    void update(float dt) override;

    
//=================// Getters / Setters //==================//
    
    /**
     * @return a const reference to the trainer name as a SFML String
     */
    const sf::String& getName() const;
    
    
    /**
     * @return a pointer to the pokemon team
     */
    PokemonTeam* getPokemonTeam();
    
    /**
     * @return the number of pokemons in the team as an int
     */
    int getNbPokemon() const;
    
    /**
     * @return a pointer to the pokemon at the given index
     */
    Pokemon* getPokemonAt(int index);
    
    
    /**
     * Get the index of a pokemon that is not KO
     * @return the index of the pokemon in the team as an int
     */
    int getFirstPokemonNotKO();
    
    /**
     * Set the team of the trainer
     * @param team the team of the trainer
     */
    void setPokemonTeam(PokemonTeam* team);
    
    
    /**
     * @return the number of Pokemons in the team as an int
     */
    int getNbPokemons() const;
    
    /**
     * @return true if the team is not full
     */
    bool canAddPokemon() const;
    
    /**
     * Add a Pokemon to the team
     * @param p a pointer to the new Pokemon
     */
    void addPokemon(Pokemon* p);
    
    
    /**
     * Set wether the trainer was already defeated or not
     * @param val true if the trainer is defeated
     */
    void setDefeated(bool val);
    
    
    /**
     * @return true if the Trainer was already defeated
     */
    bool isDefeated() const;
    
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    std::string getInfoString() const;
    
    
    
    /**
     * Return an int that is the index of a random attack of the pokemon at the given index
     * @param pokemonIndex the index of the pokemon
     * @return the index of the attack as an int
     */
    int getRandomIntAttack(int pokemonIndex);
    
    /**
     * Return an int that is the last RandomIntAttack returned
     * @return the index of the attack as an int
     */
    int getLastIntAttack() const;
    
    
    /**
     * Set the sight distance at which a trainer can spot the Character 
     * @param length the number of cases that are being watched as an int
     */
    void setSightDistance(unsigned int length);
    
    /**
     * Get the distance at which the Trainer can spot the Character
     * @return the number of cases that are being watched as an int
     */
    unsigned int getSightDistance() const;
    
    
    /**
     * Check if the character is in sight of the Trainer
     * @warning If there is an obstacle in sight of the trainer, the function returns false
     * @return true if the trainer see the character
     */
    bool seeCharacter(sf::Vector2i characterPos) const;
        
    
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
     * @param item the item ID that will be removed from the inventory
     * @warnign Throws an exception if not any item of the given ID was found in the Inventory
     */
    Item* takeItem(ItemID id);
    
    
    /**
     * Get the Character's Inventory
     * @return a pointer to the Inventory
     */
    Inventory* getInventory();
    
    
    /**
     * Check if the trainer is a champion
     * @return true as we are in Champion Class
     */
    virtual bool isChampion();
    
    
    /**
     * Set the amount of money given on defeat
     * @param money the amount of money that will be given
     */
    void setMoneyGiven(int money);
    
    /**
     * Get the money given on defeat
     * @return the money given on defeat
     */
    int getMoneyGiven();
    
    
    /**
     * Set the Trainer to wait or not at his position
     * @param waitAtPos true if the trainer must wait at his position
     */
    void waitAtPosition(bool waitAtPos);
    
    
protected:
//=================// Attributes //==================//
    // trainer name
    const sf::String& m_name;
    
    // A boolean to know if the trainer must stop moving before the character reaches its position
    bool m_waitAtPosition;

    // traainer team
    PokemonTeam* m_team;
    
    // Remember if the trainer was already defeated
    bool m_isDefeated;
    
    // Last attack returned as an int
    int m_lastAttack;
    
    // Sight of the Trainer, to spot the Character
    unsigned int m_sightDistance;
    
    // Inventory of the trainer
    Inventory m_inventory;
    
    // The money given when the trainer is defeated
    int m_moneyGiven;
};

#endif /* TRAINER_HPP */

