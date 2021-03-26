/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemInteraction.hpp
 * Author: Redbuzard
 *
 * Created on 26 octobre 2020, 17:19
 */

#ifndef ITEMINTERACTION_HPP
#define ITEMINTERACTION_HPP

#include "Interaction.hpp"
#include "../../ItemEnums.hpp"


class ItemInteraction : public Interaction{
public:
    //=================// Constructor //==================//
    
    /**
     * Constructs a Fight Interaction
     */
    ItemInteraction(NpcID npc, int interactionNumber, ItemID item, int number);
    
    
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

    // The item ID
    ItemID m_item;
    
    // The item number
    int m_number;
};

#endif /* ITEMINTERACTION_HPP */

