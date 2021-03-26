/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokeInfoDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 6 août 2019, 16:27
 */

#ifndef POKEINFODISPLAY_HPP
#define POKEINFODISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../../pokemons/Pokemon.hpp"
#include "../../Context.hpp"
#include "PokemonStatGraph.hpp"

class PokeInfoDisplay : public sf::Drawable{
public:

//===============// Constructors //===============//
    
    PokeInfoDisplay(Context& context, Pokemon* p);
    
    
//===============// Public Inherited methods //===============//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
//===============// Getters / Setters //===============//
    
    /**
     * Set the new pokemon to display its infos
     * @param p a pointer to the new pokemon
     */
    void setPokemon(Pokemon* p);
    
    /**
     * Set the position of the graphical attributes
     * @param pos the position of the topLeft corner as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
private:
//===============// Private methods //===============//
    
    /**
     * Setup all the Texts
     */
    void setupTexts();
    
    
//===============// Graphical Attributes //===============//
    // A reference to the context when updated
    Context& m_context;
    
    // Texts for the special ability
    sf::Text m_specialAbility;
    sf::Text m_specialAbilityDescription;
    
    // The Pokedex number
    sf::Text m_pokedexNumber;
    
    // Texts for the first Trainer who captured it
    sf::Text m_firstTrainer;
    
    // Level of encounter and capture zone
    sf::Text m_startLevel;
    sf::Text m_captureZone;
    sf::Text m_captureDate;
    
    // Pokemon natures
    sf::Text m_firstNature;
    sf::Text m_secondNature;
};

#endif /* POKEINFODISPLAY_HPP */

