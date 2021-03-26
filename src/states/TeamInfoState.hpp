#ifndef TEAMINFOSTATE_HPP
#define TEAMINFOSTATE_HPP

#include "State.hpp"
#include "../entities/Character.h"
#include "../ui/states/UITeamInfoState.hpp"


class TeamInfoState : public State {
public:
    TeamInfoState(StateStack* stack, Character* character);
    
    
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
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    bool update(float dt);
    
//=================// Public functions //==================//
    
private:

    
//=================// Private functions //==================//
    
    /**
     * Show the infos for the next pokemon 
     */
    void showNextPokemon();
    
    /**
     * Show the infos for the previous pokemon 
     */
    void showPreviousPokemon();
    
    
    /**
     * Show the next info panel
     */
    void showNextInfoPanel();
    
    /**
     * Show the infos for the previous pokemon 
     */
    void showPreviousInfoPanel();
    
    
    /**
     * Select the attacks to display its details
     */
    void showAttacksDetails();
    
    /**
     * Show the next attack of the pokemon
     */
    void showNextAttack();
    
    /**
     * Show the previous attack of the pokemon 
     */
    void showPreviousAttack();
    
    /**
     * Stop showing the attack details 
     */
    void unshowAttacks();
    
    
    /**
     * Get the current pokemon
     * @return a pointer to the current pokemon
     */
    Pokemon* getCurrentPokemon();
    
    /**
     * Get the current attack
     * @return a pointer to the current attack
     */
    Attack* getCurrentAttack();
    
    
    /**
     * Setup the current pokemon
     */
    void setupCurrentPokemon();
    
//=================// Attributes //==================//

    // A pointer to the character
    Character* m_character;
    
    // The index of the current pokemon
    int m_currentPokemon;
    
    // The index of the current pokemon
    PokemonInfoPanel m_currentPanel;
    
    // A boolean to store if the attacks were selected
    bool m_showAttackDetails;
    
    // The attack currently selected
    int m_currentAttack;
    
//=================// Graphical Attributes //==================//
    
    // The UI for the Team Info State
    UITeamInfoState m_ui;
};

#endif /* TEAMINFOSTATE_HPP */

