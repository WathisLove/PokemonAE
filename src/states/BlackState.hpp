/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BlackState.hpp
 * Author: Redbuzard
 *
 * Created on 11 août 2018, 11:40
 */

#ifndef BLACKSTATE_HPP
#define BLACKSTATE_HPP

#include <SFML/Graphics.hpp>
#include "State.hpp"


class BlackState : public State {
public:
//=================// Constructor //==================//
    /**
     * @param transitionTime negative if the transition must be reversed
     */
    BlackState(StateStack* stack, float lifeTime);
    
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
    float m_lifeTime;
    float m_actualTime;
    
    // Graphical attributes
    sf::RectangleShape m_rect;
};


#endif /* BLACKSTATE_HPP */

