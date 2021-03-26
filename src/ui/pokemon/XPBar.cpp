#include "XPBar.hpp"

XPBar::XPBar(Pokemon* p, sf::Vector2f size) :
m_bar(sf::Quads, 4),
m_maxSize(size),
m_length(0){
    setPokemon(p);
    
    // Set the left colors
    m_bar[0].color = sf::Color(0,100,200);
    m_bar[3].color = sf::Color(0,100,200);
}



void XPBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_bar, states);
}



void XPBar::setPokemon(Pokemon* p) {
    // Get the xp percentage
    float xpPerc = p->getXPPercentage();
    
    // Get the topLeft position
    sf::Vector2f topLeft = m_bar[0].position;
    
    
    // Set the bar size
    m_length = xpPerc * m_maxSize.x / 100.;
    
    m_bar[1].position = topLeft + sf::Vector2f(m_length, 0);
    m_bar[2].position = topLeft + sf::Vector2f(m_length, m_maxSize.y);
    
    // Set the bar color from (0,100,200) to (0,200,200)
    sf::Color endColor = sf::Color(0, 100 + xpPerc, 200);
    
    m_bar[1].color = endColor;
    m_bar[2].color = endColor;
}



void XPBar::setPosition(sf::Vector2f pos) {    
    m_bar[0].position = pos;   
    m_bar[1].position = pos + sf::Vector2f(m_length, 0);   
    m_bar[2].position = pos + sf::Vector2f(m_length, m_maxSize.y);   
    m_bar[3].position = pos + sf::Vector2f(0, m_maxSize.y);
}
