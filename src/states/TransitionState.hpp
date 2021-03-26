/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TransitionState.hpp
 * Author: Redbuzard
 *
 * Created on 24 juillet 2018, 12:14
 */

#ifndef TRANSITIONSTATE_HPP
#define TRANSITIONSTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "../Direction.h"


class TransitionState : public State {
public:
//=================// Constructor //==================//
    /**
     * @param transitionTime negative if the transition must be reversed
     */
    TransitionState(StateStack* stack, Direction dir);
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    void actionOnCompletion() override;
    
    /**
     * Draw the state
     */
    void draw() override;
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    bool handleEvent(sf::Event& event) override;
    
    
    /**
     * Manage an incoming GameEvent
     * @param event a const reference to the GameEvent
     */
    void handleGameEvent(const GameEvent& event) override;
     
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    bool update(float dt) override;
    
    /**
     * @return true if the State must be popped
     */
    bool isCompleted() const override;
    
private:
//=================// Attributes //==================//    
    // transition time
    float m_transitionTime;
    float m_actualTime;
    
    // Direction
    Direction m_dir;
    
    // Graphical attributes
    sf::RectangleShape m_rect;
};

#endif /* TRANSITIONSTATE_HPP */

