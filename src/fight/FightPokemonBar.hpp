/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightHealthBar.hpp
 * Author: Redbuzard
 *
 * Created on 20 août 2018, 17:44
 */

#ifndef FIGHTHEALTHBAR_HPP
#define FIGHTHEALTHBAR_HPP

#include <SFML/Graphics.hpp>
#include "../Enums.hpp"
#include "../Context.hpp"
#include "../pokemons/Pokemon.hpp"
#include "../ui/pokemon/MainStatusDisplay.hpp"
#include "../ui/pokemon/HealthBar.hpp"
#include "../ui/pokemon/XPBar.hpp"
#include "../ui/pokemon/SexDisplay.hpp"


class FightPokemonBar : public sf::Drawable{
public:
//=================// Constructors //==================//
    /**
     * @param dt is the side where the pokemon is displayed
     */
    FightPokemonBar(Context& context, Pokemon* p, Team team);
//=================// Public Functions //==================//
    /**
     * Overrided function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Setters //==================//
    
    /**
     * Set the pokemon linked to the fight bar
     * @param p a pointer to the pokemon linked to the bar
     */
    void setPokemon(Pokemon* p);
    
    /**
     * Update the pokemon health bar
     * @param p a pointer to the pokemon
     */
    void updateHealthBar(Pokemon* p);
    
    /**
     * Update the pokemon xp bar
     * @param p a pointer to the pokemon
     */
    void updateXPBar(Pokemon* p);
    
    
    /**
     * Set the position of the display on the screen
     * @param pos position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Update the main status displayed by the health bar
     * @param name the new status
     */
    void updateStatus(MainStatus name);
    
private:
//=================// Graphical attributes //==================//
    // Pokemon Name
    sf::Text m_name;
    
    // Pokemon Health text
    sf::Text m_health;
    
    // Pokemon Level
    sf::Text m_level;
    
    // Bar Sprite 
    sf::Sprite m_background;
    
    // Health and XP Bar
    HealthBar m_healthBar;
    XPBar m_xpBar;
    
    // MainStatus display
    MainStatusDisplay m_status;
    
    // The Pokemon Team
    Team m_team;
    
    // The Pokemon sex display
    SexDisplay m_sexDisplay;
};

#endif /* FIGHTHEALTHBAR_HPP */

