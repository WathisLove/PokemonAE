#include "MoveInteraction.hpp"
#include "../movements/EntityMover.hpp"



MoveInteraction::MoveInteraction(NpcID npc, int interactionNumber, EntityMover* mover) :
Interaction(npc, interactionNumber),
m_mover(mover)
{
    
}



void MoveInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Push a MoveEntity State
    stack->requestStackPushEntityMove(e, m_mover);
}



void MoveInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::EntityMoveS)
        m_isFinished = true;
}
