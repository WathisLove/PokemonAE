#include "StatDisplay.hpp"
#include "PokemonStatGraph.hpp"
#include "../../resources/FontHolder.hpp"
#include "../../resources/TextureHolder.hpp"

const float StatDisplay::m_textValueDistance = 95.;
const float StatDisplay::m_textNameDistance = 115.;



StatDisplay::StatDisplay(Context& context, Pokemon* p) :
m_statGraph(context, p->getStats()) 
{
    // Setup the texts
    setupTexts(context);
    
    setPokemon(p);
}



void StatDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw all the texts in the 2 arrays
    for(int i = 0; i < 6; i++){
        target.draw(m_statNames.at(i), states);
        target.draw(m_statValues.at(i), states);
        target.draw(m_statGraph, states);
    }
}



void StatDisplay::setPokemon(Pokemon* p) {
    // Set the stat values
    m_statValues[0].setString(toString(p->getHealth()) + "/" + toString(p->getStatValue(StatName::health)));
    m_statValues[1].setString(toString(p->getStatValue(StatName::attack)));
    m_statValues[2].setString(toString(p->getStatValue(StatName::defense)));
    m_statValues[3].setString(toString(p->getStatValue(StatName::speed)));
    m_statValues[4].setString(toString(p->getStatValue(StatName::special_defense)));
    m_statValues[5].setString(toString(p->getStatValue(StatName::special_attack)));
    
    m_statGraph.setStats(p->getStats());
}



void StatDisplay::setPosition(sf::Vector2f pos) {
    // Set the positions for all the texts in the 2 arrays
    for(int i = 0; i < 6; i++){
        m_statNames[i].setPosition(pos + m_statGraph.getDirectionVector(i) * m_textNameDistance);
        m_statValues[i].setPosition(pos + getNumDirectionVector(i) * m_textValueDistance);
    }
    
    m_statGraph.setPosition(pos);
}



void StatDisplay::setupTexts(Context& context) {
    // Create the texts and set the fonts, sizes and colors
    for(int i = 0; i < 6; i++){
        m_statNames[i] = CenteredText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16);
        m_statNames[i].setFillColor(sf::Color::Black);
        m_statValues[i] = CenteredText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16);
        m_statValues[i].setFillColor(sf::Color::Black);
    }
    
    // Set the Stat Names
    m_statNames[0].setString(L"PV");
    m_statNames[1].setString(L"Attaque");
    m_statNames[2].setString(L"Défense");
    m_statNames[3].setString(L"Vitesse");
    m_statNames[5].setString(L"Atk. Spé.");
    m_statNames[4].setString(L"Déf. Spé.");
}



sf::Vector2f StatDisplay::getNumDirectionVector(int statNum) {
    sf::Vector2f offset(0,0);
    
    if(statNum == 1 || statNum == 5)
        offset = sf::Vector2f(0, 0.1);
    else if(statNum == 2 || statNum == 4)
        offset = sf::Vector2f(0, -0.1);
    
    return m_statGraph.getDirectionVector(statNum) + offset;
}
