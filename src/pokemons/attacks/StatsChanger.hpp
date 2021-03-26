/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StatsChanger.hpp
 * Author: Redbuzard
 *
 * Created on 10 novembre 2018, 18:49
 */

#ifndef STATSCHANGER_HPP
#define STATSCHANGER_HPP


#include <vector>
#include "../../Utilities.hpp"
#include "../../Enums.hpp"

class StatsChanger {
public:
    StatsChanger();
    StatsChanger(Team targetTeam, int atk, int def, int speAtk, int speDef, int speed, int evas, int accur);
    
    
//===================// Gettrs / Setters //===================//
    
    
    /**
     * @return the value of the stat changer of the given statistic
     */
    int getStatChangerValue(StatName stat) const;
    
    /**
     * Set the value of the stat changer
     */
    void setStatChangerValue(StatName stat, int val);
    
    /**
     * Return the final stat value corresponding to the base one, with the changes applied
     * @return the changed value as an int
     */
    int getFinalStat(StatName stat, int baseStat) const;
    
    
    /**
     * Return the StatChanger as a vector of separated statChanger
     * each of the stat has a single element du 
     * @return 
     */
    std::vector<StatsChanger> getStatChangerAsVector() const;
    
    /**
     * Get the team targeted by the statChanger
     * @return the targeted team as a Team enum
     */
    Team getTargetedTeam() const;
    
    /**
     * Set the value of the targeted team attribute
     */
    void setTargetedTeam(Team targetTeam);
    
    
    /**
     * @return true if the statChanger change no statistic (default constructor)
     */
    bool nullChanger() const;
    
    
    /**
     * Get the name of the not null stat
     * @return te name of the not null stat
     */
    StatName getNonNullStatName() const;
    
    
    /**
     * Check if the given stat can be increased
     * @return true if the stat can be increased
     */
    bool canIncreaseStat(StatName stat) const;
    
    
    /**
     * Check if the given stat can be decreased
     * @return true if the stat can be decreased
     */
    bool canDecreaseStat(StatName stat) const;
    
    
    
    /**
     * Return a string used in fight for the stat changes
     * @return a wstring
     */
    std::wstring getValAsWString(int val) const;
    
    
    /**
     * Return a string used in fight for the name of the stat change
     * @return a wstring
     */
    std::wstring getFightWString(StatName stat) const;
    
    
    /**
     * Add the value given to the corresponding stat  to the one in the attributes
     * @param name StatName of the stat that will be changed 
     * @param val value change as an int
     */
    void add(StatName name, int val);
    
    
    /**
     * Add all the attribute of the StatsChanger in the parameters to the current one
     * @param sc StatChanger added to the current StatChanger
     */
    void add(StatsChanger sc);
    
    
    /**
     * Swithc the target from ennemy to ally, or ally to ennemy
     */
    void reverseTarget();
    
    
    /**
     * Check if the Changer is globally negative for the 
     * @return true if the StatChanger sum is < 0
     */
    bool isNegativeChanger() const;
    
    /**
     * Check if the Changer is globally positive
     * @return true if the StatChanger sum is > 0
     */
    bool isPositiveChanger() const;
    
    
private:
    
    
    /**
     * Compute the sum of the stat changes
     * @return the sum as an int
     */
    int sum() const;
    
//===================// Attributes //===================//
    int m_attack;
    int m_defense;
    int m_specialAttack;
    int m_specialDefense;
    int m_speed;
    int m_evasion;
    int m_accuracy;

    
    // Target of the stat changing
    Team m_targetTeam;
};

#endif /* STATSCHANGER_HPP */

