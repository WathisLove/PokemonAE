/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 18 août 2018, 20:32
 */

#ifndef POKEMONDISPLAY_HPP
#define POKEMONDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../Enums.hpp"
#include "../Context.hpp"
#include "../pokemons/Pokemon.hpp"


class PokemonDisplay : public sf::Drawable{
public:
    
//=================// Constructors //==================//
    
    /**
     * Constructor with a pointer to the pokemon
     */
    PokemonDisplay(Context& context, Pokemon* p, Team team);
    
    /**
     * Constructor with the pokemon ID
     */
    PokemonDisplay(Context& context, PokemonID id, Team team);
    
    
//=================// Public Functions //==================//
    /**
     * Overrided function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Set the Display to be drawn or not
     * @param isDisplayed true if the display must be drawn
     */
    void display(bool isDisplayed);
    
    
//=================// Setters //==================//
    /**
     * Set the pokemon of the PokemonDisplay in the fight
     * @param pokeTexture a const reference to the pokemon texture
     */
    void setPokemonTexture(Context& context, Pokemon* p);
    
    
    /**
     * Set the position of the display on the screen
     * @param pos position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the zoom factor of the pokemon sprite
     * @param zoom the zoom factor as a float (greater than 1 means a bigger sprite)
     */
    void setZoomFactor(float zoom);
    
private:
//=================// Attributes //==================//
    
    // A boolean to know if we must draw the Display or not
    bool m_isDisplayed;
    
//=================// Graphical attributes //==================//
    
    // Pokemon sprite 
    sf::Sprite m_sprite;
};

#endif /* POKEMONDISPLAY_HPP */

