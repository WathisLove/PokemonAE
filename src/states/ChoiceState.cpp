#include "ChoiceState.hpp"



ChoiceState::ChoiceState(StateStack* stack, Character* character, sf::String* str) :
DialogState(stack, character, str),
m_menu(stack->getContext()){
    m_id = StateID::ChoiceS;
    
    // Set the ChoiceState to wait before completion
    waitBeforeClosing(true);
    
    // Set the Menu
    m_menu.addEntry(L"Oui");
    m_menu.addEntry(L"Non");
    
    // Set the menu Position
    m_menu.setPosition(character->getSpriteCenter() + sf::Vector2f(200, 120));
    m_menu.open();
}



ChoiceState::ChoiceState(StateStack* stack, Character* character, sf::String* str, std::vector<sf::String*>* entries) :
ChoiceState(stack, character, str){
    // Add each entry
    clearEntries();
    
    // Add each entry to the menu
    for(sf::String* str: *entries)
        m_menu.addEntry(*str);
    
    delete entries;
}



bool ChoiceState::isCompleted() const {
    return m_isCompleted;
}



void ChoiceState::draw() {
    DialogState::draw();
    
    // Get a reference to the window and draw the Text
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_menu);
}



bool ChoiceState::handleEvent(sf::Event& event) {
    DialogState::handleEvent(event);
    
    if(event.type == sf::Event::KeyPressed){
        // Pass the key to the menu
        m_menu.handleKeyPressed(event.key.code);
        
        if(event.key.code == sf::Keyboard::Space)
            select();
    }

    return false;
}



void ChoiceState::actionOnCompletion() {
    // If we have recovered the result we do as a normal DialogState
    if(!m_waitBeforeClosing)
        DialogState::actionOnCompletion();
    
    // Otherwise we don't pop the state
}



int ChoiceState::getEntrySelected() {
    return m_menu.getSelectedEntry();
}



std::wstring ChoiceState::getResultString() {
    return m_menu.getSelectedText().getString().toWideString();
}



bool ChoiceState::update(float dt) {
    return m_waitBeforeClosing;
}



void ChoiceState::clearEntries() {
    m_menu.clearEntries();
}



void ChoiceState::addEntry(std::wstring txt) {
    m_menu.addEntry(txt);
}



void ChoiceState::select() {
    // Complete the State
    m_isCompleted = true;
    
    // Send a GameEvent
    GameEvent* event = new GameEvent(EventType::ChoiceSelected);
    event->choice = getEntrySelected();
    
    m_stack->addGameEvent(event);
}
