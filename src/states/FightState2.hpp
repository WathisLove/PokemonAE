/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FightState2.hpp
 * Author: Redbuzard
 *
 * Created on 23 août 2019, 16:27
 */

#ifndef FIGHTSTATE2_HPP
#define FIGHTSTATE2_HPP

#include "State.hpp"
#include "../ui/states/UIFightState.hpp"
#include "../entities/Character.h"
#include "../entities/Trainer.hpp"
#include "../fight/FightStage.hpp"
#include "../fight/FightAction.hpp"
#include "../fight/ennemy_manager/FightEnnemyManager.hpp"
#include "../fight/XPSharer.hpp"

#include <deque>

class FightState2 : public State {
public:
    FightState2(StateStack* stack, Character* character, Trainer* trainer);
    
    FightState2(StateStack* stack, Character* character, Pokemon* wildPokemon);
    
    virtual ~FightState2();

    
//=================// Public functions //==================//
    
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
    
    
    /**
     * Get the character
     * @return a pointer to the character
     */
    Character* getCharacter();
    
    /**
     * Check if the character is defeated
     * @return true if the character is defeated during the fight
     */
    bool isCharacterDefeated() const;
    
    
private:
//=================// Structures //==================//
    
    struct TurnContext{
        // Booleant to know if the ally plays first
        bool allyFirst;
        
        ItemID allyItem, ennemyItem;
        int allySelected, ennemySelected;
        int allyAttack, ennemyAttack;
        
        // Damages
        int damageToAlly, damageToEnnemy;
        
        // The current pokemons
        int currentAlly, currentEnnemy;
        
        // Number of pokeball bounces
        int ballBounces;
        
        // The current Team attacking
        Team currentTeam;
        
        bool ennemyCaptured;
        
        bool flee;
        
        float lastAttackEfficiency;
        
        // The number of hits of the last multi-hit attack
        int attackHitsPlanned;
        int attackHitsDone;
        
        // To know if the pokemon are protected
        bool allyProtected;
        bool ennemyProtected;
        
        // Ablity
        bool showAbility;
        Team abilityTeam;
        
        // Next status that will be inflicted (NoMainStatus if none)
        MainStatusName newAllyStatus, newEnnemyStatus;
        
        FightAction allyAction, ennemyAction;
        
        // Vector of stat changers
        std::vector<StatsChanger> statChangers;
        
        // Queue of attacks to learn
        std::queue<AttackID> learntAttacks;
        
        // Pokemons that will receive xp for the last ennemy KO
        std::queue<Pokemon*> xpReceivers;
    };
    
    struct FightContext{
        // Turns while protecting a pokemon
        int turnsProtectingAlly;
        int turnsProtectingEnnemy;
        
        // Next Attack learner
        Pokemon* attackLearner;
        
        // Pokemon captured if needed
        Pokemon* pokemonCaptured;
        
        // Ally pokemon that went to fight
        std::set<Pokemon*> activeFighters;
    };
    
    
    /**
     * Setup the Turn Context with values that won't interfere with the new one calculated during the turn
     */
    void setupTurnContext();
    
    /**
     * Setup the FightContext
     */
    void setupFightContext();
    
//=================// Turn Methods //==================//
    
    
    /**
     * Clean the Stage Queue
     */
    void cleanQueue();
    
    /**
     * Clean the Stage Queue until a stage with the given name is found
     * @param name the FightStage name we are loking before stopping
     */
    void cleanQueueUntil(FightStageName name);
    
    /**
     * Clean the Stage Queue until a stage with one of the given name is found
     * @param name the FightStage name we are loking before stopping
     */
    void cleanQueueUntil(FightStageName name1, FightStageName name2);
    
    /**
     * Change the TurnContext to set if the ally plays first or not
     */
    void calculateTurnPriority();
    
    /**
     * Set which pokemon will attack first at the next turn
     */
    void setFirstAttackant();
    
    /**
     * Check if the Ally pokemon is KO
     * @return true if the ally is KO
     */
    bool isAllyKO();
    
    /**
     * Check if the Ennemy pokemon is KO
     * @return true if the ennemy is KO
     */
    bool isEnnemyKO();
    
    
    /**
     * Set what will be the action of the ennemy for this turn
     */
    void calculateEnnemyTurn();
    
    
//==================// Action Methods //==================//
    
    
    /**
     * Show the Main Menu
     */
    void showMainMenu();
    
    /**
     * Choose how to change the queue depending on the menu entry selected
     */
    void selectMenu();
    
    
    /**
     * Show the Attack Menu
     */
    void showAttackMenu();
    
