/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pokemon.hpp
 * Author: Redbuzard
 *
 * Created on 20 juillet 2018, 17:57
 */

#ifndef POKEMON_HPP
#define POKEMON_HPP

#include "Stats.hpp"
#include "PokemonID.hpp"
#include "../resources/TextureHolder.hpp"
#include "Type.hpp"
#include "attacks/AttackSet.hpp"
#include "attacks/AttackID.hpp"
#include "attacks/AttackFabric.hpp"
#include "status/MainStatus.hpp"
#include "../inventory/Item.hpp"
#include "../inventory/items/effects/ItemEffect.hpp"
#include "XPCurves.hpp"
#include "pokemons/PokemonMetadata.hpp"
#include "PokemonNature.hpp"
#include "PokemonSex.hpp"
#include "EvolutionCondition.hpp"
#include "abilities/Ability.hpp"
#include "IVSet.hpp"
#include "EVSet.hpp"

#include <string>
#include <map>
#include <set>
#include <vector>

#include <iostream>

// A Typedef for each possible Ability
struct PossibleAbility{
    AbilityVisibility visibility;
    AbilityID id;
};


struct EVYield{
    StatName stat;
    int value;
};



class Pokemon {
public:
//===================// Constructors //===================//
    Pokemon(PokemonID id, int level);
    
    Pokemon(PokemonID id, int level, int actualHealth);
    
    Pokemon(PokemonID id, int level, int actualHealth, PokemonMetadata metadata);
    
    virtual ~Pokemon();

    
//===================// Public Functions //===================//
    
    /**
     * Return a coefficient depending of the pokemon and the attack's type
     * @param attack a pointer to the incoming attack
     * @return the coef as a float
     */
    float getAttackEfficiency(const Attack& attack) const;
    
    /**
     * Return a boolean which value depends on wether the attack at the given index is stabed or not
     * @param index the index of the attack in the AttackSet
     * @return true if the attack is stabed
     */
    bool isAttackStabed(int index);
    
    /**
     * Return a boolean which value depends on wether the attack at the given index is stabed or not
     * @param attack a const reference to the attack
     * @return true if the attack is stabed
     */
    bool isAttackStabed(const Attack& attack);
    
    
    /**
     * Calculates the damages infligated to the Pokemin by a given Attack
     * @warning Does not take in account the STAB, the critical hits, the types, the climate, ...
     * @param attacker a const reference to the attacking Pokemon
     * @param attack a const reference to the incoming attack
     * @param critical true if the attack was critical
     * @param previousDamagesToEnnemy the damage previously dealt to the ennemy
     * @param coefM a float for the multiplicating coefficient
     * @return the HP lost as an int
     */
    int calculateDamages(Pokemon& attacker, const Attack& attack, bool critical, int previousDamagesToEnnemy, float coefM = 1) const;
    
    
    /**
     * Attack the pokemon
     * @param attack a const reference to the incoming attack
     * @param coefM a float for the multiplicating coefficient
     * @param previousDamagesToEnnemy the damage previously dealt to the ennemy
     * @param critical true if the Attack is critical
     * @return the damages finaly received
     */
    int receiveAttack(Pokemon& ennemy, const Attack& attack, float coefM, int previousDamagesToEnnemy = 0, bool critical = false);
    
    
    /**
     * Update the attributes that change over the fight turns
     * (for example the main status)
     */
    void updateTurns();
    
    
    /**
     * Deals to the pokemon the damages of its status
     */
    void takeStatusDamages();
    
    
    /**
     * Check if the pokemon has a current main status (different from NoMainStatus)
     * @return true if the pokemon has a main status
     */
    bool hasStatus() const;
    
    /**
     * Check if the status can deal damages to the pokemon each turn
     * @return true if the status deals damages
     */
    bool doesStatusDamage() const;
    
    /**
     * Returns the number of HP lost because of the status
     * @return the hp lost as an int
     **/
    int getStatusDamages() const;
    
    
    /**
     * Cure the current MainStatus of the pokemon
     */
    void cureMainStatus();
    
    
    /**
     * Check if the pokemon can attack with its status
     */
    bool attackThisTurn();
    
    /**
     * Give an item to the pokemon
     * @param item a pointer to the Item
     */
    void giveItem(Item* item);
    
