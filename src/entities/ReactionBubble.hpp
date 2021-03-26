/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ReactionBubble.hpp
 * Author: Redbuzard
 *
 * Created on 27 décembre 2018, 10:13
 */

#ifndef REACTIONBUBBLE_HPP
#define REACTIONBUBBLE_HPP

#include <SFML/Graphics.hpp>
#include "../Enums.hpp"
#include "../Context.hpp"

class ReactionBubble : public sf::Drawable{
public:
    ReactionBubble(Context& context, sf::Vector2f position, ReactionType reaction);
    
    
    /**
     * Overriden draw function
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Set the ReactionBuble at the given position
     * @param pos the new position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set the foreground of the bubble depending on the reaction
     * @param reaction the reaction we want to display
     */
    void setReaction(ReactionType reaction);
    
    
private:
//===============// Private Attributes //===============//
    // Background sprite of the bubble
    sf::Sprite m_bgSprite;
    
    // Foreground (icon) of the bubble
    sf::Sprite m_fgSprite;

};

#endif /* REACTIONBUBBLE_HPP */

