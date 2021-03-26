/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeamEntry.hpp
 * Author: Redbuzard
 *
 * Created on 17 avril 2019, 11:32
 */

#ifndef TEAMENTRY_HPP
#define TEAMENTRY_HPP

#include <SFML/Graphics.hpp>
#include "../pokemons/Pokemon.hpp"
#include "../Context.hpp"
#include "../Constants.hpp"
#include "../inventory/ItemDisplay.hpp"
#include "../ui/pokemon/SexDisplay.hpp"


class TeamEntry : public sf::Drawable {
public:
    
    TeamEntry(Context& context, Pokemon* p, sf::Vector2f pos);
    
    //==================// Public Methods //===================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Set the position of the TeamEntry
     * @param pos the position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set wether or not the Entry must be selected
     * @param selected true if the entry is selected
     */
    void select(bool selected);
    
    
    /**
     * Set the Entry to display as the last selected
     */
    void setLastSelected();
    
    
    /**
     * Update the Item displayed
     */
    void updateItem();
    
    
    /**
     * Update the status displayed in the TeamState
     */
    void updateStatus();
    
    
    /**
     * Set the TeamEntry to show if the pokemon can learn a CT
     * @param ctAttack the AttackID of the attack contained in the CT
     */
    void setToLearnCT(AttackID ctAttack);
    
private:
    
    //==================// Private functions //===================//
    
    /**
     * Create the health bar and set its attributes
     */
    void createHealthBar();
    
    /**
     * Create the xp bar and set its attributes
     */
    void createXPBar();
    
    /**
     * Create the Texts and set their attributes
     */
    void createTexts();
    
    //==================// Attributes //===================//

    Pokemon* m_pokemon;
    
    // A booleant that stores if we must show the status
    bool m_showStatus;
    
    
    // Boolean to know if we are showing the CT compatibility
    bool m_isLearningCT;
    
    //==================// Graphical Attributes //===================//
    
    // Background for the entry
    sf::Sprite m_background;
    
    // Pokemon sprite
    sf::Sprite m_pokemonSprite;
    
    // Rectangle for the health bar
    sf::RectangleShape m_healthBar;
    
    // Rectangle for the xp bar
    sf::RectangleShape m_xpBar;
    
    // Texts for the name, the HPs and the level
    sf::Text m_nameText;
    sf::Text m_HPText;
    sf::Text m_levelText;
    
    // Text to show if the Ct is learnable
    sf::Text m_ctLearnableText;
    
    // Sex display
    SexDisplay m_sexDisplay;
    
    // Sprite for the object
    ItemDisplay m_itemDisplay;
    
    // MainStatus Sprite
    sf::Sprite m_mainStatus;
};

#endif /* TEAMENTRY_HPP */

