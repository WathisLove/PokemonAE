/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BadgeBox.hpp
 * Author: Redbuzard
 *
 * Created on 5 avril 2020, 15:56
 */

#ifndef BADGEBOX_HPP
#define BADGEBOX_HPP

#include <SFML/Graphics.hpp>
#include <array>

#include "../entities/Character.h"


class BadgeBox : public sf::Drawable {
public:
    
//==================// Constructor //=============//
    
    BadgeBox(Context& context, Character* character);
    
//==================// Public Functions //=============//
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
//==================// Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
private:
//==================// Graphical Attributes //=============//
    
    // A Vector for the different badge sprites
    std::array<sf::Sprite, 8> m_badges;
};

#endif /* BADGEBOX_HPP */

