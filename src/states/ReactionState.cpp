#include "ReactionState.hpp"

#include <iostream>

ReactionState::ReactionState(StateStack* stack, Character* character, Entity* e, ReactionType reaction, float duration) :
State(stack),
m_entity(e),
m_character(character),
m_timePassed(0),
m_duration(duration),
m_bubbleSprite(stack->getContext(), e->getSpriteCenter() + sf::Vector2f(0, -20), reaction)
{
    // Freeze the Character
    character->freeze(true);
        
    // Set the State ID
    m_id = StateID::ReactionS;
}



void ReactionState::draw() {
    // Get the window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // Draw the bubble
    window.draw(m_bubbleSprite);
}



bool ReactionState::update(float dt) {
    m_timePassed += dt;
    
    return false;
}



bool ReactionState::isCompleted() const {
    return m_timePassed >= m_duration;
}



bool ReactionState::handleEvent(sf::Event& event) {
    // If space key was pressed, quit the ReactionState by changing the time passed
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Space)
            m_timePassed = m_duration;
    }
    
    return false;
}



void ReactionState::actionOnCompletion() {
    m_stack->requestStackPop();
}
