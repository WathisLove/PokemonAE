#include "Context.hpp"

#include "resources/TextureHolder.hpp"
#include "resources/FontHolder.hpp"
#include "resources/InteractionHolder.hpp"
#include "resources/SoundBufferHolder.hpp"
#include "Constants.hpp"


Context::Context() :
m_window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "Pokemon alpha 25 (WIP)"),
m_textureHolder(TextureHolder::buildStandardTH()),
m_fontHolder(FontHolder::buildStandardFH()),
m_interactionHolder(new InteractionHolder()),
m_soundBufferHolder(new SoundBufferHolder())
{
    m_window.setFramerateLimit(FRAME_RATE);
}



Context::~Context() {
    delete m_fontHolder;
    delete m_textureHolder;
    delete m_interactionHolder;
    delete m_soundBufferHolder;
}



sf::RenderWindow& Context::getRenderWindow() {
    return m_window;
}



TextureHolder* Context::getTextureHolder() {
    return m_textureHolder;
}



FontHolder* Context::getFontHolder() {
    return m_fontHolder;
}



InteractionHolder* Context::getInteractionHolder() {
    return m_interactionHolder;
}



SoundBufferHolder * Context::getSoundBufferHolder() {
    return m_soundBufferHolder;
}



sf::Vector2f Context::getWindowTopLeftCorner() const {
    sf::View v = m_window.getView();
    return v.getCenter() - sf::Vector2f(v.getSize().x/2.f, v.getSize().y/2.f);
}



sf::Vector2f Context::getWindowCenter() const {
    sf::View v = m_window.getView();
    return v.getCenter();
}
