/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EVSet.hpp
 * Author: Redbuzard
 *
 * Created on 14 septembre 2020, 08:37
 */

#ifndef EVSET_HPP
#define EVSET_HPP


#include <map>

#include "../Enums.hpp"
#include "../Utilities.hpp"



class EVSet {
public:
//===================// Constructors //===================//
    
    /**
     * Default constructor
     * Puts each valus at 0
     */
    EVSet();
    
    
    /**
     * Constructor from an initialiezr list
     * Order : Health Attack Def Spe_A Spe_Def Speed
     */
    EVSet(std::initializer_list<unsigned int> list);
    
    
//===================// Public Method //===================//
    
    
    /**
     * Increase an IV stat by a given value
     * @param stat the StatName of the EV
     * @param value the value we want to add to the Stat
     * @warning assert the stat is not at the maximum value
     */
    void add(StatName stat, unsigned int value);
    
    
    /**
     * Check if a IV value has reach the maximum value
     * @param stat the StatName of the EV
     * @return true if the max as reached
     */
    bool isMax(StatName stat) const;
    
    
    /**
     * Check if we can increase the EV points for a Stat
     * @param stat the StateName we want to increase
     * @return true if we can increase this stat
     */
    bool canIncrease(StatName stat) const;
    
     
//===================// Getters / Setters //===================//
    
    
    /**
     * Set the maximum values for a Stat
     * @param stat the max value of a given stat
     */
    void setMaxValue(StatName stat);
    
    
    /**
     * Get the value of a stat
     * @param stat the Stat name
     * @return return the EV value
     */
    unsigned int getValue(StatName stat) const;
    
    
    /**
     * Get the IV Set as a string
     * @return the data of the IVSet as a string
     */
    std::string toString() const;
    
    
private:
//===================// Private methods //===================//
    
    /**
     * Get the total of EV values for the current Set
     * @return the sum of EV
     */
    unsigned int getTotal() const;
    
//===================// Static variable //===================//
    
    // Maximum value for a given EV
    static const unsigned int maxEvValue;
    
    // Maximum total for a pokemon's EVs
    static const unsigned int maxTotalEv;
    
    
//===================// Attributes //===================//
    
    // A Map for each statistic type
    std::map<StatName, unsigned int> m_values;

};



std::ostream& operator<<(std::ostream &flux, EVSet const& set );


#endif /* EVSET_HPP */

