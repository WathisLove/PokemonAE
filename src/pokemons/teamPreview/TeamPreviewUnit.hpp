/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeamPreviewUnit.hpp
 * Author: Redbuzard
 *
 * Created on 21 juillet 2018, 13:53
 */

#ifndef TEAMPREVIEWUNIT_HPP
#define TEAMPREVIEWUNIT_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../Pokemon.hpp"

class TeamPreviewUnit {
public:
//=================// Attributes //==================//
    /**
     * Create a previewUnit with no pokemon Assigned
     */
    TeamPreviewUnit(Context& context);
    
    /**
     * Create a previewUnit with a pokemon Assigned
     */
    TeamPreviewUnit(Context& context, Pokemon* p);
    
    
    /**
     * Update the Unit when the team has changed
     */
    void updateUnit();
    /**
     * Update the Unit when the team has changed
     */
    void updateUnit(Pokemon* p);
    
    /**
     * Draw the Unit
     */
    void drawUnit(sf::RenderTarget& target, sf::RenderStates states) const;
    
//=================// Getters / Setters //==================//
    /**
     * @return true if a pokemon is assigned to the unit
     */
    bool hasPokemonAssigned() const;
    
    
    /**
     * Set the Unit position
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the Unit offset
     * @param offset the offset as a Vector2f
     */
    void setOffset(sf::Vector2f offset);
    
    
    
    /**
     * Set wether the health bars are visible or not
     * @param visible true if the health bar are visible
     */
    void setHealthVisible(bool visible);
    
    
private:
//=================// Private function //==================//    
    
    /**
     * Function that setup the healthBar body and content
     */
    void setupHealthBar();
    
//=================// Attributes //==================//
    // A reference to the context
    Context& m_context;
    
    // true if the unit has a pokemon assigned, false otherwise
    bool m_hasPokemonAssigned;
    
    // Health Visible
    bool m_healthVisible;
    
    // Unit Offset
    sf::Vector2f m_offset;
    
    // Graphical Attributes
    sf::Sprite m_ballSprite;
    sf::Sprite m_pokemonSprite;
    sf::RectangleShape m_healthBarBody;
    sf::RectangleShape m_healthBarContent;
};

#endif /* TEAMPREVIEWUNIT_HPP */

