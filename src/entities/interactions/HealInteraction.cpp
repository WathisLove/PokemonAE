#include "HealInteraction.hpp"


HealInteraction::HealInteraction(NpcID npc, int interactionNumber) :
Interaction(npc, interactionNumber){

}



void HealInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Ask the Stack to 
    stack->requestStackPushHeal();
}



void HealInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::HealS)
        m_isFinished = true;
}
