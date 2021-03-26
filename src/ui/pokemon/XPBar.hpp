/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XPBar.hpp
 * Author: Redbuzard
 *
 * Created on 5 octobre 2019, 14:40
 */

#ifndef XPBAR_HPP
#define XPBAR_HPP

#include <SFML/Graphics.hpp>
#include "../../pokemons/Pokemon.hpp"

class XPBar : public sf::Drawable{
public:
    
    XPBar(Pokemon* p, sf::Vector2f size);
    
    
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
private:
    
//==================// Graphical attributes //=============//
    
    // Bar Max Size
    sf::Vector2f m_maxSize;
    
    // Bar length as a float
    float m_length;
    
    // Bar represented by a vertex array
    sf::VertexArray m_bar;
};

#endif /* XPBAR_HPP */

