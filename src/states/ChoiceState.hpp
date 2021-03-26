/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChoiceState.hpp
 * Author: Redbuzard
 *
 * Created on 19 mai 2019, 12:21
 */

#ifndef CHOICESTATE_HPP
#define CHOICESTATE_HPP

#include "DialogState.hpp"
#include "../ui/ChoiceMenu.hpp"

class ChoiceState : public DialogState {
public:
    
//=================// Constructors //==================//
    ChoiceState(StateStack* stack, Character* character, sf::String* str);
    
    ChoiceState(StateStack* stack, Character* character, sf::String* str, std::vector<sf::String*>* entries);
    
    
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
    
    
//=================// Public utility methods //==================//

    
    /**
     * Get the string selected
     * @return the texte of the entry selected as a wstring
     */
    std::wstring getResultString();

    /**
     * Get the Entry selected
     * @return the number of the entry as an int
     */
    int getEntrySelected();
    
    
    /**
     * Clear the entries of the menu
     */
    void clearEntries();
    
    /**
     * Reset the entries of the menu
     */
    void addEntry(std::wstring txt);
    
protected:
    
    
    /**
     * Select the current entry and send a GameEvent
     */
    void select();
    
//=================// Attributes //==================//
    // The menu to 
    ChoiceMenu m_menu;

};

#endif /* CHOICESTATE_HPP */

