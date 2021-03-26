/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneDialog.hpp
 * Author: Redbuzard
 *
 * Created on 12 novembre 2020, 17:55
 */

#ifndef ZONEDIALOG_HPP
#define ZONEDIALOG_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics/Rect.hpp>

/**
 * A class used to store a dialog somewhere in the zone
 */
class ZoneDialog {
public:
//===============// Constructor //===============//
        
    /**
     * Constructor
     */
    ZoneDialog(sf::String* string, int x, int y, int width, int height);
    
    
    /**
     * Destructor
     */
    virtual ~ZoneDialog();

    
//===============// Getters //===============//
    
    /**
     * Get the dialog
     * @return a const reference to the SFML String
     */
    const sf::String& getDialog() const;
    
    
    /**
     * Check if the ZoneDialog occupies a 
     */
    bool occupies(sf::Vector2i pos) const;
    
    
private:
//===============// Attributes //===============//
    
    // A pointer to the String
    sf::String* m_string;
    
    // The ZoneDialog position
    sf::IntRect m_rect;
};

#endif /* ZONEDIALOG_HPP */

