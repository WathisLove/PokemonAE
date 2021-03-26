/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightDialog.hpp
 * Author: Redbuzard
 *
 * Created on 3 septembre 2018, 10:31
 */

#ifndef FIGHTDIALOG_HPP
#define FIGHTDIALOG_HPP

#include <SFML/Graphics.hpp>
#include <queue>
#include "../Context.hpp"


class FightDialog : public sf::Drawable {
public:
//=================// Constructor //==================//
    
    /**
     * Create a FightDialog with a string and activates it
     * @param context a reference to the context
     * @param str the first string to be displayed 
     */
    FightDialog(Context& context, sf::String str);
    
    /**
     * Create a FightDialog (keep it unactivated)
     * @param context a reference to the context
     */
    FightDialog(Context& context);
    
    
//=================// Public Functions //==================//
    
    /**
     * Overriden function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Getters / Setters //==================//
    
    /**
     * Add a string to the Queue
     * @param str the wstring we want to add
     */
    void addString(sf::String str);
    
    
    /**
     * Go the the next string in the queue
     * If there are not string left, deactivates the Dialog
     */
    void nextString();
    
    
    /**
     * Set the position of the FightMenuSelector
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * @return true if the Dialog must be shown
     */
    bool isActive() const;
    
    /**
     * Set wether or not the Dialog must be shown
     * @param val the new val as a bool
     */
    void setActive(bool val) ;
    
private:
//=================// Attributes //==================//
    // Set wether or not the Dialog must be shown
    bool m_isActive;

//=================// Graphical attributes //==================//
    // Background
    sf::Sprite m_bg;
    
    // Text
    sf::Text m_text;
    
    // A queue to store all the strings 
    std::queue<sf::String> m_strings;
};

#endif /* FIGHTDIALOG_HPP */

