/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 20 octobre 2020, 16:48
 */

#ifndef DIALOGINTERACTION_HPP
#define DIALOGINTERACTION_HPP

#include <SFML/System/String.hpp>

#include "Interaction.hpp"


class DialogInteraction : public Interaction {
public:
    //=================// Constructor //==================//
    
    /**
     * Construct a standard dialog interaction
     */
    DialogInteraction(NpcID npc, int interactionNumber, const sf::String& line);
    
    
    //=================// Public methods //==================//
    
    /**
     * Start an interaction
     * @param stack a parameter to the StateStack
     */
    void startInteraction(StateStack* stack, Entity* e = nullptr) const override;

    
    /**
     * Handle an incoming GameEvent
     * @param event a const reference to the Game event
     */
    void handleGameEvent(const GameEvent& event) override;

    
protected:
    //=================// Attributes //==================//
    
    // A const reference to the String
    const sf::String& m_dialogLine;

};

#endif /* DIALOGINTERACTION_HPP */

