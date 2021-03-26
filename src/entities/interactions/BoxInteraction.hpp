/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoxInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 29 octobre 2020, 13:03
 */

#ifndef BOXINTERACTION_HPP
#define BOXINTERACTION_HPP

#include "Interaction.hpp"


class BoxInteraction : public Interaction {
public:
    //=================// Constructor //==================//
    
    /**
     * Constructs a Fight Interaction
     */
    BoxInteraction(NpcID npc, int interactionNumber);
    
    
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
    
private:
    //=================// Attributes //==================//
};

#endif /* BOXINTERACTION_HPP */

