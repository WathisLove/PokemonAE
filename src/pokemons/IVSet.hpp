/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IVSet.hpp
 * Author: Redbuzard
 *
 * Created on 13 septembre 2020, 12:41
 */

#ifndef IVSET_HPP
#define IVSET_HPP

#include <map>

#include "../Enums.hpp"
#include "../Utilities.hpp"


class IVSet {
public:
//===================// Constructors //===================//
    
    /**
     * Default constructor
     * Set random values
     */
    IVSet();
    
    /**
     * Constructor that combines two IV set (used by reproduction)
     */
    IVSet(const IVSet& set1, const IVSet& set2);
    
    
    /**
     * Constructor from an initialiezr list
     * Order : Health Attack Def Spe_A Spe_Def Speed
     */
    IVSet(std::initializer_list<unsigned int> list);
    
    
//===================// Public Method //===================//
    
    
    /**
     * Increase an IV stat by a given value
     * @param stat the StatName of the IV
     * @param value the value we want to add to the Stat
     * @warning assert the stat is not at the maximum value
     */
    void add(StatName stat, unsigned int value);
    
    
    /**
     * Check if a IV value has reach the maximum value
     * @param stat the StatName of the IV
     * @return true if the max as reached
     */
    bool isMax(StatName stat) const;
    
    
    /**
     * Get the IV Set as a string
     * @return the data of the IVSet as a string
     */
    std::string toString() const;
    
    
//===================// Getters / Setters //===================//
    
    
    /**
     * Set the maximum values for each Stat
     */
    void setMaxValues();
    
    
    /**
     * Get the value of a stat
     * @param stat the Stat name
     * @return return the IV value
     */
    int getValue(StatName stat) const;
    
//===================// Operator //===================//
    
    
    
private:
//===================// Private methods //===================//
    
    /**
     * Merge the IV from two pokemons for a single stat
     * @param v1 the value of the first pokemon
     * @param v2 the value of the second pokemon
     * @return the merged value of the two
     */
    static int mergeIV(unsigned int v1, unsigned int v2);
    
    
//===================// Static variable //===================//
    
    // Maximum value for a given IV
    static const unsigned int maxIvValue;
    
    
//===================// Attributes //===================//
    
    // A Map for each statistic type
    std::map<StatName, unsigned int> m_values;
};



std::ostream& operator<<(std::ostream &flux, IVSet const& set );


#endif /* IVSET_HPP */

