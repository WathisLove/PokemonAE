/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SexDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 18 décembre 2019, 21:17
 */

#ifndef SEXDISPLAY_HPP
#define SEXDISPLAY_HPP

#include <SFML/Graphics.hpp>

#include "../../Context.hpp"
#include "../../pokemons/PokemonSex.hpp"

class SexDisplay : public sf::Drawable{
public:
    
//===================// Constructor //===================//
    
    /**
     * Constructor with a specified sex
     * @param context a reference to the context
     * @param sex the pokemon sex as an enum
     */
    SexDisplay(Context& context, PokemonSex sex);
    
    
//===================// Inherited methods //===================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//===================// Setters //===================//
    
    
    /**
     * Set the Display position
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the displayed sex
     * @param sex the pokemon sex as an enum
     */
    void setSex(PokemonSex sex);
    
    
    
    /**
     * Set the sprite scale
     * @param scale the new scale as a float
     */
    void setScale(float scale);
    
private:
    
//===================// Attributes //===================//
    
    // Sex Sprite
    sf::Sprite m_sprite;
};

#endif /* SEXDISPLAY_HPP */

