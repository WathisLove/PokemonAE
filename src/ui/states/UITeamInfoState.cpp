#include "UITeamInfoState.hpp"

UITeamInfoState::UITeamInfoState(Context& context, PokemonTeam* team) :
UIPokemonInfo(context, team->getPokemonAt(0)),
m_team(team),
m_currentPokemon(0),
m_teamDisplay(context, team){
    m_teamDisplay.setHealthVisible(false);
}



void UITeamInfoState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Inherited method call
    UIPokemonInfo::draw(target, states);
    
    // Draw the team preview
    target.draw(m_teamDisplay, states);
}



void UITeamInfoState::setPosition(sf::Vector2f pos) {
    // Place the inhertied UI
    UIPokemonInfo::setPosition(pos);
    
    // Place the team display
    m_teamDisplay.setPosition(pos + sf::Vector2f(763, 5));
}



void UITeamInfoState::setCurrentPokemon(int pokemonIndex) {
    m_currentPokemon = pokemonIndex;
    
    // Get the new pokemon
    Pokemon* poke = m_team->getPokemonAt(m_currentPokemon);
    
    // Call the inherited method
    UIPokemonInfo::setPokemon(poke);
    
    // Set the offset of the selected pokemon
    m_teamDisplay.setOffsetUnit(pokemonIndex, sf::Vector2f(-20,0));
}