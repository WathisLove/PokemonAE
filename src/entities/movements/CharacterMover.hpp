/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CharacterMover.hpp
 * Author: Redbuzard
 *
 * Created on 18 juin 2020, 18:44
 */

#ifndef CHARACTERMOVER_HPP
#define CHARACTERMOVER_HPP

#include "EntityMover.hpp"
#include <set>

class CharacterMover : public EntityMover{
public:
    
//=================// Constructor //==================//
    
    /**
     * Default constructor
     */
    CharacterMover(float timeBetweenMoves);
    
    
//=================// Inherited Methods //==================//
    
    /**
     * Check if the Mover has no moves left
     * @return true if there won't be any more moves
     */
    virtual bool isFinished();
    
    
//=================// Getters //==================//
    
    /**
     * Get the next movement of the Character
     * @return 
     */
    MovementType getNextMovement() override;

    
    /**
     * Copy the EntityMover
     */
    EntityMover* copy();
    
    
private:
//=================// Private methods //==================//
   
    /**
     * Look or go up if we already are looking up
     * @return the movement if the Up key is pressed
     */
    MovementType up();
    
    /**
     * Look or go down if we already are looking down
     * @return the movement if the Up key is pressed
     */
    MovementType down();
    
    /**
     * Look or go left if we already are looking left
     * @return the movement if the Up key is pressed
     */
    MovementType left();
    
    /**
     * Look or go right if we already are looking right
     * @return the movement if the Up key is pressed
     */
    MovementType right();
    
    
    /**
     * Move in a given direction
     * @param dir the direction
     * @return the move to execute
     */
    MovementType moveIn(Direction dir);
    
    
    /**
     * Add the keys currently pressed
     */
    std::set<Direction> getCurrentDirections();
    
    
//=================// Attributes //==================//
    
    // The time before the Character start moving
    float m_timeBeforeMove;
    
    // Set of key pressed
    std::set<Direction> m_previousDirections;
    
    // Last Direction
    Direction m_lastDirection;
};

#endif /* CHARACTERMOVER_HPP */

