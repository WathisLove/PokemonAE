#include "PokedexState.hpp"

PokedexState::PokedexState(StateStack* stack, Character* character) :
State(stack),
m_character(character),
m_ui(stack->getContext(), character->getPokedex()),
m_entrySelected(0),
m_isEntrySelected(false)
{
    m_id = StateID::PokedexS;
    
    m_numberOfEntries = getPokedexSize();
    
    
    // Set the UI position
    m_ui.setPosition(m_stack->getContext().getWindowTopLeftCorner());
    m_ui.selectEntry(0);
}



void PokedexState::actionOnCompletion() {
    m_stack->requestStackPop();
}



void PokedexState::draw() {
    // Get a reference to the window and draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_ui);
}



bool PokedexState::handleEvent(sf::Event& event) {
    // Check if we pressed a key
    if(event.type == sf::Event::KeyPressed){
        // Get the key
        sf::Keyboard::Key key = event.key.code;
        
        if(key == sf::Keyboard::Escape){
            // Unselect the pokemon
            if(m_isEntrySelected)
                m_isEntrySelected = false;
            // Quit if escape is pressed
            else
                m_isCompleted = true;
        }
        
        // S to move down
        else if(key == sf::Keyboard::S){
            down();
        }
        // Z to move up
        else if(key == sf::Keyboard::Z){
            up();
        }
        
        // Space to select an entry
        else if(key == sf::Keyboard::Space){
            select();
        }
    }
    
    return false;
}



bool PokedexState::update(float dt) {

    
    return false;
}



bool PokedexState::isCompleted() const {
    return m_isCompleted;
}



void PokedexState::down() {
    // Increase the Entry number
    m_entrySelected = (m_entrySelected+1) % m_numberOfEntries;
    
    // Update the UI
    m_ui.selectEntry(m_entrySelected);
}



void PokedexState::up() {
    // Decrease the Entry number
    m_entrySelected = (m_entrySelected + m_numberOfEntries - 1) % m_numberOfEntries;
    
    // Update the UI
    m_ui.selectEntry(m_entrySelected);
}



void PokedexState::select() {
    // Select or unselect
    m_isEntrySelected = !m_isEntrySelected;
    
    // Display the Infos or the list
    if(m_isEntrySelected) 
        m_ui.showInfos();
    else
        m_ui.showList();
}