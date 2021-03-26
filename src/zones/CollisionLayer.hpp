/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CollisionLayer.hpp
 * Author: Redbuzard
 *
 * Created on 20 juin 2018, 14:14
 */

#ifndef COLLISIONLAYER_HPP
#define COLLISIONLAYER_HPP

#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

#include "../Direction.h"

class CollisionLayer{
    
public: 
//===============// Public Methods //===============//
    
    /**
     * Construct a CollisionLayer
     * @param layerPath is the path to the .csv file that contains the collision cases
     */
    CollisionLayer(const std::string& layerPath);
    
    
    /**
     * Load a LayerZone from the disk
     * @param layerPath is the path to the .csv file that contains the cases
     */
    void loadLayerFromFile(const std::string& layerPath);
    
    /**
     * Return the value stored in the case at index
     * @param index of the case
     */
    int getCaseValue(sf::Vector2i index) const;
    
    /**
     * Return a boolean depending on wether the entities can walk onto this case or not
     * @param index index of the case
     * @return true if it can walk on the case
     */
    bool canWalkOnCase(sf::Vector2i index);
    
    /**
     * Return a boolean depending on wether the entities can surf onto this case or not
     * @param index index of the case
     * @return true if it can surf on the case
     */
    bool canSurfOnCase(sf::Vector2i index);
    
    
    /**
     * Check if it is possible to jump over a case
     * @param index the case index
     * @return the direction of the jump
     */
    bool canJumpOver(sf::Vector2i index, Direction dir);
    
    
    /**
     * Chekc if the player can find pokemons on the given case
     * @param index the index of the case as a Vector2i
     * @return true if the player can encounter pokemons on the given case
     */
    bool canEncounterPokemon(sf::Vector2i index);

private:
//===============// Private methods //===============//
 
    /**
     * Load a line of the .csv file and convert it into a vector
     * @param str String that contains a line of the map
     * @return vector<int> that contains all the cases of the line
     */
    std::vector<int> loadLineFromString(const std::string& string);
    
    
    
//===============// Static constants //===============//
    
    // Value of collision tiles
    static const int collisionTile;
    
    // Value of water tiles
    static const int waterTile;
    
    // Value of wild grass tiles
    static const int wildGrassTile;
    
    // Values of jump borders
    static const int jumpUp, jumpRight, jumpDown, jumpLeft;
    
    
//===============// Attributes //===============//
    
    // 2D array that stocks the values of the cases
    // First vector is the line, the second one give the case
    // PAY ATTENTION : m_cases[x][y] returns the case at line x, column y
    std::vector<std::vector<int> > m_cases;

    // Store the MapSize
    sf::Vector2i m_zoneSize;
};

#endif /* COLLISIONLAYER_HPP */

