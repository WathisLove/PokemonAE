/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvolutionStateUI.hpp
 * Author: Redbuzard
 *
 * Created on 2 mars 2020, 20:24
 */

#ifndef EVOLUTIONSTATEUI_HPP
#define EVOLUTIONSTATEUI_HPP

#include "../../Context.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "../../fight/PokemonDisplay.hpp"


class UIEvolutionState : public sf::Drawable {
public:
//==================// Constructor //=============//
    
    /**
     * Constructor
     * @param context a reference to the context
     * @param pokemon a pointer to the pokemon displayed
     */
    UIEvolutionState(Context& context, Pokemon* pokemon);
    
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//==================// Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Display a pokemon
     * @param pokemon a pointer to the newly displayed pokemon
     */
    void setPokemonDisplayed(Pokemon* pokemon);
    
private:
//==================// Graphical Attributes //=============//
    
    // A reference to the context
    Context& m_context;
    
    // A sprite for the background
    sf::Sprite m_background;
    
    // A pokemon display 
    PokemonDisplay m_pokemonDisplay;
};

#endif /* EVOLUTIONSTATEUI_HPP */

