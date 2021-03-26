#include "Entity.hpp"
#include "../Constants.hpp"
#include "../Utilities.hpp"
#include "../Context.hpp"
#include "../zones/Zone.hpp"
#include <string>
#include <iostream>
#include <cassert>



Entity::Entity(const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone) :
sf::Drawable(),
m_pos(pos),
m_dir(Direction::South),
m_textureRect(0, 0, 16, 22),
m_zone(zone),
m_sprite(texture, m_textureRect),
m_isAlive(true),
m_type(EntityType::EmptyEntity_Type)
{
    // Setup the sprite rectangle, and its position
    m_sprite.setOrigin(m_textureRect.width/2.f, 3+m_textureRect.height/2.f);
    setSpriteCenter(m_zone->getCaseCenter(m_pos));
    m_sprite.setScale(GAME_ZOOM, GAME_ZOOM);
    
    // Set the EntityMover
    m_mover = new NoMover();
}



Entity::~Entity() {
    delete m_mover;
}



void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply texture
    states.texture = m_sprite.getTexture();
    
    // Draw the character sprite
    target.draw(m_sprite, states);
}



void Entity::setZone(Zone* zone) {
    m_zone = zone;
}



sf::Vector2i Entity::getPosition() const {
    return m_pos;
}



sf::Vector2f Entity::getSpriteCenter() const {
    return m_sprite.getPosition();
}



void Entity::setSpriteCenter(sf::Vector2f pos) {
    m_sprite.setPosition(pos);
}



void Entity::setPosition(sf::Vector2i pos) {
    if(m_zone->isOutOfBounds(pos)) throw std::string("Position is out of bounds !");
    
    m_pos = pos;
    
    m_mover->setPosition(pos);
}



bool Entity::isAlive() const {
    return m_isAlive;
}



bool Entity::isOccupingPosition(sf::Vector2i pos) const {
    return (m_pos == pos);
}



Direction Entity::getDirection() const {
    return m_dir;
}



void Entity::setDirection(Direction dir) {
    m_dir = dir;
    
    // Update The Texture Rect
    update(0);
}



sf::Vector2i Entity::getFacedCase() const {
    return getCaseFacing(m_dir, m_pos);
}



Zone* Entity::getZone() {
    return m_zone;
}



void Entity::setMover(EntityMover* mover) {
    delete m_mover;
    
    m_mover = mover;
}



void Entity::update(float dt) {
    // Update the Mover
    m_mover->update(dt);
}



void Entity::clearMover() {
    // we delete the old mover
    delete m_mover;
    
    // We replavce it with a NoMover one
    m_mover = new NoMover();
}



EntityType Entity::getType() const {
    assert(m_type != EntityType::EmptyEntity_Type);
    
    return m_type;
}



void Entity::killEntity() {
    m_isAlive = false;
}



bool Entity::isMoving() const {
    return false;
}
