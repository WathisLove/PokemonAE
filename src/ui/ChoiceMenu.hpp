/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeamMenu.hpp
 * Author: Redbuzard
 *
 * Created on 23 avril 2019, 21:40
 */

#ifndef TEAMMENU_HPP
#define TEAMMENU_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Context.hpp"


class ChoiceMenu : public sf::Drawable {
public:
    ChoiceMenu(Context& context);
    
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * Handle a key pressed
     * @param key the key pressed
     */
    void handleKeyPressed(sf::Keyboard::Key key);
    
    
    
    /**
     * Set the position of the TeamMenu
     */
    void setPosition(sf::Vector2f pos);
    
    /**
     * Show the menu and allow it to access the events
     */
    void open();
    
    /**
     * Unshow the menu and unallow it to access the events
     */
    void close();
    
    /**
     * Add a new entry to the menu
     * @param txt the wstring for the new entry
     */
    void addEntry(const sf::String& txt);
    
    /**
     * Get the current selected Text
     * @return a const reference to the currently selected text
     */
    const sf::Text& getSelectedText() const;
    
    /**
     * Get the current selected entry
     * @return the selected entry as an int
     */
    int getSelectedEntry() const;
    
    
    /**
     * Clear the entries
     */
    void clearEntries();
    
    
    /**
     * Set the main menu to be actived or not
     * @param val true if the menu is now active
     */
    void setActivated(bool val);
    
    
    /**
     * Check if the menu is activated
     * @return true if the menu is active and can be opened
     */
    bool isActivated() const;
    
    
    /**
     * Check if the menu is opened
     * @return true if the menu is opened
     */
    bool isOpen();
    
    
    /**
     * Select the last entry of the menu
     * Utility method as the last entry is often the one used to close States
     */
    void selectLastEntry();
    
    
private:
    //==================// Private methods //===================//
    
    
    /**
     * Move the cursor to the orrect place when the selected entry changes
     */
    void moveCursor();

    
    //==================// Attributes //===================//
    
    // A const reference to the font holder
    const FontHolder& m_fontHolder;
    
    // A boolean that stores wether or not the Menu is opened
    bool m_isOpened;
    
    // The index of the sleected entry (in order : Resume, Move, Cancel)
    int m_selectedEntry;
    
    // A boolean to store if the Menu is active and can be opened
    bool m_isActivated;
    
    
    //==================// Graphical Attributes //===================//
    sf::Sprite m_background;
    
    sf::Sprite m_arrow;
    
    // The set pf texts for the different options
    std::vector<sf::Text> m_texts;
};

#endif /* TEAMMENU_HPP */

