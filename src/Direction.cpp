#include "Direction.h"
#include "Utilities.hpp"
#include "pokemons/attacks/Attack.hpp"
#include "utility/Logger.hpp"

#include <iostream>



std::map<std::string, Direction> directionStrings = 
{
    {"NORTH", Direction::North},
    {"SOUTH", Direction::South},
    {"EAST", Direction::East},
    {"WEST", Direction::West},
};



sf::Vector2i getCaseFacing(Direction dir, sf::Vector2i actualCase, int distance){
    sf::Vector2i caseVariation;
    
    if(dir == Direction::North)
        caseVariation = sf::Vector2i(0,-distance);
    else if(dir == Direction::East)
        caseVariation = sf::Vector2i(distance,0);
    else if(dir == Direction::South)
        caseVariation = sf::Vector2i(0,distance);
    else // West
        caseVariation = sf::Vector2i(-distance,0);
    
    return actualCase + caseVariation;
}



Direction oppositeDirection(Direction dir){
    switch(dir){
        case Direction::North:
            return Direction::South;
        case Direction::South:
            return Direction::North;
        case Direction::East:
            return Direction::West;
        default:
            return Direction::East;
    }
}



Direction randomDirection(){
    int rand = randomInt(0, 3);
    
    switch(rand){
        case 0 : return Direction::North;
        case 1 : return Direction::East;
        case 2 : return Direction::South;
        case 3 : return Direction::West;
    }
    
    // Never reached
    Log("Wrong random direction", Logger::WARNING);
    return Direction::North;
}



Direction closestDirection(sf::Vector2i myPos, sf::Vector2i targetPos){
    // Get the x and y distance
    int xdist = std::abs(myPos.x - targetPos.x);
    int ydist = std::abs(myPos.y - targetPos.y);
    
    // Check te smallest direction and if myPos.x is less than targetPos.x
    if(xdist >= ydist && myPos.x > targetPos.x){
        return Direction::West;
    }
    else if(xdist >= ydist && myPos.x < targetPos.x){
        return Direction::East;
    }
    else if(myPos.y < targetPos.y){
        return Direction::South;
    }
    else{
        return Direction::North;
    }
}