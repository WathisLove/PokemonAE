/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneNameState.hpp
 * Author: Redbuzard
 *
 * Created on 24 mars 2020, 12:17
 */

#ifndef ZONENAMESTATE_HPP
#define ZONENAMESTATE_HPP

#include "State.hpp"
#include "../entities/Character.h"


class ZoneNameState : public State{
public:
    ZoneNameState(StateStack* stack, Character* character);
    
//=================// Public Inherited functions //==================//
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    void actionOnCompletion();

    
    /**
     * Draw the state
     */
    void draw();
    

    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    bool handleEvent(sf::Event& event);
    
    
    /**
     * Overriden Update method
     */
    bool update(float dt);

    
    /**
     * Late update of the State
     * Using LateUpdate here to match camera movement that occur in the updates below
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual void lateUpdate(float dt);
    
private:
//=================// Private methods //==================//
    
    /**
     * Updatet the zone
     * @param newzone the ZoneID of the new zone
     */
    void updateZone(ZoneID newZone);
    
    
//=================// Attributes //==================//
    
    // The time spent in the state
    float m_timePassed;
    
    // A pointer to the Character
    Character* m_character;
    
    // The offset position
    sf::Vector2f m_offset;
    
    // The lat zone displayed to know when a change occur
    ZoneID m_zone;
    
//=================// Graphical Attributes //==================//

    // Sprite for the Background
    sf::Sprite m_background;
    
    // Text for the Zone Name
    sf::Text m_zoneName;
};

#endif /* ZONENAMESTATE_HPP */

