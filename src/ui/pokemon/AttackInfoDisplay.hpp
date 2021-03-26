/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackInfoDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 9 août 2019, 16:51
 */

#ifndef ATTACKINFODISPLAY_HPP
#define ATTACKINFODISPLAY_HPP

#include "../../Context.hpp"
#include "../../pokemons/attacks/Attack.hpp"


class AttackInfoDisplay : public sf::Drawable{
public:
    
    AttackInfoDisplay(Context& context, Attack* attack);
    
    
//===============// Public Inherited methods //===============//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
//===============// Getters / Setters //===============//
    
    /**
     * Set the new attack to display its infos
     * @param p a pointer to the new attack
     */
    void setAttack(Attack* attack);
    
    /**
     * Set the position of the graphical attributes
     * @param pos the position of the topLeft corner as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
private:
//===============// Private methods //===============//
    
    /**
     * Setup the elements of the display
     */
    void setupDisplay();
    
    
//===============// Attributes //===============//
    
    // A reference to the context
    Context& m_context;
    
//===============// Graphical Attributes //===============//
    
    // Texts to display some Attacks infos
    sf::Text m_attackName;
    sf::Text m_attackDescription;
    
    // Texts for the precision and the Damages
    sf::Text m_accuracy;
    sf::Text m_damages;
    
    // The sprite to display the attack type (special, physical or none)
    sf::Sprite m_attackCategory;
    
    
};

#endif /* ATTACKINFODISPLAY_HPP */

