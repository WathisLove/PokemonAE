/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightMenuSelector.hpp
 * Author: Redbuzard
 *
 * Created on 21 août 2018, 18:09
 */

#ifndef FIGHTMENUSELECTOR_HPP
#define FIGHTMENUSELECTOR_HPP

#include <SFML/Graphics.hpp>
#include "../Context.hpp"

class FightMenuSelector : public sf::Drawable{
public:
//=================// Public enum //==================//
    enum FightChoice{
        AttacksFC,
        BagFC,
        FleeFC,
        PokemonsFC
    };
    
    
//=================// Constructors //==================//
    
    FightMenuSelector(Context& context);
    
    
//=================// Public functions //==================//
    
    /**
     * Overriden function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Manage the incoming events
     */
    void manageEvents(sf::Event& event);
    
    
    /**
     * Reset the selected choice
     */
    void resetChoice();

    
//=================// Getters / Setters //==================//
    
    /**
     * Set the position of the FightMenuSelector
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    /**
     * @return true if the choice is selected
     */
    bool isSelected() const;
    
    /**
     * Set whether the choice is selected or not
     * @param isSelected as a boolean
     */
    void setSelected(bool isSelected);
    
    
    /**
     * @return the choice actually hovered or selected
     */
    FightChoice getChoice() const;
    
    
private:
//=================// Private functions //==================//
    
    /**
     * Updatet he texture rectangle of m_sprite
     */
    void updateTextureRect();
    
    
//=================// Attributes //==================//*
    // The hoveredmenu
    FightChoice m_choice;
    
    // Is the menu selected ?
    bool m_isSelected;
    
    
//=================// Graphical attributes //==================//
    sf::Sprite m_buttonSprite;
    sf::Sprite m_choiceSprite;
};

#endif /* FIGHTMENUSELECTOR_HPP */

