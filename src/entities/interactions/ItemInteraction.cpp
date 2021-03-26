#include "ItemInteraction.hpp"



ItemInteraction::ItemInteraction(NpcID npc, int interactionNumber, ItemID item, int number) :
Interaction(npc, interactionNumber),
m_item(item),
m_number(number){

}



void ItemInteraction::handleGameEvent(const GameEvent& event) {
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::ItemS)
        m_isFinished = true;
}



void ItemInteraction::startInteraction(StateStack* stack, Entity* e) const {
    stack->requestStackPushItemGiftState(m_item, m_number);
}
