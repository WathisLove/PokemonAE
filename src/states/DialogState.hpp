/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogState.hpp
 * Author: Redbuzard
 *
 * Created on 9 juillet 2018, 18:50
 */

#ifndef DIALOGSTATE_HPP
#define DIALOGSTATE_HPP

#include "State.hpp"
#include <SFML/Graphics.hpp>
#include "../entities/Entity.hpp"

class DialogState : public State{
public:
    DialogState(StateStack* stack, Character* character, sf::String* string);
    
    virtual ~DialogState();

    
    /**
     * Draw the state
     */
    virtual void draw();
    
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    

    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);

    
    
protected:
    
    /**
     * Set the dialog string
     */
    void setDialogString();
    
    /**
     * Adapt the string to not exceed a max width
     * @param str a const reference to the previous string
     * @param maxWidth the maximum width
     */
    void adaptLength(std::wstring& str, float maxWidth);
    
    
    // Dialog UI sprite
    sf::Sprite m_uiSprite;

    // The Dialog string
    sf::String* m_string;
    
    // A pointer to the Character
    Character* m_character;
    
    // Text displayed
    sf::Text m_text;
};

#endif /* DIALOGSTATE_HPP */

