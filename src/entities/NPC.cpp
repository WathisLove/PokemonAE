#include "NPC.hpp"
#include "../Utilities.hpp"
#include "../Constants.hpp"
#include "../zones/Zone.hpp"
#include "../utility/Logger.hpp"

Npc::Npc(const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone) :
Entity(texture, context, pos, zone),
m_oldPos(pos),
m_speed(3),
m_id(NpcID::not_defined_NPC)
{
    // Set the type
    m_type = EntityType::NPC_Type;
    
    m_textureRect = sf::IntRect(16, 44, 16, 22);
    m_sprite.setTextureRect(m_textureRect);
}


Npc::~Npc() {
    
}


void Npc::update(float dt) {
    // Call the entity function
    Entity::update(dt);
    
    // Update the Texture rectangle
    updateTextureRect(dt);
    
    // Update the sprite
    updateSpritePos();
    
    // Get the next Move
    MovementType nextMove = m_mover->getNextMovement();
    move(nextMove);
}



bool Npc::isOccupingPosition(sf::Vector2i pos) const {
    return Entity::isOccupingPosition(pos) || (m_oldPos == pos);
}



void Npc::move(MovementType mv) {
    if(mv == MovementType::NoMove)
        return;
    
    // Update the Entity Direction
    updateDirection(mv);
    
    // Change the entity position if the move is correct
    if(mv >= MovementType::GoUp && mv <= MovementType::GoLeft)
        changePos();
}



void Npc::updateDirection(MovementType mv) {
    // Set the direction
    if(mv == MovementType::LookDown || mv == MovementType::GoDown)
        m_dir = Direction::South;
    else if(mv == MovementType::LookLeft || mv == MovementType::GoLeft)
        m_dir = Direction::West;
    else if(mv == MovementType::LookUp || mv == MovementType::GoUp)
        m_dir = Direction::North;
    else if(mv == MovementType::LookRight || mv == MovementType::GoRight)
        m_dir = Direction::East;
}



void Npc::changePos() {
    sf::Vector2i newPos = getCaseFacing(m_dir, m_pos);
    
    // check if the zone is a correct one
    if(!m_zone->canWalkOnCase(newPos)) {
        Log("Npc is blocked, reverting to last move", Logger::NPC_INFO);
        m_mover->revertMovement();
        return;
    } 
   
    // Update the position
    m_pos = newPos;
    m_mover->setPosition(m_pos);
}



void Npc::updateSpritePos() {
    sf::Vector2i tileSize = ZoneLayer::tileSize;
    
    // get the time since the last move
    float sinceLastMove = m_mover->getSinceLastMove();
    
    // Quit if pos == oldPos
    if(m_oldPos.x == m_pos.x && m_pos.y == m_oldPos.y) return;
    // Otherwise update the sprite
    float dx = GAME_ZOOM*(m_pos.x-m_oldPos.x)*tileSize.x*sinceLastMove*m_speed;
    float dy = GAME_ZOOM*(m_pos.y-m_oldPos.y)*tileSize.x*sinceLastMove*m_speed;
    
    // If the case was reached, update the pos
    if(dx <= -GAME_ZOOM*tileSize.x || dx >= GAME_ZOOM*tileSize.x || dy <= -GAME_ZOOM*tileSize.y || dy >= GAME_ZOOM*tileSize.y){
        m_oldPos = m_pos;
        m_sprite.setPosition(m_zone->getCaseCenter(m_oldPos));
    }
    else{ // Update the sprite
        sf::Vector2f ds(dx, dy);
        m_sprite.setPosition(m_zone->getCaseCenter(m_oldPos) + ds);
    }
    
}



void Npc::updateTextureRect(float dt) {
    m_textureRect.top = getTextureRectOffset();
    
    // Update the left depending on wether the sprite is moving or not
    if(m_pos != m_oldPos){
        if((m_pos.x+m_pos.y)%2 == 0)
            m_textureRect.left = 0;
        else
            m_textureRect.left = 2*m_textureRect.width;
    }
    else
        m_textureRect.left = m_textureRect.width;
    
    
    // Apply changes
    m_sprite.setTextureRect(m_textureRect);
}



int Npc::getTextureRectOffset() const {

    int height = m_textureRect.height;
    
    if(m_dir == Direction::North)
        return 0;
    if(m_dir == Direction::East)
        return height;
    if(m_dir == Direction::South)
        return 2*height;
    // else
    return 3*height;
}



void Npc::setSpeed(float speed) {
    m_speed = speed;
}

        

int Npc::getSpeed() const {
    return m_speed;
}



sf::Vector2i Npc::getFacedCase() {
    return getCaseFacing(m_dir, m_oldPos);
}



sf::Vector2i Npc::getOldPosition() {
    return m_oldPos;
}



void Npc::setID(NpcID id) {
    m_id = id;
}



NpcID Npc::getID() {
    return m_id;
}



bool Npc::isMoving() const {
    return m_pos != m_oldPos;
}
