#include "VerticalAttackDisplay.hpp"
#include <iostream>

VerticalAttackDisplay::VerticalAttackDisplay(Context& context, Pokemon* p) :
m_context(context),
m_currentSelected(0)
{
    setPokemon(p);
}



void VerticalAttackDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw each of the AttackDisplay
    for(AttackDisplay ad : m_attackDisplays){
        ad.draw(target, states);
    }
}



void VerticalAttackDisplay::setGreyExcept(int index) {
    for(int i = 0; i < m_attackDisplays.size(); i++){
        if(i == index){
            // Set the color to white
            m_attackDisplays.at(i).setFillColor(sf::Color::White);
        }
        else{
            // Set the color to grey
            m_attackDisplays.at(i).setFillColor(sf::Color(180,180,180));
        }
    }
    
    m_currentSelected = index;
}



void VerticalAttackDisplay::selectNext() {
    m_currentSelected = (m_currentSelected + 1) % m_attackDisplays.size();
    
    setGreyExcept(m_currentSelected);
}



void VerticalAttackDisplay::selectPrevious() {
    m_currentSelected = (m_currentSelected + m_attackDisplays.size() - 1) % m_attackDisplays.size();
    
    setGreyExcept(m_currentSelected);
}



int VerticalAttackDisplay::getSelected() const {
    return m_currentSelected;
}



void VerticalAttackDisplay::removeGreyColors() {
    for(int i = 0; i < m_attackDisplays.size(); i++){
        m_attackDisplays.at(i).setFillColor(sf::Color::White);
    }
}



void VerticalAttackDisplay::setPokemon(Pokemon* p) {
    m_attackDisplays.clear();
    
    // Get the AttackSet
    AttackSet& set = p->getAttackSet();
    
    for(int i = 0; i < set.getNbAttacks(); i++){
        // Add all the attacks as an AttackDisplay
        m_attackDisplays.push_back(AttackDisplay(m_context, set.getAttack(i)));
    }
    
    setPosition(m_pos);
}



void VerticalAttackDisplay::setPosition(sf::Vector2f pos) {
    m_pos = pos;
    
    for(int i = 0; i < m_attackDisplays.size(); i++){
        m_attackDisplays[i].setPosition(pos + sf::Vector2f(0, i*64));
    }
}