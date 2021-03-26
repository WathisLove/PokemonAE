/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   StateStack.hpp
 * Author: Redbuzard
 *
 * Created on 4 juillet 2018, 10:40
 */

#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include <vector>
#include "StateID.hpp"
#include "../entities/Entity.hpp"
#include "../entities/Character.h"
#include "../Constants.hpp"
#include "GameEvent.hpp"


enum StackAction{
    Push,
    Pop,
    Clear
};


// Forward declaration of State and Context classes
class State;
class Context;


class StateStack {
public:
    StateStack(Context& context);
    ~StateStack();

    
    /**
     * Update the states in m_states until one request to stop updating others
     * @param dt elapsed time since last frame, in seconds
     */
    void update(float dt);
    
    /**
     * Draw the states in m_states
     */
    void draw();
    
    /**
     * Manage all the events for each states
     */
    void manageEvents();
    
    
    /**
     * Apply all pending changes 
     */
    void applyPendingChanges();
    
    /**
     * Request stack to pop an item
     */
    void requestStackPop();
    
    
    
    /**
     * Request stack to add an item
     */
    void requestStackPush(StateID id);
    
    /**
     * Request stack to add an item
     * @param p a pointer to the pokemon
     */
    void requestStackPush(StateID id, Pokemon* p);
    
    /**
     * Request stack to add an item
     * @param character a pointer to the related character
     */
    void requestStackPush(StateID id, Character* character);
    
    /**
     * Request stack to add an item
     * @param e a pointer to the related Entity
     */
    void requestStackPush(StateID id, Entity* e);
    
    /**
     * Request stack to add an item
     * @param character a pointer to the related Character
     * @param e a pointer to the related Entity
     */
    void requestStackPush(StateID id, Character* character, Entity* e);
    
    
    /**
     * Special stack push used to display a dialog
     */
    void requestStackPushDialog(const sf::String& str);
    
    /**
     * Special stack push used to display a dialog with a choice box
     */
    void requestStackPushChoice(const sf::String& str);
    
    /**
     * Request to push a ChoiceState with given entries
     */    
    void requestStackPushChoice(const sf::String& str, std::vector<sf::String*>* entries);
    
    
    /**
     * Special stack push used to display a reaction
     */
    void requestStackPushReaction(Entity* e, ReactionType reaction);
    
    /**
     * Special stack push used to display a black screen
     */
    void requestStackPushBlack(float time);
    
    /**
     * Special stack push used to push a fight with a trainer
     */
    void requestStackPushFight(Character* character, Entity* trainer);
    
    /**
     * Special stack push used to push a fight with a wild pokemon
     */
    void requestStackPushFight(Character* character, Pokemon* wildPokemon);
    
    /**
     * Special stack push used to display a transition state
     */
    void requestStackPushTransition(Direction dir);
    
    /**
     * Special stack push used to display a transition state
     */
    void requestStackPushTrainerState(Character* character, Entity* trainer);
    
    /**
     * Special stack push used to give an item to the player and display a dialog box
     */
    void requestStackPushItemGiftState(ItemID item, int number);
    
    /**
     * Special stack push used to give a badge to the player
     */
    void requestStackPushBadge(int badgeNumber);
    
    
    /**
     * Request a Stack push for a pokemon evolution
     * @param character a pointer to the character
     * @param pokemonUnevolved a pointer to the pokemon unevolved
     * @param evolutionID the PokemonID of the evolution
     */
    void requestStackPushEvolutionState(Character* character, Pokemon* pokemonUnevolved, PokemonID evolutionID);
    
    
    /**
     * Request to push a BoxState
     */
    void requestStackPushBox();
    
    /**
     * Request to push a SellerState
     */
    void requestStackPushSeller(Entity* seller);
    
    
    /**
     * Request the Stack to push a State to name the Character
     */
    void requestStackPushNameCharacter();
    
    /**
     * Request the Stack to push a State to name a pokemon
     * @param pokemon a pointer to the pokemon we want to rename
     */
    void requestStackPushNamePokemon(Pokemon* pokemon);
    
    
    /**
     * Request to push a EntityMove State
     * @param entity a pointer to the Entity
     * @param mover a pointer to the EntityMover
     */
    void requestStackPushEntityMove(Entity* entity, EntityMover* mover);
    
    
    /**
     * Push a State with a pokemon and an attack
     * @param id the StateID of the new State
     * @param poke a pointer to the pokemon
     * @param attackID the AttackID of the Attack
     */
    void requestStackPush(StateID id, Pokemon* poke, AttackID attackID);
    
    
    /**
     * Push a State to force an Entity to move
     * @param character a pointer to the Character 
     * @param entity a pointer to the Entity
     * @param repulseCharacter a boolean to know if the State must then repulse the Character
     * @param dir the repulse direction
     */
    void requestStackPushForceMove(Character* character, Entity* entity, bool repulseCharacter, Direction dir);
    
    
    /**
     * Push a State to Heal the Character
     */
    void requestStackPushHeal();
    
    
    /**
     * A stack used to dispaly the player menu
     */
    void requestStackPushMenu(Character* character);
    
    /**
     * Request stack to clear itself
     */
    void requestStackClear();
    
    
    /**
     * Look in the stack to see if there is one state or more with the given ID
     * @param id the id researched
     * @return true if the id was found
     */
    bool hasStateOfID(StateID id);
    
    /**
     * Look in the stack to get the first state of the given ID (from the first to the last added)
     * @param id the id researched
     * @return a pointer to the found State
     */
    State* getStateOfID(StateID id);
    
    
    
//=================// Event Methods //==================//
    
    /**
     * Adds a GameEvent to the queue of events
     * @param event a pointer to the new GameEvent
     */
    void addGameEvent(GameEvent* event);
    
    
//=================// Getters/Setters //==================//
    /**
     * Return the game context
     * @return 
     */
    Context& getContext();
    
    
private:
//=================// Privates methods //==================//
    
    /*
     * Structure used to apply changes to the stack
     */
    struct PendingChange{
        PendingChange();        
        
        StackAction action;
        StateID id;
        Entity* entity;
        Pokemon* poke;
        Character* character;
        AttackID attackID;
        float duration;
        Direction dir;
        PokemonID pokeID;
        sf::String* string;
        ItemID item;
        int i_value;
        bool val;
        ReactionType reaction;
        std::vector<sf::String*>* choiceEntries;
        EntityMover* mover;
    };
    /**
     * Add a state to the stack
     */
    void pushState(PendingChange change);
    
    /**
     * Pop a state
     */
    void popState();
    
    /**
     * Pop a state
     */
    void clearStack();
    
    
    /**
     * Take a screenshot and save it in screenshots directory
     */
    void takeScreenShot() const;
    
    
    /**
     * Toggle the display of stack debug messages
     */
    void toggleDebugMessages();
    
    
    /**
     * Handle all the stored GameEvents
     */
    void handleGameEvents();
    
    /**
     * Ask the States to handle a single Event 
     * @param event a pointer to the Event we want to manage
     */
    void handleEvent(GameEvent* event);
    
    
//=================// Attributes //==================//
    // Stack of States
    std::vector<State*> m_states;
    
    // Pending Changes
    std::vector<PendingChange> m_changes;
    
    // A queue for the Incoming Events
    std::queue<GameEvent*> m_gameEvents;
    
    // Context of render
    Context& m_context;
    
    // Game speed
    int m_gameSpeed;
    
    // Boolean to know if we must show Debug messages
    bool m_debugActivated;
};

#endif /* STATESTACK_HPP */

