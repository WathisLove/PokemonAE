/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CharacterInfoState.hpp
 * Author: Redbuzard
 *
 * Created on 5 avril 2020, 15:35
 */

#ifndef CHARACTERINFOSTATE_HPP
#define CHARACTERINFOSTATE_HPP

#include "../ui/states/UICharacterInfoState.hpp"
#include "State.hpp"

class CharacterInfoState : public State{
public:
    
//==================// Constructor //=============//
    
    /**
     * Constructor
     */
    CharacterInfoState(StateStack* stack, Character* character);
    
    
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
    
    
private:
    
//==================// Graphical Attributes //=============//
    
    // The State UI
    UICharacterInfoState m_ui;
    
};

#endif /* CHARACTERINFOSTATE_HPP */

