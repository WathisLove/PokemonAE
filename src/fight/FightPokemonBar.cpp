#include "FightPokemonBar.hpp"

#include "../resources/FontHolder.hpp"
#include "../resources/TextureHolder.hpp"

FightPokemonBar::FightPokemonBar(Context& context, Pokemon* p, Team team) :
sf::Drawable(),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_fightHealth)),
m_name(p->getName(), context.getFontHolder()->getFont(FontHolder::dialogFont), 18),
m_health("", context.getFontHolder()->getFont(FontHolder::dialogFont), 12),
m_level("", context.getFontHolder()->getFont(FontHolder::dialogFont), 14),
m_status(context),
m_team(team),
m_healthBar(p, sf::Vector2f(70,6)),
m_xpBar(p, sf::Vector2f(85,2)),
m_sexDisplay(context, p->getSex()){
    
    m_name.setFillColor(sf::Color::Black);
    m_level.setFillColor(sf::Color::Black);
    m_health.setFillColor(sf::Color::Black);
    
    // Set the bar position depending on the team,
    // and the position of the texts
    if(team == Team::allied){
        // Bars
        m_background.setTextureRect(sf::IntRect(0, 35, 130, 42));
    }
    else{
        // Bars
        m_background.setTextureRect(sf::IntRect(0, 0, 130, 35));
    }
    
    m_sexDisplay.setScale(0.2);
    
    setPokemon(p);
}



void FightPokemonBar::setPokemon(Pokemon* p) {
    // Set the name
    m_name.setString(p->getName());
    
    updateHealthBar(p);
    updateXPBar(p);
    updateStatus(p->getMainStatus());
    
    // Set the Sex display
    m_sexDisplay.setSex(p->getSex());
}



void FightPokemonBar::updateHealthBar(Pokemon* p) {
    float healthPercentage = p->getHealthPercentage();
    
    // Update the texts
    m_name.setString(p->getName());
    
    m_healthBar.setPokemon(p);
    
    updateStatus(p->getMainStatus());
    
    // Set the Health Text
    m_health.setString(toString(p->getHealth()) + "/" + toString(p->getStatValue(StatName::health)));
}



void FightPokemonBar::updateXPBar(Pokemon* p) {
    // The Xp bar is 85 pixels long
    m_xpBar.setPokemon(p);
    
    // Set the level Text
    m_level.setString(L"N°" + toWString(p->getLevel()));
}



void FightPokemonBar::setPosition(sf::Vector2f pos) {    
    // Set the position of the bar body
    m_background.setPosition(pos);
    
    m_status.setPosition(pos + sf::Vector2f(5,32));
    
    if(m_team == Team::allied){
        // Texts
        m_name.setPosition(pos + sf::Vector2f(18, 1));
        m_level.setPosition(pos + sf::Vector2f(104, 2));
        m_health.setPosition(pos + sf::Vector2f(22, 15));
        
        m_healthBar.setPosition(pos + sf::Vector2f(54, 23));
        m_xpBar.setPosition(pos + sf::Vector2f(35, 34));

        // Sex display
        m_sexDisplay.setPosition(pos + sf::Vector2f(100, 4));
    }
    else{
        m_healthBar.setPosition(pos + sf::Vector2f(6, 23));
        
        // Texts
        m_name.setPosition(pos + sf::Vector2f(4, 1));
        m_level.setPosition(pos + sf::Vector2f(80, 16));

        // Sex display
        m_sexDisplay.setPosition(pos + sf::Vector2f(85, 4));
    }
}



void FightPokemonBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the bar body
    states.texture = m_background.getTexture();
    target.draw(m_background, states);
    
    // Draw the bar content
    target.draw(m_healthBar);
    
    // draw the xp if it's an ally
    if(m_team == Team::allied){
        target.draw(m_xpBar);
        target.draw(m_health);
    }
    
    // Draw the texts
    target.draw(m_name);
    
    target.draw(m_level);
    
    target.draw(m_status);
    
    target.draw(m_sexDisplay);
}



void FightPokemonBar::updateStatus(MainStatus status) {
    m_status.setStatus(status);
}
