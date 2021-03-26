/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Direction.h
 * Author: Redbuzard
 *
 * Created on 18 juin 2018, 11:36
 */

#ifndef DIRECTION_H
#define DIRECTION_H

#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>


enum Direction{
    North,
    East,
    South,
    West
};


// Map to convert enum to string
extern std::map<std::string, Direction> directionStrings;



/**
 * Utility functions that provides functions to manage direction and cases movements
 */
sf::Vector2i getCaseFacing(Direction dir, sf::Vector2i actualCase, int distance = 1);

/**
 * Return the opposite direction
 */
Direction oppositeDirection(Direction dir);


/**
 * Generate a random direction
 * @return a random direction
 */
Direction randomDirection();


/**
 * Return the closest direction to look from a point to an other
 * @return the direction as a Direction enum
 */
Direction closestDirection(sf::Vector2i myPos, sf::Vector2i targetPos);


#endif /* DIRECTION_H */

