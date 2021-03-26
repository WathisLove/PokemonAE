/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokedexState.hpp
 * Author: Redbuzard
 *
 * Created on 16 avril 2020, 16:07
 */

#ifndef POKEDEXSTATE_HPP
#define POKEDEXSTATE_HPP

#include "State.hpp"
#include "../entities/Character.h"
#include "../ui/states/UIPokedexState.hpp"

class PokedexState : public State{
public:
    
//==================// Constructor //=============//
    
    /**
     * Constructor
     */
    PokedexState(StateStack* stack, Character* character);
    
    
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
//==================// Private methods //=============//
    
    /**
     * Select the next entry
     */
    void down();
    
    /**
     * Select the previous entry
     */
    void up();
    
    
    /**
     * Select the current pokemon and show its infos
     */
    void select();
    
    
//==================// Attributes //=============//
    
    // A pointer to the Character
    Character* m_character;
        
    // The number of entries
    int m_numberOfEntries;
    
    // The current entry selected
    int m_entrySelected;
    
    // A boolean to know if we selected a pokemon or not
    bool m_isEntrySelected;
    
//==================// Graphical Attributes //=============//
    
    // The State UI
    UIPokedexState m_ui;
};

#endif /* POKEDEXSTATE_HPP */

