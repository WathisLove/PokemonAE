/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContinuousMover.hpp
 * Author: Redbuzard
 *
 * Created on 6 décembre 2018, 15:18
 */

#ifndef CONTINUOUSMOVER_HPP
#define CONTINUOUSMOVER_HPP

#include "EntityMover.hpp"

class ContinuousMover : public EntityMover{
public:
    /**
     * Create a ContinousMover, with a given move repeated all the time
     * @param move the continuous move returned
     */
    ContinuousMover(MovementType move);
    
    /**
     * Create a ContinousMover, with a given move repeated each time the pause ends
     * @param move the continuous move returned
     * @param pauseTime time between two moves
     */
    ContinuousMover(MovementType move, float pauseTime);
    
    
    
    /**
     * Get the next movement of the Entity
     * Can just return a None Movement
     * @return the next movement as en Enum MovementType
     */
    MovementType getNextMovement() override;

    
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
    
    
protected:
    // The pause time between two moves
    float m_pauseTime;
    
    // The returned move
    MovementType m_move;
};

#endif /* CONTINUOUSMOVER_HPP */

