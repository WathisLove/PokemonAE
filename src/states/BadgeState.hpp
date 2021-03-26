/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BadgeState.hpp
 * Author: Redbuzard
 *
 * Created on 9 avril 2020, 18:33
 */

#ifndef BADGESTATE_HPP
#define BADGESTATE_HPP

#include "State.hpp"
#include "../ui/states/UIBadgeState.hpp"

class Character;

class BadgeState : public State{
public:
    
//=================// Constructor //==================//
    
    /**
     * Default constructor
     */
    BadgeState(StateStack* stack, Character* character, int badgeNumber);
    
//=================// Public inherited methods //==================//
    
    /**
     * Overriden draw method
     */
    virtual void draw() override;

    /**
     * Handle the incoming Events
     * @param event a reference to the current Event
     * @return true if the next state must handle the event
     */
    virtual bool handleEvent(sf::Event& event) override;
    
    /**
     * Check if a choice was made by the player
     * @return true if a choice was made
     */
    virtual bool isCompleted() const override;

    /**
     * Act when the State is completed 
     * As we are in a DialogState we wait until a state request our result
     */
    virtual void actionOnCompletion() override;
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return true as we want the next states to be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * Late update the State
     * Used to detect when the dialog before was pushed
     * @param dt time elapsed since last frame
     */
    virtual void lateUpdate(float dt) override;

    
private:
//==================// Private methods //=============//
    
    
    /**
     * Push the dialog before the badge was gained
     */
    void pushBeginDialog();
    
    
    /**
     * Push the dialog once the badge was gained
     */
    void pushEndDialog();
    
    
//==================// Attributes //=============//
    
    // A boolean to kow if the dialog showed
    bool m_dialogShowed;
    
    // The badge displayed
    int m_badgeDisplayed;
    
    // The time passed in the State
    float m_timePassed;
    
    
//==================// Graphical Attributes //=============//
    
    // The State UI
    UIBadgeState m_ui;
};

#endif /* BADGESTATE_HPP */

