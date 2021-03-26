/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StoryTrigger.hpp
 * Author: Redbuzard
 *
 * Created on 13 juin 2020, 09:16
 */

#ifndef STORYTRIGGER_HPP
#define STORYTRIGGER_HPP

#include "FieldObject.hpp"
#include "../entities/NPCId.hpp"
#include "../Direction.h"

class StoryTrigger : public FieldObject{
public:
    /**
     * Default constructor
     * @param rect the rect of the FieldObject
     * @param npc the Npc concerned by the StoryTrigger
     * @param deactivatesAfterTrigger true if the Trigger deactivates once it was 
     */
    StoryTrigger(sf::IntRect rect, NpcID npc, bool deactivatesAfterTrigger, Direction repulseDir);
    
    
//=================// Getters / Setters //==================//
    
    /**
     * Get the Npc concerned by the StoryTrigger
     * @return the Npc ID
     */
    NpcID getNpc();
    
    /**
     * Get the direction to repulse the character
     * @return the Direction as an enum
     */
    Direction getRepulseDir() const;
    
    /**
     * Check if a given pos is insinde the trigger
     * @param pos the position we want to check
     * @return true if the pos is in the Field
     */
    bool isinsideRect(sf::Vector2i pos) const override;
    
            
    /**
     * Set the Story Trigger to be active or not
     * @param active true if the Story Trigger must be active
     */
    void setActive(bool active);
    
    
    /**
     * Get if the Story Trigger deactivates after a trigger
     * @return true if the StroyTrigger must be deactivated once triggered
     */
    bool deactivatesAfterTrigger();
    
    
protected:
//=================// Attributes //==================//
    
    // The NPC ID concerned
    NpcID m_npcID;
    
    // A boolean to know if the StoryTrigger is active
    bool m_isActive;
    
    // A booleant to know if it must be deactivated once triggered
    bool m_deactivatesAfterTrigger;
    
    // Repulse direction
    Direction m_repulseDirection;
};

#endif /* STORYTRIGGER_HPP */

