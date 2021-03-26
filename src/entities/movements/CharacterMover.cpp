#include "CharacterMover.hpp"
#include "NoMover.hpp"
#include "../../utility/Logger.hpp"
#include "../../Utilities.hpp"
#include <algorithm>


CharacterMover::CharacterMover(float timeBetweenMoves) :
EntityMover(),
m_timeBeforeMove(0.4*timeBetweenMoves),
m_lastDirection(Direction::North){

}



bool CharacterMover::isFinished() {
    // Never ending :D
    return false;
}



MovementType CharacterMover::getNextMovement() {
    // Get the current directions
    std::set<Direction> currentDir = getCurrentDirections();
    
    // If no current Move
    if(currentDir.empty())
        return MovementType::NoMove;
    
    // Keep the difference
    std::set<Direction> diff;
    
    for(Direction d : currentDir){
        // If the direction is not in the previous set
        if(m_previousDirections.count(d) == 0)
            diff.emplace(d);
    }
    
    // Save the currentDirections
    m_previousDirections = currentDir;
    
    // If empty
    if(diff.empty()){
        // If the direction is not in the map
        if(m_previousDirections.count(m_lastDirection) == 0)
            return moveIn(*m_previousDirections.begin());
        else 
            return moveIn(m_lastDirection);
    }
    // Move in the first direction of the difference
    else{
        // Reset time since last move
        m_timeSinceLastMove = 0;
        
        // Return the move
        return moveIn(*diff.begin());
    }
}



EntityMover* CharacterMover::copy() {
    return new CharacterMover(m_timeBeforeMove/0.4);
}



MovementType CharacterMover::up() {
    if(m_timeSinceLastMove >= m_timeBeforeMove)
        return MovementType::GoUp;
    else
        return MovementType::LookUp;
}



MovementType CharacterMover::down() {
    if(m_timeSinceLastMove >= m_timeBeforeMove)
        return MovementType::GoDown;
    else
        return MovementType::LookDown;
}



MovementType CharacterMover::left() {
    if(m_timeSinceLastMove >= m_timeBeforeMove)
        return MovementType::GoLeft;
    else
        return MovementType::LookLeft;
}



MovementType CharacterMover::right() {
    if(m_timeSinceLastMove >= m_timeBeforeMove)
        return MovementType::GoRight;
    else
        return MovementType::LookRight;
}



MovementType CharacterMover::moveIn(Direction dir) {
    // Save last direction
    m_lastDirection = dir;
    
    switch(dir){
        case Direction::North:
            return up();
        case Direction::East:
            return right();
        case Direction::South:
            return down();
        case Direction::West:
            return left();
    }
    
    Log("Reached end of Character Mover MoveIn", Logger::WARNING_CODE);
    return MovementType::NoMove;
}



std::set<Direction> CharacterMover::getCurrentDirections() {    
    // Result
    std::set<Direction> res;
    
    // Check the Key pressed
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        res.emplace(Direction::North);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        res.emplace(Direction::South);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        res.emplace(Direction::West);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        res.emplace(Direction::East);
    
    return res;
}
