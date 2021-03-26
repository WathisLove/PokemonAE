/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameState.hpp
 * Author: Redbuzard
 *
 * Created on 5 juillet 2018, 15:54
 */

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP


#include "../zones/Zone.hpp"
#include "../entities/Character.h"

#include "State.hpp"
#include "../ui/DebugPanel.hpp"

#include <SFML/Audio.hpp>

class Interaction;


class GameState : public State
{
public:
    GameState(StateStack* stack);
    virtual ~GameState();

    
    /**
     * Draw the Game state
     */
    virtual void draw();
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * Overriden Late Update method
     */
    void lateUpdate(float dt) override;

    
    /**
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);
    
    
    /**
     * Manage an incoming GameEvent
     * @param event a const reference to the GameEvent
     */
    void handleGameEvent(const GameEvent& event) override;

    
    /**
     * Get the character of the GameState
     * @return a pointer to the Character
     */
    Character* getCharacter();
    
protected:
//=================// Private methods //==================//

    
    /**
     * Called when the player wants to interact with something
     */
    void interactionEvent();
    
    
    /**
     * Start an interaction with an entity
     * @param e a pointer to the Entity
     */
    void startInteraction(Entity* e);
    
    
    /**
     * Start an interaction with an Npc
     * @param npc a pointer to the Npc
     */
    void startInteraction(Npc* n);
    
    
    /**
     * Start an interaction with a physical Item
     * @param item a pointer to the Physical Item
     */
    void startInteraction(PhysicalItem* item);
    
    
    /**
     * Start an interaction with a BoxPC
     * @param pc a pointer to the BoxPC
     */
    void startInteraction(BoxPC* pc);
    
    
    /**
     * Start an interaction with a Seller
     * @param pc a pointer to the Seller
     */
    void startInteraction(Seller* seller);
    
    
    /**
     * Called when the interaction is finished
     */
    void interactionFinished();
    
    
    /**
     * Try to delete the Interaction
     */
    void tryDeleteInteraction();
    
    
    /**
     * Start the current Interaction if the condition is valid or reset it
     */
    void startInteractionOrReset();
    
    
    /**
     * Update the camera position
     */
    void updateCamera(float dt);
    
//=================// Attributes //==================//
    // Actual Game Zone
    Zone m_zone;
    
    // Main Character
    Character m_character;
    
    // A background music
    sf::Music m_music;
    
    // A debug panel for the Keyboard infos
    DebugPanel m_debugPanel;
    
    // The current Interaction
    Interaction* m_interaction;
    
    // A pointer to the Entity concerned by the Interaction
    Entity* m_interactionEntity;
};

#endif /* GAMESTATE_HPP */

