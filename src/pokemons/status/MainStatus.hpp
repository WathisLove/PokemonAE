/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainStatus.hpp
 * Author: Redbuzard
 *
 * Created on 28 septembre 2018, 21:28
 */

#ifndef MAINSTATUS_HPP
#define MAINSTATUS_HPP

#include <string>
#include "../../Enums.hpp"


class MainStatus {
public:
    
    /**
     * Create a new empty status
     */
    MainStatus();
    
    /**
     * Create a new Status with a given name
     * @param name the name of the status
     */
    MainStatus(MainStatusName name);
    
    /**
     * Create a new Status with a given name and a value for the turns attribute
     * @param name the name of the Status 
     * @param turns the value for the turns attribute as an int
     */
    MainStatus(MainStatusName name, int turns);
    
    /**
     * Return the value of the turns attribute 
     * @return the turns as an int
     */
    int getTurns() const;
    
    /**
     * Return the name of the status
     * @return the name as a MainStatusName
     */
    MainStatusName getName() const;
    
   /**
    * Update the turns of the status (for poison or sleep)
    */
    void updateTurns();
    
    /**
     * Change the current status to a given status
     * @param name the name of the new Status
     */
    void changeStatus(MainStatusName name);
    
    /**
     * Change the current status to a given status
     * @param name te name of the status
     * @param turns the new value of the turns attribute
     */
    void changeStatus(MainStatusName name, int turns);
    
    /**
     * Clear the actual status
     */
    void clearStatus();
    
    /**
     * Returns if the status of the pokemon can end naturally or not
     * @return 
     */
    bool statusEnd() const;
    
    /**
     * Return the fraction of hp that the pokemon will lost with the status
     * @return a factor of the HP as a float
     */
    float getDamageFactor() const;
    
    /**
     * Return true if the status is a poison one, false otherwise
     * @return a boolean 
     */
    bool isPoison() const;
    
    
    /**
     * Return the status name as a lower case string
     * @return a string
     */
    std::string toString() const;
    
    
    /**
     * Get the capture bonus factor given by the status
     * @return the rate as a float from 1 to 2
     */
    float getCaptureBonus();
    
private:
//===================// Private Attributes //===========//
    
    // The number of turns left or since the status started
    int m_turns;
    
    // The name of the status
    MainStatusName m_name;

};

#endif /* MAINSTATUS_HPP */

