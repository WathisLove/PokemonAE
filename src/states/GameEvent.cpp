#include "GameEvent.hpp"

GameEvent::GameEvent(EventType type) :
m_type(type),
string(nullptr){
    if(type == EventType::NameChosen)
        string = new sf::String();
}


GameEvent::~GameEvent() {
    // Delete the string if set
    if(m_type == EventType::NameChosen)
        delete string;
}



EventType GameEvent::getType() const {
    return m_type;
}
