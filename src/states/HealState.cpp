#include "HealState.hpp"


HealState::HealState(StateStack* stack, Character* character) :
State(stack),
m_character(character),
m_timePassed(0.0),
m_timeBeforeLeaving(2.0){
    m_id = StateID::HealS;
}



void HealState::actionOnCompletion() {
    // Request to pop
    m_stack->requestStackPop();
    
    // Push a Dialog
    m_stack->requestStackPushDialog(sf::String(L"Votre équipe a été soignée !"));
}



bool HealState::update(float dt) {
    m_timePassed += dt;
    
    // Leave after enough time
    if(m_timePassed >= m_timeBeforeLeaving){
        m_isCompleted = true;
        
        // Heal after the timer ends
        m_character->healTeam();
        m_character->saveHealData();
    }
    
    return false;
}


void HealState::draw() {
    // Nothing to do
}
