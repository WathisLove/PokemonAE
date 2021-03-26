#include "CenteredText.hpp"

#include <iostream>


CenteredText::CenteredText() :
sf::Text(){
    // Center the text
    centerText();
    
    // Set to Int coords
    setToIntCoords();
}


CenteredText::CenteredText(const sf::String& string, const sf::Font& font, unsigned int characterSize) :
sf::Text(string, font, characterSize)
{
    // Center the text
    centerText();
}



void CenteredText::setString(const sf::String& string) {
    
    // Call inherited method
    sf::Text::setString(string);
    
    // Recenter the text
    centerText();
}



void CenteredText::setCharacterSize(unsigned int size) {
    
    // Call inherited method
    sf::Text::setCharacterSize(size);
    
    // Recenter the text
    centerText();
}



void CenteredText::setPosition(float x, float y) {
    
    // Call inherited method
    sf::Text::setPosition(x,y);
    
    // Set to Int coords
    setToIntCoords();
}



void CenteredText::setPosition(sf::Vector2f pos) {

    // Call inherited method
    sf::Text::setPosition(pos);
    
    // Set to Int coords
    setToIntCoords();
}



void CenteredText::centerText() {
    sf::Vector2f origin;
    
    // Set x depending on the string length and character size
    origin.x = getCharacterSize()*getString().getSize()/4.;
    
    // Set y to the vertical middle
    origin.y = getCharacterSize()/2.;
    
    // Set the Text origin
    setOrigin(origin);
}



void CenteredText::setToIntCoords() {
    
    // Change the position
    sf::Vector2f pos = getPosition();
    
    pos.x = (int)pos.x;
    pos.y = (int)pos.y;
    
    sf::Text::setPosition(pos);
    
    
    // Change the origin
    sf::Vector2f origin = getOrigin();
    
    origin.x = (int)origin.x;
    origin.y = (int)origin.y;
    
    setOrigin(origin);
}
