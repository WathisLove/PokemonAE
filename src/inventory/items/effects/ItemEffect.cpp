#include "ItemEffect.hpp"


ItemEffect::ItemEffect(ItemEffect::Type type) :
m_str(nullptr),
m_type(type){

}



ItemEffect::ItemEffect(ItemEffect::Type type, sf::String* str) :
m_type(type),
m_str(str){

}



ItemEffect::~ItemEffect() {
    if(hasString())
        delete m_str;
}



bool ItemEffect::hasString() const {
    return m_str != nullptr;
}



ItemEffect::Type ItemEffect::getType() const {
    return m_type;
}



const sf::String& ItemEffect::getString() const {
    return *m_str;
}
