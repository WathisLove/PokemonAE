#include "PokemonDisplay.hpp"

PokemonDisplay::PokemonDisplay(Context& context, Pokemon* p, Team team) :
PokemonDisplay(context, p->getID(), team)
{
    
}



PokemonDisplay::PokemonDisplay(Context& context, PokemonID id, Team team) :
sf::Drawable(),
m_sprite(context.getTextureHolder()->getTexture(Pokemon::getPokemonTextureID(id))),
m_isDisplayed(true)
{
    if(team == Team::allied) {
        m_sprite.setTextureRect(sf::IntRect(80, 0, 80, 80));
        m_sprite.setScale(1.5, 1.5);
    }
    else 
        m_sprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
}



void PokemonDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_isDisplayed){
        // Apply texture
        states.texture = m_sprite.getTexture();

        // Draw the character sprite
        target.draw(m_sprite, states);
    }
}



void PokemonDisplay::display(bool isDisplayed) {
    m_isDisplayed = isDisplayed;
}



void PokemonDisplay::setPokemonTexture(Context& context, Pokemon* p) {
    // Look for the textureHolder and ask for the pokemon texture
    m_sprite.setTexture(context.getTextureHolder()->getTexture(p->getPokemonTextureID(p->getID())));
}



void PokemonDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void PokemonDisplay::setZoomFactor(float zoom) {
    m_sprite.setScale(zoom, zoom);
}
