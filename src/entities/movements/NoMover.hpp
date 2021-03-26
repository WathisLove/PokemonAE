/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoMover.hpp
 * Author: Redbuzard
 *
 * Created on 5 décembre 2018, 18:55
 */

#ifndef NOMOVER_HPP
#define NOMOVER_HPP

#include "EntityMover.hpp"

class NoMover : public EntityMover {
    
public:
    NoMover();
    
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

};

#endif /* NOMOVER_HPP */

