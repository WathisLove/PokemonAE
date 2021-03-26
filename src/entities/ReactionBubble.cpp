#include "ReactionBubble.hpp"
#include "../resources/TextureHolder.hpp"
#include <iostream>


ReactionBubble::ReactionBubble(Context& context, sf::Vector2f position, ReactionType reaction) :
sf::Drawable(),
m_bgSprite(context.getTextureHolder()->getTexture(TextureHolder::npc_bubble)),
m_fgSprite(context.getTextureHolder()->getTexture(TextureHolder::npc_reactions))
{
    // Set the offset to center it over the position
    m_bgSprite.setOrigin(12, 24);
    m_fgSprite.setOrigin(8, 18);
    
    // Set the position of both buubles
    setPosition(position);
    
    // Set the foreground 
    setReaction(reaction);
}



void ReactionBubble::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the background
    target.draw(m_bgSprite, states);
    
    // Then the foreground
    target.draw(m_fgSprite, states);
}



void ReactionBubble::setPosition(sf::Vector2f pos) {
    // Set the position of both sprites
    m_fgSprite.setPosition(pos);
    m_bgSprite.setPosition(pos);
}



void ReactionBubble::setReaction(ReactionType reaction) {
    m_fgSprite.setTextureRect(sf::IntRect(0, 14*(int)reaction, 16, 14));
}
