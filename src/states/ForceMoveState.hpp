/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ForceMoveState.hpp
 * Author: Redbuzard
 *
 * Created on 8 juin 2020, 09:58
 */

#ifndef FORCEMOVESTATE_HPP
#define FORCEMOVESTATE_HPP

#include "State.hpp"
#include "../entities/NPC.hpp"


class ForceMoveState : public State{
public:
    
    /**
     * Default constructor
     * NPC is a a pointer to the Npc that will be updated apart from the GameState
     * And target is the position the Npc will need to get to
     */
    ForceMoveState(StateStack* stack, Npc* npc, Character* character, sf::Vector2i target, bool repulseCharacter, Direction dir);
    
    
//=================// Public inherited methods //==================//
    
    /**
     * Overriden draw method
     */
    virtual void draw() override;

    /**
     * Handle the incoming Events
     * @param event a reference to the current Event
     * @return true if the next state must handle the event
     */
    virtual bool handleEvent(sf::Event& event) override;
    
    
    /**
     * Manage an incoming GameEvent
     * @param event a const reference to the GameEvent
     */
    void handleGameEvent(const GameEvent& event) override;

    
    /**
     * Act when the State is completed 
     * As we are in a DialogState we wait until a state request our result
     */
    virtual void actionOnCompletion() override;
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return true as we want the next states to be updated
     */
    virtual bool update(float dt);

    
private:
//=================// Private methods //==================//
    
    /**
     * Setup the NPC mover to reach target
     */
    void setupNpcMover();
    
//=================// Attributes //==================//
    
    // A pointer to the NPC the State moves
    Npc* m_npc;
    
    // The target position
    sf::Vector2i m_targetPos;
    
    // A pointer to the Character
    Character* m_character;
    
    // A boolean to know if we must repulse the Character at the end
    bool m_repulseCharacter;
    
    // Repulse direction
    Direction m_repulseDirection;
    
    // A boolean to know if we must update the GameState
    bool m_updateOtherStates;
};

#endif /* FORCEMOVESTATE_HPP */

