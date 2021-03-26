#include <cassert>

#include "Interaction.hpp"

#include "../../states/StateStack.hpp"


std::map<InteractionCondition, std::function<bool(const Interaction*, Character*)> > Interaction::m_conditionFunctions {
    std::make_pair(InteractionCondition::DEFAULT, [](const Interaction* i, Character* c) 
    {
        return true;
    }),
    std::make_pair(InteractionCondition::UNIQUE, [](const Interaction* i, Character* c) 
    {
        return !c->metNPC(i->getNpcID());
    })
    
};



Interaction::Interaction(NpcID npc, int interactionNumber) :
m_npc(npc),
m_interactionNumber(interactionNumber),
m_nextInteraction(interactionNumber+1),
m_isFinished(false),
m_condition(InteractionCondition::DEFAULT){

}



NpcID Interaction::getNpcID() const {
    return m_npc;
}



int Interaction::getNumber() const {
    return m_interactionNumber;
}



int Interaction::getNext() const{
    return m_nextInteraction;
}



void Interaction::setNext(int nextInteraction) {
    m_nextInteraction = nextInteraction;
}



bool Interaction::isFinished() const {
    return m_isFinished;
}



void Interaction::reset() {
    m_isFinished = false;
}



void Interaction::setCondition(InteractionCondition condition) {
    m_condition = condition;
}



bool Interaction::conditionValid(Character* character) const {
    // Assert the condition is in the table
    assert(m_conditionFunctions.find(m_condition) != m_conditionFunctions.end());
    
    // Return the condition result
    return m_conditionFunctions[m_condition](this, character);
}
