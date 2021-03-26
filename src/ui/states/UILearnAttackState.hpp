/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UILearnAttackState.hpp
 * Author: Redbuzard
 *
 * Created on 12 février 2020, 20:23
 */

#ifndef UILEARNATTACKSTATE_HPP
#define UILEARNATTACKSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../pokemon/TypeDisplay.hpp"
#include "../pokemon/VerticalAttackDisplay.hpp"
#include "../../fight/PokemonDisplay.hpp"
#include "../../pokemons/attacks/AttackDisplay.hpp"
#include "../../ui/pokemon/SexDisplay.hpp"

class UILearnAttackState : public sf::Drawable{
public:
    
//===================// Constructor  //===================//
    
    UILearnAttackState(Context& context, Pokemon* pokemon, AttackID attackLearning);
    
    
    virtual ~UILearnAttackState();

    
//===================// Public methods //===================//
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Select one of the attack
     * @param attackNum the attack number (0-3 for the attack already learnt, 4 for the new one)
     */
    void selectAttack(int attackNum);
    
//===================// Setters //===================//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    
private:
//===================// Private Methods //===================//
    
    /**
     * Setup the differents texts
     */
    void setupTexts();
    
//===================// Attributes //===================//
    
    // A reference to the context for graphical uses
    Context& m_context;
    
    // A pointer to the pokemon
    Pokemon* m_pokemon;
    
    // A pointer to the attack we want to learn
    Attack* m_learningAttack;
    
//===================// Graphical Attributes //===================//
    
    // The UI background
    sf::Sprite m_background;
    
    // A pokemon display for the concerned pokemon
    PokemonDisplay m_pokemonDisplay;
    
    // A vertical display for the attacks
    VerticalAttackDisplay m_attacksDisplay;
    
    // A display for the attack we want to learn
    AttackDisplay m_learnAttackDisplay;
    
    // A sprite for the selection
    sf::Sprite m_cursor;
    
    // A display for the pokemon types
    TypeDisplay m_firstType;
    TypeDisplay m_secondType;
    
    
    // Sprite for the sex
    SexDisplay m_sexDisplay;
    
    // Text for the Pokemon Name, and its level
    sf::Text m_nameText, m_levelText;
    
    // Array of Texts for the Statistics
    std::array<sf::Text, 5> m_statLabels;
    std::array<sf::Text, 5> m_statValues;
    
    
    // Texts for the current Attack
    sf::Text m_attackPower;
    sf::Text m_attackDescription;
};

#endif /* UILEARNATTACKSTATE_HPP */

