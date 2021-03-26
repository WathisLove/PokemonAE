/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIPokemonInfo.hpp
 * Author: Redbuzard
 *
 * Created on 20 janvier 2020, 19:10
 */

#ifndef UIPOKEMONINFO_HPP
#define UIPOKEMONINFO_HPP

#include <SFML/Graphics.hpp>

#include "../../Context.hpp"
#include "../../fight/PokemonDisplay.hpp"
#include "../pokemon/StatDisplay.hpp"
#include "../pokemon/VerticalAttackDisplay.hpp"
#include "../pokemon/PokeInfoDisplay.hpp"
#include "../pokemon/AttackInfoDisplay.hpp"
#include "../pokemon/HealthBar.hpp"
#include "../pokemon/XPBar.hpp"
#include "../pokemon/MainStatusDisplay.hpp"
#include "../pokemon/SexDisplay.hpp"
#include "../pokemon/TypeDisplay.hpp"



enum PokemonInfoPanel{
    TI_GlobalInfoPanel,
    TI_StatsPanel,
    TI_AttacksPanel
};


class UIPokemonInfo : public sf::Drawable {
public:
//==================// Constructor //=============//
    
    UIPokemonInfo(Context& context, Pokemon* pokemon);
    
    
//==================// Public Functions //=============//
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Show the global infos related to the pokemon
     */
    void showGlobalInfos();
    
    /**
     * Show the pokemon statistics
     */
    void showStats();
    
    /**
     * Show the pokemon Attacks
     */
    void showAttacks();
    
    
    /**
     * Show the next attack of the pokemon
     */
    void setAttackDetails(Attack* attack);
    
    /**
     * Set all attacks to a grey color except one
     * @param index the index of the attack we want to show
     */
    void setAttackGreyExcept(int index);
    
    /**
     * Set wether or not we must show the attack details
     * @param show true fi we must show the details, false otherwise
     */
    void showAttackDetails(bool show);
    
//==================// Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the displayed pokemon
     * @param poke a pointer to the new pokemon to be displayed
     */
    void setPokemon(Pokemon* poke);
    
    
private:
    
//==================// Private methods //=============//
    
    /**
     * Setup the text attributes
     */
    void setupTexts();
    
//==================// Attributes //=============//
    
    // A pointer to the current pokemon
    Pokemon* m_pokemon;
    
    // The current displayed panel
    PokemonInfoPanel m_currentPanel;
    
    // The index of the current attack Selected
    int m_currentAttack;
    
    // Boolean that stores if we show the attack infos
    bool m_showAttackDetails;

    
//==================// Graphical Attributes //=============//
    
    // A reference to the context for graphical uses
    Context& m_context;
    
    // Background Sprite
    sf::Sprite m_background;

    // The pokemon display
    PokemonDisplay m_pokemonDisplay;
    
    // Pokemon sex Display
    SexDisplay m_sexDisplay;
    
    // The pokemon name
    sf::Text m_pokemonName;
    
    // Health and XP Bars
    HealthBar m_healthBar;
    XPBar m_xpBar;
    
    // Texts for Level, XP and Health
    sf::Text m_level;
    sf::Text m_healthText;
    sf::Text m_xpText;
    
    // Status Display
    MainStatusDisplay m_status;
    
    // The StatDisplay for the current pokemon
    StatDisplay m_statDisplay;
    
    // Attack display for the current pokemon
    VerticalAttackDisplay m_attacksDisplay;
    
    // Attack Info showing the current attack name, description and type
    AttackInfoDisplay m_attackInfoDisplay;
    
    // Info Display specific infos
    PokeInfoDisplay m_infoDisplay;
    
    // A display for the pokemon types
    TypeDisplay m_firstType;
    TypeDisplay m_secondType;
    
};

#endif /* UIPOKEMONINFO_HPP */

