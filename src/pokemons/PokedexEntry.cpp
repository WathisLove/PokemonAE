#include "PokedexEntry.hpp"
#include "../resources/FontHolder.hpp"

PokedexEntry::PokedexEntry(Context& context, PokemonID pokemon) :
m_miniature(context),
m_isCaptured(true),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_pokedexEntry)),
m_name("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_number("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20)
{
    m_miniature.setPokemon(pokemon);
    
    
    // Setup the text
    m_name.setFillColor(sf::Color::Black);
    
    
    // Setup the pokemon name
    Pokemon* p = new Pokemon(pokemon, 1);
    m_name.setString(p->getName());
    delete p;
    
    // Pokemon number
    m_number.setFillColor(sf::Color::Black);
    m_number.setString(toString((int)(pokemon+1)));
}



void PokedexEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // Draw the elements
    target.draw(m_background, states);
    target.draw(m_miniature, states);
    target.draw(m_name, states);
    target.draw(m_number, states);
}



void PokedexEntry::setCaptured() {
    m_miniature.setStandardColor();
    m_isCaptured = true;
    
    m_background.setTextureRect(sf::IntRect(0, 40, 350, 40));
}



void PokedexEntry::setSaw() {
    m_miniature.setStandardColor();
    m_isCaptured = false;
    
    m_background.setTextureRect(sf::IntRect(0, 0, 350, 40));
}



void PokedexEntry::setUnknown() {
    m_miniature.setBlackColor();
    m_name.setString("???");
    m_isCaptured = false;
    
    m_background.setTextureRect(sf::IntRect(0, 0, 350, 40));
}



void PokedexEntry::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_miniature.setPosition(pos + sf::Vector2f(6, 6));
    m_name.setPosition(pos + sf::Vector2f(48, 6));
    m_number.setPosition(pos + sf::Vector2f(250, 6));
}



sf::Vector2f PokedexEntry::getPosition() {
    return m_background.getPosition();
}
