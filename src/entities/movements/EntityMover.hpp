/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityMover.hpp
 * Author: Redbuzard
 *
 * Created on 28 novembre 2018, 06:14
 */

#ifndef ENTITYMOVER_HPP
#define ENTITYMOVER_HPP

#include "../../Enums.hpp"
#include "../../Direction.h"
#include <SFML/Graphics.hpp>

class EntityMover {
public:
//================// Constructor //==============//
    EntityMover();
    
    
    
//================// Public functions //==============//
    
    /**
     * Get the next movement of the Entity
     * Can just return a None Movement
     * @return the next movement as en Enum MovementType
     */
    virtual MovementType getNextMovement() = 0;
    
    /**
     * Revert the last movement cause the movement was blocked
     */
    virtual void revertMovement();
    
    
    /**
     * Update the entityMover with the elapsed time
     * @param elapsedTime seconds since the last frame as a float
     */
    void update(float elapsedTime);
    
    
    /**
     * Set the position of the entity linked to the RandomMover
     * @param actualPos
     */
    void setPosition(sf::Vector2i actualPos);
    
    
    /**
     * Get the elapsed time since the last move
     * @return the elapsed time as a float
     */
    float getSinceLastMove() const;
    
    
    /**
     * Reset the counter of time since the last move
     */
    void resetSinceLastMove();
    
    
    /**
     * Check if the Mover has no moves left
     * @return true if there won't be any more moves
     */
    virtual bool isFinished() = 0;
    
    
    /**
     * Copy the EntityMover
     */
    virtual EntityMover* copy() = 0;
    
    
    /**
     * Get the movement corresponding to move in a direction
     * @param dir the direction of the movement
     * @return the movement as a MovementType enum
     */
    static MovementType goDirection(Direction dir);
    
protected:
//================// Attributes //==============//
    // Time since the last move different from None
    float m_timeSinceLastMove;
    
    // Actual position of the related entity
    sf::Vector2i m_actualPos;

};

#endif /* ENTITYMOVER_HPP */

