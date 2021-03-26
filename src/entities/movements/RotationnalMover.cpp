/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RotationnalMover.cpp
 * Author: Redbuzard
 * 
 * Created on 7 décembre 2018, 08:40
 */

#include <cmath>

#include "RotationnalMover.hpp"



RotationnalMover::RotationnalMover(MovementType firstMove, float pauseTime, bool clockWise) :
EntityMover(),
m_currentMove(firstMove),
m_pauseTime(pauseTime),
m_isClockWise(clockWise),
m_originalFirstMove(firstMove){
    m_timeSinceLastMove = pauseTime;
}



MovementType RotationnalMover::getNextMovement() {
    // If enough time passed get the next move
    if(m_timeSinceLastMove >= m_pauseTime){
        switchToNextMove();
        resetSinceLastMove();
        return m_currentMove;
    }
    else
        return MovementType::NoMove;
}



EntityMover* RotationnalMover::copy() {
    return new RotationnalMover(m_originalFirstMove, m_pauseTime, m_isClockWise);
}



bool RotationnalMover::isFinished() {
    return false;
}



void RotationnalMover::switchToNextMove() {
    MovementType nextMove = m_currentMove;
    if(m_isClockWise){
        if(m_currentMove == MovementType::LookLeft)
            m_currentMove = MovementType::LookUp;
        else if(m_currentMove == MovementType::LookUp)
            m_currentMove = MovementType::LookRight;
        else if(m_currentMove == MovementType::LookRight)
            m_currentMove = MovementType::LookDown;
        else if(m_currentMove == MovementType::LookDown)
            m_currentMove = MovementType::LookLeft;
    }
    else{
        if(m_currentMove == MovementType::LookLeft)
            m_currentMove = MovementType::LookDown;
        else if(m_currentMove == MovementType::LookDown)
            m_currentMove = MovementType::LookRight;
        else if(m_currentMove == MovementType::LookRight)
            m_currentMove = MovementType::LookUp;
        else if(m_currentMove == MovementType::LookUp)
            m_currentMove = MovementType::LookLeft;
    }
}
