#include "DialogState.hpp"
#include "../resources/FontHolder.hpp"
#include "../Context.hpp"
#include <iostream>
#include "../entities/NPC.hpp"
#include "../game_data/GameInfo.hpp"
#include "../Utilities.hpp"

DialogState::DialogState(StateStack* stack, Character* character, sf::String* string) :
State(stack),
m_string(string),
m_character(character),
m_uiSprite(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_dialog))
{   
    // Freeze the Character
    character->freeze(true);
        
    // Set the ID
    State::m_id = StateID::DialogS;
    
    // Set the Dialog
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    m_uiSprite.setOrigin(400, 300);
    m_uiSprite.setPosition(window.getView().getCenter());
    
    
    m_text.setFont(m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont));
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
    //m_text.setOrigin(0, 0);
    m_text.setPosition(window.getView().getCenter() + sf::Vector2f(-338, 204));
    
    // Set the Dialog string
    setDialogString();
}



DialogState::~DialogState() {
    delete m_string;
}



void DialogState::actionOnCompletion() {
    // Close the Dialog state
    m_stack->requestStackPop();
}



void DialogState::draw() {
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_uiSprite);
    window.draw(m_text);
}



bool DialogState::handleEvent(sf::Event& event) {
// Check if the player pushed Space to qui dialog
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            // Check if the player wants to interact
            case sf::Keyboard::Space:
                m_isCompleted = true;
                break;
        }
    }

    return false;
}



bool DialogState::update(float dt) {
    return false;
}



void DialogState::setDialogString() {
    // Get the dialog string
    std::wstring dialog = m_string->toWideString();
    
    // The marker we are looking for
    std::wstring marker(L"@charac");
    
    // The character name that will replace the marker
    std::wstring replacer(gamedata::characterName.toWideString());
    
    // Replace @charac by the character name
    replaceInString(dialog, marker, gamedata::characterName.toWideString());
    
    // Adapte Length
    adaptLength(dialog, 560);
    
    // Set the Text string
    m_text.setString(dialog);
}



void DialogState::adaptLength(std::wstring& str, float maxWidth) {
    // Copy the Text display
    sf::Text textDisplay(m_text);
    
    // Set the string
    textDisplay.setString(str);
    
    // If the text is too long
    if(textDisplay.getGlobalBounds().width > maxWidth){
        // Index of the last space found
        int lastSpace(0);
        int previousSpace(0);
        
        std::wstring s1(L"");
        
        textDisplay.setString(s1);
        
        int i = 0;
        while(i < str.size() && textDisplay.getGlobalBounds().width <= maxWidth){
            previousSpace = lastSpace;
            
            // Put the next word in s1
            for(; i < str.size(); i++){
                char c = str[i];
                s1 += c;
                
                // Save the last Space found and quit
                if(c == ' '){
                    lastSpace = i;
                    i++;
                    break;
                }
            }
            
            // Cut str and check the display size again
            s1 = str.substr(0, previousSpace);
            textDisplay.setString(s1);
        }
        
        str.insert(previousSpace+1, L"\n");
    }
}
