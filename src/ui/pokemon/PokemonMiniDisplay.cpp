#include "PokemonMiniDisplay.hpp"


PokemonMiniDisplay::PokemonMiniDisplay(Context& context) :
m_context(context),
m_isVisible(true){
    // Set the miniature texture rect
    m_sprite.setTextureRect(sf::IntRect(160, 0, 32, 32));
}



void PokemonMiniDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_isVisible)
        target.draw(m_sprite, states);
}



void PokemonMiniDisplay::show() {
    m_isVisible = true;
}



void PokemonMiniDisplay::hide() {
    m_isVisible = false;
}


void PokemonMiniDisplay::setPokemon(PokemonID id) {
    // Set the texture corresponding to the pokemo
    m_sprite.setTexture(m_context.getTextureHolder()->getTexture(Pokemon::getPokemonTextureID(id)));
}



void PokemonMiniDisplay::setStandardColor() {
    m_sprite.setColor(sf::Color::White);
}



void PokemonMiniDisplay::setBlackColor() {
    m_sprite.setColor(sf::Color(20, 20, 20));
}



void PokemonMiniDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void PokemonMiniDisplay::setScale(float scale) {
    m_sprite.setScale(scale, scale);
}
