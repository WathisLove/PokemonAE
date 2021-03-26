/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SellerInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 29 octobre 2020, 14:04
 */

#ifndef SELLERINTERACTION_HPP
#define SELLERINTERACTION_HPP

#include "Interaction.hpp"


class SellerInteraction : public Interaction {
public:
    //=================// Constructor //==================//
    
    /**
     * Constructor for a Seller Interaction
     */
    SellerInteraction(NpcID npc, int interactionNumber);
    
    
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

#endif /* SELLERINTERACTION_HPP */

