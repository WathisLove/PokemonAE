/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InventoryEntry.hpp
 * Author: Redbuzard
 *
 * Created on 10 avril 2019, 16:17
 */

#ifndef INVENTORYENTRY_HPP
#define INVENTORYENTRY_HPP

#include "../ItemEnums.hpp"
#include "../Context.hpp"
#include <SFML/Graphics.hpp>


class InventoryEntry : public sf::Drawable{
public:
    
    InventoryEntry(Context& context, ItemID id, int count);
    

    //==================// Public Methods //===================//
    
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    
    //==================// Getters / Setters //===================//
    
    /**
     * Set the new position for the Text displayed
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Get the ItemID used to build the InventoryEntry
     * @return an ItemID enum
     */
    ItemID getItemID() const;
    
    
    /**
     * Get the item count
     * @return the count as an int
     */
    int getItemCount() const;
    
    
    /**
     * Get the Item name
     * @return the name as a sf::String which can be automatically converted
     */
    sf::String getItemName() const;
    
    
private:
    
    //==================// Attributes //===================//
    
    // The item ID
    ItemID m_id;
    
    // The item count
    int m_count;
    
    
    //==================// Graphical Attributes //===================//
    
    // Text used for displaying the name and the item count
    sf::Text m_textName;
    sf::Text m_textCount;
};

#endif /* INVENTORYENTRY_HPP */

