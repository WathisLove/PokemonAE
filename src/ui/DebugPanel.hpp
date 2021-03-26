/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DebugPanel.hpp
 * Author: Redbuzard
 *
 * Created on 20 mars 2020, 18:52
 */

#ifndef DEBUGPANEL_HPP
#define DEBUGPANEL_HPP

#include <SFML/Graphics.hpp>
#include "../Context.hpp"

class DebugPanel : sf::Drawable {
public:
//=================// Constructor //==================//
    
    DebugPanel(Context& context);
    
    
//=================// Inherited draw method //==================//
    
    
    /**
     * Inherited dra method
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    
//=================// Public methods //==================//
    
    /**
     * Toggle the Debug panel display
     */
    void toggleDisplay();
    
    
//=================// Setters //==================//
    
    /**
     * Set the display position
     * @param pos the new position of the display
     */
    void setPosition(sf::Vector2f pos);
    
private:
//=================// Attributes //==================//

    // Text for the different debug entries
    sf::Text m_text;
    
    // A boolean to know if we must draw the text
    bool m_show;
};

#endif /* DEBUGPANEL_HPP */

