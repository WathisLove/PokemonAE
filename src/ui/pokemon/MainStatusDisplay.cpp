#include "MainStatusDisplay.hpp"
#include "../../resources/TextureHolder.hpp"

MainStatusDisplay::MainStatusDisplay(Context& context) :
m_sprite(context.getTextureHolder()->getTexture(TextureHolder::main_status), sf::IntRect(0,0,0,0))
{

}



void MainStatusDisplay::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}



void MainStatusDisplay::setStatus(MainStatus status) {
    MainStatusName name = status.getName();
    
    if(name == MainStatusName::NoMainStatus)
        m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
    else if(name == MainStatusName::Burn)
        m_sprite.setTextureRect(sf::IntRect(0, 0, 26, 10));
    else if(name == MainStatusName::Freeze)
        m_sprite.setTextureRect(sf::IntRect(0, 10, 26, 10));
    else if(name == MainStatusName::Paralysis)
        m_sprite.setTextureRect(sf::IntRect(0, 20, 26, 10));
    else if(name == MainStatusName::Poison)
        m_sprite.setTextureRect(sf::IntRect(0, 30, 26, 10));
    else if(name == MainStatusName::BadlyPoison)
        m_sprite.setTextureRect(sf::IntRect(0, 40, 26, 10));
    else if(name == MainStatusName::Sleep)
        m_sprite.setTextureRect(sf::IntRect(0, 50, 26, 10));
}



void MainStatusDisplay::setPosition(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void MainStatusDisplay::setZoomFactor(float factor) {
    m_sprite.setScale(factor, factor);
}
