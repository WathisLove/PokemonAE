/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MoveInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 24 décembre 2020, 16:12
 */

#ifndef MOVEINTERACTION_HPP
#define MOVEINTERACTION_HPP

#include "Interaction.hpp"


class MoveInteraction : public Interaction {
public:
    
    /**
     * Constructor
     */
    MoveInteraction(NpcID npc, int interactionNumber, EntityMover* mover);

    
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
    
    // The Entity Mover
    EntityMover* m_mover;

};

#endif /* MOVEINTERACTION_HPP */

