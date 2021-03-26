#include "BadgeInteraction.hpp"
#include "../Character.h"
#include "../../states/GameState.hpp"

BadgeInteraction::BadgeInteraction(NpcID npc, int interactionNumber, int badge) :
Interaction(npc, interactionNumber),
m_badge(badge){

}



void BadgeInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Get the Character
    Character* character = ((GameState*)stack->getStateOfID(StateID::GameS))->getCharacter();
    
    // Push a BadgeState for the Champion
    if(character->hasBadge(m_badge)){
        GameEvent* event = new GameEvent(EventType::StatePopped);
        event->stateID = StateID::BadgeS;
        stack->addGameEvent(event);
    }
    else{
        stack->requestStackPushBadge(m_badge);
    }
}



void BadgeInteraction::handleGameEvent(const GameEvent& event) {
    // Nothing to do here yet    
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::BadgeS)
        m_isFinished = true;
}
