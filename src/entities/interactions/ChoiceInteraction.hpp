/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ChoiceInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 29 novembre 2020, 10:28
 */

#ifndef CHOICEINTERACTION_HPP
#define CHOICEINTERACTION_HPP

#include "Interaction.hpp"
#include <vector>


class ChoiceInteraction : public Interaction{
public:
    //=================// Constructor / Destructor²²²²²²²²²²²²²²² //==================//
    
    /**
     * Construct a standard dialog interaction
     */
    ChoiceInteraction(NpcID npc, int interactionNumber, const std::string& dialog, const std::string& data);
    
    
    /**
     * Destructor
     */
    virtual ~ChoiceInteraction();

    
    //=================// Public methods //==================//
    
    /**
     * Start an interaction
     * @param stack a parameter to the StateStack
     */
    void startInteraction(StateStack* stack, Entity* e = nullptr) const override;
    
    
    /**
     * Get the number of the next interaction
     * @return the number of the next interaction as an int
     */
    int getNext() const override;

    
    /**
     * Handle an incoming GameEvent
     * @param event a const reference to the Game event
     */
    void handleGameEvent(const GameEvent& event) override;

    
protected:
    //=================// Private methods //==================//
    
    /**
     * Create the choices for the Choice Interaction
     * @param data a const reference to the string containing the data
     */
    void createChoices(const std::string& data);
    
    
    //=================// Choice structure //==================//
    
    /**
     * Structure to hold a choice
     */
    struct Choice{
        sf::String* str;
        int nextInteraction;
    };
    
    
    //=================// Attributes //==================//
    
    // A const reference to the String
    sf::String m_dialogLine;
    
    // Vector of choices
    std::vector<Choice> m_choices;
    
    // The next interaction chosen
    int m_nextInteraction;
};

#endif /* CHOICEINTERACTION_HPP */

