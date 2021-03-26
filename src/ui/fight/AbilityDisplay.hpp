/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AbilityDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 2 août 2020, 11:23
 */

#ifndef ABILITYDISPLAY_HPP
#define ABILITYDISPLAY_HPP

#include <SFML/Graphics.hpp>

#include "../../Context.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "../../Enums.hpp"
#include "../../Utilities.hpp"


class AbilityDisplay : public sf::Drawable{
public:
//=================// Constructor //==================//
    
    /**
     * Constructor
     * @param context a reference to the context
     */
    AbilityDisplay(Context& context);
    

//=================// Inherited Method //==================//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//=================// Setters //==================//
    
    /**
     * Set the currently displayed team
     * @param p a pointer to the pokemon
     * @param ability a reference to the displayed ability
     * @param team the team that will be displayed
     */
    void setDisplayedAbility(Pokemon* p, Team team);
    
    
    /**
     * Set the Position of the Display for the ally
     * @param allyPos the position for the Ally
     */
    void setAllyPosition(sf::Vector2f allyPos);
    
    /**
     * Set the Position of the Display for the Ennemy
     * @param allyPos the position for the Ennemy
     */
    void setEnnemyPosition(sf::Vector2f ennemyPos);
    
    
    /**
     * Set if the Ability is displayed or not
     * @param show true if the Ability must be displayed
     */
    void show(bool show);
    
    
private:
//=================// Private methods //==================//
    
    /**
     * Set the Text for a given ability
     * @param p a pointer to the Pokemon
     * @param team the Team which has the Ability
     */
    void setText(Pokemon* p, Team team);
    
    
//=================// Attributes //==================//
    
    // The position for the Ally Team
    sf::Vector2f m_allyPos;
    
    // The position for the Ennemy Team
    sf::Vector2f m_ennemyPos;
    
    // A boolean to know if the Ability is displayed
    bool m_isDisplayed;
    
//=================// Graphical Attributes //==================//
    
    // The background sprite
    sf::Sprite m_background;
    
    // The Displayed text
    sf::Text m_text;
};

#endif /* ABILITYDISPLAY_HPP */

