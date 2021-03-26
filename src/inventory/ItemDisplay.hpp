/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemDisplay.hpp
 * Author: Redbuzard
 *
 * Created on 21 février 2019, 22:00
 */

#ifndef ITEMDISPLAY_HPP
#define ITEMDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "Item.hpp"
#include "../Context.hpp"

class ItemDisplay : public sf::Drawable{
    
public:
    
    ItemDisplay(Context& context);
    ItemDisplay(Context& context, Item* item);
        
    /**
     * Inherited function draw
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Change the ItemDisplay to display a new Item
     * @param item a pointer to the new item
     */
    void setItem(Item* item);
    
    
    /**
     * Set the position of the ItemDisplay
     * @param pos the new position on the screen as a Vector2f
     */
    void setPosition(sf::Vector2f pos);  
    
    
    /**
     * Set the origin of the ItemDisplay
     * @param pos the new origin as a Vector2f
     */
    void setOrigin(sf::Vector2f pos);
    
    
    /**
     * The zoom factor of the sprite
     * @param zoom the zoom as a float (>1 is a greater sprite)
     */
    void setZoomFactor(float zoom);
    
protected:
    
    /**
     * Change the textureRect of the current Sprite
     * @param item a pointer to the new item
     */
    void setTextureRect(Item* item);
    
    
    // Sprite of the ItemDisplay
    sf::Sprite m_sprite;
};

#endif /* ITEMDISPLAY_HPP */

