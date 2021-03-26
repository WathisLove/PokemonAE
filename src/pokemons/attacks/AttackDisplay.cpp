#include "AttackDisplay.hpp"
#include "../../Utilities.hpp"
#include "../../resources/TextureHolder.hpp"
#include "../../resources/FontHolder.hpp"

AttackDisplay::AttackDisplay(Context& context, Attack* a) :
sf::Drawable(),
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::ui_attackBackground)),
m_nameText(a->getName(), context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_ppsText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_isEmpty(false){
    // Set the texts colors
    m_nameText.setFillColor(sf::Color::White);
    m_ppsText.setFillColor(sf::Color::White);
    
    // Set the position of the texts
    m_nameText.setOrigin(-14, -6);
    m_ppsText.setOrigin(-72, -26);
    
    // Set the text for the pps
    m_ppsText.setString("PP " + toString(a->getPP()) + "/" + toString(a->getPPMax()));
    
    setTextureRect(a->getType());
}




AttackDisplay::AttackDisplay(Context& context)  :
sf::Drawable(),
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::ui_attackBackground)),
m_nameText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_ppsText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_isEmpty(true){
    // Set the texts colors
    m_nameText.setFillColor(sf::Color::White);
    m_ppsText.setFillColor(sf::Color::White);
    
    // Set the position of the texts
    m_nameText.setOrigin(-14, -6);
    m_ppsText.setOrigin(-72, -26);
}



void AttackDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!m_isEmpty){
        // Draw the sprite
        states.texture = m_sprite.getTexture();
        target.draw(m_sprite, states);

        // Draw the texts
        target.draw(m_nameText);
        target.draw(m_ppsText);
    }
}



void AttackDisplay::update(Attack* a) {
    m_isEmpty = false;
    
    // Set the texts
    m_nameText.setString(a->getName());
    m_ppsText.setString("PP " + toString(a->getPP()) + "/" + toString(a->getPPMax()));
    
    setTextureRect(a->getType());
}



void AttackDisplay::update() {
    m_isEmpty = true;
}



void AttackDisplay::setTextureRect(const Type& type) {
    m_sprite.setTextureRect(sf::IntRect(0, ((int)type.getFirstType())*60, 160, 60));
}



void AttackDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
    m_ppsText.setPosition(pos);
    m_nameText.setPosition(pos);
}



sf::Vector2f AttackDisplay::getPosition() {
    return m_sprite.getPosition();
}



void AttackDisplay::setFillColor(sf::Color color) {
    m_sprite.setColor(color);
    m_nameText.setFillColor(color);
    m_ppsText.setFillColor(color);
}