    /**
     * Select the pokemon attack
     */
    void selectAttack();
    
    
    /**
     * Try to protect the pokemon of a team
     * @param team the team of the Pokemon the Attack tries to protect
     */
    void tryProtect(Team team);
    
    /**
     * Check if the protect is successfull
     * @param previousTurns the number of previous turns where the pokemon was protected
     * @return true if the protect successed
     */
    bool checkProtectSuccess(int previousTurns);
    
//==================// Switch Methods //==================//
    
    /**
     * Retrieve the ally pokemon
     */
    void retrieveAllyPokemon();
    
    /**
     * Called when retrieving the ally pokemon fails
     */
    void failRetrieveAllyPokemon();
    
    /**
     * Send the ally pokemon
     */
    void sendAllyPokemon();
    
    /**
     * Retrieve the ennemy pokemon
     */
    void retrieveEnnemyPokemon();
    
    /**
     * Send the ennemy pokemon
     */
    void sendEnnemyPokemon();
    
    
    /**
     * Check if the current pokemon of a team can switch out of the fight
     * @param team the team concerned by the switch
     * @return true if the pokemon of the team can leave
     */
    bool canSwitch(Team team);
    
    
    
    /**
     * Use the ally selected item
     */
    void useAllyItem();
    
    
    /**
     * Use the ennemy selected item
     */
    void useEnnemyItem();
    
    
    /**
     * Use a pokemon on the ennemy
     */
    void usePokeball();
    
    
    /**
     * Replace the ennemy sprite with the pokeball thrown
     */
    void replaceEnnemyWithBall();
    
    /**
     * Replace the ennemy sprite with the pokemon sprite
     */
    void replaceEnnemyWithSprite();
    
    
    /**
     * Adds the dialog to capture the ennemy pokemon
     */
    void captureTry();
    
    
    /**
     * Update the pokemon displays
     */
    void updatePokemonDisplays();
    
    
    /**
     * Update the Ally Status
     * Adds a dialog line if the ally doesn't have a status anymore
     */
    void updateAllyStatus();
    
    /**
     * Update the Ennemy Status
     * Adds a dialog line if the ennemy doesn't have a status anymore
     */
    void updateEnnemyStatus();
    
    
    /**
     * Flee the fight
     */
    void flee();
    
    /**
     * Set the Dialog when the Fight is done
     */
    void endFight();
    
    
    /**
     * Quit the FightState
     */
    void quit();
    
    /**
     * Add the dialog at the end
     * @param characterWon true if the character won the fight
     */
    void addEndDialog(bool characterWon);
    
//=================// Stage Methods //==================//
    
    
    /**
     * Check if the current stage is finished
     * @return true if the current stage is finished
     */
    bool isStageFinished();
    
    
    /**
     * Get the current FightStage
     * @return a reference to the current FightStage
     */
    const FightStage& getCurrentStage();
    
    /**
     * Get the last FightStage
     * @return a reference to the last FightStage
     */
    const FightStage& getLastStage();
    
    
    
    /**
     * Pop the current Stage and go to the next one
     */
    void nextStage();
    
    
    
//=================// Queue Modifiers//==================//
    
    /**
     * Push a Stage with its name, its Quit Condition and some actions
     * @param name the FightStage name
     * @param condition the QuitCondition of the new Stage
     * @param onStart the action at the FightStage start (nullptr or 0 for none)
     * @param onUpdate the action at the FightStage update (nullptr or 0 for none)
     * @param onQuit the action at the FightStage quit (nullptr or 0 for none)
     */
    void pushStage(FightStageName name, QuitCondition condition, action onStart = nullptr, action onUpdate = nullptr, action onQuit = nullptr);
    
    /**
     * Push a Stage with its name, its Quit Condition and some actions
     * @param name the FightStage name
     * @param condition the QuitCondition of the new Stage
     * @param lifetime the minimal lifetime of the stage as a float
     * @param onStart the action at the FightStage start (nullptr or 0 for none)
     * @param onUpdate the action at the FightStage update (nullptr or 0 for none)
     * @param onQuit the action at the FightStage quit (nullptr or 0 for none)
     */
    void pushStage(FightStageName name, QuitCondition condition, float lifetime, action onStart = nullptr, action onUpdate = nullptr, action onQuit = nullptr);
    
    
    /**
     * Insert a FightStage after a given stage
     * @param insertAfterStage the FightStage Name that will be before
     * @param stages a pointer to the FightStages that will be inserted
     */
    void insertStageAfter(FightStageName insertAfterStage, FightStage* stage);
    
    /**
     * Insert a queue of FightStages after a given stage
     * @param insertAfterStage the FightStage Name that will be before the queue
     * @param stages a deque of pointers to the FightStages that will be inserted
     */
    void insertStagesAfter(FightStageName insertAfterStage, std::deque<FightStage*>& stages);
    
