/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RandomMover.cpp
 * Author: Redbuzard
 * 
 * Created on 29 novembre 2018, 17:17
 */

#include "RandomMover.hpp"
#include "../../Utilities.hpp"

RandomMover::RandomMover(sf::IntRect zoneRect, sf::Vector2i actualPos, float pauseTime) :
EntityMover(),
m_zoneRect(zoneRect),
m_pauseTime(pauseTime),
m_originPosition(actualPos){
    m_actualPos = actualPos;
}



MovementType RandomMover::getNextMovement() {
    // If enough time passed, return a move different frome None
    if(m_timeSinceLastMove >= m_pauseTime){
        MovementType move = (MovementType)(randomInt(GoUp, LookLeft));
        
        // Check if the Entity does not leave the zoneRect
        if(m_actualPos.x <= m_zoneRect.left && move == MovementType::GoLeft)
            move = MovementType::LookLeft;
        else if(m_actualPos.x >= (m_zoneRect.left + m_zoneRect.width - 1) && move == MovementType::GoRight)
            move = MovementType::LookRight;
        else if(m_actualPos.y <= m_zoneRect.top && move == MovementType::GoUp)
            move = MovementType::LookUp;
        else if(m_actualPos.y >= (m_zoneRect.top + m_zoneRect.height - 1) && move == MovementType::GoDown)
            move = MovementType::LookDown;
        
        // Return the move
        resetSinceLastMove();
        return move;
    }
    
    else return MovementType::NoMove;
}



EntityMover* RandomMover::copy() {
    return new RandomMover(m_zoneRect, m_originPosition, m_pauseTime);
}



bool RandomMover::isFinished() {
    return false;
}
