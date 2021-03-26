/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReactionInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 24 octobre 2020, 16:24
 */

#ifndef REACTIONINTERACTION_HPP
#define REACTIONINTERACTION_HPP


#include "Interaction.hpp"


class ReactionInteraction : public Interaction{
public:
    //=================// Constructor //==================//
    
    /**
     * Construct a reaction
     */
    ReactionInteraction(NpcID npc, int interactionNumber, ReactionType reaction);
    
    
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
    
    // The Reaction Type
    ReactionType m_reactionType;
};

#endif /* REACTIONINTERACTION_HPP */

