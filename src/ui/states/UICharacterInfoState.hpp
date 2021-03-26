/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UICharacterInfoState.hpp
 * Author: Redbuzard
 *
 * Created on 5 avril 2020, 15:37
 */

#ifndef UICHARACTERINFOSTATE_HPP
#define UICHARACTERINFOSTATE_HPP

#include <SFML/Graphics.hpp>

#include "../../entities/Character.h"
#include "../BadgeBox.hpp"

class UICharacterInfoState : public sf::Drawable {
public:
//==================// Constructor //=============//
    
    /**
     * Constructor
     */
    UICharacterInfoState(Context& context, Character* character);
    
    
    
//==================// Public Functions //=============//
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
//==================// Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    
private:
//==================// Private methods //=============//
    
    
    /**
     * Setup the UI elements
     * @param context a reference to the context
     * @param character a pointer to the character
     */
    void setupUI(Context& context, Character* character);
    
    
    /**
     * Setup the Text elements
     * @param context a reference to the context
     * @param character a pointer to the character
     */
    void setupTexts(Context& context, Character* character);
    
    
//==================// Graphical Attributes //=============//
    
    // Sprite for the Background
    sf::Sprite m_background;
    
    // Sprite for the Character
    sf::Sprite m_characterSprite;
    
    // A Badge Box
    BadgeBox m_badges;
    
    // Texts for the Name, Money and Time played
    sf::Text m_characterName, m_money, m_timePlayed;
    
    // Texts for the pokemon saw and captured
    sf::Text m_pokemonSaw, m_pokemonCaptured;
};

#endif /* UICHARACTERINFOSTATE_HPP */

