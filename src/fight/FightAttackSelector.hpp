/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightAttackSelector.hpp
 * Author: Redbuzard
 *
 * Created on 22 août 2018, 18:34
 */

#ifndef FIGHTATTACKSELECTOR_HPP
#define FIGHTATTACKSELECTOR_HPP

#include <array>
#include "../Context.hpp"
#include "../pokemons/Pokemon.hpp"
#include "../pokemons/attacks/AttackDisplay.hpp"

class FightAttackSelector : public sf::Drawable{
public:
//=================// Constructors //==================//
    
    FightAttackSelector(Context& context, Pokemon* p);
    
    virtual ~FightAttackSelector();

    
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
     * Update the AttackSelector
     * @param p a pointer to the pokemon
     */
    void update(Pokemon* p);
    
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
     * Set the choice of the Attack selector
     * @param choice as an int
     */
    void setChoice(int choice);
    
    /**
     * @return the choice actually selected as an int
     */
    int getChoice() const;
    
private:
//=================// Private functions //==================//
    
    /**
     * Update the choice sprite
     */
    void updateChoiceSprite();
    
        
//=================// Attributes //==================//
    // The actually hovered or selected choice
    int m_choice;
    int m_nbAttacks;
    
    // True if the attack is selected
    bool m_isSelected;
    
    // Array of AttackDisplays
    std::array<AttackDisplay*, 4> m_displays;
    
//=================// Graphical Attributes //==================//

    sf::Sprite m_choiceSprite;
};

#endif /* FIGHTATTACKSELECTOR_HPP */

