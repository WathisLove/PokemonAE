#include "ItemDisplay.hpp"
#include "../resources/TextureHolder.hpp"
#include <iostream>


ItemDisplay::ItemDisplay(Context& context, Item* item) :
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::itemsTileSet)){
    // Set the texture Rect
    setTextureRect(item);
    
    // set the sprite origin
    // the item texture have 32.32 pxs as dimensions
    m_sprite.setOrigin(sf::Vector2f(16,16));
}



ItemDisplay::ItemDisplay(Context& context) :
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::itemsTileSet)){
    // set the sprite origin
    // the item texture have 32.32 pxs as dimensions
    m_sprite.setOrigin(sf::Vector2f(16,16));
}



void ItemDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the Sprite
    target.draw(m_sprite, states);
}



void ItemDisplay::setItem(Item* item) {
    // Set the texture Rect
    setTextureRect(item);
}



void ItemDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void ItemDisplay::setTextureRect(Item* item) {  
    // Set the sprite texture
    m_sprite.setTextureRect(item->getTextureRect(item->getID()));
}



void ItemDisplay::setOrigin(sf::Vector2f pos) {
    m_sprite.setOrigin(pos);
}



void ItemDisplay::setZoomFactor(float zoom) {
    m_sprite.setScale(zoom, zoom);
}
