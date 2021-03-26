#include "TypeDisplay.hpp"
#include "../../resources/TextureHolder.hpp"

TypeDisplay::TypeDisplay(Context& context, Type::TypeName type) :
m_typeDisplay(context.getTextureHolder()->getTexture(TextureHolder::ui_type)){
    // Set the Type
    setType(type);
}



void TypeDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_typeDisplay, states);
}



void TypeDisplay::setPosition(sf::Vector2f pos) {
    m_typeDisplay.setPosition(pos);
}



void TypeDisplay::setType(Type::TypeName type) {
    // Set the texture rect
    if(type == Type::TypeName::None){
        m_typeDisplay.setTextureRect(sf::IntRect(0,0,0,0));
    }
    else{
        int typeNum = (int)type;
        
        m_typeDisplay.setTextureRect(sf::IntRect(0, typeNum * 18, 58, 18));
    }
}
