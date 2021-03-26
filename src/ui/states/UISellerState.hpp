/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UISellerState.hpp
 * Author: Redbuzard
 *
 * Created on 6 mai 2020, 10:53
 */

#ifndef UISELLERSTATE_HPP
#define UISELLERSTATE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

#include "../../entities/Seller.hpp"
#include "../seller/SellEntry.hpp"

class UISellerState : public sf::Drawable{
public:
    
    /**
     * UI Constructor
     */
    UISellerState(Context& context, Seller* seller, int characterMoney);
    
    
//=================// Inherited methods //==================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Setters //==================//
    
    /**
     * Select a given entry
     * @param entryNumber the number of the entry to select
     */
    void setCurrentEntry(int entryNumber);
    
    
    /**
     * Set the current number of item we will buy and their price
     * @param number the number of items we will buy
     * @param totalPrice the total price of the items
     */
    void setQuantity(int number, int totalPrice);
    
    
    /**
     * Set the UI position
     * @param pos the position of the top left of the Entry
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the displayed money
     * @param money the character money
     */
    void setCharacterMoney(int money);
    
    
    /**
     * Set the UI to show the item was selected or not
     * @param selected true if the item is currently selected
     */
    void setSelected(bool selected);
    
private:
    
//=================// Private methods //==================//
    
    /**
     * Get the index of the first entry currently dispayed
     * @return the index of the first entry displayed
     */
    int getFirstEntryDisplayed() const;
    
    
    /**
     * Set the positions of the entries
     */
    void setEntriesPositions();
    
    
    /**
     * Create the entries for the SellerState
     * @param context a reference to the context
     * @param seller a pointer to the seller
     */
    void createEntries(Context& context, Seller* seller);
    
    
    /**
     * Setup the Text
     * @param characterMoney the character money
     */
    void setupTexts(int characterMoney);
    
    
//=================// Attributes //==================//
    
    // A boolean to know if we selected the item
    bool m_isSelected;
    
    // The current entry selected
    int m_currentEntry;
    
//=================// Graphical Attributes //==================//
    // The UI Background
    sf::Sprite m_background;
    
    // A vector of SellEntries
    std::vector<SellEntry> m_entries;
    
    // A cursor for the current Entry
    sf::Sprite m_cursor;
    
    // A text for the Character money
    sf::Text m_money;
    
    // A text for the current buying quantity
    sf::Text m_quantity;
    
    // A text for the Current Item
    sf::Text m_currentItemName;
    
    // A text for the current total price
    sf::Text m_totalPrice;
    
    // An item display for the current Item
    ItemDisplay m_itemDisplay;
};

#endif /* UISELLERSTATE_HPP */

