/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChooseNameState.hpp
 * Author: Redbuzard
 *
 * Created on 30 août 2020, 10:52
 */

#ifndef CHOOSENAMESTATE_HPP
#define CHOOSENAMESTATE_HPP


#include "State.hpp"
#include "../ui/tools/NameChooser.hpp"


class ChooseNameState : public State{
public:
//=================// Constructor //==================//
    
    ChooseNameState(StateStack* stack);
    
    
//=================// Inherited methods //==================//
    
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
     * Manage an incoming GameEvent
     * @param event a const reference to the GameEvent
     */
    virtual void handleGameEvent(const GameEvent& event) override;

    
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
     * Displays the Character
     */
    void displayCharacter();
    
    /**
     * Displays a pokemon
     * @param id the PokemonID of the pokemon we want to display
     */
    void displayPokemon(PokemonID id);

    
//=================// Getters //==================//
    
    
    /**
     * Get the String chosen by the State
     * @return the string wrote by the user
     */
    const sf::String& getEnteredString();
    
private:
//=================// Private methods //==================//
    
    
    /**
     * Select the current name and wait for a confirmation
     */
    void selectName();
    
    
    /**
     * Unselect the current Name 
     */
    void unselectName();
    
    
    /**
     * Confirm the current name and close the State
     */
    void confirmName();
    
    
//=================// Attributes //==================//
    
    // A boolean to know if we are waiting for a confirmaton
    bool m_waitForConfirmation;
    
//=================// Graphical Attributes //==================//
    
    // A name chooser
    NameChooser m_nameChooser;
};

#endif /* CHOOSENAMESTATE_HPP */