    /**
     * Insert a FightStage before a given stage
     * @param insertAfterStage the FightStage Name that will be after
     * @param stages a pointer to the FightStages that will be inserted
     */
    void insertStageBefore(FightStageName insertBeforeStage, FightStage* stage);
    
    /**
     * Insert a queue of FightStages before a given stage
     * @param insertBeforeStage the FightStage Name that will be after the queue
     * @param stages a deque of pointers to the FightStages that will be inserted
     */
    void insertStagesBefore(FightStageName insertBeforeStage, std::deque<FightStage*>& stages);
    
    
    /**
     * Push a stage for the dialog state at the beginning of the fight
     */
    void pushStartStage();
    
    
    
    /**
     * Push a stage to select in the main menu
     */
    void pushMainMenuStage();
    
    
    
    /**
     * Push the Menu to select the attacks
     */
    void pushAttackMenuStage();
    
    /**
     * Push a BagStage and add a BagState in the StateStack
     */
    void pushBagStage();
    
    /**
     * Push a TeamStage and add a TeamState in the StateStack
     */
    void pushTeamStage();
    
    
    /**
     * Push the stages for the new turn
     */
    void pushNewTurnStages();
    
    /**
     * Push stages for the Ally turn
     */
    void pushAllyTurn();
    
    /**
     * Push stages for the Ennemy turn
     */
    void pushEnnemyTurn();
    
    /**
     * Push a stage to update health bars
     */
    void pushHealthUpdate();
    
    /**
     * Push stages for the ally to attack
     */
    void pushAllyAttackStages();
    
    /**
     * Push stages for the ennemy to attack
     */
    void pushEnnemyAttackStages();
    
    
    /**
     * Push stages to use a pokeball
     */
    void pushPokeballUseStages();
    
    /**
     * Push stages to use an item
     */
    void pushItemUseStages(Team team);
    
    
    /**
     * Push stages to switch the fighting pokemon
     */
    void pushPokemonSwitchStages(Team team);
    
    
    /**
     * Push the stages at the end of the fight
     */
    void pushEndFightStages();
    
    
    /**
     * Push stages for all the evolutions
     */
    void pushEvolutionStages();
    
    /**
     * Insert stages for giving XP
     */
    void insertXPStages();
    
    /**
     * Insert stages for the effects of a pokemon entering fight
     */
    void insertEnteringEffect(Team team);
    
    
    /**
     * End the turn once a pokemon is KO
     */
    void endTurnByKO();
    
    
//===========// Secondary State //============//
    
    /**
     * Open a TeamState
     */
    void openTeamState();
    
    /**
     * Pop the TeamState and change the queue
     */
    void popTeamState();
    
    
    /**
     * Open a BagState
     */
    void openBagState();
    
    /**
     * Pop the BagState and change the queue
     */
    void popBagState();
    
    
    /**
     * Find the secondary State (TeamState, BagState, ChoiceState, ...) if needed
     */
    void findSecondaryState();
    
    /**
     * Close the secondary state (stop it from waiting before completion)
     */
    void closeSecondaryState();
    
    
    /**
     * Check if the secondary state was quit with or without selecting
     * @return true if the secondary state has a selection
     */
    bool secondaryStateHasSelected();
    
    
    /**
     * Get the Pokemon selected in the TeamState
     * @warning this method will crash if the TeamState was quit without selecting a Pokemon
     * @return a pointer to the pokemon selected
     */
    Pokemon* getTeamSelection();
    
    /**
     * Get the Item selected in the BagState
     * @warning this method will crash if the BagState was quit without selecting a Item
     * @return the ID of the selected Item
     */
    ItemID getBagSelection();
    
    
    /**
     * Get the ally pokemon in the fight
     */
    Pokemon* getAllyPokemon();
    
    /**
     * Get the ennemy pokemon in the fight
     */
    Pokemon* getEnnemyPokemon();
    
    /**
     * Get the index of the ally pokemon in the fight
     */
    int getAllyIndex();
    
    /**
     * Give XP and EVs to all the pokemons once the ennemy is KO 
     */
    void giveXPAndEVs();
    
    
    /**
     * Send a GameEvent for the Fight Result
     */
    void sendFightResultEvent();
        
//=================// Attack methods //============//
    
    /**
     * Check if a pokemon is KO and change the stage queue if so
     */
    void checkKOs();
    
    /**
     * Dialog and damages for the ally attack
     */
    void allyAttack();
    
