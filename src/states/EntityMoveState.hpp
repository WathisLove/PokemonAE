/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityMoveState.hpp
 * Author: Redbuzard
 *
 * Created on 24 décembre 2020, 16:18
 */

#ifndef ENTITYMOVESTATE_HPP
#define ENTITYMOVESTATE_HPP

#include "State.hpp"


class EntityMoveState : public State {
public:

    /**
     * Default constructor
     * NPC is a a pointer to the Npc that will be updated apart from the GameState
     * And target is the position the Npc will need to get to
     */
    EntityMoveState(StateStack* stack, Entity* entity, EntityMover* mover);
    
    
//=================// Inherited methods //==================//
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
    
    
protected:
//=================// Attributes //==================//
    // The moving entity
    Entity* m_movingEntity;
    
    // A pointer to the mover
    EntityMover* m_mover;
};

#endif /* ENTITYMOVESTATE_HPP */

