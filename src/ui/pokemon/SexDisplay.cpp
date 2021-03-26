#include "SexDisplay.hpp"

#include "../../resources/TextureHolder.hpp"

SexDisplay::SexDisplay(Context& context, PokemonSex sex) : 
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::ui_pokemonSex)){
    // Reduce the Sprite scale
    setScale(0.3);
    
    // Set the pokemon Sex
    setSex(sex);
}



void SexDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}



void SexDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void SexDisplay::setSex(PokemonSex sex) {
    if(sex == PokemonSex::Sx_None){
        m_sprite.setTextureRect(sf::IntRect(0,0,0,0));
    }
    else if(sex == PokemonSex::Sx_Male){
        m_sprite.setTextureRect(sf::IntRect(0,0,68,67));
    }
    else{
        m_sprite.setTextureRect(sf::IntRect(0,67,68,83));
    }
}



void SexDisplay::setScale(float scale) {
    m_sprite.setScale(scale, scale);
}
