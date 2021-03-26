/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIBuyingState.hpp
 * Author: Redbuzard
 *
 * Created on 22 mai 2020, 11:31
 */

#ifndef UIBUYINGSTATE_HPP
#define UIBUYINGSTATE_HPP

#include "../../ItemEnums.hpp"
#include "../../inventory/ItemDisplay.hpp"

class UIBuyingState : public sf::Drawable{
public:
//=================// Constructor //==================//
    
    
    UIBuyingState(Context& context);
    
    
//=================// Inherited methods //==================//
    
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    
//=================// Setters //==================//
    
    /**
     * Set the Item
     * @param item the ItemID of the new Item
     */
    void setItem(ItemID item);
    
    /**
     * Set the current number of item being sold from the Character
     * @param number the number of current item
     * @param maxNumber the maximum number that can be sold
     */
    void setItemSold(int number, int maxNumber);
    
    /**
     * Set the UI position
     * @param pos the position of the top left of the Entry
     */
    void setPosition(sf::Vector2f pos);
    
private:
//=================// Private methods //==================//
    
    /**
     * Setup the texts
     */
    void setupTexts();
    
//=================// Attributes //==================//

    // A reference to the context
    Context& m_context;
    
    // The current ItemID
    ItemID m_itemID;
    
//=================// Graphical Attributes //==================//
    
    // A sprite for the background
    sf::Sprite m_background;
    
    // A phrase for the UI, and the number of item sold
    sf::Text m_text, m_itemSold, m_totalPrice;
    
    // An item display
    ItemDisplay m_itemDisplay;
};

#endif /* UIBUYINGSTATE_HPP */

