/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackPredicate.hpp
 * Author: Redbuzard
 *
 * Created on 27 septembre 2020, 13:13
 */

#ifndef ATTACKPREDICATE_HPP
#define ATTACKPREDICATE_HPP

#include <functional>
#include "../pokemons/attacks/AttackID.hpp"


class AttackPredicate {
public:
    //=================// Public enum //==================//
    
    enum class AttackSearched{
        Priority,
        StatReduceEnnemy,
        StatRaiseAlly
    };
    
//=================// Constructor//==================//
    
    /**
     * Creates an ITemPredicate 
     */
    AttackPredicate(AttackSearched search);
    
    
//=================// Functer operator//==================//
    
    /**
     * Check if the Attack is validated by the predicate
     * @param id the id of the attack we want to check
     * @return true if the item is validated by the intern function
     */
    bool operator()(AttackID id);
    
    
private:
//=================// Attributes//==================//
    
    // The target of the ItemPredicate
    AttackSearched m_target;
    
//=================// Methods  //==================//
    
    // A predicate for the healing items
    const static std::function<bool(AttackID)> priority;
    
    // A predicate for the stat reducing attacks
    const static std::function<bool(AttackID)> statReduceEnnemy;
    
    // A predicate for the stat raising attacks
    const static std::function<bool(AttackID)> statRaiseEnnemy;
};

#endif /* ATTACKPREDICATE_HPP */

