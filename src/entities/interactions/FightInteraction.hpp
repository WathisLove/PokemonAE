/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 25 octobre 2020, 17:34
 */

#ifndef FIGHTINTERACTION_HPP
#define FIGHTINTERACTION_HPP

#include "Interaction.hpp"

class Trainer;

class FightInteraction : public Interaction {
public:
    /**
     * Constructs a Fight Interaction
     */
    FightInteraction(NpcID npc, int interactionNumber);
    
    
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

#endif /* FIGHTINTERACTION_HPP */

