/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LearnAttackState.hpp
 * Author: Redbuzard
 *
 * Created on 12 février 2020, 20:22
 */

#ifndef LEARNATTACKSTATE_HPP
#define LEARNATTACKSTATE_HPP

#include "State.hpp"
#include "../ui/states/UILearnAttackState.hpp"

class LearnAttackState : public State{
public:
    
    LearnAttackState(StateStack* stack, Pokemon* p, AttackID attackLearning);
    
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
    
private:
//===================// Utility enum //===================//
    
    // Enum for the different stages
    enum LearnStage{
        ls_SelectingAttack,
        ls_ReplaceConfirmation,
        ls_QuitConfirmation
    };
    
    
//===================// Private methods //===================//
    
    /**
     * Move the cursor to the next attack
     */
    void nextAttack();
    
    /**
     * Move the cursor to the previous attack
     */
    void previousAttack();
    
    
    /**
     * Select the current attack
     */
    void selectAttack();
    
    
    /**
     * Push a ChoiceMenu to quit the State
     */
    void quit();
    
    
    /**
     * Choose what to do once the replace ChoiceState is finished
     */
    void choiceReplace();
    
    /**
     * Choose what to do once the quit ChoiceState is finished
     */
    void choiceQuit();
    
    
//===================// Attributes //===================//

    // The State UI
    UILearnAttackState m_ui;
    
    // The pokemon we want to learn an attack to
    Pokemon* m_pokemon;
    
    // The attack ID we want to learn
    AttackID m_newAttackID;
    
    // The Old AttackID
    AttackID m_oldAttackID;
    
    // The current stage
    LearnStage m_currentStage;
    
    // A pointer to the secondary state
    State* m_secondaryState;
    
    // The attack selected
    int m_attackSelected;
    
    // Boolean to know if the attack was learnt
    bool m_attackWasLearnt;
};

#endif /* LEARNATTACKSTATE_HPP */

