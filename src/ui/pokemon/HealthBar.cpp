#include "HealthBar.hpp"



HealthBar::HealthBar(Pokemon* p, sf::Vector2f size) :
m_background(size)
{
    m_background.setOutlineThickness(1);
    
    setPokemon(p);
}



void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    target.draw(m_background);
    target.draw(m_bar);
}



void HealthBar::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_bar.setPosition(pos);
}



void HealthBar::setPokemon(Pokemon* p) {
    
    // Bar Size
    sf::Vector2f mainSize = m_background.getSize();
    sf::Vector2f barSize = sf::Vector2f(p->getHealthPercentage()*mainSize.x/100., mainSize.y);
    
    m_bar.setSize(barSize);
    
    // Bar color    
    setColor(p->getHealthPercentage());
}



void HealthBar::setColor(float healthPercentage) {
    
    if(healthPercentage < 20)
        m_bar.setFillColor(sf::Color::Red);
    else if(healthPercentage < 50)
        m_bar.setFillColor(sf::Color(255, 210, 0));
    else
        m_bar.setFillColor(sf::Color::Green);
    
    
    // Background color
    m_background.setFillColor(sf::Color(196, 196, 196));
    m_background.setOutlineColor(sf::Color(64, 64, 64));
}
