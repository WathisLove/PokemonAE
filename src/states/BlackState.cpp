#include "BlackState.hpp"
#include "../Constants.hpp"
#include "../Context.hpp"

BlackState::BlackState(StateStack* stack, float lifeTime) :
State(stack),
m_lifeTime(lifeTime),
m_actualTime(0){
    // Set the ID
    State::m_id = StateID::BlackS;
    
    // Setup the black rect
    m_rect = sf::RectangleShape(sf::Vector2f(SCREEN_SIZE));
    m_rect.setFillColor(sf::Color::Black);
    
    
    sf::View v = m_stack->getContext().getRenderWindow().getView();
    sf::Vector2f pos = v.getCenter() - sf::Vector2f(v.getSize().x/2.f, v.getSize().y/2.f);
    m_rect.setPosition(pos);
}



void BlackState::actionOnCompletion() {
    requestStackPop();
}



void BlackState::draw() {
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_rect);
}



bool BlackState::handleEvent(sf::Event& event) {
    return false;
}



bool BlackState::isCompleted() const {
    return m_actualTime >= m_lifeTime;
}



bool BlackState::update(float dt) {
    m_actualTime += dt;
    
    return false;
}
