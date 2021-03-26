/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HealInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 18 novembre 2020, 09:59
 */

#ifndef HEALINTERACTION_HPP
#define HEALINTERACTION_HPP

#include "Interaction.hpp"


class HealInteraction : public Interaction{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor
     */
    HealInteraction(NpcID npc, int interactionNumber);
    
    //=================// Public methods //==================//
    
    /**
     * Start an interaction
     * @param stack a parameter to the StateStack
     * @param e a pointer to the Entity concerned by the interaction
     */
    void startInteraction(StateStack* stack, Entity* e) const override;
    
    
    /**
     * Handle an incoming GameEvent
     * @param event a const reference to the Game event
     */
    void handleGameEvent(const GameEvent& event) override;

    
private:

};

#endif /* HEALINTERACTION_HPP */

