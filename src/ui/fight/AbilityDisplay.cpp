#include "AbilityDisplay.hpp"
#include "../../resources/TextureHolder.hpp"
#include "../../resources/FontHolder.hpp"


AbilityDisplay::AbilityDisplay(Context& context) :
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_fightAbilityDisplay)),
m_text("", context.getFontHolder()->getFont(FontHolder::dialogFont), 16),
m_isDisplayed(false){
    // Setup the Text
    m_text.setFillColor(sf::Color::White);
}



void AbilityDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(m_isDisplayed){
        target.draw(m_background, states);
        target.draw(m_text, states);
    }
}



void AbilityDisplay::setDisplayedAbility(Pokemon* p, Team team) {
    // Set the positions
    if(team == Team::allied){
        m_background.setPosition(m_allyPos);
        m_text.setPosition(m_allyPos + sf::Vector2f(30, 0));
    }
    else{
        m_background.setPosition(m_ennemyPos);
        m_text.setPosition(m_ennemyPos + sf::Vector2f(30, 0));
    }
    
    // Set the text
    setText(p, team);
}



void AbilityDisplay::show(bool show) {
    m_isDisplayed = show;
}



void AbilityDisplay::setAllyPosition(sf::Vector2f allyPos) {
    m_allyPos = allyPos;
}



void AbilityDisplay::setEnnemyPosition(sf::Vector2f ennemyPos) {
    m_ennemyPos = ennemyPos;
}



void AbilityDisplay::setText(Pokemon* p, Team team) {
    if(team == Team::allied)
        m_text.setString(p->getAbility().getName() + L" de \n" + p->getName());
    else
        m_text.setString(p->getAbility().getName() + L" du \n" + p->getName() + L" ennemi");
}
