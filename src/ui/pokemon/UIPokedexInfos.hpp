/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIPokedexInfos.hpp
 * Author: Redbuzard
 *
 * Created on 21 avril 2020, 17:25
 */

#ifndef UIPOKEDEXINFOS_HPP
#define UIPOKEDEXINFOS_HPP

#include "TypeDisplay.hpp"
#include "../../fight/PokemonDisplay.hpp"


class UIPokedexInfos : public sf::Drawable{
public:
//===================// Constructor  //===================//
    
    /**
     * Constructor
     */
    UIPokedexInfos(Context& context);
    
    
//===================// Inherited methods  //===================//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//===================// Setters  //===================//
    
    
    /**
     * Set the UI position
     * @param pos the position of the Top left Corner
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the pokemon infos displayed
     * @param id the id of the pokemon captured
     * @param captured the number of times the pokemon was captured
     * @param saw the number of times the pokemon was seen
     */
    void setPokemon(PokemonID id, int captured, int saw);
    
    
private:
//===================// Private methods  //===================//
    
    
    /**
     * Setup the texts
     */
    void setupTexts();
    
    
//===================// Attributes  //===================//
    
    // A reference to the context
    Context& m_context;
    
//===================// Graphical Attributes  //===================//

    // Pokemon sprite
    PokemonDisplay m_pokemonDisplay;
    
    // Texts for the name, number, seens and captured
    sf::Text m_name, m_number, m_seen, m_captured;
    
    // Type displays
    TypeDisplay m_type1, m_type2;
};

#endif /* UIPOKEDEXINFOS_HPP */