    /**
     * Take the item from the pokemon
     * @return a pointer to the item
     */
    Item* takeItem();
    
    
    /**
     * Switch the currently hold item with the one of another pokemon
     * @param p a pointer to the other pokemon
     */
    void swapItem(Pokemon* p);
    
    
    /**
     * Check if the given attack can touch the Pokemon
     * @param attack a pointer to the attack
     * @return true if the attack can touche the Pokemon
     */
    bool isTouchedByAttack(Attack* attack);
    
    
    
    /**
     * Give a certain amount of Xp to a pokemon. If it wins a level, it will return the numer of xp unused
     * @param xpPoints the number of xp points to give
     * @return the number of xp points unused as an int
     */
    int giveXp(int xpPoints);
    
    
    /**
     * Level up the pokemon and update its stats
     * @return 
     */
    void levelUp();
    
    
    
    /**
     * Check if the Pokemon has at least 1 capacity with some PP Lefts
     * @return true if there is a capacity, false otherwise
     */
    bool hasAnyPPLeft();
    
    
//===================// Getters / Setters //===================//
    /**
     * @return true if the pokemon is KO no hp left
     */
    bool isKO() const;
    
    /**
     * @return the pokemon name
     */
    const sf::String& getName() const;
    
    /**
     * Set the Pokemon name
     * @param string
     */
    void setName(const sf::String& string);
    
    
    /**
     * @return the pokemon level as an int
     */
    int getLevel() const;
    
    /**
     * @return the stat value as an int
     */
    int getStatValue(StatName stat) const;
    
    /**
     * Get the stat value when in fight
     * @return the stat value as an int
     */
    int getInFightStat(StatName stat) const;
    
    /**
     * @return the base stat value as an int
     */
    int getBaseStatValue(StatName stat) const;
    
    /**
     * @return the Pokemon's ID
     */
    PokemonID getID() const;
    
    /**
     * @return the textureID corresponding to the Pokemon ID
     */
    static TextureHolder::textureID getPokemonTextureID(PokemonID id);
    
    /**
     * @return the health left as a percentage (from 0 to 100)
     */
    float getHealthPercentage() const;
    
    /**
     * @return a percentage corresponding to the current xp divided by the xp to the next level (from 0 to 100)
     */
    float getXPPercentage() const;
    
    /**
     * @return a const reference to the pokemon type
     */
    const Type& getType() const;
    
    /**
     * @return a const reference to the AttackSet
     */
    AttackSet& getAttackSet();
    
    
    /**
     * Set the current main status
     * @param status the new status
     */
    void setMainStatus(MainStatus status);
    
    /**
     * Return the current main status of the pokemon
     * @return the status as a MainStatus object
     */
    MainStatus getMainStatus() const;
    
    
    /**
     * Check if the pokemon can learn a given attack by CT
     * @param pokeID the Pokemon ID
     * @param attackID the Attack ID of the Attack
     * @return true if the pokemon can learn this attack by a CT
     */
    static bool canLearnByCT(PokemonID pokeID, AttackID attackID);
    
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    virtual std::string getInfoString() const;
    
    
    /**
     * Heal the pokemon and all its attacks
     */
    void healEverything();
    
    
    /**
     * Restore the Poekmon health of a certain amount
     * @param value the number of HP restored
     * @return the number of HP restored
     */
    int healHP(int value);
    
    /**
     * Heal a percentage of the max HP
     * @param coeff a ration from 0 to 1
     * @return the number of HP restored
     */
    int healRatio(float coeff);
    
    
    /**
     * Set the pokemon HP to a targeted value
     * The value will be bound between 0 and Max value 
     * @param val the value of HP as an int
     */
    void setHP(int val);
    
    
    /**
     * Return an int that is the index of a random attack of the pokemon
     * @return the index of the attack as an int
     */
    int getRandomIntAttack() const;
    
    
    /**
     * Function called when the pokemon leave the fight
     * It resets :
     * the statChanger
     */
    void leaveFight();
    
    
    /**
     * Get the pokemo stat changer
     * @return the pokemon StatChanger
     */
    StatsChanger getStatChanger() const;
    
    
    /**
     * Add a StatsChanger to the pokemon's one
     * @param stChanger the StatsChanger that will be added
     */
    void addStatChanger(StatsChanger stChanger);
    
    
    /**
     * Get the pokemon statistics
     * @return a const reference to the pokemon statistics
     */
    const Stats& getStats();
    
    
    /**
     * Get the current health of the pokemon
     * @warning use getStatValue to get the max health
     * @return the health points as an int
     */
    int getHealth();
    
    
    /**
     * Check if the pokemon is holding an item
     * @return true if the pokemon has an item
     */
    bool hasItem() const;
    
