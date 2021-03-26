/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 22 août 2018, 18:46
 */

#ifndef ATTACKDISPLAY_HPP
#define ATTACKDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "Attack.hpp"

class AttackDisplay : public sf::Drawable{
public:
//=================// Constructor //==================//
    AttackDisplay(Context& context);
    AttackDisplay(Context& context, Attack* a);
    
    
//=================// Public function //==================//
    
    /**
     * Overriden function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    /**
     * Update the Attack display
     * @param a a pointer to the new Attack
     */
    void update(Attack* a);
    /**
     * Update the Attack display, and make it invisible
     */
    void update();
    
    
    /**
     * Set the fill color of the AttackDisplay
     * @param color the color used as the fill Color
     */
    void setFillColor(sf::Color color);
    
    
//=================// Getters / Setters //==================//

    /**
     * Set the position of the AttackDisplay
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    /**
     * Get the AttackDisplay position
     * @return the position as a Vector2f
     */
    sf::Vector2f getPosition();
    
private:
//=================// Private functions //==================//
    
    /**
     * Set the texture of the AttackDisplay
     */
    void setTextureRect(const Type& type);
    
    
//=================// Graphical Attributes //==================//
    // Boolean that stores wether the display should be drawn or not
    bool m_isEmpty;
    
    // text for the PPs and the Attack name
    sf::Text m_ppsText;
    sf::Text m_nameText;
    
    // Background sprite
    sf::Sprite m_sprite;
};

#endif /* ATTACKDISPLAY_HPP */

