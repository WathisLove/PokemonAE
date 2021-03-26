/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TeamState.hpp
 * Author: Redbuzard
 *
 * Created on 15 avril 2019, 12:41
 */

#ifndef TEAMSTATE_HPP
#define TEAMSTATE_HPP

#include "State.hpp"
#include "../team/TeamEntry.hpp"
#include "../ui/ChoiceMenu.hpp"

/**
 * A state used to display the team and choose between all the pokemons
 */
class TeamState : public State{
public:
    
    TeamState(StateStack* stack, Character* c);
    
    
//==================// Public Methods //===================//
    
    /**
     * Draw the state
     */
    virtual void draw();
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
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
     * Check if the TeamState has selected a pokemon
     * @return true if a pokemon was selected
     */
    bool hasSelectedPokemon();
    
    
    /**
     * Get the currently selected pokemon
     * @return a Pointer to the pokemon
     */
    Pokemon* getSelectedPokemon();
    
    
    /**
     * Get the index of the currently selected pokemon
     * @return the pokemon indx as an int
     */
    int getSelectedPokemonIndex();
    
    
    /**
     * Unselect the pokemon
     */
    void unselectPokemon();
    
    
    /**
     * Update the whole team display
     */
    void updateTeamDislay();
    
    
    /**
     * Deactivates the menu (for example when the BagState is used a secondary state
     */
    void deactivateMenus();
    
    /**
     * Set the menu entries to be used during a fight
     */
    void setFightEntries();
    
    
    /**
     * Force the TeamState to select a pokemon and to do not leave before
     */
    void forceSelection();
    
    
    /**
     * Set the index of the pokemon currently fighting
     * @param index te index of the pokemon as an int
     */
    void setPokeInFight(int index);
    
    
    /**
     * Try if we need to setup to learn an attack to a pokemon
     * @return true if there is a state that wants to learn an attack
     */
    void stateTryToLearnAttack();
    
    /**
     * Set the TeamState so as to show which pokemons can learn a CT
     * @param ctAttack the AttackID of the attack contained in the CT
     */
    void setToLearnCT(AttackID ctAttack);
    
private:
    
//==================// Private enum //===================//
    
    // Enum to know what stage we are currently in
    enum TeamStage{
        TChoosingPokemon,
        TChoosingAction,
        TObjectChoosing,
        TObjectMenu,
        TObjectMoving,
        TObjectTaking,
        TObjectReplacing,
        TMovingPokemon,
        TResumePokemon,
    };
    
    
//==================// Private functions //===================//
    
    
    /**
     * Manage events when choosing a pokemon
     * @param event a reference to the Event
     */
    void eventChoosingPokemon(sf::Event& event);
    
    
    /**
     * Manage events when choosing an action
     * @param event a reference to the Event
     */
    void eventChoosingAction(sf::Event& event);
    
    
    /**
     * Manage events when choosing an action for the object
     * @param event a reference to the Event
     */
    void eventObjectMenu(sf::Event& event);
    
    
    /**
     * Manage events to move around a pokemon object
     * @param event a reference to the Event
     */
    void eventMovingObject(sf::Event& event);
    
    
    /**
     * Manage events to move a pokemon in the team
     * @param event a reference to the Event
     */
    void eventMovingPokemon(sf::Event& event);
    
    
    /**
     * Update the entries when a new one is selected
     */
    void updateEntries();
    
    
    /**
     * Move the selector to the left
     */
    void goLeft();
    
    /**
     * Move the selector to the right
     */
    void goRight();
    
    /**
     * Move up the selector 
     */
    
    void goUp();
    /**
     * Move down the cursor
     */
    void goDown();
    
    
    /**
     * Get the last selected pokemon
     * @return a Pointer to the pokemon
     */
    Pokemon* getLastSelectedPokemon();
    
    
    /**
     * Get the maximum index possible for the selected entry
     * @return the max index as an int
     */
    int getMaxIndex();
    
    
    /**
     * Set the entries for the constructor
     */
    void setEntries();
    
    
    /**
     * Select the current entry when needed by the events 
     */
    void choosePokemon();
    
    
    /**
     * Choose an action from the opened menu 
     */
    void chooseAction();
    
    /**
     * Choose an action from the opened object menu 
     */
    void chooseObjectAction();
    
    
    
    /**
     * Open a bag state to select an object
     */
    void openBag();
    
    /**
     * Take the object from the Pokemon, and show a small message
     */
    void takeObject();
    
    /**
     * Replace the object from the pokemon 
     */
    void replaceObject();
    
    /**
     * Open a pokemon State to show its infos
     */
    void openPokemonInfos();
    
    
    /**
     * Switch the currently selected pokemon with the last
     */
    void switchTeamMembers();
    
    /**
     * Function that look for the secondary state
     */
    void findSecondaryState();
    
    /**
     * Setup the TeamMenus
     */
    void setupMenus();
    
    
//==================// Attributes //===================//
    
    // A pointer to the character
    Character* m_character;
    
    // The selected entry as an int
    int m_selectedEntry;
    
    // The last selected entry as an int
    int m_lastSelectedEntry;
    
    // The current stage
    TeamStage m_currentStage;
    
    
    // A pointer to a state that can either be a BagState or a PokemonState
    // This pointer is used to get some info about what item we want to give to the pokemon for example
    State* m_secondaryState;
    
    
    // A buffer for the item once selected
    Item* m_itemBuffer;
    
    
    // Force to select a pokemon
    bool m_mustSelectPokemon;
    
    // Index of the pokemon already in the Fight
    int m_pokeInFight;
    
    
    // Boolean to know if we are trying to learn a CT
    bool m_learningCt;
    
//==================// Graphical Attributes //===================//
    
    // The menu for the current pokemon
    ChoiceMenu m_actionMenu;
    
    // The menu for the object choices
    ChoiceMenu m_objectMenu;
    
    // Background Sprite
    sf::Sprite m_background;
    
    // All the PokemonTeamEntry
    std::vector<TeamEntry> m_pokemonTeamEntry;
};

#endif /* TEAMSTATE_HPP */

