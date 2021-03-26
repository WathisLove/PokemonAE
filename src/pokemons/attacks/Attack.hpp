/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Attack.hpp
 * Author: Redbuzard
 *
 * Created on 30 juillet 2018, 16:58
 */

#ifndef ATTACK_HPP
#define ATTACK_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/String.hpp>

#include "../Type.hpp"
#include "../../Utilities.hpp"
#include "../status/MainStatus.hpp"
#include "StatsChanger.hpp"
#include "AttackID.hpp"

class Attack {
public:
//===============// Enums //===============//
    enum AttackCategory{
        Special,
        Physical,
        Status
    };
    
    enum AttackTarget{
        Self,
        SingleEnnemy,
        SingleAlly,
        AllEnnemies,
        AllAllies,
        AllPokemons
    };
    
    
//===============// Constructors //===============//
    Attack(AttackID id, const sf::String& name, Type type, AttackCategory category, AttackTarget target, const sf::String& description);
    
    
//===============// Public functions //===============//
    
    /**
     * @return true if the attack was successfully launched
     */
    bool succeeded() const;
    
    /**
     * Use a certain amount of PP
     * @param n the amount of pp (1 by default)
     */
    void usePP(int n = 1);
    
    
    /**
     * Set the main status
     * param name the name of the Attack Status
     * @param chance the chance to deal the new status
     */
    void setMainStatus(MainStatusName name, float chance);
    
    /**
     * Return true if the attack can deal a status
     */
    bool canDealStatus() const;
    
    /**
     * Return true if the attack can burn
     */
    bool canBurn() const;
    
    /**
     * Return true if the attack can freeze
     */
    bool canFreeze() const;
    
    /**
     * Return true if the attack can paralyse
     */
    bool canParalyse() const;
    
    /**
     * Return true if the attack can poison
     */
    bool canPoison() const;
    
    /**
     * Return true if the attack can badly poison
     */
    bool canBadlyPoison() const;
    
    /**
     * Return true if the attack can asleep
     */
    bool canAsleep() const;
    
    /**
     * Get the chance of the attack to burn
     * @return the chance as a float (0 to 1)
     */
    float getBurnChance() const;
    
    /**
     * Get the chance of the attack to freeze
     * @return the chance as a float (0 to 1)
     */
    float getFreezeChance() const;
    
    /**
     * Get the chance of the attack to paralyse
     * @return the chance as a float (0 to 1)
     */
    float getParalyseChance() const;
    
    /**
     * Get the chance of the attack to poison
     * @return the chance as a float (0 to 1)
     */
    float getPoisonChance() const;
    
    /**
     * Get the chance of the attack to badly poison
     * @return the chance as a float (0 to 1)
     */
    float getBadlyPoisonChance() const;
    
    /**
     * Get the chance of the attack to make asleep
     * @return the chance as a float (0 to 1)
     */
    float getAsleepChance() const;
    
    
    /**
     * Restore the PPs of the attack by a given amount
     * @param amount the amount or empty (-1) if all must be restored
     */
    void restorePPs(int amount = -1);
    
//===============// Setters //===============//
    
    /**
     * @param damage damage as an int
     */
    void setDamage(int damage);
    /**
     * @param precision as an int in %
     */
    void setAccuracy(int accuracy);
    /**
     * Set the precision to the max value, so the attack can't miss
     * (as an int, more than 300)
     */
    void setMaxAccuracy();
    /**
     * @param ppMax PPMax as an int
     */
    void setPPMax(int ppMax);
    /**
     * @param pp PPs as an int
     */
    void setPP(int pp);
    /**
     * Set the attak priority
     * @param level the attack priority as an int
     */
    void setPriorityLevel(int level);
    /**
     * Set the attack recoil after the hit
     * @param percentage the perccentage of health lost after (as a percentage from 0 to 100)
     */
    void setRecoilPercentage(int percentage);
    /**
     * Set if the pokemon needs a break after the attack
     * @param breakAfter true if the attack needs a break after
     */
    void setBreakAfter(bool breakAfter);
    /**
     * Set if the pokemon needs a break before the attack
     * @param breakAfter true if the attack needs a break before
     */
    void setBreakBefore(bool breakBefore);
    /**
     * Set the minimal number of hits the attack made
     * @param minHits the minimum number of hits as an int
     */
    void setMinimumHits(int minHits);
    /**
     * Set the maximum number of hits the attack made
     * @param maxHits the maximum number of hits as an int
     */
    void setMaximumHits(int maxHits);
    
    /**
     * Set the attack to be protecting the Pokemon
     */
    void setProtecting();
    
    /**
     * Set the Attack to double damages if attacked this turn
     */
    void setDoublesIfDamaged();
    
    
//===============// Getters //===============//
    /**
     * @param previousDamagesToEnnemy the damages dealt to the pokemon before
     * @return the damage as an int
     */
    int getDamage(int previousDamagesToEnnemy = 0) const;
    /**
     * @return the precision in % as an int
     */
    int getAccuracy() const;
    /**
     * @return the PPMax as an int
     */
    int getPPMax() const;
    /**
     * @return the PPs as an int
     */
    int getPP() const;
    
