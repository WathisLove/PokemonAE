#include "State.hpp"
#include <iostream>
#include <cassert>


State::State(StateStack* stack) :
m_stack(stack),
m_isCompleted(false),
m_id(StateID::BlackS),
m_waitBeforeClosing(false),
m_isSecondaryState(false),
m_isShown(true),
m_letEventsPass(false),
m_ignoreEvents(false)
{

}



State::~State() {

}



void State::lateUpdate(float dt) {
    // Nothing to do by default
}



bool State::isCompleted() const {
    return m_isCompleted;
}



void State::requestStackClear() {
    m_stack->requestStackClear();
}



void State::requestStackPop() {
    m_stack->requestStackPop();
}



void State::requestStackPush(StateID id) {
    m_stack->requestStackPush(id);
}



bool State::handleEvent(sf::Event& event) {
    // Default behavior
    return false;
}



void State::handleGameEvent(const GameEvent& event) {
    // Nothing to do by default
    if(event.getType() == EventType::RequestStateClosure && m_id == event.stateID){
        m_waitBeforeClosing = false;
        m_isCompleted = true;
    }
}



StateID State::getID() const {
    return m_id;
}



void State::waitBeforeClosing(bool wait) {
    m_waitBeforeClosing = wait;
}



bool State::waitBeforeClosing() {
    return m_waitBeforeClosing;
}



void State::setAsSecondaryState(bool val) {
    m_isSecondaryState = val;
    waitBeforeClosing(val);
}



bool State::isSecondaryState() {
    return m_isSecondaryState;
}



void State::show(bool shown) {
    m_isShown = shown;
}



void State::letEventPass(bool letPass) {
    m_letEventsPass = letPass;
}



void State::ignoreEvents(bool ignore) {
    m_ignoreEvents = ignore;
}



sf::Keyboard::Key State::getKeyPressed(sf::Event& event) {
    // We check it is a KeyPressed Event
    assert(event.type == sf::Event::KeyPressed);
    
    // Return the key
    return event.key.code;
}



sf::RenderWindow& State::getRenderWindow() {
    return m_stack->getContext().getRenderWindow();
}
