#include "SelectAttackState.hpp"
#include "../pokemons/Pokemon.hpp"


SelectAttackState::SelectAttackState(StateStack* stack, Pokemon* pokemon) :
State(stack),
m_display(stack->getContext(), pokemon),
m_pokemon(pokemon){
    // Set he ID
    m_id = StateID::SelectAttackS;
    
    m_display.setPosition(stack->getContext().getWindowTopLeftCorner());
    m_display.setGreyExcept(0);
}



void SelectAttackState::draw() {
    // Get the RenderWindow
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // Draw the Background
    window.draw(m_display);
}



bool SelectAttackState::update(float dt) {
    // Nothing to do here
    return false;
}



bool SelectAttackState::isCompleted() const {
    return m_isCompleted;
}



void SelectAttackState::actionOnCompletion() {
}



bool SelectAttackState::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Get the key code
        sf::Keyboard::Key key = event.key.code;
        
        if(key == sf::Keyboard::S)
            m_display.selectNext();
        else if(key == sf::Keyboard::Z)
            m_display.selectPrevious();
        
        // Quit
        else if(key == sf::Keyboard::Escape)
            m_isCompleted = true;
        
        // Choose attack
        else if(key == sf::Keyboard::Space){
             m_stack->requestStackPop();
            
            // create a Game Event for the attack selected
            GameEvent* event = new GameEvent(EventType::SelectingAttack);
            event->attack = m_pokemon->getAttackSet().getAttack(m_display.getSelected());
            m_stack->addGameEvent(event);
        }
    }
    
    return false;
}
