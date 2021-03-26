/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SellEntry.hpp
 * Author: Redbuzard
 *
 * Created on 7 mai 2020, 14:12
 */

#ifndef SELLENTRY_HPP
#define SELLENTRY_HPP

#include <SFML/Graphics.hpp>

#include "../../inventory/ItemDisplay.hpp"

class SellEntry : public sf::Drawable{
public:
    
//=================// Constructor //==================//
    
    /**
     * Constructor
     */
    SellEntry(Context& context, ItemID item, int price);
    
//=================// Inherited methods //==================//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Setters / Getters //==================//
    
    /**
     * Set the entry position
     * @param pos the position of the top left of the Entry
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Get the item sold
     * @return the ItemID of the entry
     */
    ItemID getItem();
    
private:
//=================// Private methods //==================//
    
    /**
     * Setup the Text of the Entry
     * @param id the ItemID of the item that will be sold
     * @param price the price of the item
     */
    void setupText(ItemID id, int price);
    
    
//=================// Attributes //==================//
    
    // The entry background
    sf::Sprite m_background;
    
    // A mini item display
    ItemDisplay m_itemDisplay;
    
    // The Item Name and price
    sf::Text m_name, m_price;
    
    // The Item ID
    ItemID m_item;

};

#endif /* SELLENTRY_HPP */

