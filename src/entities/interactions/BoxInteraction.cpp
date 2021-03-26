#include "BoxInteraction.hpp"


BoxInteraction::BoxInteraction(NpcID npc, int interactionNumber) :
Interaction(npc, interactionNumber){

}



void BoxInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::BoxS)
        m_isFinished = true;
}



void BoxInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Push a Box State
    stack->requestStackPushBox();
}
