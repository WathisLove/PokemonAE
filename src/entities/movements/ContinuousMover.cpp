/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ContinuousMover.cpp
 * Author: Redbuzard
 * 
 * Created on 6 décembre 2018, 15:18
 */

#include "ContinuousMover.hpp"



ContinuousMover::ContinuousMover(MovementType move) :
EntityMover(),
m_move(move),
m_pauseTime(0){

}



ContinuousMover::ContinuousMover(MovementType move, float pauseTime) :
EntityMover(),
m_move(move),
m_pauseTime(pauseTime){
    
}



MovementType ContinuousMover::getNextMovement() {
    // Return m_move if enough time passed
    if(m_timeSinceLastMove >= m_pauseTime){
        resetSinceLastMove();
        return m_move;
    }
    else
        return MovementType::NoMove;
}



EntityMover* ContinuousMover::copy() {
    return new ContinuousMover(m_move, m_pauseTime);
}



bool ContinuousMover::isFinished() {
    return false;
}
