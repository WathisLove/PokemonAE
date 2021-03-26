#include "TeamEntry.hpp"
#include "../resources/FontHolder.hpp"
#include <iostream>

TeamEntry::TeamEntry(Context& context, Pokemon* p, sf::Vector2f pos) :
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_teamEntry), sf::IntRect(0,0,340,140)),
m_pokemonSprite(context.getTextureHolder()->getTexture(p->getPokemonTextureID(p->getID())), sf::IntRect(160, 0, 32, 32)),
m_nameText(p->getName(), context.getFontHolder()->getFont(FontHolder::dialogFont), 32),
m_HPText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_levelText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_ctLearnableText("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_pokemon(p),
m_itemDisplay(context),
m_mainStatus(context.getTextureHolder()->getTexture(TextureHolder::main_status)),
m_sexDisplay(context, p->getSex()),
m_isLearningCT(false){
    // Set the position for the background
    setPosition(pos);
    
    // Set the scale of the pokemon and object sprite
    m_pokemonSprite.setScale(50/32., 50/32.);
    m_mainStatus.setScale(1.6, 1.6);
    
    // Set the Health bar
    createHealthBar();
    
    // Set the XP Bar
    createXPBar();
    
    // Set the texts attributes
    createTexts();
    
    // Set  the pokemon status
    updateStatus();
}



void TeamEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    
    target.draw(m_pokemonSprite, states);
    
    
    
    target.draw(m_sexDisplay, states);
    
    // Draw the texts
    target.draw(m_nameText, states);
    target.draw(m_levelText, states);
    
    if(m_isLearningCT){
        target.draw(m_ctLearnableText, states);
    }
    else{
        target.draw(m_healthBar, states);
        target.draw(m_HPText, states);
        target.draw(m_xpBar, states);
    }
    
    // Draw the status
    if(m_showStatus)
        target.draw(m_mainStatus, states);
    
    // Draw the object if the pokemon is holding one
    if(m_pokemon->hasItem())
        m_itemDisplay.draw(target, states);
}



void TeamEntry::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    
    m_pokemonSprite.setPosition(pos + sf::Vector2f(15,15));
    
    // Set the bar positions
    m_healthBar.setPosition(pos + sf::Vector2f(27,77));
    m_xpBar.setPosition(pos + sf::Vector2f(26,115));
    
    // Texts
    m_nameText.setPosition(pos + sf::Vector2f(80, 15));
    m_HPText.setPosition(pos + sf::Vector2f(235, 68));
    m_levelText.setPosition(pos + sf::Vector2f(265, 102));
    m_ctLearnableText.setPosition(pos + sf::Vector2f(47,77));
    
    // Item sprite
    m_itemDisplay.setPosition(pos + sf::Vector2f(20,62));
    
    m_mainStatus.setPosition(pos + sf::Vector2f(60,58));
    
    
    m_sexDisplay.setPosition(pos + sf::Vector2f(60,10));
}



void TeamEntry::select(bool selected) {
    int left;
    
    // Move the texture rect if we are learning a CT
    if(m_isLearningCT)
        left = 340;
    else
        left = 0;
    
    if(selected){
        m_background.setTextureRect(sf::IntRect(left,140,340,140));
    }
    else{
        // check if the Pokemon is KO
        if(m_pokemon->isKO()){
            m_background.setTextureRect(sf::IntRect(left,420,340,140));
        }
        else{
            m_background.setTextureRect(sf::IntRect(left,0,340,140));
        }
    }
}



void TeamEntry::setLastSelected() {
    m_background.setTextureRect(sf::IntRect(0,280,340,140));
}



void TeamEntry::createHealthBar() {    
    // Set the color 
    float HPpercentage = m_pokemon->getHealthPercentage();
    
    // Under 20%
    if(HPpercentage<20) 
        m_healthBar.setFillColor(sf::Color(255, 0, 0));
    
    // Under 50%
    else if(HPpercentage<50) 
        m_healthBar.setFillColor(sf::Color(255, 180, 0));
    
    // Else
    else 
        m_healthBar.setFillColor(sf::Color(0, 255, 0));
    
    
    // Set the bar size (the bar is 200 pixels long)
    m_healthBar.setSize(sf::Vector2f(2. * HPpercentage, 16));
}



void TeamEntry::createXPBar() {    
    // Set the color 
    float XPPercentage = m_pokemon->getXPPercentage();
    
    
    // Set the fill color
    m_xpBar.setFillColor(sf::Color(0, 200, 230));
    
    
    // Set the bar size (the bar is 225 pixels long)
    m_xpBar.setSize(sf::Vector2f(2.25 * XPPercentage, 5));
}



void TeamEntry::updateItem() {
    if(m_pokemon->hasItem()){
        m_itemDisplay.setItem(m_pokemon->getItem());
    }
    
    updateStatus();
}



void TeamEntry::createTexts() {
    // Colors
    m_nameText.setFillColor(sf::Color::White);
    m_HPText.setFillColor(sf::Color::White);
    m_levelText.setFillColor(sf::Color::White);
    m_ctLearnableText.setFillColor(sf::Color::White);
    
    // Content
    // The name text is already defined in the constructor
    m_HPText.setString(toString(m_pokemon->getHealth()) + " / " + toString(m_pokemon->getStatValue(StatName::health)));
    m_levelText.setString(L"N° " + toWString(m_pokemon->getLevel()));
}



void TeamEntry::updateStatus() {
    MainStatusName name = m_pokemon->getMainStatus().getName();
    
    if(name == MainStatusName::NoMainStatus){
        m_showStatus = false;
    }
    else{
        m_showStatus = true;
        
        if(name == MainStatusName::Burn)
            m_mainStatus.setTextureRect(sf::IntRect(0, 0, 26, 10));
        else if(name == MainStatusName::Freeze)
            m_mainStatus.setTextureRect(sf::IntRect(0, 10, 26, 10));
        else if(name == MainStatusName::Paralysis)
            m_mainStatus.setTextureRect(sf::IntRect(0, 20, 26, 10));
        else if(name == MainStatusName::Poison)
            m_mainStatus.setTextureRect(sf::IntRect(0, 30, 26, 10));
        else if(name == MainStatusName::BadlyPoison)
            m_mainStatus.setTextureRect(sf::IntRect(0, 40, 26, 10));
        else // Sleep
            m_mainStatus.setTextureRect(sf::IntRect(0, 50, 26, 10));
    }
}



void TeamEntry::setToLearnCT(AttackID ctAttack) {
    m_isLearningCT = true;
    
    
    if(m_pokemon->getAttackSet().contains(ctAttack)){
        m_ctLearnableText.setString("Déjà appris");
        m_ctLearnableText.setFillColor(sf::Color(60, 255, 255));
    }
    else if(m_pokemon->canLearnByCT(m_pokemon->getID(), ctAttack)){
        m_ctLearnableText.setString("Apte");
        m_ctLearnableText.setFillColor(sf::Color::White);
    }
    else{
        m_ctLearnableText.setString("Pas apte");
        m_ctLearnableText.setFillColor(sf::Color::Red);
    }
    
    // Update the entry texture Rect to remove health and xp bars
    sf::IntRect rect = m_background.getTextureRect();
    rect.left = rect.width;
    
    m_background.setTextureRect(rect);
}
