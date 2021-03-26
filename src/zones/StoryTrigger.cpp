#include "StoryTrigger.hpp"

StoryTrigger::StoryTrigger(sf::IntRect rect, NpcID npc, bool deactivatesAfterTrigger, Direction repulseDir) :
FieldObject(rect),
m_npcID(npc),
m_isActive(true),
m_deactivatesAfterTrigger(deactivatesAfterTrigger),
m_repulseDirection(repulseDir){

}



NpcID StoryTrigger::getNpc() {
    return m_npcID;
}



Direction StoryTrigger::getRepulseDir() const {
    return m_repulseDirection;
}



bool StoryTrigger::isinsideRect(sf::Vector2i pos) const {
    if(m_isActive)
        return FieldObject::isinsideRect(pos);
    
    // Return false if the story trigger is inactivated
    else 
        return false;
}



void StoryTrigger::setActive(bool active) {
    m_isActive = active;
}



bool StoryTrigger::deactivatesAfterTrigger() {
    return m_deactivatesAfterTrigger;
}
