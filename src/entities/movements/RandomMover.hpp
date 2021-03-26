/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandomMover.hpp
 * Author: Redbuzard
 *
 * Created on 29 novembre 2018, 17:17
 */

#ifndef RANDOMMOVER_HPP
#define RANDOMMOVER_HPP

#include "EntityMover.hpp"
#include <SFML/Graphics.hpp>

class RandomMover : public EntityMover{
public:
    
//================// Constructor //==============//
    RandomMover(sf::IntRect zoneRect, sf::Vector2i actualPos, float pauseTime);
    
    
//================// Public functions //==============//
    
    /**
     * Get the next movement of the Entity
     * Can just return a None Movement
     * @return the next movement as en Enum MovementType
     */
    MovementType getNextMovement();


    
    /**
     * Copy the EntityMover
     */
    EntityMover* copy();

    
//=================// Inherited Methods //==================//
    
    /**
     * Check if the Mover has no moves left
     * @return true if there won't be any more moves
     */
    virtual bool isFinished();
    
private:
//================// Attributes //==============//
    sf::IntRect m_zoneRect;
    
    float m_pauseTime;
    
    // Position at creation
    sf::Vector2i m_originPosition;
};

#endif /* RANDOMMOVER_HPP */

