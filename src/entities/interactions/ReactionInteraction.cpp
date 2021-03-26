#include "ReactionInteraction.hpp"


ReactionInteraction::ReactionInteraction(NpcID npc, int interactionNumber, ReactionType reaction) :
Interaction(npc, interactionNumber),
m_reactionType(reaction){

}



void ReactionInteraction::startInteraction(StateStack* stack, Entity* e) const {
    stack->requestStackPushReaction(e, m_reactionType);
}



void ReactionInteraction::handleGameEvent(const GameEvent& event) {
    // Nothing to do here yet    
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::ReactionS)
        m_isFinished = true;
}
