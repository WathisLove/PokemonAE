/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIPokedexState.hpp
 * Author: Redbuzard
 *
 * Created on 16 avril 2020, 16:07
 */

#ifndef UIPOKEDEXSTATE_HPP
#define UIPOKEDEXSTATE_HPP

#include <SFML/Graphics.hpp>

#include "../../pokemons/PokedexEntry.hpp"
#include "../../pokemons/Pokedex.hpp"
#include "../pokemon/UIPokedexInfos.hpp"


class UIPokedexState : public sf::Drawable{
public:
    
//===================// Constructor  //===================//
    
    /**
     * Constructor
     */
    UIPokedexState(Context& context, Pokedex& pokedex);


    /**
     * Destructor
     */
    virtual ~UIPokedexState();

    
//===================// Inherited methods  //===================//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Select the Entry of a given number
     * @param number the number of the entry
     */
    void selectEntry(int number);
    
    
    /**
     * Show the pokemon infos 
     */
    void showInfos();
    
    
    /**
     * Show the pokedex list 
     */
    void showList();
    
    
//===================// Setters  //===================//
    
    
    /**
     * Set the UI position
     * @param pos the position of the Top left Corner
     */
    void setPosition(sf::Vector2f pos);
    
private:
//===================// Private methods  //===================//
    
    /**
     * Create the Pokedex entries
     */
    void createEntries();
    
    
    /**
     * Set the Entries positions
     * @param firstPosition the position of the first entry
     */
    void setEntriesPositions(sf::Vector2f firstPosition);
    
    
    /**
     * Updates the current description
     * @param id the Pokemon ID of the pokemon
     */
    void updateDescription(PokemonID id);
    
    
    /**
     * Setup the texts attributes
     */
    void setupTexts();
    
    
//===================// Graphical Attribute  //===================//
    
    // A reference to the context
    Context& m_context;
    
    // A reference to the Pokedex
    Pokedex& m_pokedex;
    
    // A boolean to know if we show the infos or the list
    bool m_showList;
    
    
//===================// Graphical Attribute  //===================//
    
    // Pokedex background
    sf::Sprite m_background;
    
    // UI for the current pokemon Infos
    UIPokedexInfos m_currentInfos;
    
    // A text for the total of pokemon seens and captured
    sf::Text m_totalSeen, m_totalCaptured;
    
    
    //===// Attributes for the Pokedex list //===//
    
    // Entry cursor
    sf::Sprite m_entryCursor;
    
    // A vector of Pokedex entries
    std::vector<PokedexEntry*> m_entries;
    
    
    //===// Attributes for the current Pokemon infos //===//
    
    // A text for the description
    sf::Text m_description;
};

#endif /* UIPOKEDEXSTATE_HPP */