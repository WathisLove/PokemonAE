#include "ChoiceMenu.hpp"
#include "../resources/TextureHolder.hpp"
#include "../resources/FontHolder.hpp"

ChoiceMenu::ChoiceMenu(Context& context) :
m_isOpened(false),
m_selectedEntry(0),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_teamMenuBackground)),
m_fontHolder(*context.getFontHolder()),
m_arrow(context.getTextureHolder()->getTexture(TextureHolder::ui_bagArrows)),
m_isActivated(true){
    m_arrow.setScale(0.5, 0.5);
    m_arrow.rotate(90);
    m_arrow.setTextureRect(sf::IntRect(0, 0, 32, 32));
}



void ChoiceMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw only if the menu is opened
    if(m_isOpened){
        target.draw(m_background, states);
    
        for(const sf::Text& t : m_texts){
            target.draw(t, states);
        }
        
        target.draw(m_arrow, states);
    }
}



void ChoiceMenu::handleKeyPressed(sf::Keyboard::Key key) {

    // Handle the keys if the menu is opened
    if(m_isOpened){
        // Choose an upper Entry
        if(key == sf::Keyboard::Z){
            m_selectedEntry = (m_selectedEntry+(m_texts.size()-1)) % m_texts.size();
            // Update the cursor position
            moveCursor();
        }
        // Choose an upepr Entry
        else if(key == sf::Keyboard::S){
            m_selectedEntry = (m_selectedEntry+1) % m_texts.size();
            // Update the cursor position
            moveCursor();
        }
    }
}



void ChoiceMenu::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    
    for(int i = 0; i < m_texts.size(); i++){
        m_texts.at(i).setPosition(pos + sf::Vector2f(15,5 + i*30));
    }
    
    // Update the cursor position
    moveCursor();
}



void ChoiceMenu::open() {
    if(!m_isActivated)
        throw "Can't open a menu deactivated";
    
    m_isOpened = true;
}



void ChoiceMenu::setActivated(bool val) {
    m_isActivated = val;
}



bool ChoiceMenu::isActivated() const {
    return m_isActivated;
}



bool ChoiceMenu::isOpen() {
    return m_isOpened;
}



void ChoiceMenu::selectLastEntry() {
    m_selectedEntry = m_texts.size()-1;
}



void ChoiceMenu::close() {
    m_isOpened = false;
    
    // Reset the selected entry
    m_selectedEntry = 0;
    
    // Update the cursor position
    moveCursor();
}



void ChoiceMenu::addEntry(const sf::String& txt) {
    m_texts.push_back(sf::Text(txt, m_fontHolder.getFont(FontHolder::dialogFont)));
    m_texts.at(m_texts.size()-1).setFillColor(sf::Color::Black);
    
    setPosition(m_background.getPosition());
}



const sf::Text& ChoiceMenu::getSelectedText() const {
    return m_texts.at(m_selectedEntry);
}



void ChoiceMenu::clearEntries() {
    m_texts.clear();
}



int ChoiceMenu::getSelectedEntry() const {
    return m_selectedEntry;
}



void ChoiceMenu::moveCursor() {
    m_arrow.setPosition(m_background.getPosition() + sf::Vector2f(13, 30*m_selectedEntry + 17));
}
