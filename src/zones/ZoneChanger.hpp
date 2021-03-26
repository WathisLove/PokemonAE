/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneChanger.hpp
 * Author: Redbuzard
 *
 * Created on 11 juillet 2018, 11:19
 */

#ifndef ZONECHANGER_HPP
#define ZONECHANGER_HPP

#include <SFML/Graphics.hpp>
#include "FieldObject.hpp"
#include "../Direction.h"
#include "ZoneID.hpp"



class ZoneChanger : public FieldObject{
public:
    ZoneChanger(sf::IntRect rect, ZoneID id, sf::Vector2i newCharacterPos, Direction newDir);
    ZoneChanger(sf::IntRect rect, ZoneID id, sf::IntRect newZoneRect, Direction newDir);
    
    
//=================// Public Functions //==================//
   
    
    
//=================// Getters //==================//

    /**
     * Return the new Character position
     */
    sf::Vector2i getNewCharacterPos(sf::Vector2i characterPos) const;
    
    /**
     * Return the new Character position
     */
    sf::Vector2i getNewCharacterPos(sf::Vector2i characterPos, sf::IntRect newZoneRect) const;

    /**
     * Return the id of the new Zone
     */
    ZoneID getNewZoneID() const;
    
    
    /**
     * Get the new direction of the Character once it passes through the zone Changer
     * @return the new direction of the character
     */
    Direction getNewDirection() const;
    
    
    
    
private:
//=================//  Attributes //==================//
    // ID of the new Zone
    ZoneID m_newZoneID;
    
    // Character Position in the newZone
    sf::Vector2i m_newCharacterPos;
    
    // Character Position in the newZone
    sf::IntRect m_newZoneRect;
    
    // New Character Direction
    Direction m_newDir;
};

#endif /* ZONECHANGER_HPP */

