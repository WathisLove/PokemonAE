/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   State.hpp
 * Author: Redbuzard
 *
 * Created on 4 juillet 2018, 10:40
 */

#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>
#include "StateStack.hpp"
#include "GameEvent.hpp"

class State {
public:
    State(StateStack* stack);
    virtual ~State();
    
    /**
     * Draw the state
     */
    virtual void draw() = 0;
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt) = 0;
    
    
    /**
     * A late update that occur after the update of the stages
     * It concerns all the stages and is mostly a utility method
     * @param dt time elapsed since last frame in seconds 
     */
    virtual void lateUpdate(float dt);
    
    
    /**
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion() = 0;
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);
    
    
    /**
     * Manage an incoming GameEvent
     * @param event a const reference to the GameEvent
     */
    virtual void handleGameEvent(const GameEvent& event);
    
    
    /**
     * @return the id of the state
     */
    virtual StateID getID() const;
    
    
    /**
     * Check if the State waits a special action before closing
     * @return ture if the State waits before closing
     */
    bool waitBeforeClosing();
    
    
    /**
     * Set if the state must wait before closing
     * @param wait true if the state must wait before closing
     */
    void waitBeforeClosing(bool wait);
    
    
    /**
     * Set the state to be a secondary state or not
     * @param val true if the state is a secondary state (false otherwise)
     */
    virtual void setAsSecondaryState(bool val = true);
    
    
    /**
     * Check if the state is a secondary one
     * @return true if the state is a secondary state
     */
    bool isSecondaryState();
    
    
    /**
     * Set the State to be shown or not
     * @param shown true if the state must be shown
     */
    void show(bool shown);
    
    
    /**
     * Set the State to let pass events to lower states
     * @param letPass true if the State must let pass events
     */
    void letEventPass(bool letPass);
    
    
    /**
     * Set the state to ignore event management
     * @param ignore true if the state must ignore events
     */
    void ignoreEvents(bool ignore);
    
    
protected:
//=================// Private methods //==================//
    
    
    void requestStackPush(StateID id);
    
    void requestStackPop();
    
    void requestStackClear();
    
    
    /**
     * Get the key pressed in a game event
     * @param event a reference to the game event
     * @return the key as a Keyboad Key
     */
    sf::Keyboard::Key getKeyPressed(sf::Event& event);
    
    /**
     * Get the RenderWindow from the stack context
     * @return a reference to the render window
     */
    sf::RenderWindow& getRenderWindow();
    
//=================// Attributes //==================//
    // A pointer to the stack
    StateStack* m_stack;
    
    // A boolean that stores wether the state is completed or not
    bool m_isCompleted;
    
    // ID of the State
    StateID m_id;
    
    // A boolean that stores if a state wait before beeing popped
    bool m_waitBeforeClosing;
    
    // A boolean that stores if the state is a secondary one or not
    bool m_isSecondaryState;
    
    // A boolean to know if the state is shown or not
    bool m_isShown;
    
    // A boolean to know if the state let pass events to lower states or not
    bool m_letEventsPass;
    
    // A boolean to know if the state should ignore events
    bool m_ignoreEvents;
};

#endif /* STATE_HPP */

