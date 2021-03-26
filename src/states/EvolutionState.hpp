/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EvolutionState.hpp
 * Author: Redbuzard
 *
 * Created on 2 mars 2020, 20:23
 */

#ifndef EVOLUTIONSTATE_HPP
#define EVOLUTIONSTATE_HPP

#include "State.hpp"
#include "../ui/states/EvolutionStateUI.hpp"
#include "../entities/Character.h"

class EvolutionState : public State {
private:
//==================// Stages for the Evolution State //=============//
    
    enum EvolutionStage{
        DialogBegin,
        PreEvolution,
        Evolution,
        EvolutionCancelled,
        DialogEnd
    };
    
    
public:
    
//==================// Constructor //=============//
    
    EvolutionState(StateStack* stack, Character* character, Pokemon* pokemonUnevolved, PokemonID evolutionID);

    
//==================// Public Methods //=============//
    
    
    /**
     * Choose what to do when the FightState is completed
     */
    void actionOnCompletion();

    /**
     * Inherited draw method
     */
    void draw();

    /**
     * Handle the incoming events
     * @param event a reference to the incoming event
     * @return true if the next State must handle events
     */
    bool handleEvent(sf::Event& event);
    
    /**
     * Update the FightState
     * @param dt the elapsed time in seconds
     * @return true if the next State must be updated
     */
    bool update(float dt);

    /**
     * Check if the State is completed and muste be popped 
     * @return true if the State must be popped
     */
    bool isCompleted() const;

    
private:
//==================// Private methods //=============//
    
    /**
     * Evolve the pokemon
     */
    void evolvePokemon();
    
    
    /**
     * Cancel the evolution
     */
    void cancelEvolution();
    
    
    /**
     * Check if the pokemon didn't evolved yet
     * @return true if the pokemon didn't evolved yet
     */
    bool notEvolvedYet();
    
    
    /**
     * Check if the evolution can still be cancelled
     * @return true if the evolution can be cancelled
     */
    bool canCancel();
    
//==================// Attributes //=============//
    
    // A pointer to the two pokemons
    Pokemon* m_pokemon;
    Pokemon* m_pokemonEvolved;
    
    
    // A pointer to the character
    Character* m_character;

    
    // A boolean to know if the pokemon finally evolved
    bool m_evolved;
    
    // A float containing the seconds passed in the stage
    float m_timePassed;
    
    EvolutionStage m_stage;
    
    // The State UI
    UIEvolutionState m_ui;
};

#endif /* EVOLUTIONSTATE_HPP */

