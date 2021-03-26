/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoxPC.hpp
 * Author: Redbuzard
 *
 * Created on 27 janvier 2020, 13:33
 */

#ifndef BOXPC_HPP
#define BOXPC_HPP

#include "Entity.hpp"

class Interaction;

class BoxPC : public Entity{
public:
//=================// Constructor //==================//
    
    BoxPC(Context& context, sf::Vector2i pos, Zone* zone);
    
    
//=================// Public method //==================//
    /**
     * Creates an interaction for the BoxPC
     * @return a pointer to the Interaction
     */
    Interaction* createInteraction() const;
};

#endif /* BOXPC_HPP */

