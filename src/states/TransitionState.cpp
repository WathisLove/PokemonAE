#include "TransitionState.hpp"
#include "../Constants.hpp"
#include "../Context.hpp"


TransitionState::TransitionState(StateStack* stack, Direction dir) :
State(stack),
m_actualTime(0),
m_transitionTime(0.15),
m_dir(dir),
m_rect(sf::Vector2f(0, 0))
{
    // set the ID
    m_id = StateID::TransitionS;
    
    m_rect.setFillColor(sf::Color::Black);
    
    // Set the rect position
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    sf::View v = window.getView();
    if(m_dir == Direction::South || m_dir == Direction::East){
        sf::Vector2f pos = v.getCenter() - sf::Vector2f(v.getSize().x/2.f, v.getSize().y/2.f);
        m_rect.setPosition(pos);
    }
    else{
        sf::Vector2f pos = v.getCenter() + sf::Vector2f(v.getSize().x/2.f, v.getSize().y/2.f);
        m_rect.setRotation(180);
        m_rect.setPosition(pos);
    }
}



bool TransitionState::update(float dt) {
    m_actualTime += dt;
    
    if(m_dir == Direction::North)
        m_rect.setSize(sf::Vector2f(SCREEN_SIZE.x, SCREEN_SIZE.y*m_actualTime/m_transitionTime));
    else if(m_dir == Direction::East)
        m_rect.setSize(sf::Vector2f(SCREEN_SIZE.x*m_actualTime/m_transitionTime, SCREEN_SIZE.y));
    else if(m_dir == Direction::South)
        m_rect.setSize(sf::Vector2f(SCREEN_SIZE.x, SCREEN_SIZE.y*m_actualTime/m_transitionTime));
    else 
        m_rect.setSize(sf::Vector2f(SCREEN_SIZE.x*m_actualTime/m_transitionTime, SCREEN_SIZE.y));
    
    
    // If enough time passed, load the new zone by updating GameState
    if((m_actualTime >= m_transitionTime + 0.2)){
        // Update with 0 secondes
        m_stack->getStateOfID(StateID::GameS)->update(0.);
    }
    
    
    // Return false to prevent the Game state from updating
    return false;
}



void TransitionState::actionOnCompletion() {
    m_stack->requestStackPop();
}



bool TransitionState::handleEvent(sf::Event& event) {
    return false;
}



void TransitionState::handleGameEvent(const GameEvent& event) {
    // Complete once the zone is loaded, and wait for enough time to pass
    if(event.getType() == EventType::ZoneLoaded)
        m_isCompleted = true;
}



bool TransitionState::isCompleted() const {
    return m_isCompleted && (m_actualTime >= m_transitionTime + 0.2);
}



void TransitionState::draw() {
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow(); 
    
    window.draw(m_rect);
}