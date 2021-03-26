#include "TeamPreview.hpp"
#include <iostream>

TeamPreview::TeamPreview(Context& context) :
m_context(context),
m_position(2,2){
    std::cout << "Team Preview building" << std::endl;
    
    // Initialise the Preview Units
    for(int i = 0; i < 6; i++){
        m_units.at(i) = new TeamPreviewUnit(context);
    }
    
    setPosition(m_position);
    
    std::cout << "Team Preview Built" << std::endl;
}



TeamPreview::TeamPreview(Context& context, PokemonTeam* team) :
TeamPreview(context){
    std::cout << "Team Preview building 1" << std::endl;
    // For each pokemon of the team
    for(int i = 0; i < team->getNbPokemon(); i++){
        m_units.at(i) = new TeamPreviewUnit(context, team->getPokemonAt(i));
    }
    
    std::cout << "Team Preview Built 2" << std::endl;
}



TeamPreview::~TeamPreview() {
    for(TeamPreviewUnit* unit : m_units) delete unit;
}



void TeamPreview::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(TeamPreviewUnit* unit : m_units){
        unit->drawUnit(target, states);
    }
}



void TeamPreview::updatePreview(PokemonTeam* team) {
    // For each pokemon of the team
    int i = 0;
    for(; i < team->getNbPokemon(); i++){
        m_units.at(i)->updateUnit(team->getPokemonAt(i));
    }
    // For the remaining units
    for(; i < 6; i++){
        m_units.at(i)->updateUnit();
    }
}



void TeamPreview::setHealthVisible(bool visible) {
    // For each unit
    for(int i = 0; i < 6; i++){
        m_units.at(i)->setHealthVisible(visible);
    }
}



void TeamPreview::setOffsetUnit(int index, sf::Vector2f offset) {
    // Reset the position
    setPosition(m_position);
    
    // Set the Offset of a single unit
    m_units.at(index)->setOffset(offset);
}



void TeamPreview::setPosition(sf::Vector2f pos) {
    m_position = pos;
    
    // For each unit
    for(int i = 0; i < 6; i++){
        m_units.at(i)->setPosition(pos + sf::Vector2f(0, 33*i));
    }
}



void TeamPreview::setTopLeftPosition() {
    setPosition(m_context.getWindowTopLeftCorner() + sf::Vector2f(2,2));
}
