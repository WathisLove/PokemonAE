/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeamPreview.hpp
 * Author: Redbuzard
 *
 * Created on 23 juillet 2018, 19:37
 */

#ifndef TEAMPREVIEW_HPP
#define TEAMPREVIEW_HPP

#include "../PokemonTeam.hpp"
#include "TeamPreviewUnit.hpp"

#include <array>
#include <SFML/Graphics.hpp>


class TeamPreview : public sf::Drawable{
public:
//=================// Constructors //==================//
    TeamPreview(Context& context);
    
    TeamPreview(Context& context, PokemonTeam* team);
    
    
    ~TeamPreview();
    
//=================// Inherited functions //==================//
    
    /**
     * Draw each of the units
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//=================// Public Functions //==================//
    
    /**
     * Update the sprites of all the units when the team changes
     * @param team the Pokemon team
     */
    void updatePreview(PokemonTeam* team);
    
    
    /**
     * Set wether the health bars are visible or not
     * @param visible true if the health bar are visible
     */
    void setHealthVisible(bool visible);
    
    
//=================// Setters //==================//
    
    /**
     * Adds an offset to a given unit
     * @param index the index of the TeamPreviewUnit
     * @param offset the given offset
     */
    void setOffsetUnit(int index, sf::Vector2f offset);
    
    
    /**
     * Set the TeamPreview position
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the TeamPreview position to the top left of the window
     */
    void setTopLeftPosition();
    
private:    
//=================// Attributes //==================//
    // A reference to the context
    Context& m_context;
    
    // Array of units to display each pokemon
    std::array<TeamPreviewUnit*, 6> m_units;
    
    // The position
    sf::Vector2f m_position;
};

#endif /* TEAMPREVIEW_HPP */

