#include "ZoneNameState.hpp"
#include "../resources/FontHolder.hpp"
#include "../zones/Zone.hpp"

ZoneNameState::ZoneNameState(StateStack* stack, Character* character) :
State(stack),
m_character(character),
m_background(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_zoneNameBackground)),
m_zoneName("", m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont)),
m_timePassed(0.0),
m_offset(-300, 0),
m_zone(character->getZone()->getZoneID()){
    // Set the ID
    m_id = StateID::ZoneNameS;
    
    m_zoneName.setString(Zone::getZoneName(character->getZone()->getZoneID()));
    
    // Get the top left position
    sf::Vector2f pos = sf::Vector2f(m_stack->getContext().getWindowTopLeftCorner());

    // Set the Background and Text to a fixed position
    m_background.setPosition(pos + m_offset);
    m_zoneName.setPosition(pos + sf::Vector2f(20, 20) + m_offset);
}



void ZoneNameState::actionOnCompletion() {
    m_stack->requestStackPop();
}



void ZoneNameState::draw() {
    // Get the Window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();

    // Draw the background and Text
    window.draw(m_background);
    window.draw(m_zoneName);
}



bool ZoneNameState::handleEvent(sf::Event& event) {
    return true;
}



bool ZoneNameState::update(float dt) {
    return true;
}



void ZoneNameState::lateUpdate(float dt) {
    // Check if the zone changed
    if(m_character->getZone()->getZoneID() != m_zone){
        updateZone(m_character->getZone()->getZoneID());
    }
    
    
    // Update the time passed
    m_timePassed += dt;
    
    // Get the Top left position
    sf::Vector2f top = sf::Vector2f(m_stack->getContext().getWindowTopLeftCorner());
    
    
    if(m_timePassed <= 1){
        // Update the Offset
        m_offset += sf::Vector2f(300 * dt, 0);
        
        // Move to the right
        m_background.setPosition(top + m_offset);
        m_zoneName.setPosition(top + sf::Vector2f(20, 20) + m_offset);
    }
    else if(m_timePassed <= 4){
        // Set the Background and Text to a fixed position
        m_background.setPosition(top);
        m_zoneName.setPosition(top + sf::Vector2f(20, 20));
    }
    else if(m_timePassed >= 4){
        // Update the Offset
        m_offset += sf::Vector2f(-300 * dt, 0);
        
        // Move to the left
        m_background.setPosition(top + m_offset);
        m_zoneName.setPosition(top + sf::Vector2f(20, 20) + m_offset);
    }
    else{
        m_isCompleted = true;
    }
}



void ZoneNameState::updateZone(ZoneID newZone) {
    // Update the Time
    m_timePassed = 0;

    // Reset the Offset
    m_offset = sf::Vector2f(-300, 0);

    // Update the zone name, otherwise pop the state
    if(m_character->getZone()->mustShowZoneName()){
        m_zoneName.setString(Zone::getZoneName(newZone));
    }
    else{
        m_isCompleted = true;
    }

    // Update the zone
    m_zone = m_character->getZone()->getZoneID();
}
