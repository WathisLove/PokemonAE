/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrainerState.hpp
 * Author: Redbuzard
 *
 * Created on 8 janvier 2019, 10:47
 */

#ifndef TRAINERSTATE_HPP
#define TRAINERSTATE_HPP

#include "State.hpp"
#include "../entities/Trainer.hpp"

class TrainerState : public State{
    
public:
    TrainerState(StateStack* stack, Character* character, Trainer* t);
    
    
    /**
     * Draw the state
     */
    virtual void draw();
    
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    
    
    /**
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);

    
protected:
    // A pointer to the trainer in question
    Trainer* m_trainer;
    
    // A pointer to the character 
    Character* m_character;
};

#endif /* TRAINERSTATE_HPP */

