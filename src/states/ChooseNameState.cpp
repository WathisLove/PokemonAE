#include "ChooseNameState.hpp"
#include <iostream>

ChooseNameState::ChooseNameState(StateStack* stack) :
State(stack),
m_nameChooser(stack->getContext()),
m_waitForConfirmation(false)
{
    m_id = StateID::ChooseNameS;
}



void ChooseNameState::draw() {
    // Get a reference to the window and draw the NameChoosher
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_nameChooser);
}



bool ChooseNameState::handleEvent(sf::Event& event) {
    // Check if we pressed Enter
    if(event.type == sf::Event::KeyPressed){
        // Get the Key
        sf::Keyboard::Key key = getKeyPressed(event);
        
        // Select the name and ask for confirmation
        if(!m_waitForConfirmation && key == sf::Keyboard::Return)
            selectName();
    }
    // Pass the event to the NameChooser
    m_nameChooser.handleEvent(event);
    
    
    return false;
}



void ChooseNameState::handleGameEvent(const GameEvent& event) {
    // Call inherited method
    State::handleGameEvent(event);
    
    if(event.getType() == EventType::ChoiceSelected){
        if(event.choice == 0) // If the first entry is selected
            confirmName();
        else
            unselectName();
    }
}



void ChooseNameState::actionOnCompletion() {
    // Pop the State
    m_stack->requestStackPop();
}



bool ChooseNameState::update(float dt) {
    return false;
}



const sf::String& ChooseNameState::getEnteredString() {
    return m_nameChooser.getString();
}



void ChooseNameState::selectName() {
    m_waitForConfirmation = true;
    
    m_stack->requestStackPushChoice(m_nameChooser.getString() + " vous convient ?");
}



void ChooseNameState::unselectName() {
    m_waitForConfirmation = false;
}



void ChooseNameState::confirmName() {
    m_isCompleted = true;
    
    // Send a GameEvent to close the choice State
    GameEvent* event = new GameEvent(EventType::RequestStateClosure);
    event->stateID = StateID::ChoiceS;
    m_stack->addGameEvent(event);
}



void ChooseNameState::displayCharacter() {
    m_nameChooser.displayCharacter();
}



void ChooseNameState::displayPokemon(PokemonID id) {
    m_nameChooser.displayPokemon(id);
}
