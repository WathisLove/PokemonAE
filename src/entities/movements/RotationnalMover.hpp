/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RotationnalMover.hpp
 * Author: Redbuzard
 *
 * Created on 7 décembre 2018, 08:40
 */

#ifndef ROTATIONNALMOVER_HPP
#define ROTATIONNALMOVER_HPP

#include "EntityMover.hpp"

class RotationnalMover : public EntityMover{
public:
    RotationnalMover(MovementType firstMove, float pauseTime, bool clockWise);
    
    
    /**
     * Get the next movement of the Entity
     * Can just return a None Movement
     * @return the next movement as en Enum MovementType
     */
    virtual MovementType getNextMovement() override;

    
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
    
    /**
     * Switch the MovementType to the next one
     */
    void switchToNextMove();
    
    
    // Time between two rotation
    float m_pauseTime;
    
    // Current move of the RotationnalMover
    MovementType m_currentMove;

    // True if the entity rotates clockwise
    bool m_isClockWise;
    
    // The original first movement
    MovementType m_originalFirstMove;
};

#endif /* ROTATIONNALMOVER_HPP */

