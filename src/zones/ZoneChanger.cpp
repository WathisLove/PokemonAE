#include "ZoneChanger.hpp"

ZoneChanger::ZoneChanger(sf::IntRect rect, ZoneID id, sf::Vector2i newCharacterPos, Direction newDir) :
FieldObject(rect),
m_newCharacterPos(newCharacterPos),
m_newZoneID(id),
m_newZoneRect(0, 0, 0, 0),
m_newDir(newDir)
{
    
}

ZoneChanger::ZoneChanger(sf::IntRect rect, ZoneID id, sf::IntRect newZoneRect, Direction newDir) :
FieldObject(rect),
m_newCharacterPos(0, 0),
m_newZoneID(id),
m_newZoneRect(newZoneRect),
m_newDir(newDir){

}



sf::Vector2i ZoneChanger::getNewCharacterPos(sf::Vector2i characterPos) const  {
    if(m_newZoneRect == sf::IntRect(0, 0, 0, 0))
        return m_newCharacterPos;
    else
        return getNewCharacterPos(characterPos, m_newZoneRect);
}



ZoneID ZoneChanger::getNewZoneID() const  {
    return m_newZoneID;
}



sf::Vector2i ZoneChanger::getNewCharacterPos(sf::Vector2i characterPos, sf::IntRect newZoneRect) const {
    // Get the relative character position
    sf::Vector2i relativePos(characterPos.x-m_rect.left, characterPos.y-m_rect.top);
    
    sf::Vector2i newPos;
    
    newPos.x = newZoneRect.left + relativePos.x * (newZoneRect.width / m_rect.width);
    newPos.y = newZoneRect.top + relativePos.y * (newZoneRect.height / m_rect.height);
    
    return newPos;
}



Direction ZoneChanger::getNewDirection() const {
    return m_newDir;
}
