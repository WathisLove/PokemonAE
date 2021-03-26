/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SelectAttackState.hpp
 * Author: Redbuzard
 *
 * Created on 25 mars 2021, 10:40
 */

#ifndef SELECTATTACKSTATE_HPP
#define SELECTATTACKSTATE_HPP

#include "State.hpp"
#include "../ui/pokemon/VerticalAttackDisplay.hpp"


class Pokemon;

class SelectAttackState : public State{
public:
    
    SelectAttackState(StateStack* stack, Pokemon* pokemon);
    
    
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
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);
    
    
private:
    // The state display
    VerticalAttackDisplay m_display;
    
    // Keep the pokemon
    Pokemon* m_pokemon;
};

#endif /* SELECTATTACKSTATE_HPP */

