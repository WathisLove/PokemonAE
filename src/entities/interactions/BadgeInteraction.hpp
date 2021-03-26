/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BadgeInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 2 novembre 2020, 14:06
 */

#ifndef BADGEINTERACTION_HPP
#define BADGEINTERACTION_HPP

#include "Interaction.hpp"


class BadgeInteraction : public Interaction{
public:
    /**
     * Constructor for a badge interaction
     */
    BadgeInteraction(NpcID npc, int interactionNumber, int badge);
    
    
private:
    
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
    // The Badge Number
    int m_badge;
};

#endif /* BADGEINTERACTION_HPP */

