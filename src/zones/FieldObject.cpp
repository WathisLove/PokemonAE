#include "FieldObject.hpp"

FieldObject::FieldObject(sf::IntRect rect) :
m_rect(rect){

}



bool FieldObject::isinsideRect(sf::Vector2i pos) const {
    return m_rect.contains(pos);
}



sf::IntRect FieldObject::getRect() const  {
        return m_rect;
}