/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BackHealerState.hpp
 * Author: Redbuzard
 *
 * Created on 31 octobre 2020, 17:33
 */

#ifndef BACKHEALERSTATE_HPP
#define BACKHEALERSTATE_HPP

#include "BlackState.hpp"
#include "DialogState.hpp"


class BackHealerState : public DialogState{
public:
    
    /**
     * Default constructor
     */
    BackHealerState(StateStack* stack, Character* character);
    
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
    // Boolean to know th dialog was closed
    bool m_dialogClosed;
    
    // The time passed
    float m_timePassed;

    // Graphical attributes
    sf::RectangleShape m_rect;
};

#endif /* BACKHEALERSTATE_HPP */

