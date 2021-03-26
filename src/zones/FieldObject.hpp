/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FieldObject.hpp
 * Author: Redbuzard
 *
 * Created on 15 juillet 2018, 14:43
 */

#ifndef FIELDOBJECT_HPP
#define FIELDOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "../Enums.hpp"

class FieldObject {
public:
    
    FieldObject(sf::IntRect rect);
    
    
//=================// Public Functions //==================//
    /**
     * @return true if the position is inside the rect
     */
    virtual bool isinsideRect(sf::Vector2i pos) const;
    
//=================// Getters //==================//
    /**
     * Return the active rect of the ZoneChanger
     */
    sf::IntRect getRect() const;
    
protected:
//=================//  Attributes //==================//
    // Active rect of the ZoneChanger
    sf::IntRect m_rect;
};

#endif /* FIELDOBJECT_HPP */