    /**
     * Get the attak priority level
     * @return the attack priority as an int
     */
    int getPriority();
    
    /**
     * Check if the attack has a recoil
     * @return true if the attack has a recoil on the attacking pokemon
     */
    bool hasRecoil();
    
    /**
     * Get the attack recoil
     * @return the attack recoil as a percentage from 0 to 100
     */
    int getRecoilPercentage();
    
    /**
     * Check if the pokemon needs a break after the attack
     * @return true if the pokemon needs a break
     */
    bool getBreakAfter();
    
    /**
     * Check if the pokemon needs a break before the attack
     * @return true if the pokemon needs a break
     */
    bool getBreakBefore();
    
    /**
     * Check if the Attack is a multi-hit attack
     * @return true fi the attack is a multi-hits one
     */
    bool isMultiHitAttack();
    
    /**
     * Get the minimum number of hits the attack can make
     * @return the minimum as an int
     */
    int getMinimumHits();
    
    /**
     * Get the maximum number of hits the attack can make
     * @return the maximum as an int
     */
    int getMaximumHits();
    
    
    /**
     * Get the critical level of the attack
     * @return the critical level of the attack
     */
    int getCriticalLevel();
    
    
    /**
     * Set the attack critical level
     * @param level the new attack critical level
     */
    void setCriticalLevel(int level);
    
    
    /**
     * Check if the attack always make critical hits
     * @return true if the attack always make critical hits
     */
    bool isAlwaysCritical();
    
    /**
     * Set if the attack always make critical hits
     * @param critical true if the attack always make critical hits
     */
    void setAlwaysCritical();
    
    
    /**
     * @return the attack type
     */
    Type getType() const;
    
    /**
     * @return the attack name as a const reference to a string
     */
    const sf::String& getName() const;
    
    /**
     * @return the attack category 
     */
    AttackCategory getCategory() const;
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    virtual std::string getInfoString() const;
    
    
    /**
     * Get the dialogs that shows the efficiency of the attack
     * @return the dialog as a wstring
     */
    static std::wstring getEfficiencyDialog(float coef);
    
    /**
     * Set the statChanger
     * @param statChanger the new statChanger
     */
    void setStatsChanger(StatsChanger statChanger);
    
    /**
     * Get the StatsChanger
     * @return a const reference to the stat changer
     */
    const StatsChanger& getStatsChanger() const;
    
    /**
     * Return the StatChanger as a vector of separated statChanger
     * each of the stat has a single element du 
     * @return 
     */
    std::vector<StatsChanger> getStatChangerAsVector() const;
    
    
    
    /**
     * Get the TextureRect related to the given attack category
     * @param category the attack category
     * @return a IntRect containing the TextureRect
     */
    sf::IntRect getCategoryTextureRect();
    
    /**
     * Get the TextureRect related to the given attack category
     * @param category the attack category
     * @return a IntRect containing the TextureRect
     */
    static sf::IntRect getCategoryTextureRect(AttackCategory category);
    
    
    /**
     * Get the attack description 
     * @return the description as a const reference to a String
     */
    const sf::String& getDescription() const;
    
    
    /**
     * Get the attackID
     * @return the AttackID
     */
    AttackID getID();
    
    /**
     * Check if the Attack protects the Pokemon
     * @return true if teh attack protects the pokemon
     */
    bool isProtectingPokemon();
    
    
    /**
     * Check if the attack double damages when hurt before
     * @return true if the attack can double damages
     */
    bool isDoublingIfDamaged() const;
    
private:
//===============// Attributes //===============//
    // The attack ID
    AttackID m_id;
    
    // Attack Type 
    Type m_type;
    
    // Attack category
    AttackCategory m_category;
    
    // Attack target
    AttackTarget m_target;
    
    // Attack damages and accuracy
    int m_damage;
    int m_accuracy; // In %, = 
    
    // PPMax an PPs
    int m_ppMax;
    int m_pp;
    
    // The priority from -7 to +5
    int m_priorityLevel;
    
    // The attack recoil (a percentage from 0 to 100)
    int m_recoilPercentage;
    
    // Boolean to know if the attack needs a break before or after beeing launched
    bool m_breakBefore;
    bool m_breakAfter;
    
    // Boolean to how much hits the attacks can make
    int m_minimumHits;
    int m_maximumHits;
    
    
    // The critical hit level
    int m_criticalLevel;
    
    // Boolean to know if the attack is always a critical hit
    bool m_alwaysCritical;
    
    // A boolean to know if the attack damage increases when hurt
    bool m_doubleIfDamaged;
    
    
    // A boolean to know if the attack protects or not
    bool m_isProtecting;
    
    // Attack name
    const sf::String& m_name;
    
    // Posible dealt status
    MainStatusName m_mainStatus;
    
    // Chance to deal the main status
    float m_mainStatusChance;
    
    // Stat changers
    StatsChanger m_statsChanges;
    
    // Description
    const sf::String& m_description;
};

#endif /* ATTACK_HPP */