    /**
     * Get the pokemon item
     * @return a pointer to the Pokemon Item
     */
    Item* getItem();
    
    
    /**
     * Check if the pokemon has all its HP
     * @return true if the pokemon has all its HP
     */
    bool isFullHP();
    
    
    
    /**
     * Get the experience value a given pokemon on-death experience yields
     * @return the experience value as an int
     */
    static int getBaseExperienceYield(PokemonID id);
    
    
    /**
     * Get the experience points the pokemons gives when killed
     * @param wild true if the pokemon killed was wild
     * @param luckyEgg check if the lucky egg was hold 
     * @return the experience points as an int
     */
    int getExperiencePointsYield(bool wild, bool luckyEgg);
    
    
    /**
     * Get the xp points the pokemon earned at its current level
     * @return the xp points as an int
     */
    int getXPCurrentLevel();
    
    
    /**
     * Get the number of xp points needed to get to the next level
     * @return the xp points as an int
     */
    int getXPNextLevel() const;
    
    
    /**
     * Set the pokemon Metadata
     * @param metadata the new pokemon metadata
     */
    void setMetadata(PokemonMetadata metadata);
    
    /**
     * Get the Pokemon Metadata
     * @return a reference to the Pokemon Metadatas
     */
    PokemonMetadata& getMetadata();
    
    
    /**
     * Get the pokemon Nature
     * @return the nature of the pokemon as a PokemonNature
     */
    PokemonNature& getNature();
    
    
    /**
     * Set the Pokemon Nature
     * @param id the NatureID of the new pokemon Nature
     */
    void setNature(PokemonNature::NatureID id);
    
    
    /**
     * Get the pokemon sex
     * @return the pokemon sex as an enum
     */
    PokemonSex getSex();
    
    
    /**
     * Set the pokemon sex 
     * @param sex the pokemon sex as an enum
     */
    void setSex(PokemonSex sex);
    
    
    /**
     * Check if the Pokemon can reproduce
     * @return true if the pokemon sex is different from None
     */
    bool canReproduce();
    
    
    /**
     * Get the pokemon capture rate
     * @return the catpure rate as an int from 3 to 255
     */
    int getCaptureRate();
    
    
    /**
     * Deals some damage recoil after an attack
     * @param recoilPercentage the recoil as a percentage from 0 to 100
     */
    void sufferRecoil(int recoilPercentage);
    
    
    /**
     * Get the chance of one of the pokemon attacks to make a critical hit
     * @param attackCricitalLevel the attack critical level
     * @return the critical rate (from 0 to 1)
     */
    float getCriticalChance(int attackCricitalLevel);
    
    
    /**
     * Replace one of the Attacks by a new one
     * @param index the index of the old attack
     * @param newAttack the AttackID of the new attack
     */
    void replaceAttack(int index, AttackID newAttack);
    
    
    /**
     * Get a set of attacks the pokemon can learn since the last level
     * @param lastLevel the last level of the pokemon
     * @return a set of all the attacks the pokemon can learn now
     */
    std::set<AttackID> getAttacksSinceLevel(int lastLevel);
    
    
    /**
     * Get the ItemID of the last Item used on the pokemon
     * @return the ItemID of the last item used
     */
    ItemID getLastItemUsed();
    
    
    /**
     * Check if a pokemon has at least an evolution
     * @param pokemon the pokemon ID
     * @return true if the pokemon has an evolution
     */
    static bool hasEvolution(PokemonID pokemon);
    
    
    /**
     * Check if the pokemon can evolve
     * @return true if there is a possible evolution for the pokemon
     */
    bool canEvolve();
    
    
    /**
     * Get the ID of the possible evolution
     * @warning throw an exception if there is no possible evolution
     * @return the PokemonID of the evolution
     */
    PokemonID getEvolutionID();
    
    
    /**
     * Evolve the pokemon into an other one
     * @param evolutionID the PokemonID of the evolution
     * @return a pointer to the pokemon evolved
     */
    Pokemon* evolve(PokemonID evolutionID);
    
    
    /**
     * Sets the Pokemon ID
     * @param id the AbilityID of the new Ability
     */
    void setAbility(AbilityID id);
    
    
    /**
     * Give a random ability between all the Pokemon can have
     * @param allowHiddenAbility true if the method can give a hidden ability
     */
    void setRandomAbility(bool allowHiddenAbility);
    
    
    /**
     * Get the Pokemon Ability
     * @return a reference to the pokemon ability
     */
    Ability& getAbility();
    
    
    /**
     * Get the Pokemon EVs
     * @return a const reference to the poekmon EVSet
     */
    EVSet& getEVs();
    
