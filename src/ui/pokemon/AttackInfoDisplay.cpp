#include "AttackInfoDisplay.hpp"
#include "../../resources/FontHolder.hpp"
#include "../../resources/TextureHolder.hpp"


AttackInfoDisplay::AttackInfoDisplay(Context& context, Attack* attack) : 
m_context(context)
{
    setupDisplay();
    
    setAttack(attack);
}



void AttackInfoDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_attackName, states);
    target.draw(m_attackDescription, states);
    target.draw(m_attackCategory, states);
    target.draw(m_damages, states);
    target.draw(m_accuracy, states);
}



void AttackInfoDisplay::setAttack(Attack* attack) {
    m_attackName.setString(attack->getName());
    
    m_attackCategory.setTextureRect(attack->getCategoryTextureRect());
    
    m_attackDescription.setString(attack->getDescription());
    
    m_damages.setString(L"Dégats: " + toWString(attack->getDamage()));
    
    m_accuracy.setString(L"Précision : " + toWString(attack->getAccuracy()));
}



void AttackInfoDisplay::setPosition(sf::Vector2f pos) {
    m_attackName.setPosition(pos + sf::Vector2f(20, 20));
    m_attackDescription.setPosition(pos + sf::Vector2f(20, 120));
    m_attackCategory.setPosition(pos + sf::Vector2f(20, 40));
    m_damages.setPosition(pos + sf::Vector2f(150, 40));
    m_accuracy.setPosition(pos + sf::Vector2f(250, 40));
}



void AttackInfoDisplay::setupDisplay() {
    // Get a reference to the font
    const sf::Font& font = m_context.getFontHolder()->getFont(FontHolder::dialogFont);
    
    m_attackName = sf::Text("", font, 12);
    m_attackDescription = sf::Text("", font, 12);
    m_damages = sf::Text("", font, 12);
    m_accuracy = sf::Text("", font, 12);
    
    // Set the Texture for the attack category
    m_attackCategory.setTexture(m_context.getTextureHolder()->getTexture(TextureHolder::ui_attackCategory));
    // Dezoom the sprite
    m_attackCategory.setScale(0.5, 0.5);
    
    
    // Set the fill Colors
    m_attackName.setFillColor(sf::Color::Black);
    m_attackDescription.setFillColor(sf::Color::Black);
    m_damages.setFillColor(sf::Color::Black);
    m_accuracy.setFillColor(sf::Color::Black);
}
