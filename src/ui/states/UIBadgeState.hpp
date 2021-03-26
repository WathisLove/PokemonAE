/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIBadgeState.hpp
 * Author: Redbuzard
 *
 * Created on 10 avril 2020, 18:26
 */

#ifndef UIBADGESTATE_HPP
#define UIBADGESTATE_HPP


#include <SFML/Graphics.hpp>

#include "../../Context.hpp"

class UIBadgeState : public sf::Drawable{
public:
//==================// Constructor //=============//
    
    /**
     * Constructor
     */
    UIBadgeState(Context& context, int badgeNumber);
    
    
//==================// Public Functions //=============//
    
    /**
     * Overriden function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /**
     * Choose wether or not we must show the UI
     * @param val true if we must show the UI
     */
    void show(bool val);
    
//==================// Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    
private:
//==================// Attributes //=============//
    // Boolean to know if we show the UI elements
    bool m_show;
    
//==================// Graphical Attributes //=============//
        
    // A sprite for the Badge
    sf::Sprite m_badge;
};

#endif /* UIBADGESTATE_HPP */

