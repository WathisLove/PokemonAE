/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Interaction.hpp
 * Author: Redbuzard
 *
 * Created on 20 octobre 2020, 16:24
 */

#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "../NPCId.hpp"
#include "../../states/StateStack.hpp"
#include "../../states/GameEvent.hpp"
#include "../Character.h"
#include "InteractionCondition.hpp"

#include <map>
#include <functional>


class Character;


class Interaction {
public:
    //=================// Constructor //==================//
    
    /**
     * Construct a standard interaction
     */
    Interaction(NpcID npc, int interactionNumber);
    
    
    //=================// Public methods //==================//
    
    /**
     * Start an interaction
     * @param stack a parameter to the StateStack
     * @param e a pointer to the Entity concerned by the interaction
     */
    virtual void startInteraction(StateStack* stack, Entity* e) const = 0;
    
    
    /**
     * Handle an incoming GameEvent
     * @param event a const reference to the Game event
     */
    virtual void handleGameEvent(const GameEvent& event) = 0;
    
    
    /**
     * Get the Npc ID related to the Interaction
     * @return the NpcID 
     */
    virtual NpcID getNpcID() const;
    
    
    /**
     * Get the number of the interaction
     * @return the number as an int
     */
    int getNumber() const;
    
    
    /**
     * Get the Number of the next interaction
     * @return the interaction number + 1 by default
     */
    virtual int getNext() const;
    
    /**
     * Set the number of the next interaction
     * @param nextInteraction the number of the next interaction
     */
    void setNext(int nextInteraction);
    
    
    /**
     * Check if the Interaction is finished
     * @return true if the interaction is finished
     */
    virtual bool isFinished() const;
    
    
    /**
     * Reet the Interaction
     */
    virtual void reset();
    
    
    /**
     * Set the Interaction condition
     * @param condition the Interaction condition
     */
    void setCondition(InteractionCondition condition);
    
    
    /**
     * Check if the condition is valid
     * @param character a pointer to the character
     * @return true if the Interaction condition is valid
     */
    bool conditionValid(Character* character) const;
    
    
protected:   
    //=================// Static Attributes //==================//

    // Map of functions for conditions
    static std::map<InteractionCondition, std::function<bool(const Interaction*, Character*)> > m_conditionFunctions;
    
    
    //=================// Attributes //==================//
    
    // The Npc ID concerned by the Interaction
    NpcID m_npc;

    // The interaction number
    int m_interactionNumber;
    
    // Number of the next interaction
    int m_nextInteraction;
    
    // A boolean to know if the interaction is finished
    bool m_isFinished;
    
    // The Interaction Condition
    InteractionCondition m_condition;
};

#endif /* INTERACTION_HPP */

