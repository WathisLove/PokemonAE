/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemPredicates.hpp
 * Author: Redbuzard
 *
 * Created on 27 septembre 2020, 12:18
 */

#ifndef ITEMPREDICATES_HPP
#define ITEMPREDICATES_HPP

#include <functional>
#include "../ItemEnums.hpp"
#include "../pokemons/status/MainStatus.hpp"
#include "../inventory/Item.hpp"


class ItemPredicate {
public:
    
//=================// Public enum //==================//
    
    enum class ItemSearched{
        Healing,
        CuringStatus
    };
    
//=================// Constructor//==================//
    
    /**
     * Creates an ITemPredicate 
     */
    ItemPredicate(ItemSearched search);
    
    
    /**
     * Creates an ITemPredicate to look for an 
     */
    ItemPredicate(ItemSearched search, MainStatusName status);
    
    
//=================// Functer operator//==================//
    
    /**
     * Check if the Item is validated by the predicate
     * @param id the id of the item we want to check
     * @return true if the item is validated by the intern function
     */
    bool operator()(ItemID id);
    
    
private:
//=================// Attributes//==================//
    
    // The target of the ItemPredicate
    ItemSearched m_target;
    
    // The Status we want to heal if needed
    MainStatusName m_status;
    
    
//=================// Methods  //==================//
    
    // A predicate for the healing items
    const static std::function<bool(ItemID)> healing;
    
    // A predicate for the curing Status items
    const static std::function<bool(ItemID, MainStatusName)> curingStatus;
};

#endif /* ITEMPREDICATES_HPP */

