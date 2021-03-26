/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Entity.hpp
 * Author: Redbuzard
 *
 * Created on 21 juin 2018, 12:22
 */

#ifndef ENTITY_HPP
#define ENTITY_HPP


#include <SFML/Graphics.hpp>
#include "../Direction.h"
#include "movements/MoverHeaders.hpp"
#include "../Context.hpp"
#include <vector>


class Zone;


/**
 * Different types of Entities
 */
enum class EntityType{
    NPC_Type,
    Trainer_Type,
    PhysicalItem_Type,
    BoxPC_Type,
    Character_Type,
    Seller_Type,
    EmptyEntity_Type
};
    

class Entity : public sf::Drawable{
public:
//=================// Public Methods //==================//
    Entity(const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone);
    
    virtual ~Entity();

    
    /**
     * Update the Entity
     * @param dt elapsed time since last frame
     */
    virtual void update(float dt);
    
    
    /**
     * Check if the Entity is occuping the given position
     * @return true if the position is occupied by the entity
     */
    virtual bool isOccupingPosition(sf::Vector2i pos) const;
    
    
    /**
     * Overrided function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Kill the Entity so it can be deleted 
     */
    void killEntity();
    
    
    /**
     * Check if the Entity is moving
     * @return true if the Entity is moving
     */
    virtual bool isMoving() const;
    
    
//=============// Getters/Setters //=============//
    /**
     * Check if the Entity is still alive
     * @return 
     */
    bool isAlive() const;
    
    
    /**
     * Set the zone of the Entity
     * @param zone of the entity
     */
    void setZone(Zone* zone);
    
    
    /**
     * Get the zone of the Entity
     * @return a pointer to the zone of the entity
     */
    Zone* getZone();
    
    
    /**
     * @return the position of the sprite center
     */
    virtual sf::Vector2i getPosition() const;
    
    /**
     * Set the Entity at the given position
     * @param pos new position of the Entity
     */
    virtual void setPosition(sf::Vector2i pos);
    
    
    /**
     * Return the index of the face that the Entity is facing
     * @return the index of the case faced
     */
    sf::Vector2i getFacedCase() const;
    
    
    /**
     * @return the coordinates of the sprite center
     */
    virtual sf::Vector2f getSpriteCenter() const;
    
    /**
     * Center the sprite at the given position
     * @param pos position of the sprite
     */
    virtual void setSpriteCenter(sf::Vector2f pos);
    
    
    /**
     * Return the direction of the Entity
     */
    virtual Direction getDirection() const;
    
    
    /**
     * Set the Entity Direction
     */
    virtual void setDirection(Direction dir);
    
    
    /**
     * Set the EntityMover of the Entity
     * @param mover a pointer to the new EntityMover
     */
    void setMover(EntityMover* mover);
    
    /**
     * Replace the Entity Mover with a NoMover one
     */
    void clearMover();
    
    
    /**
     * Get the Entity Type
     * @return the entity type as an enum
     */
    EntityType getType() const;
    
protected:
//=================// Private Functions //==================//
    
    
//=================// Attributes //==================//
    // Entity sprite
    sf::Sprite m_sprite;
    
    // Zone of the Entity
    Zone* m_zone;
    
    // Direction of the character (the direction in which it is looking)
    Direction m_dir;
    
    // Position (case on which the character will stand when it moves)
    sf::Vector2i m_pos;
    
    // Texture rectangle for the sprite
    sf::IntRect m_textureRect;
    
    // True if the Entity must be kept alive
    bool m_isAlive;
    
    
    // Entity Mover
    EntityMover* m_mover;
    
    // The Entity type
    EntityType m_type;
};

#endif /* ENTITY_HPP */

