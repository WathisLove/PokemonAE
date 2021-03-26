/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokedexEntry.hpp
 * Author: Redbuzard
 *
 * Created on 16 avril 2020, 16:35
 */

#ifndef POKEDEXENTRY_HPP
#define POKEDEXENTRY_HPP

#include <SFML/Graphics.hpp>

#include "PokemonID.hpp"
#include "../Context.hpp"
#include "../ui/pokemon/PokemonMiniDisplay.hpp"

class PokedexEntry : public sf::Drawable{
public:
    
//===================// Constructor  //===================//
    
    /**
     * Constructor
     */
    PokedexEntry(Context& context, PokemonID pokemon);
    
//===================// Inherited methods  //===================//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//===================// Setters / Getters //===================//
    
    
    /**
     * Set the entry to show a captured pokemon
     */
    void setCaptured();
    
    /**
     * Set the entry to show an already saw pokemon
     */
    void setSaw();
    
    /**
     * Set the entry to show an unknown pokemon
     */
    void setUnknown();
    
    
    /**
     * Set the entry positon
     * @param pos the positon as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Get the Entry position
     * @return the position of the top left corner of the Entry background
     */
    sf::Vector2f getPosition();
    
private:
//===================// Graphical Attributes  //===================//
    
    // A boolean to know if the pokemon was captured
    bool m_isCaptured;
    
//===================// Graphical Attributes  //===================//
    
    // The Entry background
    sf::Sprite m_background;
    
    // A Pokemon miniature
    PokemonMiniDisplay m_miniature;
    
    // The Pokemon Name and number
    sf::Text m_name, m_number;
};

#endif /* POKEDEXENTRY_HPP */

