#include "MenuState.hpp"
#include "../resources/FontHolder.hpp"
#include "../Constants.hpp"
#include <iostream>
#include <cmath>
#include <complex>

MenuState::MenuState(StateStack* stack, Character* c) :
State(stack),
m_currentAngularPos(0),
m_selectedIcon(0),
m_iconDistance(160),
m_character(c),
m_timeLeft(0),
m_rotationTime(0.2),
m_bgLarge(m_iconDistance*4.3/3., 90),
m_bgSmall(m_iconDistance-2, 90),
m_arrow(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_menuArrow)),
m_text(L"Equipe", m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont)){
    //We set the ID
    m_id = StateID::MenuS;
    
    // We generate the icons
    for(int i = 0; i < 7; i++){
        sf::IntRect rect(i*90, 0, 90, 90);
        
        // We load the sprite number i
        sf::Sprite* s = new sf::Sprite(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_menuIcons), rect);
        s->setOrigin(45,45);
        
        m_icons.push_back(s);
    }
    
    // Set the Background Circles
    setBGCircles();
    
    // Set the Arrow
    m_arrow.setOrigin(8,8);
    m_arrow.setPosition(m_character->getSpriteCenter() - sf::Vector2f(0, m_iconDistance-55));
    
    // Set the Text parameters
    m_text.setFillColor(sf::Color::White);
    m_text.setOutlineColor(sf::Color::Black);
    m_text.setOutlineThickness(1);
    m_text.setCharacterSize(32);
    setTextPosition();
}



MenuState::~MenuState() {
    // We generate the icons
    for(int i = 0; i < 7; i++){
        delete m_icons[i];
    }
}



void MenuState::actionOnCompletion() {
    
    if(m_selectedIcon >= 0){
        // Choose wich state we want to push
        if(m_selectedIcon == 0)
            m_stack->requestStackPush(StateID::TeamS, m_character);
        
        else if(m_selectedIcon == 1)
            m_stack->requestStackPush(StateID::BagS, m_character);
            
        else if(m_selectedIcon == 2)
            m_stack->requestStackPush(StateID::CharacterInfoS, m_character);
            
        else if(m_selectedIcon == 6)
            m_stack->requestStackPush(StateID::PokedexS, m_character);
            
        else
            m_stack->requestStackPop();
        
        
        // At the end we deselect the icon by setting the state to uncompleted
        m_isCompleted = false;
    }
    else
        m_stack->requestStackPop();
    
    // Unfreeze the Character
    m_character->freeze(false);
}



void MenuState::draw() {
    // Get the center of the positions
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // We draw all the Circle Shapes
    drawCircles(window);
    
    // Draw the Arrow
    window.draw(m_arrow);
    
    // Draw the Text
    window.draw(m_text);
}



bool MenuState::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Escape){
            m_selectedIcon = -1;
            m_isCompleted = true;
        }
        else if(event.key.code == sf::Keyboard::Space)
            m_isCompleted = true;
            
        else if(event.key.code == sf::Keyboard::D && m_timeLeft == 0){
            m_timeLeft = m_rotationTime;
            
            // update the selected icon
            m_selectedIcon ++;
            
            if(m_selectedIcon > 6){
                m_selectedIcon = 0;
            }
            // We update the text
            updateText();
        }
        else if(event.key.code == sf::Keyboard::Q && m_timeLeft == 0){
            m_timeLeft = -m_rotationTime;
            
            // update the selected icon
            m_selectedIcon --;
            if(m_selectedIcon < 0){
                m_selectedIcon = 6;
            }
            // We update the text
            updateText();
        }
    }
    
    return false;
}



bool MenuState::isCompleted() const {
    return m_isCompleted;
}



bool MenuState::update(float dt) {
    
    if(m_timeLeft > 0){
        float t = std::min(dt, m_timeLeft);
        
        // We update the pos
        m_currentAngularPos -= t * 360 / (m_rotationTime*7);
        
        // We update the time left for the movement
        m_timeLeft -= t;
    }
    else if(m_timeLeft < 0){
        float t = std::min(dt, -m_timeLeft);
        
        // We update the pos
        m_currentAngularPos += t * 360 / (m_rotationTime*7);
        
        // We update the time left for the movement
        m_timeLeft += t;
    }
    
    return false;
}



void MenuState::setTextPosition() {
    // We calculate the text origin from its bounds
    sf::Vector2f origin(m_text.getLocalBounds().width/2., m_text.getCharacterSize()/2);
    m_text.setOrigin(origin);
    
    // And we set its position
    m_text.setPosition(m_character->getSpriteCenter());
}



void MenuState::updateText() {
    if(m_selectedIcon == 0)
        m_text.setString(L"Equipe");
    else if(m_selectedIcon == 1)
        m_text.setString(L"Sac");
    else if(m_selectedIcon == 2)
        m_text.setString(L"Carte Dresseur");
    else if(m_selectedIcon == 3)
        m_text.setString(L"Sauvegarder");
    else if(m_selectedIcon == 4)
        m_text.setString(L"Quitter");
    else if(m_selectedIcon == 5)
        m_text.setString(L"Réglages");
    else if(m_selectedIcon == 6)
        m_text.setString(L"Pokédex");
    
    
    // We set the Text position
    setTextPosition();
}



void MenuState::drawCircles(sf::RenderWindow& window) {
    // Draw the Background circles
    window.draw(m_bgLarge);
    window.draw(m_bgSmall);
    
    
    // Draw the Circles
    sf::Vector2f posCentral = m_character->getSpriteCenter();
    
    for(int i = 0; i < 7; i++){        
        // Coords on x and y
        float x = std::sin((360* i/7 + m_currentAngularPos)* PI/180)*m_iconDistance;
        float y = -std::cos((360* i/7 + m_currentAngularPos)* PI/180)*m_iconDistance;
        
        sf::Vector2f pos(x,y);
        
        // Draw the circle
        drawIconCircle(window, pos + posCentral);
        
        // Place and draw the Icon
        m_icons[i]->setPosition(pos + posCentral);
        window.draw(*m_icons[i]);
    }
}



void MenuState::drawIconCircle(sf::RenderWindow& window, sf::Vector2f center) {

    // Place the circle
    sf::CircleShape circle(45);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color(110, 110, 110));
    circle.setOrigin(45,45);
    circle.setPosition(center);
        
    // Draw it
    window.draw(circle);
}



void MenuState::setBGCircles() {
    
    // Set the BG Circles
    m_bgLarge.setOrigin(m_bgLarge.getRadius(), m_bgLarge.getRadius());
    m_bgSmall.setOrigin(m_bgSmall.getRadius(), m_bgSmall.getRadius());
    
    // Position
    m_bgLarge.setPosition(m_character->getSpriteCenter());
    m_bgSmall.setPosition(m_character->getSpriteCenter());
    
    // Colors
    m_bgLarge.setFillColor(sf::Color(200,200,200));
    m_bgLarge.setOutlineColor(sf::Color(110,110,110));
    m_bgSmall.setFillColor(sf::Color(200,200,200));
    m_bgSmall.setOutlineColor(sf::Color(110,110,110));
    
    // Outline Thickness
    m_bgLarge.setOutlineThickness(4);
    m_bgSmall.setOutlineThickness(4);
}
