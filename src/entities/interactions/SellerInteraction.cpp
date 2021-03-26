#include <cassert>

#include "SellerInteraction.hpp"


SellerInteraction::SellerInteraction(NpcID npc, int interactionNumber) :
Interaction(npc, interactionNumber){

}



void SellerInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::SellerActionS)
        m_isFinished = true;
}



void SellerInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Check the Entity is not null and is a Seller
    assert(e != nullptr);
    assert(e->getType() == EntityType::Seller_Type);
    
    // Request a Seller State
    stack->requestStackPushSeller(e);
}
