#include "ForceMoveState.hpp"
#include "../entities/movements/SequenceMover.hpp"
#include "GameState.hpp"
#include "../utility/Logger.hpp"

ForceMoveState::ForceMoveState(StateStack* stack, Npc* npc, Character* character, sf::Vector2i target, bool repulseCharacter, Direction dir) :
State(stack),
m_npc(npc),
m_targetPos(target),
m_character(character),
m_repulseCharacter(repulseCharacter),
m_updateOtherStates(false),
m_repulseDirection(dir){
    // Set the State ID
    m_id = StateID::ForceMoveS;
    
    // Setup the mover
    setupNpcMover();
    
    // Freeze the Character
    character->freeze(true);
}



void ForceMoveState::actionOnCompletion() {
    // Pop the State
    m_stack->requestStackPop();
    
    // Remove the Npc Mover
    m_npc->setMover(new NoMover());
}



void ForceMoveState::draw() {
    // Nothing to draw !
}



bool ForceMoveState::handleEvent(sf::Event& event) {
    // Nothing to do
    // Prevent lower states to handle events
    return false;
}



void ForceMoveState::handleGameEvent(const GameEvent& event) {
    // If the interactions finished
    if(event.getType() == EventType::InteractionsFinished){
        // Complete the ForceMove State
        m_isCompleted = true;
        
        // If the character must be repelled
        if(m_repulseCharacter){
            // Create the Mover
            SequenceMover* m = new SequenceMover();

            // Move away from the Npc
            m->pushMove(EntityMover::goDirection(m_repulseDirection), 0.);

            // Deactivates the loop
            m->setLoop(false);

            // Set the Mover
            m_character->setMover(m);
            m_character->update(0);
        }
    }
}



bool ForceMoveState::update(float dt) {
    // Update the Entity
    m_npc->update(dt);
    
    // If the Entity reached the position, complete the State
    if(!m_isCompleted && !m_updateOtherStates && m_npc->getFacedCase() == m_targetPos){
        // Ask for an interaction
        GameEvent* event = new GameEvent(EventType::RequestInteraction);
        event->entity = m_npc;
        m_stack->addGameEvent(event);
        
        m_updateOtherStates = true;
    }

    // Prevent lower states from updating
    return m_updateOtherStates;
}



void ForceMoveState::setupNpcMover() {
    // Create a continuous mover from the Npc pos to the State target
    SequenceMover* mover = new SequenceMover(m_npc->getPosition(), m_targetPos, 1./m_npc->getSpeed());
    
    // Prevent the mover from repeting the sequence
    mover->setLoop(false);
    
    // Set the Mover
    m_npc->setMover(mover);
}
