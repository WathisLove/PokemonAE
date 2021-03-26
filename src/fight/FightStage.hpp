/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightStage.hpp
 * Author: Redbuzard
 *
 * Created on 10 septembre 2019, 19:38
 */

#ifndef FIGHTSTAGE_HPP
#define FIGHTSTAGE_HPP

#include <functional>

class FightState2;

enum FightStageName{
    // Starting the fight
    FS_DialogState,
    
    // A utility Stage used when the queue is cleaned
    FS_QueueCleaned,
    
    FS_Dialog,
    
    // Attacks
    FS_AttackEfficiency,
    FS_Attack,
    FS_LearnAttacks,
    
    // Misc
    FS_CheckKOs,
    FS_HealthUpdate,
    FS_XP,
    FS_Evolution,
    
    // Items
    FS_ItemSelection, // 10
    FS_ItemUse,
    
    // Switching
    FS_PokemonSwitch,
    FS_PokemonSwitchFail,
    
    // Stat Changes
    FS_StatChanges,
    
    // Status
    FS_StatusGive,
    FS_StatusUpdate,
    
    // Stage for menus
    FS_MainMenu,
    FS_EnnemyActionSelection,
    FS_AllyAttackSelection,
    FS_EnnemyAttackSelection,
    FS_AllySelection,
            
    FS_FindSecondaryState,
    
    FS_EndTurn,
    
    FS_Flee,
    FS_QuitFight, // 25
};

enum QuitCondition{
    DialogClosed,
    NoDialogState,
    NoEvolutionState,
    MenuSelected,
    AttackSelected,
    StageStarted,
    PokemonSelected,
    SecondaryStateFound,
    SecondaryStateCompleted,
    FightQuitted,
    TimePassed,
    AllAttacksLearned,
    NoQuitCondition
};

// A typedef for the action functions
typedef std::function<void(FightState2&)> action;


class FightStage {
public:
    
//===============// Constructor //===============// 
    
    /**
     * Construct a Fightstage with a name and a quitCondition
     */
    FightStage(FightStageName name, QuitCondition quitCondition);
    
    
    /**
     * Get the function launched when the stage starts
     * @return the action function
     */
    action onStartAction() const;
    
    /**
     * Get the function launched when the stage updates
     * @return the action function
     */
    action onUpdateAction() const;
    
    /**
     * Get the function launched when the stage ends
     * @return the action function
     */
    action onQuitAction() const;
    
    
//===============// Setters / Getters //===============// 
    
    /**
     * Get the QuitCondition for the FightStage
     * @return a QuitCondition enum
     */
    QuitCondition getQuitCondition() const;
    
    /**
     * Get the FightStage name
     * @return the name as a FightStageName enum
     */
    FightStageName getName() const;   
    
    
    /**
     * Set the action function launched when starting the stage
     * @param startAction the action function at the start
     */
    void setStartAction(action startAction);
    
    /**
     * Set the action function launched when updating the stage
     * @param updateAction the action function at the update time
     */
    void setUpdateAction(action updateAction);
    
    /**
     * Set the action function launched when quitting the stage
     * @param quitAction the action function at the end
     */
    void setQuitAction(action quitAction);
    
    
    /**
     * Get the Stage lifetime
     * @return the lifetime as a float
     */
    float getLifeTime() const;
    
    
    /**
     * Set the Stage lifetime
     * @param time the lifetime as a float
     */
    void setLifeTime(float time);
    
    
protected:
//===============// Attributes //===============// 
    
    // The Stage QuitCondition
    QuitCondition m_quitCondition;
    
    // The Stage name
    FightStageName m_name;
    
    // The action when the fightStage starts
    action m_startAction;
    
    // The action when the fightStage updates
    action m_updateAction;
    
    // The action when the fightStage ends
    action m_quitAction;
    
    // The minimal lifetime of the stage 
    float m_lifeTime;
};

#endif /* FIGHTSTAGE_HPP */

