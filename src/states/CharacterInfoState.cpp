#include "CharacterInfoState.hpp"


CharacterInfoState::CharacterInfoState(StateStack* stack, Character* character) :
State(stack),
m_ui(stack->getContext(), character){
    m_id = StateID::CharacterInfoS;
    
    // Set the UI Position
    m_ui.setPosition(stack->getContext().getWindowTopLeftCorner());
}



void CharacterInfoState::actionOnCompletion() {
    m_stack->requestStackPop();
}



void CharacterInfoState::draw() {
    // Get a reference to the window and draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_ui);
}



bool CharacterInfoState::handleEvent(sf::Event& event) {
    
    // Quit if we press Escape
    if(event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        
        if(key == sf::Keyboard::Escape)
            m_isCompleted = true;
    }
    
    return false;
}



bool CharacterInfoState::isCompleted() const {
    return m_isCompleted;
}



bool CharacterInfoState::update(float dt) {
    return false;
}
