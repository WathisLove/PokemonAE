/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SequenceMover.hpp
 * Author: Redbuzard
 *
 * Created on 18 décembre 2018, 18:39
 */

#ifndef SEQUENCEMOVER_HPP
#define SEQUENCEMOVER_HPP

#include <vector>
#include "EntityMover.hpp"



class SequenceMover : public EntityMover{
public:
    
    SequenceMover();
    
    /**
     * Create a Sequence mover so the Entity goes from a position to an other
     * @param breakTime time between each move
     */
    SequenceMover(sf::Vector2i posStart, sf::Vector2i posEnd, float breakTime);
   
    
    /**
     * Get the next movement of the Entity
     * Can just return a None Movement
     * @return the next movement as en Enum MovementType
     */
    virtual MovementType getNextMovement();

    
    /**
     * Revert the last movement cause the movement was blocked
     */
    void revertMovement() override;

    
    /**
     * Copy the EntityMover
     */
    EntityMover* copy();
    
    
    /**
     * Push a move in the vector
     * @param move the move that will be pushed
     * @param times the number of times the move will be pushed
     */
    void pushMove(MovementType moveType, float breakTime, int times = 1);
    
    
    /**
     * Set the mover to loop or not
     * @param val true if the mover must loop
     */
    void setLoop(bool val);
    
    
//=================// Inherited Methods //==================//
    
    /**
     * Check if the Mover has no moves left
     * @return true if there won't be any more moves
     */
    virtual bool isFinished();
    
    
private:
    
    struct Sequence{
        MovementType move;
        float breakTime;
    };
    
    
    /**
     * Switch to the next Move in the vector
     */
    void switchToNextMove();
    
    
    // Vector of the moves ordered 
    std::vector<Sequence> m_moves;
    
    // Index of the current move
    int m_currentMove;
    
    // A boolean to know if the mover must loop or not
    bool m_loop;
    
    // A boolean to know if we gave the first move
    bool m_gaveFirstMove;
};

#endif /* SEQUENCEMOVER_HPP */

