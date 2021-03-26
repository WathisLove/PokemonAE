/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonMiniDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 31 décembre 2019, 12:03
 */

#ifndef POKEMONMINIDISPLAY_HPP
#define POKEMONMINIDISPLAY_HPP


#include <SFML/Graphics.hpp>
#include "../../pokemons/Pokemon.hpp"
#include "../../Context.hpp"

class PokemonMiniDisplay : public sf::Drawable{
public:
    
//==================// Constructor //=============//
    
    PokemonMiniDisplay(Context& context);
    
    
//==================// Inherited methods //=============//
    
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//==================// Public methods //=============//
    
    /**
     * Shows the display
     */
    void show();
    
    /**
     * Hides the display
     */
    void hide();
    
//==================// Setters //=============//
    
    /**
     * Set the display positon
     * @param pos the positon as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    /**
     * Set the display scale
     * @param scale the new scale as a float
     */
    void setScale(float scale);
    
    /**
     * Set the pokemon displayed
     * @param id the PokemonID of the new displayed pokemon
     */
    void setPokemon(PokemonID id);
    
    
    /**
     * Set the display to the standard color
     */
    void setStandardColor();
    
    /**
     * Set the display to a black color
     */
    void setBlackColor();
    
    
private:
//==================// Attributes //=============//
    
    // A reference to the context
    Context& m_context;
    
//==================// Graphical Attributes //=============//
    
    // The pokemon sprite
    sf::Sprite m_sprite;
    
    // A boolean to know if we must show the display
    bool m_isVisible;
};

#endif /* POKEMONMINIDISPLAY_HPP */