    /**
     * Set the pokemon EVSet
     * @param set a const reference to the EVSet
     */
    void setEVSet(const EVSet& set);
    
    
    /**
     * Get the Pokemon IVs
     * @return a const reference to the poekmon EVSet
     */
    IVSet& getIVs();
    
    /**
     * Set the pokemon IVSet
     * @param set a const reference to the IVSet
     */
    void setIVSet(const IVSet& set);
    
    
    /**
     * Adds the Ev a pokemon get when killing an other pokemon
     * @param killed the PokemonID of the pokemon killed
     */
    void addEVYielded(PokemonID killed);
    
    
    /**
     * Get the pokemon Strategic role
     * @return the Strategic role of the pokemon as an enum
     */
    StrategicRole getRole() const;
    
    /**
     * Set the pokemon role when used by a trainer
     * @param role the Strategic role of the pokemon
     */
    void setRole(StrategicRole role);
    
    
    // TODO confusion
    /**
     * Set the pokemon confused for a given amount of turns
     * @param turns the number of confusion turns
     */
    void setConfused(int turns);
    
    /**
     * Check if the pokemon is confused
     * @return true if the pokemon is confused
     */
    bool isConfused();
    
    
protected:
//===================// Private functions //===================//
    
    /**
     * Initialize the pokemon
     */
    virtual void initializePokemon(); 
    
    
    /**
     * Replace the attacks by the last ones the pokemons learns by level
     */
    virtual void learnLastAttacksByLevel();
    
    
    /**
     * Set the pokemon XP Curve
     */
    void setXPCurve();
    
    
    /**
     * Set the Pokemon Type
     */
    void setupType();
    
    
    /**
     * Builds the Evolution Table if it is not done yet
     */
    void buildEvolutionTable();
    
    
    /**
     * Setup a common ability for the current pokemon
     */
    void setupCommonAbility();
    
//===================// Attributes //===================//
    
    // BaseStats of the Pokemon
    Stats* m_baseStats;
    // Actual stats of the Pokemon
    Stats* m_stats;
    
    // Pokemon Level
    int m_level;
    
    // Pokemon health
    int m_health;
    
    // Pokemon ID
    PokemonID m_id;
    
    // Pokemon name
    sf::String m_name;
    
    
    // Pokemon Type
    Type m_type;
    
    
    // Xp related 
    int m_xpTotalEarned;
    int m_xpCurrentLvl;
    XPCurveType m_xpCurveType;
    
    
    // Pokemon Nature
    PokemonNature m_nature;
    
    // The Metadata of the pokemon
    PokemonMetadata m_metadata;
    
    // The pokemon Sex
    PokemonSex m_sex;
    
    // Pokemon attack set
    AttackSet m_attackSet;
    
    // Pokemon Main status
    MainStatus m_mainStatus;
    
    // Number of confusion turns
    int m_confusionTurns;
    
    // In fight stat changer
    StatsChanger m_statChanger;
    
    // Item hold
    Item* m_item;
    
    // The ItemID of the last Item used
    ItemID m_lastItemUsed;
    
    // The Pokemon Ability
    Ability m_ability;
    
    // Pokemon EV and ID sets
    EVSet m_evs;
    IVSet m_ivs;
    
    // The pokemon role (when used by a trainer)
    StrategicRole m_role;
    
//===================// Maps //===================//
    
    // The attacks the Pokemons can learn by levels
    static std::map<PokemonID, std::multimap<int, AttackID> > m_attackByLevel;
    
    // The Attacks the Pokemons can learn by cts
    static std::map<PokemonID, std::set<AttackID> > m_attacksByCT;
    
    // The Attacks the Pokemons can learn by cts
    static std::multimap<PokemonID, EVYield > m_evYields;
    
    // A map of all the possible evolutions
    static std::multimap<PokemonID, EvolutionCondition> m_evolutionTable;
    
    // A map of all the possible evolutions
    static std::multimap<PokemonID, PossibleAbility> m_possibleAbilities;
};

#endif /* POKEMON_HPP */

