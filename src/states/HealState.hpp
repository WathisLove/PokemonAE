/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealState.hpp
 * Author: Redbuzard
 *
 * Created on 18 novembre 2020, 10:06
 */

#ifndef HEALSTATE_HPP
#define HEALSTATE_HPP

#include "State.hpp"


class HealState : public State{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     * @param stack a pointer to the stack
     */
    HealState(StateStack* stack, Character* character);
    
    
    /**
     * Draw the state
     */
    void draw() override;
    
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    bool update(float dt) override;
    
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    void actionOnCompletion() override;

    
private:    
    //=================// Attributes //==================//
    
    // A pointer Character 
    Character* m_character;
    
    // The time passed
    float m_timePassed;
    
    // The minimum time before leaving
    float m_timeBeforeLeaving;
};

#endif /* HEALSTATE_HPP */

