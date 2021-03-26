#include "FightDialog.hpp"
#include "../resources/TextureHolder.hpp"
#include "../resources/FontHolder.hpp"

FightDialog::FightDialog(Context& context, sf::String str) :
sf::Drawable(),
m_bg(context.getTextureHolder()->getTexture(TextureHolder::ui_fightDialog)),
m_text(L"", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_isActive(true){
    m_text.setOrigin(-220, -351);
    m_text.setFillColor(sf::Color::Black);
    
    // Push the string in the queue
    addString(str);
}


FightDialog::FightDialog(Context& context) :
sf::Drawable(),
m_bg(context.getTextureHolder()->getTexture(TextureHolder::ui_fightDialog)),
m_text(L"", context.getFontHolder()->getFont(FontHolder::dialogFont), 22),
m_isActive(false){
    m_text.setOrigin(-220, -351);
    m_text.setFillColor(sf::Color::Black);
}



void FightDialog::setPosition(sf::Vector2f pos) {
    m_bg.setPosition(pos);
    m_text.setPosition(pos);
} 



void FightDialog::addString(sf::String str) {
    m_strings.push(str);
    
    // Check if this is the first dialog 
    if(m_strings.size() == 1){
        m_text.setString(str);
    }
}



void FightDialog::nextString() {
    // Pop the current string
    m_strings.pop();
    
    // If the queue is empty, unactivates the Dialog
    if(m_strings.empty()){
        m_isActive = false;
    }
    else{
        m_text.setString(m_strings.front());
    }
}



void FightDialog::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // Draw only if activated
    if(m_isActive){
        // Draw the background
        target.draw(m_bg, states);

        // Draw the text
        target.draw(m_text);
    }
}



bool FightDialog::isActive() const {
    return m_isActive;
}



void FightDialog::setActive(bool val)  {
    m_isActive = val;
}
