#include "UIPokemonInfo.hpp"

#include "../../resources/FontHolder.hpp"

#include <iostream>

UIPokemonInfo::UIPokemonInfo(Context& context, Pokemon* pokemon) :
m_context(context),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_teamInfo)),
m_pokemonDisplay(context, pokemon, Team::ennemy),
m_pokemonName(pokemon->getName(), context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_currentPanel(PokemonInfoPanel::TI_GlobalInfoPanel),
m_statDisplay(context, pokemon),
m_attacksDisplay(context, pokemon),
m_attackInfoDisplay(context, pokemon->getAttackSet().getAttack(0)),
m_infoDisplay(context, pokemon),
m_showAttackDetails(false),
m_healthBar(pokemon, sf::Vector2f(150, 8)),
m_xpBar(pokemon, sf::Vector2f(200, 4)),
m_status(context),
m_healthText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_xpText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_level("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_sexDisplay(context, pokemon->getSex()),
m_firstType(context, pokemon->getType().getFirstType()),
m_secondType(context, pokemon->getType().getSecondType()){

    
    m_pokemonName.setFillColor(sf::Color::Black);
    
    m_pokemonDisplay.setZoomFactor(1.5);
    m_status.setZoomFactor(1.2);
    
    setupTexts();
    
    showGlobalInfos();
}



void UIPokemonInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the Background
    target.draw(m_background, states);
    
    // Draw the pokemon and the other fixed infos
    target.draw(m_pokemonDisplay, states);
    target.draw(m_pokemonName, states);
    target.draw(m_healthBar, states);
    target.draw(m_healthText, states);
    target.draw(m_xpBar, states);
    target.draw(m_xpText, states);
    target.draw(m_status, states);
    target.draw(m_level, states);
    target.draw(m_sexDisplay, states);
    
    target.draw(m_firstType, states);
    target.draw(m_secondType, states);
    
    // Draw the elements associated with the current panel
    if(m_currentPanel == PokemonInfoPanel::TI_GlobalInfoPanel){
        m_infoDisplay.draw(target, states);
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_StatsPanel){
        m_statDisplay.draw(target, states);
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_AttacksPanel){
        m_attacksDisplay.draw(target, states);
        
        if(m_showAttackDetails)
            m_attackInfoDisplay.draw(target, states);
    }
}



void UIPokemonInfo::showGlobalInfos() {
    m_currentPanel = PokemonInfoPanel::TI_GlobalInfoPanel;
    
    // Update the textureRect
    m_background.setTextureRect(sf::IntRect(0, 0, 800, 600));
}



void UIPokemonInfo::showStats() {
    m_currentPanel = PokemonInfoPanel::TI_StatsPanel;
    
    // Update the textureRect
    m_background.setTextureRect(sf::IntRect(0, 600, 800, 600));
}



void UIPokemonInfo::showAttacks() {
    m_currentPanel = PokemonInfoPanel::TI_AttacksPanel;
    
    // Update the textureRect
    m_background.setTextureRect(sf::IntRect(0, 1200,800, 600));
}



void UIPokemonInfo::showAttackDetails(bool show) {
    m_showAttackDetails = show;
    
    if(!m_showAttackDetails){
        m_attacksDisplay.removeGreyColors();
    }
}



void UIPokemonInfo::setAttackGreyExcept(int index) {
    m_attacksDisplay.setGreyExcept(index);
}



void UIPokemonInfo::setAttackDetails(Attack* attack) {
    m_attackInfoDisplay.setAttack(attack);
}



void UIPokemonInfo::setPosition(sf::Vector2f pos) {

    // Background Position
    m_background.setPosition(pos);
    
    // Set the pokemon display and its releated infos
    m_pokemonDisplay.setPosition(pos + sf::Vector2f(55, 35));
    m_pokemonName.setPosition(pos + sf::Vector2f(220, 70));
    m_level.setPosition(pos + sf::Vector2f(380, 70));
    m_healthBar.setPosition(pos + sf::Vector2f(220, 100));
    m_healthText.setPosition(pos + sf::Vector2f(380, 98));
    m_xpBar.setPosition(pos + sf::Vector2f(215, 120));
    m_xpText.setPosition(pos + sf::Vector2f(240, 135));
    m_status.setPosition(pos + sf::Vector2f(200, 130));
    m_sexDisplay.setPosition(pos + sf::Vector2f(190,85));
    m_firstType.setPosition(pos + sf::Vector2f(60, 180));
    m_secondType.setPosition(pos + sf::Vector2f(120, 180));
    
    
    //===// Placing the panels
    
    // Info panel
    m_infoDisplay.setPosition(pos + sf::Vector2f(25,325));
    
    // Position for the Stat Display
    m_statDisplay.setPosition(pos + sf::Vector2f(160,445));
    
    // Positions for the attack related displays
    m_attacksDisplay.setPosition(pos + sf::Vector2f(100,325));
    m_attackInfoDisplay.setPosition(pos + sf::Vector2f(260,325));
    
}



void UIPokemonInfo::setPokemon(Pokemon* poke) {
    // Update the elements with the pokemon attributes
    m_pokemonDisplay.setPokemonTexture(m_context, poke);
    m_pokemonName.setString(poke->getName());
    m_infoDisplay.setPokemon(poke);
    m_statDisplay.setPokemon(poke);
    m_attacksDisplay.setPokemon(poke);
    m_healthBar.setPokemon(poke);
    m_xpBar.setPokemon(poke);
    m_status.setStatus(poke->getMainStatus());
    m_sexDisplay.setSex(poke->getSex());
    m_firstType.setType(poke->getType().getFirstType());
    m_secondType.setType(poke->getType().getSecondType());
    
    // Set the texts
    m_healthText.setString(toString(poke->getHealth()) + " / " + toString(poke->getStatValue(StatName::health)));
    m_xpText.setString(toString(poke->getXPCurrentLevel()) + " / " + toString(poke->getXPNextLevel()));
    m_level.setString(L"N° : " + toWString(poke->getLevel()));
}



void UIPokemonInfo::setupTexts() {
    // Set the colors
    m_xpText.setFillColor(sf::Color::Black);
    m_healthText.setFillColor(sf::Color::Black);
    m_level.setFillColor(sf::Color::Black);
}
