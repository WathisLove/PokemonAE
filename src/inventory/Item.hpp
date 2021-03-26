/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.hpp
 * Author: Redbuzard
 *
 * Created on 28 janvier 2019, 21:21
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include "../ItemEnums.hpp"
#include "../pokemons/PokemonID.hpp"
#include "../pokemons/Type.hpp"
#include "items/ItemComponent.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <tuple>
#include <map>
#include <set>


class Pokemon;
class ItemPredicate;


class Item {
public:
    // Declare Item as friend for predicates usage
    friend ItemPredicate;
    
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    Item(ItemID id);
    
    
    //=================// Getters / Setters //==================//
    
    /**
     * Get the Item name
     * @return a const reference a SFML String
     */
    const sf::String& getName() const;
    
    
    /**
     * Get the Item ID
     * @return the Item ID of the current Item
     */
    ItemID getID() const;
    
    
    /**
     * Get the description of the item
     * @return a const reference to the item description
     */
    const sf::String& getItemDescription() const;
    
    
    /**
     * Get the Item Category
     * @return the ItemCategory Enum
     */
    ItemCategory getCategory() const;
    
    
    /**
     * Get the attack Learned by the Item
     * @return the Attack ID
     */
    AttackID getAttackTeached() const;
    
    /**
     * Get the attack Learned by the Item
     * @param id the ItemID
     * @return the Attack ID
     */
    static AttackID getAttackTeached(ItemID id);
    
    
    /**
     * Get the capture value of the Item
     * @return the capture value as an int
     */
    float getCaptureValue() const;
    
    
    //=================// Item Use methods //==================//
    
    
    /**
     * Check if an item can be used outside a battle
     * @return true if the item can be used outside battle
     */
    bool isUsable() const;
    
    
    /**
     * Check if an item can be used in a battle
     * @return true if an item can be used in a battle
     */
    bool isUsableInFight() const;
    
    
    /**
     * Apply changes to a stat value
     * @param statValue a reference to the stat value
     * @param stat the Stat Type
     * @param holder the Pokemon ID of the Holder
     */
    void onStat(int& statValue, StatName stat, PokemonID holder) const;
    
    /**
     * Apply a boost on damages of a certain type
     * @param damages a reference to the damage done to the defender
     * @param attackType the Attack type
     * @param attacker the Pokemon ID of the attacker
     */
    void onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const;
    
    /**
     * Apply an effect on a pokemon
     * @param pokemon a pointer to the Pokemon
     * @return a queue of ItemEffects
     */
    std::queue<ItemEffect*> onPokemon(Pokemon* pokemon) const;
    
    /**
     * Modifiy an attack
     * @param attack a pointer to the Attack
     * @return a queue of ItemEffects
     */
    std::queue<ItemEffect*> onAttack(Attack* attack) const;
    
    /**
     * Apply a boost on damages of a certain type
     * @param critLeve a reference to the crit level of the attack
     */
    void onCritLevel(int& critLevel) const;
    
    /**
     * Apply a boost on the XP Gained
     * @param xpGained a reference to the xp gained
     */
    void onXPGained(int& xpGained) const;
    
    /**
     * Apply a boost on the Money Gained
     * @param moneyGained a reference to the money gained
     */
    void onMoneyGained(int& moneyGained) const;
    
    /**
     * Apply a boost on the happiness gained
     * @param happinessAmount a reference to the hapinness amount
     */
    void onHappinessReceived(int& happinessAmount) const;
    
    
    /**
     * Apply a boost on the Ev gained
     * @param evAmount a reference to the Ev amount
     * @param stat the Ev StatName 
     */
    void onEvReceived(int& evAmount, StatName stat) const;
    
    
    /**
     * Check if the Item has an effect on the pokemon
     * @param pokemon a pointer to the pokemon
     * @return true if the item has an effect on the pokemon
     */
    bool hasEffectOnPokemon(Pokemon* pokemon) const;
    
    
    /**
     * Check if the item has an effect on an Attack
     * @param attack a pointer to the Attack
     * @return true if the item can has an effect on the attack
     */
    bool hasEffectOnAttack(Attack* attack) const;
    
    
    /**
     * Get the item use in battle
     * @return the UseInBattle for the current item
     */
    UseInBattle getUseInBattle() const;
    
    
    /**
     * Get the item use out of battle
     * @return the UseInBattle for the current item
     */    
    UseOutBattle getUseOutBattle() const;
    
    
    /**
     * Check if the ITem is givable
     * @return true if the item can be given
     */
    bool isGivable() const;
    
    
    //=================// Static methods //==================//
    
