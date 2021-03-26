#include "NameChooser.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "../../resources/FontHolder.hpp"
#include <iostream>

NameChooser::NameChooser(Context& context) :
m_context(context),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_nameChooserBackground)){
    // Position
    m_background.setPosition(context.getWindowTopLeftCorner());
    m_currentName.setPosition(context.getWindowTopLeftCorner() + sf::Vector2f(205, 160));
    
    // Setup the texts
    setupText();
}



void NameChooser::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_currentName, states);
    target.draw(m_miniDisplay, states);
}



void NameChooser::handleEvent(sf::Event& event) {
    // Update the text
    if(event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        
        if(key == sf::Keyboard::BackSpace)
            removeCharacter();
    }
    else if(event.type == sf::Event::TextEntered){
        // Get the Text
        addCharacter(event.text.unicode);
    }
}



const sf::String& NameChooser::getString() {
    return m_currentName.getString();
}



void NameChooser::displayCharacter() {
    m_miniDisplay.setTexture(m_context.getTextureHolder()->getTexture(TextureHolder::character));
    m_miniDisplay.setTextureRect(sf::IntRect(16, 44, 16, 22));
    m_miniDisplay.setPosition(m_context.getWindowTopLeftCorner() + sf::Vector2f(140, 150));
    m_miniDisplay.setScale(2.5, 2.5);
}



void NameChooser::displayPokemon(PokemonID pokemon) {
    m_miniDisplay.setTexture(m_context.getTextureHolder()->getTexture(Pokemon::getPokemonTextureID(pokemon)));
    m_miniDisplay.setTextureRect(sf::IntRect(160, 0, 32, 32));
    m_miniDisplay.setPosition(m_context.getWindowTopLeftCorner() + sf::Vector2f(130, 150));
    m_miniDisplay.setScale(2, 2);
}



void NameChooser::removeCharacter() {
    // Get the current String
    sf::String str = m_currentName.getString();
    
    // Exit if there is no character to prevent a crash
    if(str.getSize() == 0)
        return;
    
    // Remove the last character 
    str.erase(str.getSize()-1, 1);
    
    // Set the new text
    m_currentName.setString(str);
    
    std::cout << "Removing character" << std::endl;
    std::cout << str.toAnsiString() << std::endl;;
}



void NameChooser::addCharacter(sf::Uint32 key) {
    // Only keep some characters
    if(key <= 31 || (key >= 127 && key <= 160) || key >= 256)
        return;
    
    // Get the current String
    sf::String str = m_currentName.getString();
    
    // Don't add a Character if there are already 24
    if(!canAddCharacter())
        return;
    
    str += key;
    
    // Set the new text
    m_currentName.setString(str);
    
    std::cout << "Added character " << static_cast<char>(key) << "(" << (int)key << ")" << std::endl;
    std::cout << str.toAnsiString() << std::endl;;
}



bool NameChooser::canAddCharacter() const {
    return m_currentName.getGlobalBounds().width <= 460;
}



void NameChooser::setupText() {
    // Fonts
    m_currentName.setFont(m_context.getFontHolder()->getFont(FontHolder::dialogFont));
    
    // Colors
    m_currentName.setFillColor(sf::Color::White);
    
    // Size
    m_currentName.setCharacterSize(32);
}
