#include "DialogInteraction.hpp"


DialogInteraction::DialogInteraction(NpcID npc, int interactionNumber, const sf::String& line) :
Interaction(npc, interactionNumber),
m_dialogLine(line){

}



void DialogInteraction::startInteraction(StateStack* stack, Entity* e) const {
    stack->requestStackPushDialog(m_dialogLine);
}



void DialogInteraction::handleGameEvent(const GameEvent& event) {
    // Nothing to do here yet    
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::DialogS)
        m_isFinished = true;
}
