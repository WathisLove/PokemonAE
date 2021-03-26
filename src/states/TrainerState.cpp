/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrainerState.cpp
 * Author: Redbuzard
 * 
 * Created on 8 janvier 2019, 10:47
 */

#include "TrainerState.hpp"

TrainerState::TrainerState(StateStack* stack, Character* character, Trainer* t) :
State(stack),
m_trainer(t),
m_character(character)
{
    // Set the Satte ID
    m_id = StateID::TrainerS;
    
    // Change the trainer mover so it goes to the Character position
    m_trainer->setMover(new SequenceMover(t->getPosition(), m_character->getFacedCase(), 1.f/m_trainer->getSpeed()));
    
    
    // Set the Character direction
    character->setDirection(oppositeDirection(t->getDirection()));
}



void TrainerState::actionOnCompletion() {
    
    // Pop the Trainer State
    m_stack->requestStackPop();
    
    // Request an Interaction stage
    std::cout << "Should push EndFight Interaction ! " << std::endl;
    
    // Clear the Mover of the Entity so it doesn't move away
    m_trainer->clearMover();
}



bool TrainerState::update(float dt) {
    // Update the trainer
    m_trainer->update(dt);
    
    // Prevent the following States from updating
    return false;
}



bool TrainerState::handleEvent(sf::Event& event) {
    // Prevent the following States from handling events
    return false;
}



void TrainerState::draw() {
    // Nothing to do here, continue on you're way
}



bool TrainerState::isCompleted() const {
    // The state is completed once the trainer is looking at the Character
    return m_trainer->getFacedCase() == m_character->getPosition();
}
