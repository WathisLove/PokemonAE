/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stats.hpp
 * Author: Redbuzard
 *
 * Created on 20 juillet 2018, 18:05
 */

#ifndef STATS_HPP
#define STATS_HPP

#include <string>
#include "../Enums.hpp"

class Stats {
public:
    Stats(int hp, int atk, int def, int spatk, int spdef, int speed);
    
    
//===================// Getters / Setters //===================//
    
    /**
     * @return the stat value corresponding
     */
    int getStatValue(StatName stat) const;
    
    /**
     * Set the value of the given stat
     */
    void setStatValue(StatName stat, int val);
    
    /**
     * Returns a string that can be used to display infos about the class
     * @return a const reference to a string
     */
    std::string getInfoString() const;
    
private:
//===================// Attributes //===================//
    int m_hp;
    int m_attack;
    int m_defense;
    int m_specialAttack;
    int m_specialDefense;
    int m_speed;
};

#endif /* STATS_HPP */

