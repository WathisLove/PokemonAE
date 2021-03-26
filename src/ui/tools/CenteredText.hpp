/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CenteredText.hpp
 * Author: Redbuzard
 *
 * Created on 12 décembre 2019, 15:13
 */

#ifndef CENTEREDTEXT_HPP
#define CENTEREDTEXT_HPP

#include <SFML/Graphics/Text.hpp>

class CenteredText : public sf::Text {
public:
    
//==================// Constructor //=============//
    
    /**
     * Empty constructor
     */
    CenteredText();
    
    /**
     * Default consructor, same as sf::Text
     */
    CenteredText(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);
    
    
//==================// Overriden methods //=============//
    
    /**
     * Overriden setString method
     * Centers the text after setting the new String
     * @param string a const reference to the new String
     */
    void setString(const sf::String& string);
    
    
    /**
     * Overriden setCharacterSize method
     * Centers the after setting the new size
     * @param size the new character size as a unsigned int
     */
    void setCharacterSize(unsigned int size);
    
    
    /**
     * Inherited setPosition 
     * @warning position the text to Int Coords
     * @param x the x coordinate as a float
     * @param y the y coordinate as a float
     */
    void setPosition(float x, float y);
    
    
    /**
     * Inherited setPosition 
     * @warning position the text to Int Coords
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
//==================// Public methods //=============//
    
    
    /**
     * Set the CenteredText to Integer coords
     */
    void setToIntCoords();
    
    
private:
    
//==================// Private methods //=============//
    
    /**
     * Centers the text
     */
    void centerText();
    
};

#endif /* CENTEREDTEXT_HPP */

