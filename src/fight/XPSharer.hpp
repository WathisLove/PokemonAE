/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPSharer.hpp
 * Author: Redbuzard
 *
 * Created on 11 août 2020, 14:09
 */

#ifndef XPSHARER_HPP
#define XPSHARER_HPP

#include <map>
#include <queue>


#include "../pokemons/Pokemon.hpp"

class XPSharer {
public:
//=================// Constructor //==================//
    
    XPSharer();
    
//=================// Public methods //==================//
    
    
    /**
     * Updates the XPSharer to remember ally faced the given ennemy
     * @param ennemy a poiner to the Ennemy pokemon
     * @param ally a pointer to the ally pokemon
     */
    void addFaced(Pokemon* ennemy, Pokemon* ally);
    
    
//=================// Getters //==================//
    
    /**
     * Get the xp given to each pokemon once the ennemy is defeated
     * @param ennemy a pointer to the ennemy defeated
     * @return the xp points that will be given to each pokemons
     */
    int getXPGivingEach(Pokemon* ennemy);
    
    /**
     * Get all the pokemons not KO that faced the Ennemy
     * @param ennemy a pointer to the ennemy
     * @return a vector of ally pokemon pointers
     */
    std::queue<Pokemon*> getFacedNotKO(Pokemon* ennemy);
    
    
private:
//=================// Attributes //==================//
    
    // Multimap storing the ennemis -> faced allies
    std::multimap<Pokemon*, Pokemon*> m_facedAllies;
};

#endif /* XPSHARER_HPP */

