/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReactionState.hpp
 * Author: Redbuzard
 *
 * Created on 29 décembre 2018, 16:56
 */

#ifndef REACTIONSTATE_HPP
#define REACTIONSTATE_HPP

#include "State.hpp"
#include "../entities/ReactionBubble.hpp"


class ReactionState : public State{
public:
    ReactionState(StateStack* stack, Character* character, Entity* e, ReactionType reaction, float duration = 1.f);
    
    
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
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);

    
protected:
    // A pointer to the related Entity and to the character
    Entity* m_entity;
    Character* m_character;
    
    // Reaction Bubble
    ReactionBubble m_bubbleSprite;
    
    // Duration of the State, and current time passed
    float m_duration;
    float m_timePassed;
};

#endif /* REACTIONSTATE_HPP */

