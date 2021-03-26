/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.hpp
 * Author: Redbuzard
 *
 * Created on 24 juin 2018, 10:39
 */

#ifndef NPC_HPP
#define NPC_HPP

#include "Entity.hpp"
#include "movements/MoverHeaders.hpp"
#include "NPCId.hpp"


class Npc  : public Entity
{
    
public:
    Npc(const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone);
    
    virtual ~Npc();

    
    /**
     * Update the Pnj
     * @param dt elapsed time since last frame
     */
    virtual void update(float dt);
    
    
    /**
     * Check if the Npc is occuping a position on the map
     * @param pos the position as a Vector2i
     * @return true if the Npc is occuping the position
     */
    bool isOccupingPosition(sf::Vector2i pos) const override;

    
    /**
     * Set the speed of each movement
     * @param speed Movement speed (case/seconds)
     */
    void setSpeed(float speed);
    
    /**
     * Return the NPC Speed
     * @return the speed as an int, corresponding of the number of cases travelled by second
     */
    int getSpeed() const;
    
    
    /**
     * Return the index of the face that the Entity is facing
     * @return the index of the case faced
     */
    sf::Vector2i getFacedCase();
    
    
    /**
     * Get the old position of the Npc
     * This is the position the Npc is leaving or its position if it isn't moving
     * @return the leaving position
     */
    sf::Vector2i getOldPosition();
    
    
    /**
     * Set the NPC Number
     * @param num the NPC ID
     */
    void setID(NpcID id);
    
    /**
     * Get the NPC Number
     * @return the NPC Number as an int
     */
    NpcID getID();
    
    
    /**
     * Check if the Entity is moving
     * @return true if the Entity is moving
     */
    bool isMoving() const override;

protected:
//=================// Protected Methods //==================//
    
    /**
     * Update the direction when the NPC move
     * @param The movement executed by the NPC
     */
    void updateDirection(MovementType mv);
    
    /**
     * Move the NPC (change its direction and position)
     */
    void move(MovementType mv);
    
    /**
     * Change the NPC Position
     */
    void changePos();
    
    /**
     * Update the sprite position
     */
    void updateSpritePos();
    
    
    /**
     * Update the TextureRectangle, depending on the direction and the elapsed time
     * @param dt elapsed time since last frame
     */
    void updateTextureRect(float dt);
    
    /**
     * Return the offset of the TextureRectangle depending on the character Direction
     * @return the offset of the TextureRect for a given Direction
     */
    int getTextureRectOffset() const;
    
    
//=================// Attributes //==================//
    // Old Position (case on which the character was standing until it moved)
    sf::Vector2i m_oldPos;
    
    // Movement speed
    float m_speed;
    
    // The NPC or Trainer Number
    NpcID m_id;
};

#endif /* NPC_HPP */

