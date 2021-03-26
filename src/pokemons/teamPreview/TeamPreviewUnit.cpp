#include "TeamPreviewUnit.hpp"

TeamPreviewUnit::TeamPreviewUnit(Context& context) :
m_context(context),
m_hasPokemonAssigned(false),
m_ballSprite(context.getTextureHolder()->getTexture(TextureHolder::ui_teamPreview), sf::IntRect(0, 32, 32, 32)),
m_pokemonSprite(context.getTextureHolder()->getTexture(TextureHolder::marcacrinTex), sf::IntRect(160, 0, 32, 32)),
m_healthBarBody(sf::Vector2f(5, 22)),
m_healthBarContent(sf::Vector2f(3, 20)),
m_healthVisible(true)
{
    
    setupHealthBar();
    updateUnit();
}



TeamPreviewUnit::TeamPreviewUnit(Context& context, Pokemon* p)  :
m_context(context),
m_hasPokemonAssigned(true),
m_ballSprite(context.getTextureHolder()->getTexture(TextureHolder::ui_teamPreview), sf::IntRect(0, 0, 32, 32)),
m_pokemonSprite(context.getTextureHolder()->getTexture(Pokemon::getPokemonTextureID(p->getID())), sf::IntRect(160, 0, 32, 32)),
m_healthBarBody(sf::Vector2f(5, 22)),
m_healthBarContent(sf::Vector2f(3, 20)),
m_healthVisible(true)
{
    
    setupHealthBar();
    updateUnit(p);
}



void TeamPreviewUnit::updateUnit() {
    m_hasPokemonAssigned = false;
    // Set the Ball Rectangle
    m_ballSprite.setTextureRect(sf::IntRect(0, 32, 32, 32));
}



void TeamPreviewUnit::updateUnit(Pokemon* p) {
    m_hasPokemonAssigned = true;
    // Set the Pokemon Texture
    m_pokemonSprite.setTexture(m_context.getTextureHolder()->getTexture(Pokemon::getPokemonTextureID(p->getID())));
    
    // Set the Ball Rectangle
    m_ballSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    
    // Set the Bar Color
    float HPpercentage = p->getHealthPercentage();
    if(HPpercentage<20) m_healthBarContent.setFillColor(sf::Color(255, 0, 0));
    else if(HPpercentage<50) m_healthBarContent.setFillColor(sf::Color(255, 180, 0));
    else m_healthBarContent.setFillColor(sf::Color(0, 255, 0));
    
    if(HPpercentage == 0) m_pokemonSprite.setColor(sf::Color(128, 128, 128));
    else m_pokemonSprite.setColor(sf::Color::White);
    
    // Change the Bar Length
    m_healthBarContent.setSize(sf::Vector2f(3, HPpercentage/5));
}



bool TeamPreviewUnit::hasPokemonAssigned() const {
    return m_hasPokemonAssigned;
}



void TeamPreviewUnit::setupHealthBar() {
    // Setup Bar Body
    m_healthBarBody.setFillColor(sf::Color(128, 128, 128, 200));
    m_healthBarBody.setOutlineColor(sf::Color(0, 0, 0, 100));
    m_healthBarBody.setOutlineThickness(-1);
    
    // Setup Bar Content
    m_healthBarContent.setRotation(180);
}



void TeamPreviewUnit::drawUnit(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // Draw the Ball
    states.texture = m_ballSprite.getTexture();
    target.draw(m_ballSprite, states);
    
    // If a pokmon was assigned then draw the pokemon sprite and the health
    if(m_hasPokemonAssigned){
        // Draw the Sprite
        states.texture = m_pokemonSprite.getTexture();
        target.draw(m_pokemonSprite, states);
        
        // Draw the Health Bar
        if(m_healthVisible){
            target.draw(m_healthBarBody);
            target.draw(m_healthBarContent);
        }
    }
}



void TeamPreviewUnit::setOffset(sf::Vector2f offset) {
    m_offset = offset;
    setPosition(m_ballSprite.getPosition() + offset);
}



void TeamPreviewUnit::setPosition(sf::Vector2f pos) {
    m_ballSprite.setPosition(pos);
    m_pokemonSprite.setPosition(pos);
    m_healthBarBody.setPosition(pos + sf::Vector2f(34, 5));
    m_healthBarContent.setPosition(pos + sf::Vector2f(38, 26));
}



void TeamPreviewUnit::setHealthVisible(bool visible) {
    m_healthVisible = visible;
}
