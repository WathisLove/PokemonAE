/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealthBar.hpp
 * Author: Redbuzard
 *
 * Created on 5 octobre 2019, 14:39
 */

#ifndef HEALTHBAR_HPP
#define HEALTHBAR_HPP

#include <SFML/Graphics.hpp>
#include "../../pokemons/Pokemon.hpp"

class HealthBar : public sf::Drawable{
public:
    
    HealthBar(Pokemon* p, sf::Vector2f size);
    
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Set the pokemon represented by the HealthBar
     * @param p a pointer to the pokemon
     */
    void setPokemon(Pokemon* p);
    
    
    /**
     * Set the HealthBar position on the screen
     * @param pos the position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the bar Color according to the health percentage
     */
    void setColor(float healthPercentage);
    
private:
    
//==================// Graphical attributes //=============//
    
    // Background Shape 
    sf::RectangleShape m_background;
    
    // Health bar shape 
    sf::RectangleShape m_bar;
};

#endif /* HEALTHBAR_HPP */

