#include "BadgeBox.hpp"


BadgeBox::BadgeBox(Context& context, Character* character) {
    // A reference to the TextureHolder
    TextureHolder* texHolder = context.getTextureHolder();
    
    // Set the Badges 
    for(int i = 0; i < 8; i++){
        if(character->hasBadge(i+1)){
            // The x and y position of the badge
            int x = i%2;
            int y = i/2;
            
            // Set the Texture
            m_badges.at(i).setTexture(texHolder->getTexture(TextureHolder::ui_badges));
            
            // Set the Texture Rect
            sf::IntRect rect(x*170, y*170, 170, 170);
            m_badges.at(i).setTextureRect(rect);
            m_badges.at(i).setScale(0.3, 0.3);
        }
    }
}



void BadgeBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(sf::Sprite badge : m_badges)
        target.draw(badge, states);
}



void BadgeBox::setPosition(sf::Vector2f pos) {
    // Set the position of each badge
    for(int i = 0; i < 8; i++){
        // The x and y position of the badge
        int x = i%2;
        int y = i/2;
        
        // The new position
        sf::Vector2f badgePos = pos + sf::Vector2f(60*x, 60*y);
        
        m_badges.at(i).setPosition(badgePos);
    }
}
