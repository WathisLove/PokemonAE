/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BagItemSelector.hpp
 * Author: Redbuzard
 *
 * Created on 11 avril 2019, 15:04
 */

#ifndef BAGITEMSELECTOR_HPP
#define BAGITEMSELECTOR_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "InventoryEntry.hpp"
#include "Inventory.hpp"


class BagItemSelector : public sf::Drawable{
public:
    
    BagItemSelector(Context& context, sf::Vector2f offset);
    
    virtual ~BagItemSelector();
    
    

    //==================// Methods //===================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Handle an event thrown by the system
     * @param event the Event to handle
     */
    void handleEvent(sf::Event& event);
    
    
    /**
     * Set the list of the ItemEntries according to the list of IDs
     * @param idList a vector containing the list of item IDs
     */
    void setIDList(Inventory* inventory, ItemCategory type);
    
    
    
    /**
     * Check if the current vector is empty
     * @return true if the vector is empty
     */
    bool isEmpty();
    
    
    
    /**
     * Get the ID of the selected Entry
     * @return the ID as an ItemID enum
     * @warning throws an exception if there is no item in the vector
     */
    ItemID getCurrentItemID();
    
    
    
    /**
     * Get the current Inventory Entry
     * @return a pointer to the InventoryEntry
     * @warning throws an exception if there is no item in the vector
     */
    InventoryEntry* getCurrentInventoryEntry();
    
    
    /**
     * Go down in the list if possible
     */
    void goDown();
    
    /**
     * Go up in the list if possible
     */
    void goUp();
    
    
    /**
     * Check if the current item changed
     * Reset once called
     * @return true if the current item changed
     */
    bool changed();
    
    
    /**
     * Get the number of ItemEntries
     * @return the number of entries as an int
     */
    int getItemCount();
    
    
private:
    
    //==================// Private methods //===================//
    
    
    /**
     * Check if the ItemSelector can go upper
     * @return true if the ItemSelector has items not shown upper in the list
     */
    bool canGoUp() const;
    
    /**
     * Check if the ItemSelector can go further
     * @return true if the ItemSelector has items not shown further in the list
     */
    bool canGoDown() const;
    
    
    /**
     * Replace graphically the entries when the list move up or down
     */
    void replaceEntries();
    
    
    /**
     * Replace graphically the entry selector
     */
    void replaceSelector();
    
    
    //==================// Attributes //===================//
    
    
    // The global offset applied to each InventoryEntry
    sf::Vector2f m_offset;
    
    // The current InventoryEntry
    int m_currentEntry;
    
    
    // The number of the first Entry displayed
    int m_firstDisplayed;
    
    // The current context
    Context& m_context;
    
    
    // Boolean that sotres if the current item changed
    bool m_changed;
    
    // The previous ItemType
    ItemCategory m_currentItemType;
    
    //==================// Graphical Attributes //===================//
    
    // A vector for all the Inventory entries
    std::vector<InventoryEntry*> m_inventoryEntries;
    
    
    // The up and down arrows
    sf::Sprite m_arrowUp;
    sf::Sprite m_arrowDown;
    
    // The selection rectangle
    sf::Sprite m_selector;
};

#endif /* BAGITEMSELECTOR_HPP */

