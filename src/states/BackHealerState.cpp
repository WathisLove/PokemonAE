#include "BackHealerState.hpp"
#include "../zones/Zone.hpp"


BackHealerState::BackHealerState(StateStack* stack, Character* character) :
DialogState(stack, character, new sf::String("Vous retournez vous soignez au dernier endroit visité.")),
m_dialogClosed(false),
m_timePassed(0.)
{
    m_id = StateID::BackHealerS;
    
    // Move the character back to heal
    character->getZone()->characterBackToHeal();

    // Update the preview Pos
    character->updateTeamPreviewPos();
    character->update(0);
    
    
    
    // Setup the black rect
    m_rect = sf::RectangleShape(sf::Vector2f(SCREEN_SIZE));
    m_rect.setFillColor(sf::Color::Black);
    
    
    sf::View v = m_stack->getContext().getRenderWindow().getView();
    sf::Vector2f pos = v.getCenter() - sf::Vector2f(v.getSize().x/2.f, v.getSize().y/2.f);
    m_rect.setPosition(pos);
}



void BackHealerState::actionOnCompletion() {
    m_stack->requestStackPop();
    
    m_character->freeze(false);
}



bool BackHealerState::update(float dt) {
    DialogState::update(dt);
    
    m_timePassed += dt;
    
    return false;
}



void BackHealerState::draw() {
    // Draw the Rect
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    window.draw(m_rect);
    
    // Draw the Dialog
    DialogState::draw();
}



bool BackHealerState::handleEvent(sf::Event& event) {
    // Check if the player pushed Space to qui dialog
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            // Check if the player wants to interact
            case sf::Keyboard::Space:
                m_dialogClosed = true;
                break;
        }
    }

    return false;
}



bool BackHealerState::isCompleted() const {
    return m_dialogClosed && m_timePassed > 1.0;
}