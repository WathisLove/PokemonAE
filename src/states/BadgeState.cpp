#include "BadgeState.hpp"
#include "../entities/Character.h"


BadgeState::BadgeState(StateStack* stack, Character* character, int badgeNumber) :
State(stack),
m_badgeDisplayed(badgeNumber),
m_dialogShowed(false),
m_timePassed(0.0),
m_ui(stack->getContext(), badgeNumber)
{
    m_id = StateID::BadgeS;
    
    m_ui.setPosition(stack->getContext().getWindowTopLeftCorner());
    
    // Give the badge to the Character
    character->addBadge(badgeNumber);
}



void BadgeState::actionOnCompletion() {
    m_stack->requestStackPop();
    
    // Push the dialod at the end
    pushEndDialog();
}



void BadgeState::draw() {
    // Get a reference to the window and draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_ui);
}



bool BadgeState::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
        std::cout << "Quit" << std::endl;
        m_isCompleted = true;
    }
    
    return false;
}



bool BadgeState::isCompleted() const {
    return m_isCompleted;
}



void BadgeState::lateUpdate(float dt) {
    if(!m_dialogShowed){
        // Check if the Dialgo was popped
        if(m_stack->hasStateOfID(StateID::DialogS))
            m_dialogShowed = true;
    }
}



bool BadgeState::update(float dt) {
    
    // If the Dialog was Pushed
    if(m_dialogShowed){
        // And Popped
        if(!m_stack->hasStateOfID(StateID::DialogS))
            m_ui.show(true);
        
        // Update the time passed
        m_timePassed += dt;

        // Close the State after a given time
        if(m_timePassed >= 3)
            m_isCompleted = true;
    }
    else{
        pushBeginDialog();
    }
    
    return false;
}



void BadgeState::pushBeginDialog() {
    // String for the dialog
    std::wstring str = L"Vous récupérez le badge ";
    
    // Badge name
    switch(m_badgeDisplayed)
    {
        case 1:
            str += L" num1"; break;
        case 2:
            str += L" num2"; break;
        case 3:
            str += L" num3"; break;
        case 4:
            str += L" num4"; break;
        case 5:
            str += L" num5"; break;
        case 6:
            str += L" num6"; break;
        case 7:
            str += L" num7"; break;
        case 8:
            str += L" num8"; break;
        default:
            throw std::string("Unknown dialog for badge ") + toString(m_badgeDisplayed);
    }
    
    m_stack->requestStackPushDialog(str);
}



void BadgeState::pushEndDialog() {
    m_stack->requestStackPushDialog(sf::String(L"Vous rangez le badge dans votre poche."));
}
