#include "EvolutionStateUI.hpp"

#include <iostream>

UIEvolutionState::UIEvolutionState(Context& context, Pokemon* pokemon) : 
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_teamBackground)),
m_pokemonDisplay(context, pokemon, Team::ennemy),
m_context(context)
{
    m_pokemonDisplay.setZoomFactor(3.0);
}



void UIEvolutionState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_pokemonDisplay, states);
}



void UIEvolutionState::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    
    m_pokemonDisplay.setPosition(pos + sf::Vector2f(280, 180));
}



void UIEvolutionState::setPokemonDisplayed(Pokemon* pokemon) {
    m_pokemonDisplay.setPokemonTexture(m_context, pokemon);
}
