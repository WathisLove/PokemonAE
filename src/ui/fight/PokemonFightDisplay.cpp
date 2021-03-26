#include "PokemonFightDisplay.hpp"

PokemonFightDisplay::PokemonFightDisplay(Context& context, Pokemon* p, Team team) :
m_context(context),
m_pokemon(p),
m_team(team),
m_pokeDisplay(context, p, team),
m_healthBar(context, p, team),
m_isVisible(true){

}



void PokemonFightDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_isVisible){
        target.draw(m_pokeDisplay, states);

        target.draw(m_healthBar, states);
    }
}



void PokemonFightDisplay::update() {
    m_healthBar.updateHealthBar(m_pokemon);
    m_healthBar.updateXPBar(m_pokemon);
    m_healthBar.updateStatus(m_pokemon->getMainStatus().getName());
}



void PokemonFightDisplay::setPokemon(Pokemon* p) {
    m_pokemon = p;
    
    // Set the new pokemon texture
    m_pokeDisplay.setPokemonTexture(m_context, m_pokemon);
    
    // Update the health bar
    m_healthBar.setPokemon(p);
}



void PokemonFightDisplay::setPosition(sf::Vector2f pos) {
    m_pokeDisplay.setPosition(pos + sf::Vector2f(0, 0));
    
    if(m_team == Team::allied){
        m_healthBar.setPosition(pos + sf::Vector2f(218, 50));
    }
    else{
        m_healthBar.setPosition(pos - sf::Vector2f(218, 50));
    }
    
}



void PokemonFightDisplay::setVisibility(bool val) {
    m_isVisible = val;
}
