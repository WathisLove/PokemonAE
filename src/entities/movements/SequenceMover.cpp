/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SequenceMover.cpp
 * Author: Redbuzard
 * 
 * Created on 18 décembre 2018, 18:39
 */

#include "SequenceMover.hpp"
#include "NoMover.hpp"

#include <iostream>

SequenceMover::SequenceMover() :
EntityMover(),
m_currentMove(0),
m_loop(true),
m_gaveFirstMove(false)
{
    
}



SequenceMover::SequenceMover(sf::Vector2i posStart, sf::Vector2i posEnd, float breakTime) :
EntityMover(),
m_currentMove(0),
m_loop(false),
m_gaveFirstMove(false)
{
    // Get the Start position, used in the loops
    int x = posStart.x; int y = posStart.y;
    
    // We go Right of left if needed
    for(; x < posEnd.x; x++)
        pushMove(MovementType::GoRight, breakTime);
    for(; x > posEnd.x; x--)
        pushMove(MovementType::GoLeft, breakTime);
    
    // Same : We go Up or Down if needed
    for(; y < posEnd.y; y++)
        pushMove(MovementType::GoDown, breakTime);
    for(; y > posEnd.y; y--)
        pushMove(MovementType::GoUp, breakTime);
}



void SequenceMover::pushMove(MovementType moveType, float breakTime, int times) {
    // If this is the first move
    if(m_moves.size() == 0)
        m_timeSinceLastMove = breakTime;
    
    // Create the Sequence Move
    Sequence mv;
    mv.move = moveType;
    mv.breakTime = breakTime;
    
    // Add it as much time as needed in the vector
    for(int i = 0; i < times; i++){
        m_moves.push_back(mv);
    }
}



void SequenceMover::setLoop(bool val) {
    m_loop = val;
}



bool SequenceMover::isFinished() {
    // Check if we reached the end of the moves
    // Minus 1 for the first NoMove
    return m_currentMove == m_moves.size();
}



void SequenceMover::switchToNextMove() {
    // If we didn't already reach the end
    if(m_currentMove != m_moves.size())
        m_currentMove++;
    
    // Reset to the first if we loop and reached the end
    if(m_loop && m_currentMove == m_moves.size())
        m_currentMove = 0;
    
    // Reset the time
    resetSinceLastMove();
}



MovementType SequenceMover::getNextMovement() {
    // Return no Move if we don't have any
    if(m_moves.size() == 0)
        return MovementType::NoMove;
    
    // Give the first move if we didn't gave it
    if(!m_gaveFirstMove){
        m_gaveFirstMove = true;
        resetSinceLastMove();
        return m_moves.at(m_currentMove).move;
    }
    // If we did'nt reach the end
    else if(m_currentMove < m_moves.size()){
    // Else if enough time passed, switch to the next
        if(m_timeSinceLastMove >= m_moves.at(m_currentMove).breakTime){
            switchToNextMove();

            // If we are not at the end of the vector
            if(m_currentMove != m_moves.size())
                return m_moves.at(m_currentMove).move;
            else
                return MovementType::NoMove;
        }
    }
    
    // Else don't move
    return MovementType::NoMove;
}



void SequenceMover::revertMovement() {
    if(m_moves.size() > 0)
        m_currentMove = (m_currentMove + m_moves.size() - 1) % m_moves.size();
}



EntityMover* SequenceMover::copy() {
    SequenceMover* m = new SequenceMover();
    
    // Add each of our moves to the SequenceMover
    for(int i = 0; i < m_moves.size(); i++){
        m->pushMove(m_moves.at(i).move, m_moves.at(i).breakTime);
    }
    
    return m;
}
