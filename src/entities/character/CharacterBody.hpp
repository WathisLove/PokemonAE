/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CharacterBody.hpp
 * Author: Redbuzard
 *
 * Created on 21 juin 2020, 10:25
 */

#ifndef CHARACTERBODY_HPP
#define CHARACTERBODY_HPP

#include <SFML/Graphics.hpp>
#include "../../Direction.h"
#include "../../Enums.hpp"

class Zone;

class CharacterBody : public sf::Drawable{
public:
    
//=================// Constructor //==================//
    
    /**
     * Default constructor
     * @param sprite a reference to the Character sprite
     * @param speed the speed of the character in cases/s
     */
    CharacterBody(sf::Sprite& sprite, float speed, Zone* zone);
    
    
//=================// Public methods //==================//
    
    
    /**
     * Update the CharacterBody
     * @param dt the elapsed time in seconds
     */
    void update(float dt);
    
    
    /**
     * Freeze the CharacterBody so it won't leave the next position
     * @param frozen true if the character must be frozen
     */
    void freeze(bool frozen);


    /**
     * Manage a given move order and move the body accordingly
     */
    void manageMove(MovementType move);
    
    
    /**
     * Toggle if the Character is running or not
     */
    void toggleRun();
    

//=================// Inherited methods //==================//
    
    /**
     * Overriden Draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


//=================// Getters / Sellers //==================//
    
    /**
     * Set the position of the Character in the Zone
     * @param pos the position of the Character
     */
    void setPosition(sf::Vector2i pos);
    
    
    /**
     * Get the current position of the character
     * It is also the case the Character is leaving if in movement
     */
    sf::Vector2i getPosition() const;
    
    /**
     * Get the next position of the character
     * @warning throw an exception if the Character isn't moving
     */
    sf::Vector2i getNextPosition() const;
    
    
    /**
     * Check if the Character is moving
     * @return true if the Character is moving
     */
    bool isMoving() const;
    
    /**
     * Check if the Character body was moving last frame
     * @return true if the Character was moving last frame
     */
    bool wasMoving() const;
    
    
    /**
     * Cjeck if the Character is jumping 
     * @return true if the character is jumping
     */
    bool isJumping() const;


    /**
     * Set the Direction the Character must be looking in
     * @param dir the Direction the Character must be looking in
     */
    void setDirection(Direction dir);

    /**
     * Get the Body direction
     * @return the body direction as a Direction Enum
     */
    Direction getDirection() const;


    /**
     * Check if the Character Body is frozen
     * @return true if the body is frozen
     */
    bool isFrozen() const;

    
    /**
     * Get the case in front of the current case
     * @param distance the distance of the faced case
     * @return the position of the case in front of the body
     */
    sf::Vector2i getFrontCase(int distance = 1) const;

private:
//=================// Private methods //==================//
    
    /**
     * Check if the Character reached the next position
     * @return true if the next position was reached
     */
    bool hasReachedNextPosition();
    
    
    /**
     * Called when the Character reached the next position
     */
    void reachNextPosition();
    
    
    /**
     * Called once the position is reached to update the CharacterBody
     */
    void endMovement();
    
    
    /**
     * Reset the time passed
     */
    void resetTime();
    
    
    /**
     * Set the Texture Rectangle
     */
    void setTextureRect();
    
    
    /**
     * Set the sprite position when moving normally
     */
    void setSpritePosition();


    /**
     * Set the Sprite position when the Character is Jumping
     */
    void setJumpSpritePosition();
    
    
//=================// Movement methods //==================//

    /**
     * Jump in a given direction
     */
    void jump();

    
    /**
     * Update the Character Body to look Up
     */
    void lookUp();
    
    /**
     * Update the Character Body to look Down
     */
    void lookDown();
    
    /**
     * Update the Character Body to look in the Right direction
     */
    void lookRight();
    
    /**
     * Update the Character Body to look in the Left direction
     */
    void lookLeft();
    
    
    /**
     * Update the Character to move Up one case
     */
    void goUp();
    
    /**
     * Update the Character to move Down one case
     */
    void goDown();
    
    /**
     * Update the Character to move Right one case
     */
    void goRight();
    
    /**
     * Update the Character to move Left one case
     */
    void goLeft();
    
    
    /**
     * Check if the Character must jump in the current direction
     * @return true if the Character must jump 
     */
    bool mustJump() const;
    
//=================// Attributes //==================//
    
    // The time the character spend on each movement
    float m_moveTime;
    
    // A pointer to the Zone
    Zone* m_zone;
    
    // The current position of the Character
    sf::Vector2i m_pos;
    
    // The Next position of the Character
    sf::Vector2i m_nextPos;
    
    // The time passed during the movement
    float m_timePassed;

    // A boolean to know if the Character body is frozen
    bool m_isFrozen;

    // A boolean to know if the Character is jumping
    bool m_isJumping;
    
    // The Character jump speed
    float m_jumpSpeed;
    
    // A boolean to know if the character is running
    bool m_isRunning;
    
    // Number of following frames without moving
    unsigned int m_framesWithoutMoving;
    
//=================// Graphical Attributes //==================//
    
    // The current Direction of the Character
    Direction m_direction;
    
    // A sprite for the Character
    sf::Sprite& m_sprite;
};

#endif /* CHARACTERBODY_HPP */