    /**
     * Get the Item name
     * @return a const reference to a SFML String
     */
    static const sf::String& getName(ItemID id);
    
    
    /**
     * Get the ItemID corresponding to the string
     * @param str a const reference to the String
     * @return the Item ID corresponding
     */
    static ItemID getID(const std::string& str);

    
    /**
     * Get the default price of the item
     * @return the default price of the item
     */
    static int getDefaultPrice(ItemID id);
    
    /**
     * Get the default price at which the character can sold this item
     * @return the default selling price of the item
     */
    static int getDefaultSellingPrice(ItemID id);
    
    
    /**
     * Get the Item Category
     * @param id the Item ID
     * @return the ItemCategory Enum
     */
    static ItemCategory getCategory(ItemID id);
    
    
    /**
     * Get the texture rect for the Given Item
     * @param item the Item ID
     * @return the Textur Rect for the item
     */
    static sf::IntRect getTextureRect(ItemID item);
    

protected:
    //=================// Structs //==================//
    
    struct PokemonStatBoost{
        StatName stat;
        float factor;
        PokemonID poke;
    };
    
    struct PokemonTypeBoost{
        Type::TypeName type;
        float factor;
        PokemonID poke;
    };
    
    struct StoneEvolution{
        PokemonID unevolved;
        PokemonID evolution;
    };
    
    struct EvBoost{
        EvBoost(int b, StatName s, BonusType bonus);
        
        int boost;
        StatName stat;
        BonusType bonusType;
    };
    
    //=================// Private methods //==================//
    
    /**
     * Setup the components for the Item
     */
    void setupComponents();
    
    /**
     * Setup the item uses in and out of battles
     */
    void setupUses();    
    
    //=================// Attributes //==================//
    
    // The Item ID
    ItemID m_id;
    
    // Use in and out of battle
    UseInBattle m_useInBattle;
    UseOutBattle m_useOutBattle;
    
    // Vector of Components
    std::vector<ItemComponent*> m_components;
    
    
    //=================// Static Maps //==================//
    
    // Map for the Item names
    const static std::map<ItemID, sf::String> itemNames;
    
    // Map for the Item names
    const static std::map<ItemID, sf::String> itemDescriptions;
    
    // Map for the Item names
    const static std::map<ItemID, ItemCategory> itemCategories;
    
    // Map for the default prices
    const static std::map<ItemID, int> itemPrices;
    
    // Vector for the first items in each row
    const static std::vector<ItemID> firstRowItems;
    
    // Speed modifier
    const static std::map<ItemID, float> speedModifier;
    
    // Uses
    const static std::map<ItemID, UseInBattle> inBattleUses;
    const static std::map<ItemID, UseOutBattle> outBattleUses;
    
    // Teached attacks
    const static std::map<ItemID, AttackID> teachedAttacks;
    
    //===// Data for Components
    
    // Stats boosted
    const static std::multimap<ItemID, std::pair<StatName, float> > statBoosters;
    const static std::multimap<ItemID, PokemonStatBoost> specialisedStatBoosters;
    
    // EV Boosts
    const static std::multimap<ItemID, EvBoost> evBoosters;
    
    // Attack type boosters
    const static std::multimap<ItemID, std::pair<Type::TypeName, float> > typeBoosters;
    const static std::multimap<ItemID, PokemonTypeBoost> specialisedTypeBoosters;
    
    // Crit Boost
    const static std::map<ItemID, int> critBooster;
    
    // Heal 
    const static std::map<ItemID, int> healHPs;
    const static std::map<ItemID, float> healPercentages;
    
    // PPs
    static const std::map<ItemID, int> ppRestored;
    
    // Revive and hp restored
    const static std::map<ItemID, float> revives;
    
    // Status
    static const std::map<ItemID, MainStatusName> statusHealed;
    static const std::set<ItemID> allStatusHealed;
    
    // Confusion
    static const std::set<ItemID> confusionHealed;
    
    // XP Boosts
    static const std::map<ItemID, float> xpBooster;
    
    // Money Boost
    static const std::map<ItemID, float> moneyBooster;
    
    // Happiness boosters
    static const std::map<ItemID, float> happinessBooster;
    
    // Stat boosters for evolu-items
    static const std::multimap<ItemID, std::pair<StatName, float> > evoluBoosters;
    
    // Capture Rates
    static const std::map<ItemID, float> captureRates;
    
    // Evolution Stones
    const static std::multimap<ItemID, StoneEvolution> stoneEvolutions;    
};

#endif /* ITEM_HPP */