    /**
     * Dialog and damages for the ennemy attack
     */
    void ennemyAttack();
    
    
    /**
     * Checks if the attackant can attack this turn
     * Adds a dialog line if it can't
     * @param attacker a pointer to the pokemon attacking
     * @return true if the pokemon can attack correctly
     */
    bool canAttackThisTurn(Pokemon* attacker);
    
    /**
     * Make the attacker to attack the defender using attack
     * @param attacker a pointer to the attacking pokemon
     * @param defender a pointer to the defending pokemon
     * @param a pointer to the attack
     * @param the damage dealt to the attack
     * @return the damage dealt befre to the Attacker
     */
    int attackPokemon(Pokemon* attacker, Pokemon* defender, Attack* attack, int previousDamagesToAttacker);
    
    
    /**
     * Insert stages for a multi-hit attack
     * @param attacker a pointer to the attacking pokemon
     * @param defender a pointer to the defending pokemon
     * @param attack a pointer to the attack
     * @param attackerTeam the team of the attacker
     */
    void multiAttackPokemon(Pokemon* attacker, Pokemon* defender, Attack* attack, Team attackerTeam);
    
    
    /**
     * Hit the ally once with the ennemy multi-hit attack
     */
    void hitAllyOnce();
    
    /**
     * Hit the ennemy once with the ally multi-hit attack
     */
    void hitEnnemyOnce();
    
    
    /**
     * Show a dialog to display the number of hits
     */
    void displayNbHits();
    
    
    /**
     * Force the pokemon to use struggle this turn
     * Adds a dialog for the attack
     * @param p a pointer to the struggling pokemon
     */
    void struggle(Pokemon* attacker, Pokemon* defender);
    
    
    /**
     * Deals the ally recoil damages if there is some recoil
     */
    void allyRecoil();
    
    /**
     * Deals the ennemy recoil damages if there is some recoil
     */
    void ennemyRecoil();
    
    
    /**
     * Show a dialog for the efficiency of the last attack
     */
    void attackEfficiency();
    
    
    /**
     * Show the dialog after some stat changes
     */
    void attackStatsChange();
    
    /**
     * Applies a single stat changer to a pokemon
     * @param p a pointer to the targeted pokemon
     * @param stc a reference to the stat changer
     */
    void applyStatChanger(Pokemon* p, StatsChanger& stc);
    
    /**
     * Add a dialog corresponding to the current stat changer
     */
    void dialogCurrentStatChanger(StatsChanger& stc);
    
    
    /**
     * Tries to give a status to the ally and shows a dialog line
     */
    void giveAllyStatus();
    
    /**
     * Tries to give a status to the ennemy and shows a dialog line
     */
    void giveEnnemyStatus();
    
    /**
     * Get the new status dealt by the attack (can be NoMainStatus)
     * @param p a pointer to the pokemin that will get the new Status
     * @param attack a pointer to the used attack
     */
    MainStatusName getNewStatus(Pokemon * defender, Attack* attack);
    
    
    /**
     * Get the trainer name
     * @warning can throw an exception if the ennemy is not a trainer
     * @return a const reference to a string containing the trainer name
     */
    const sf::String& getTrainerName();
    
    
    /**
     * Check if an attack hit is critical
     * @return true if the attack hit is critical
     */
    bool attackHitIsCritical(Pokemon& attacker, Attack& attack);
    
    
    /**
     * Push a stage to learn an attack
     */
    void learnAttacks();
    
    /**
     * Learn attacks after an evolution
     */
    void addEvolutionAttacks();
    
    
    /**
     * Push a stage to learn an attack
     */
    void learnSingleAttack(Pokemon* p, AttackID a);
    
    
    /**
     * Evolve the first pokemon of the team that can evolve
     */
    void evolvePokemons();
    
    
    /**
     * Displas or hide the ability
     * @param display true to show the Ability
     */
    void showAbility();
    
    /**
     * Hides the Ability
     */
    void hideAbility();
    
//=================// Attributes //==================//
    
    
    // A pointer to the secondary state
    State* m_secondaryState;    
    // The secondaryState ID
    StateID m_secondaryStateID;
    
    // The context of the current turn
    TurnContext m_turnContext;
    
    // The context of the current Fight
    FightContext m_fightContext;
    
    // The Stage Queue
    std::deque<FightStage*> m_stages;
    
    
    // The time in seconds since the beginning of the Stage
    float m_stageTime;
    
    // A pointer to the Character
    Character* m_character;
    
    // A pointer to the EnnemyManager
    FightEnnemyManager* m_ennemyManager;
    
    // The XP Sharer
    XPSharer m_xpSharer;
    
//=================// Graphical Attributes //==================//
    
    
    // The FightState UI
    UIFightState m_ui;
    
};

#endif /* FIGHTSTATE2_HPP */

