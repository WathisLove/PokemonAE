#include "UIBadgeState.hpp"

#include "../../resources/TextureHolder.hpp"

UIBadgeState::UIBadgeState(Context& context, int badgeNumber) :
m_show(false),
m_badge(context.getTextureHolder()->getTexture(TextureHolder::ui_badges)){
    
    // The badge number on the texture
    int badgeTextureNum = badgeNumber-1;
    
    // The x and y position of the badge
    int x = badgeTextureNum%2;
    int y = badgeTextureNum/2;

    // Set the Texture Rect
    sf::IntRect rect(x*170, y*170, 170, 170);
    m_badge.setTextureRect(rect);
}



void UIBadgeState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(!m_show)
        return;
    
    // Draw the Badge
    target.draw(m_badge, states);
}



void UIBadgeState::setPosition(sf::Vector2f pos) {
    m_badge.setPosition(pos + sf::Vector2f(315, 215));
}



void UIBadgeState::show(bool val) {
    m_show = val;
}
