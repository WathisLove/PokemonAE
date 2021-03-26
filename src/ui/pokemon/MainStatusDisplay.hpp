/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainStatusDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 7 octobre 2019, 20:13
 */

#ifndef MAINSTATUSDISPLAY_HPP
#define MAINSTATUSDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../../pokemons/status/MainStatus.hpp"

class MainStatusDisplay : public sf::Drawable{
public:
    
//=================// Constructors //==================//
    
    MainStatusDisplay(Context& context);
    
    
//=================// Public Methods //==================//
    
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Getters / Setters //==================//
    
    
    /**
     * Set the status that we want to display
     * @param status the status displayed
     */
    void setStatus(MainStatus status);
    
    
    /**
     * Set the status Display position
     * @param pos the position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the sprite zoom factor
     * @param factor the factor of zoom we want to apply to the sprite
     */
    void setZoomFactor(float factor);
    
    
private:
    
//=================// Graphical Attributes //==================//
    
    // The sprite showing the status
    sf::Sprite m_sprite;
};

#endif /* MAINSTATUSDISPLAY_HPP */

