/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TypeDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 14 février 2020, 20:39
 */

#ifndef TYPEDISPLAY_HPP
#define TYPEDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../../pokemons/Type.hpp"

class TypeDisplay : public sf::Drawable {
public:
//===================// Attributes //===================//
    
    TypeDisplay(Context& context, Type::TypeName type);
    
//===================// Overriden methods //===================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//===================// Setters //===================//

    
    /**
     * Set the display position
     * @param pos the new position of the display
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the displayed type
     * @param type the TypeName enum of the new type
     */
    void setType(Type::TypeName type);
    
private:
//===================// Graphical Attributes //===================//
    
    // Sprite for the type 
    sf::Sprite m_typeDisplay;
};

#endif /* TYPEDISPLAY_HPP */

