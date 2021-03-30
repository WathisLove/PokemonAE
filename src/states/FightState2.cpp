#include "FightState2.hpp"
#include "TeamState.hpp"
#include "BagState.hpp"
#include "ChoiceState.hpp"
#include "../Utilities.hpp"
#include "../inventory/Item.hpp"
#include "MenuState.hpp"
#include "../zones/Zone.hpp"
#include "../utility/Logger.hpp"

#include "../fight/ennemy_manager/FightTrainerManager.hpp"
#include "../fight/ennemy_manager/FightWildManager.hpp"


#include <iostream>
#include <cassert>

FightState2::FightState2(StateStack* stack, Character* character, Trainer* trainer) :
State(stack),
m_character(character),
m_secondaryState(nullptr),
m_secondaryStateID(StateID::TrainerFightS),
m_ui(stack->getContext(), character->getPokemonAt(0), trainer->getPokemonAt(0)),
m_stageTime(0){
    
    // Setup the Turn and Context at the beginning
    setupTurnContext();
    setupFightContext();
    
    // Set the EnnemyManager
    m_ennemyManager = new FightTrainerManager(trainer);
    
    // Set the ID
    m_id = StateID::TrainerFightS;
    
    // Push the start stage
    pushStartStage();
    
    // Push the menu stages
    pushMainMenuStage();
    
    // Save the Team Order
    m_character->getPokemonTeam()->saveTeamOrder();
    
    
    // Set the UI with the first pokemon not KO
    m_ui.setAlly(getAllyPokemon());
    m_ui.setEnnemy(getEnnemyPokemon());
    
    // Add the first pokemon to the list of actives
    m_fightContext.activeFighters.emplace(getAllyPokemon());
    
    // Add the encounter
    m_xpSharer.addFaced(getEnnemyPokemon(), getAllyPokemon());
}



FightState2::FightState2(StateStack* stack, Character* character, Pokemon* wildPokemon) :
State(stack),
m_character(character),
m_secondaryState(nullptr),
m_secondaryStateID(StateID::WildFightS),
m_ui(stack->getContext(), character->getPokemonAt(0), wildPokemon),
m_stageTime(0){
    // Setup the Turn and Context at the beginning
    setupTurnContext();
    setupFightContext();
    
    // Set the EnnemyManager
    m_ennemyManager = new FightWildManager(wildPokemon);
    
    // Set the ID
    m_id = StateID::WildFightS;
    
    // Push the start stage
    pushStartStage();
    
    // Push the menu stages
    pushMainMenuStage();
    
    // Save the Team Order
    m_character->getPokemonTeam()->saveTeamOrder();
    
    // Set the UI with the first pokemon not KO
    m_ui.setAlly(getAllyPokemon());
    
    m_ui.setEnnemy(getEnnemyPokemon());
    
    // Add the first pokemon to the list of actives
    m_fightContext.activeFighters.emplace(getAllyPokemon());
    
    // Push a Dialog in front
    m_ui.addDialog(L"Un " + wildPokemon->getName() + L" sauvage apparaît !");
}



FightState2::~FightState2() {
    // Deleting the ennemy manager
    delete m_ennemyManager;
}



void FightState2::actionOnCompletion() {
    m_stack->requestStackPop();
    
    // Restore the Team Order
    m_character->getPokemonTeam()->reloadTeamOrder();
    m_character->updateTeamPreview();
    
    // Pop the SecondaryStages that might be left
    if(m_stack->hasStateOfID(StateID::TeamS))
        m_stack->requestStackPop();
    if(m_stack->hasStateOfID(StateID::BagS))
        m_stack->requestStackPop();
    
    // Clean the queue
    cleanQueue();
    
    // Ennemy captured -> He looses
    if(m_turnContext.ennemyCaptured){
        m_ennemyManager->endFight(false);
        m_stack->requestStackPushNamePokemon(m_fightContext.pokemonCaptured);
    }
    // Ennemy captured or we flee -> He Wins
    else if(m_ennemyManager->hasPokemonsNotKO() || m_turnContext.flee)
        m_ennemyManager->endFight(true);
    // Else : No pkmn left -> He Looses
    else
        m_ennemyManager->endFight(false);
    
    // Send the GameEvent for the Fight Result
    sendFightResultEvent();
}



void FightState2::draw() {
    // Get the render window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // Draw the UI
    window.draw(m_ui);
}



bool FightState2::handleEvent(sf::Event& event) {
    
    if(event.type == event.KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        
        // Debug Key : F7 close the fight
        if(key == sf::Keyboard::F7){
            cleanQueue();
            
            // Ennemy loose the fight
            m_turnContext.flee = true;
            
            // End the Fight for the EnnemyManager
            m_ennemyManager->endFight(false);

            m_character->freeze(false);

            // End the Fight
            pushEndFightStages();
        }
        
        // Debug Key : (-) set the Ennemy HP to 1
        if(key == sf::Keyboard::Add){
            getEnnemyPokemon()->setHP(std::min(getEnnemyPokemon()->getHealth(), 1));
            updatePokemonDisplays();
        }
        // Debug Key : (-) set the Ally HP to 1
        if(key == sf::Keyboard::Subtract){
            getAllyPokemon()->setHP(std::min(getAllyPokemon()->getHealth(), 1));
            updatePokemonDisplays();
        }
    }
    
    m_ui.handleEvent(event);
    
    return false;
}



bool FightState2::isCompleted() const {
    return m_isCompleted;
}



bool FightState2::update(float dt) {
    
    // Update the uI for animations
    m_ui.update(dt);
    
    // Update the time passed
    m_stageTime += dt;
    
    // Loop to see if the current stage is finished
    while(isStageFinished())
        nextStage();
    
    
    // Update action
    action updateAction = getCurrentStage().onUpdateAction();
    
    // Do the Update Action of the current Stage
    if(updateAction != nullptr)
        updateAction(*this);
    
    return false;
}



void FightState2::openTeamState() {
    // Push a TeamState
    m_stack->requestStackPush(StateID::TeamS, m_character);
    
    // Set the SecondaryState ID
    m_secondaryStateID = StateID::TeamS;
}



void FightState2::popTeamState() {
    TeamState* ts = (TeamState*)m_secondaryState;
    
    if(ts->hasSelectedPokemon()){
        // Update the turn context
        m_turnContext.allySelected = ts->getSelectedPokemonIndex();
        m_turnContext.allyAction = FightAction::FA_Switch;
        
        // Push the new turn stages if the ally is not KO (to prevent attack after KO switch)
        if(!getAllyPokemon()->isKO())
            pushNewTurnStages();
        else{
            // Insert stages for the Switch Dialog
            pushAllyTurn();
            pushMainMenuStage();
        }
    }
    else{
        pushMainMenuStage();
    }
    
    // Pop the state
    m_secondaryState->setAsSecondaryState(false);
    m_secondaryState = nullptr;
}



void FightState2::openBagState() {
    // Push a BagState
    m_stack->requestStackPush(StateID::BagS, m_character);
    
    // Set the SecondaryState ID
    m_secondaryStateID = StateID::BagS;
}



void FightState2::popBagState() {
    BagState* bs = (BagState*)m_secondaryState;
    
    if(bs->hasSelectedItem()){
        // Update the turn context
        m_turnContext.allyAction = FightAction::FA_Item;
        m_turnContext.allyItem = bs->getItemIDSelected();
        m_turnContext.allySelected = bs->getSelectedPokemonIndex();
        
        // Push the correct stages in the queue
        pushNewTurnStages();
    }
    else{
        pushMainMenuStage();
    }
    
    // Pop the state
    m_secondaryState->setAsSecondaryState(false);
    m_secondaryState = nullptr;
}



void FightState2::findSecondaryState() {
    // Looking for the secondaryState
    if(m_stack->hasStateOfID(m_secondaryStateID)){
        // Get the State
        m_secondaryState = m_stack->getStateOfID(m_secondaryStateID);
        std::cout << "SecondaryState of ID" << m_secondaryStateID << " found !" << std::endl;
        
        // Set the State to be used as a secondary state
        if(m_secondaryStateID == StateID::BagS){
            BagState * bs = (BagState*)m_secondaryState;
            bs->setFightEntries();
        }
        else if(m_secondaryStateID == StateID::TeamS){
            TeamState * ts = (TeamState*)m_secondaryState;
            ts->setFightEntries();
            ts->setPokeInFight(getAllyIndex());
            
            // If Ally is KO then force to select a pokemon
            if(getAllyPokemon()->isKO())
                ts->forceSelection();
        }
        
        m_secondaryState->setAsSecondaryState(true);
    }
    else{
        std::cout << "No State with ID " << m_secondaryStateID << std::endl;
        m_secondaryState = nullptr;
    }
}



void FightState2::closeSecondaryState() {
    m_secondaryState->setAsSecondaryState(false);
    m_secondaryState = nullptr;
}



bool FightState2::secondaryStateHasSelected() {
    if(m_secondaryStateID == StateID::TeamS){
        TeamState* ts = (TeamState*) m_secondaryState;
        
        return ts->hasSelectedPokemon();
    }
    else if(m_secondaryStateID == StateID::BagS){
        BagState* bs = (BagState*) m_secondaryState;
        
        return bs->hasSelectedItem();
    }
    
    Log("Reached the end of FightState secondaryStateHasSelected", Logger::WARNING);
    return false;
}



ItemID FightState2::getBagSelection() {
    BagState* bs = (BagState*) m_secondaryState;

    return bs->getItemIDSelected();
}



Pokemon* FightState2::getTeamSelection() {
    TeamState* ts = (TeamState*) m_secondaryState;

    return ts->getSelectedPokemon();
}



bool FightState2::isStageFinished() {
    // Get the Current QuitCondition
    QuitCondition quitCondition = getCurrentStage().getQuitCondition();
    
    // Stage launched => immediately close
    if(quitCondition == QuitCondition::StageStarted)
        return true;
    
    // Stack : DialogState 
    else if(quitCondition == QuitCondition::NoDialogState)
        return !m_stack->hasStateOfID(StateID::DialogS) && m_stageTime >= 0.01; // Wait a bit for the Stack to push the State
    
    // Dialog 
    else if(quitCondition == QuitCondition::DialogClosed)
        return !m_ui.isShowingDialog();
    
    // Main Menu 
    else if(quitCondition == QuitCondition::MenuSelected)
        return m_ui.getMenu().isSelected();
    
    // Attack Menu 
    else if(quitCondition == QuitCondition::AttackSelected){
        if(m_ui.getAttackMenu().isSelected())
            std::cout << "Attack selected !" << std::endl;
        return m_ui.getAttackMenu().isSelected();
    }
    
    // Secondary State found
    else if(quitCondition == QuitCondition::SecondaryStateFound)
        return m_secondaryState != nullptr;
    
    // Secondary State completed
    else if(quitCondition == QuitCondition::SecondaryStateCompleted)
        return m_secondaryState->isCompleted();
    
    // FightQuit -> do not pop the Stage to prevent empty queue
    else if(quitCondition == FightQuitted)
        return false;
    
    // NoQuitCondition -> always true
    else if(quitCondition == NoQuitCondition)
        return true;
    
    else if(quitCondition == TimePassed)
        return m_stageTime >= getCurrentStage().getLifeTime();
    
    // All attacks are learned when the attack queue is empty and if there is no 
    else if(quitCondition == AllAttacksLearned)
        return m_turnContext.learntAttacks.size() == 0 && !m_ui.isShowingDialog();
    
    // Stack : EvolutionState 
    else if(quitCondition == QuitCondition::NoEvolutionState)
        return !m_stack->hasStateOfID(StateID::EvolutionS) && m_stageTime >= 0.01; // Wait a bit for the Stack to push the State;
    
    else{
        std::cout << "Quit condition " << quitCondition << " not managed" << std::endl;
        return false;
    }
}



void FightState2::nextStage() {
    
    // Check The number of stages left
    /*
    std::cout << "Currently " << m_stages.size() << " FightStages" << std::endl;
    for(FightStage* fs : m_stages) std::cout << (int)fs->getName() << " ";
    std::cout << std::endl;
    */
    
    //std::cout << "      Get quit action" << std::endl;
    // Get the quit action
    action quitAction = getCurrentStage().onQuitAction();
    
    //std::cout << "      Obtained quit action" << std::endl;
    
    // Delete and pop the stage
    delete m_stages.front();
    m_stages.pop_front();
    
    // Reset the Stage time
    m_stageTime = 0;
    
    
    //std::cout << "      Trying quit action" << std::endl;
    // Do the QuitAction of the current Stage
    if(quitAction != nullptr){
        quitAction(*this);
        //std::cout << "      Quit action done" << std::endl;
    }
    //else
        //std::cout << "          Quit : Null pointer" << std::endl;
    
    
    
    
    //std::cout << "      Trying start action" << std::endl;
    
    // Get the start action
    action startAction = getCurrentStage().onStartAction();
    
    // Do the StartAction of the new current Stage
    if(startAction != nullptr){
        startAction(*this);
        //std::cout << "      Start action done" << std::endl;
    }
    //else
        //std::cout << "          Start : Null pointer" << std::endl;
    
    // Check The number of stages left
    //std::cout << "Finally " << m_stages.size() << " FightStages" << std::endl;
}



void FightState2::pushStage(FightStageName name, QuitCondition condition, action onStart, action onUpdate, action onQuit) {
    pushStage(name, condition, 0, onStart, onUpdate, onQuit);
}



void FightState2::pushStage(FightStageName name, QuitCondition condition, float lifetime, action onStart, action onUpdate, action onQuit) {
    FightStage* fs = new FightStage(name, condition);
    
    fs->setLifeTime(lifetime);
    
    fs->setStartAction(onStart);
    fs->setUpdateAction(onUpdate);
    fs->setQuitAction(onQuit);
    
    m_stages.push_back(fs);
}



void FightState2::insertStageAfter(FightStageName insertAfterStage, FightStage* stage) {
    // Create an iterator to the stage queue
    std::deque<FightStage*>::iterator insertIt = m_stages.begin();
    
    // Find the stage where we must insert the stages
    for(; insertIt != m_stages.end() && (*insertIt)->getName() != insertAfterStage; insertIt++){}
    
    // Insert the vector in parameter after the place found
    m_stages.insert(insertIt+1, stage);
}



void FightState2::insertStagesAfter(FightStageName insertAfterStage, std::deque<FightStage*>& stages) {
    // Create an iterator to the stage queue
    std::deque<FightStage*>::iterator insertIt = m_stages.begin();
    
    // Find the stage where we must insert the stages
    for(; insertIt != m_stages.end() && (*insertIt)->getName() != insertAfterStage; insertIt++){}
    
    // Assert that we are not at the end (we can't insert at end+1)
    assert(insertIt != m_stages.end());
    
    // Insert the vector in parameter after the place found
    m_stages.insert(insertIt+1, stages.begin(), stages.end());
}



void FightState2::insertStageBefore(FightStageName insertBeforeStage, FightStage* stage) {
    // Create an iterator to the stage queue
    std::deque<FightStage*>::iterator insertIt = m_stages.begin();
    
    // Find the stage where we must insert the stages
    for(; insertIt != m_stages.end() && (*insertIt)->getName() != insertBeforeStage; insertIt++){}
    
    // Insert the vector in parameter before the place found
    m_stages.insert(insertIt, stage);
}



void FightState2::insertStagesBefore(FightStageName insertBeforeStage, std::deque<FightStage*>& stages) {
    // Create an iterator to the stage queue
    std::deque<FightStage*>::iterator insertIt = m_stages.begin();
    
    // Find the stage where we must insert the stages
    for(; insertIt != m_stages.end() && (*insertIt)->getName() != insertBeforeStage; insertIt++){}
    
    // Insert the vector in parameter before the place found
    m_stages.insert(insertIt, stages.begin(), stages.end());
}



void FightState2::pushStartStage() {
    // Push a stage to wait until the DialogState pops out
    pushStage(FS_DialogState, NoDialogState);
}



void FightState2::pushMainMenuStage() {
    pushStage(FS_MainMenu, MenuSelected, &FightState2::showMainMenu, nullptr, &FightState2::selectMenu);
}



void FightState2::pushAttackMenuStage() {
    pushStage(FS_AllyAttackSelection, AttackSelected, &FightState2::showAttackMenu, nullptr, &FightState2::selectAttack);
}



void FightState2::pushBagStage() {
    // Open a BagState
    openBagState();
    
    // Find the BagState
    pushStage(FS_FindSecondaryState, SecondaryStateFound, nullptr, &FightState2::findSecondaryState);
    
    // Pop the BagState when done with selecting an item
    pushStage(FS_ItemSelection, SecondaryStateCompleted, nullptr, nullptr, &FightState2::popBagState);
}



void FightState2::pushNewTurnStages() {
    calculateEnnemyTurn();
    calculateTurnPriority();
    
    if(m_turnContext.allyFirst){
        pushAllyTurn();
        pushEnnemyTurn();
    }
    else{
        pushEnnemyTurn();
        pushAllyTurn();
    }
    
    
    // Push a stage for the end of turn and KOs
    pushStage(FS_EndTurn, NoQuitCondition, nullptr, nullptr, nullptr);
    
    // Check KOs
    pushStage(FS_CheckKOs, StageStarted, &FightState2::checkKOs);
    
    // And a new MainMenu for the next turn
    pushMainMenuStage();
}



void FightState2::pushAllyTurn() {
    // Item
    if(m_turnContext.allyAction == FightAction::FA_Item){
        // Use a pokeball
        if(Item::getCategory(m_turnContext.allyItem) == ItemCategory::Pokeball){
            pushPokeballUseStages();
        }
        // Use another kind of item
        else{
            pushItemUseStages(Team::allied);
        }
    }
    // Switch
    else if(m_turnContext.allyAction == FightAction::FA_Switch)
        pushPokemonSwitchStages(Team::allied);
    // Attack
    else
        pushAllyAttackStages();
}



void FightState2::pushEnnemyTurn() {
    // Item
    if(m_turnContext.ennemyAction == FightAction::FA_Item)
        pushItemUseStages(Team::ennemy);
    // Switch
    else if(m_turnContext.ennemyAction == FightAction::FA_Switch)
        pushPokemonSwitchStages(Team::ennemy);
    // Attack
    else
        pushEnnemyAttackStages();
}



void FightState2::pushTeamStage() {
    // Open a TeamState
    pushStage(FS_AllySelection, StageStarted, &FightState2::openTeamState);
    
    // Push a stage to find the Secondary State
    pushStage(FS_FindSecondaryState, SecondaryStateFound, nullptr, &FightState2::findSecondaryState);    
    
    // Stage to select the ally
    pushStage(FS_AllySelection, SecondaryStateCompleted, nullptr, nullptr, &FightState2::popTeamState);
}



void FightState2::pushHealthUpdate() {
    pushStage(FS_HealthUpdate, StageStarted, &FightState2::updatePokemonDisplays);
    
    // Wait a time before 
    pushStage(FS_HealthUpdate, TimePassed, 0.2);
}



void FightState2::pushAllyAttackStages() {
    // Update Ally Status
    pushStage(FS_StatusUpdate, DialogClosed, &FightState2::updateAllyStatus);
            
    // Ally attack and dialog
    pushStage(FS_Attack, DialogClosed, &FightState2::allyAttack);
    pushHealthUpdate();
    
    // Ally efficiency
    pushStage(FS_AttackEfficiency, DialogClosed, &FightState2::attackEfficiency);
    
    // Ally recoil and dialog
    pushStage(FS_Attack, DialogClosed, &FightState2::allyRecoil);
    pushHealthUpdate();
    
    // Check KOs
    pushStage(FS_CheckKOs, StageStarted, &FightState2::checkKOs);
    
    // Status
    pushStage(FS_StatusGive, DialogClosed, &FightState2::giveEnnemyStatus);
    pushHealthUpdate();

    // Stat Changers
    pushStage(FS_StatChanges, DialogClosed, &FightState2::attackStatsChange);
    


    pushHealthUpdate();
    
    // Check KOs
    pushStage(FS_CheckKOs, StageStarted, &FightState2::checkKOs);
}



void FightState2::pushEnnemyAttackStages() {
    // Update Ennemy Status
    pushStage(FS_StatusUpdate, DialogClosed, &FightState2::updateEnnemyStatus);
    
    // Ennemy attack and dialog
    pushStage(FS_Attack, DialogClosed, &FightState2::ennemyAttack);
    pushHealthUpdate();
    
    // Ennemy efficiency
    pushStage(FS_AttackEfficiency, DialogClosed, &FightState2::attackEfficiency);
    
    // Ennemy recoil and dialog
    pushStage(FS_Attack, DialogClosed, &FightState2::ennemyRecoil);
    pushHealthUpdate();
    
    // Check KOs
    pushStage(FS_CheckKOs, StageStarted, &FightState2::checkKOs);
    
    // Status
    pushStage(FS_StatusGive, DialogClosed, &FightState2::giveAllyStatus);
    pushHealthUpdate();

    // Stat Changers
    pushStage(FS_StatChanges, DialogClosed, &FightState2::attackStatsChange);
    


    pushHealthUpdate();
    
    // Check KOs
    pushStage(FS_CheckKOs, StageStarted, &FightState2::checkKOs);
}



void FightState2::pushPokeballUseStages() {
    // Throw a ball and calculate the result
    pushStage(FS_ItemUse, DialogClosed, &FightState2::usePokeball, nullptr, &FightState2::replaceEnnemyWithBall);
    
    // Wait a time before showing dialogs
    pushStage(FS_ItemUse, TimePassed, 0.5);
    
    // Throw a ball and calculate the result
    pushStage(FS_Dialog, DialogClosed, &FightState2::captureTry, nullptr, &FightState2::replaceEnnemyWithSprite);
}



void FightState2::pushItemUseStages(Team team) {
    if(team == Team::allied)
        pushStage(FS_ItemUse, DialogClosed, &FightState2::useAllyItem);
    else
        pushStage(FS_ItemUse, DialogClosed, &FightState2::useEnnemyItem);
    
    // Update health bars
    pushHealthUpdate();
}



void FightState2::pushPokemonSwitchStages(Team team) {
    if(team == Team::allied){
        // Check if the ally can switch
        if(canSwitch(team)){
            pushStage(FS_PokemonSwitch, DialogClosed, &FightState2::retrieveAllyPokemon);
            pushStage(FS_PokemonSwitch, DialogClosed, &FightState2::sendAllyPokemon);
        }
        else{
            pushStage(FS_PokemonSwitchFail, DialogClosed, &FightState2::failRetrieveAllyPokemon);
        }
    }
    else{
        // Check if the ability allow the switch
        if(canSwitch(team)){
            pushStage(FS_PokemonSwitch, DialogClosed, &FightState2::retrieveEnnemyPokemon);
            pushStage(FS_PokemonSwitch, DialogClosed, &FightState2::sendEnnemyPokemon);
        }
        else{
            std::cout << "FIGHT : Tentative de retirer l'ennemi a échoué" << std::endl;
        }
    }
}



void FightState2::pushEndFightStages() {
    pushEvolutionStages();
    pushStage(FS_QuitFight, DialogClosed, &FightState2::endFight);
    pushStage(FS_QuitFight, FightQuitted, &FightState2::quit);
}



void FightState2::pushEvolutionStages() {
    // Push a stage for each pokemon (even if it won't evolve)
    for(int i = 0; i < m_character->getNbPokemon(); i++){
        // Push the FightStage for the evolution
        pushStage(FS_Evolution, NoEvolutionState, &FightState2::evolvePokemons, nullptr, &FightState2::updatePokemonDisplays);

        // Push LearnAttacks
        pushStage(FS_LearnAttacks, AllAttacksLearned, &FightState2::addEvolutionAttacks, &FightState2::learnAttacks);
    }
}



void FightState2::insertXPStages() {
    // Get the pokemon that need xp
    m_turnContext.xpReceivers = m_xpSharer.getFacedNotKO(getEnnemyPokemon());
    
    // insert as many xp Stages as needed
    for(int i = 0; i < m_turnContext.xpReceivers.size(); i++){
        // Giving XP
        FightStage* fs = new FightStage(FS_XP, DialogClosed);
        fs->setStartAction(&FightState2::giveXPAndEVs);
        insertStageAfter(getLastStage().getName(), fs);
        
        // Learning attacks if needed
        fs = new FightStage(FS_LearnAttacks, AllAttacksLearned);
        fs->setUpdateAction(&FightState2::learnAttacks);
        insertStageAfter(FS_XP, fs); 
    }
}



void FightState2::insertEnteringEffect(Team team) {
    // Pointers to the pokemons
    Pokemon *entering, *ennemy;
    
    
    if(team == Team::allied){
        entering = getAllyPokemon();
        ennemy = getEnnemyPokemon();
    }
    else{
        entering = getEnnemyPokemon();
        ennemy = getAllyPokemon();
    }
    
    // Get the ability effect when entering
    AbilityEffect effect = entering->getAbility().onEnteringFight(*entering, *ennemy);
    
    // Insert a Change Stats if needed
    if(effect.getType() == AbilityEffect::AE_ChangeStats){
        // Get the State Changer
        StatsChanger changer = effect.getStatChanger();
        
        // Revert the team if ennemy
        if(team == Team::ennemy)
            changer.reverseTarget();
        
        // Add the Changer to the Context and ask for an Ability Display
        m_turnContext.statChangers.push_back(changer);
        m_turnContext.showAbility = true;
        m_turnContext.abilityTeam = team;
        
        
        // Update Stats
        std::deque<FightStage*> stages;
        
        FightStage* fs = new FightStage(FS_StatChanges, DialogClosed);
        fs->setStartAction(&FightState2::attackStatsChange);
        stages.push_back(fs);
        
        // Hide the Ability
        fs = new FightStage(FS_StatChanges, NoQuitCondition);
        fs->setStartAction(&FightState2::hideAbility);
        stages.push_back(fs);
        
        insertStagesAfter(getCurrentStage().getName(), stages);
    }
}



void FightState2::endTurnByKO() {
    // Clean the queue until the end of the utnr
    cleanQueueUntil(FS_EndTurn);
    
    // Create a stage for HealthUpdate
    FightStage* fs = new FightStage(FS_HealthUpdate, StageStarted);
    fs->setStartAction(&FightState2::updatePokemonDisplays);
    insertStageAfter(FS_EndTurn, fs);
    
    // Wait  
    fs = new FightStage(FS_HealthUpdate, TimePassed);
    fs->setLifeTime(0.2);
    insertStageAfter(FS_EndTurn, fs);
    
    // Recoil Stage
    fs = new FightStage(FS_Attack, DialogClosed);
    if(m_turnContext.currentTeam == Team::allied)
        fs->setStartAction(&FightState2::allyRecoil);
    else
        fs->setStartAction(&FightState2::ennemyRecoil);
    
    insertStageAfter(FS_HealthUpdate, fs);
    
    // Create an other stage for HealthUpdate
    fs = new FightStage(FS_HealthUpdate, StageStarted);
    fs->setStartAction(&FightState2::updatePokemonDisplays);
    insertStageAfter(FS_Attack, fs);
    fs = new FightStage(FS_HealthUpdate, TimePassed);
    fs->setLifeTime(0.2);
    insertStageAfter(FS_EndTurn, fs);
}



void FightState2::setupTurnContext() {
    // Clear the stat Changer
    m_turnContext.statChangers.clear();
    
    // Set the new status to None
    m_turnContext.newAllyStatus = MainStatusName::NoMainStatus;
    m_turnContext.newEnnemyStatus = MainStatusName::NoMainStatus;
    
    // Set the current pokemons
    m_turnContext.currentAlly = m_character->getPokemonTeam()->getFirstNotKO();
    m_turnContext.currentEnnemy = 0;
    
    // Set the ennemy to not captured
    m_turnContext.ennemyCaptured = false;
    m_turnContext.ballBounces = 0;
    
    // We didn't flee yet
    m_turnContext.flee = false;
    
    // Set the Ability
    m_turnContext.showAbility = false;
    
    // Protecting the Ally
    m_turnContext.allyProtected = false;
    m_turnContext.ennemyProtected = false;
    
    // Reset the Damages dealt
    m_turnContext.damageToAlly = 0;
    m_turnContext.damageToEnnemy = 0;
}



void FightState2::setupFightContext() {
    m_fightContext.turnsProtectingAlly = 0;
    m_fightContext.turnsProtectingEnnemy = 0;
    m_fightContext.attackLearner = nullptr;
    m_fightContext.pokemonCaptured = nullptr;
}



void FightState2::cleanQueue() {
    // Pop each stage until there is no one left
    while(!m_stages.empty()){
        delete m_stages.front();
        m_stages.pop_front();
    }
    
    pushStage(FS_QueueCleaned, NoQuitCondition);
}



void FightState2::cleanQueueUntil(FightStageName name) { 
    // Save the First stage
    FightStage * fsFront = m_stages.front();
    
    // Pop the front stage
    m_stages.pop_front();
    
    bool continuer = true;
    
    // Pop each stage until we find one with the given ID
    while(!m_stages.empty() && continuer){
        FightStage * fs = m_stages.front();
        
        if(fs->getName() == name)
            continuer = false;
        else{
            delete fs;
            m_stages.pop_front();
        }
    }
    
    // Put back the front Stage
    m_stages.push_front(fsFront);
}



void FightState2::cleanQueueUntil(FightStageName name1, FightStageName name2) {

    // Save the First stage
    FightStage * fsFront = m_stages.front();
    
    // Pop the front stage
    m_stages.pop_front();
    
    bool continuer = true;
    
    // Pop each stage until we find one with the given ID
    while(!m_stages.empty() && continuer){
        FightStage * fs = m_stages.front();
        
        if(fs->getName() == name1 || fs->getName() == name2)
            continuer = false;
        else{
            delete fs;
            m_stages.pop_front();
        }
    }
    
    // Put back the front Stage
    m_stages.push_front(fsFront);
}



void FightState2::calculateTurnPriority() {
    // If the ally doesn't attack, then it plays first
    if(m_turnContext.allyAction != FightAction::FA_Attack){
        m_turnContext.allyFirst = true;
    }
    // Else if the ennemy doesn't attack, then it plays first
    else if(m_turnContext.ennemyAction != FightAction::FA_Attack){
        m_turnContext.allyFirst = false;
    }
    // Else we compare the pokemon speeds
    else{
        setFirstAttackant();
    }
}



void FightState2::setFirstAttackant() {
    // Get the Attacks priority
    int ennemyAttackPriority = getEnnemyPokemon()->getAttackSet().getAttack(m_turnContext.ennemyAttack)->getPriority();
    int allyAttackPriority = getAllyPokemon()->getAttackSet().getAttack(m_turnContext.allyAttack)->getPriority();
    
    // Check a difference in attackpriority
    if(ennemyAttackPriority < allyAttackPriority)
        m_turnContext.allyFirst = true;
    
    else if(ennemyAttackPriority > allyAttackPriority)
        m_turnContext.allyFirst = false;
    
    // Else calculate the first to attack
    else{
        // Get the pokemons
        Pokemon* ally = getAllyPokemon();
        int allySpeed = ally->getInFightStat(StatName::speed);

        Pokemon* ennemy = getEnnemyPokemon();
        int ennemySpeed = ennemy->getInFightStat(StatName::speed);
        
        // Same speed => Random priority
        if(allySpeed == ennemySpeed){
            m_turnContext.allyFirst = (randomInt(0, 1) == 0);
        }
        // Else, we check the higher speed
        else {
                m_turnContext.allyFirst = (allySpeed > ennemySpeed);
        }  
    }
}



void FightState2::allyAttack() {
    // Update the current Team
    m_turnContext.currentTeam = Team::allied;
    
    // Get the pokemons
    Pokemon* attacker = getAllyPokemon();
    Pokemon* defender = getEnnemyPokemon();
    
    // Get the Attack
    Attack* attack = attacker->getAttackSet().getAttack(m_turnContext.allyAttack);
    
    if(canAttackThisTurn(attacker)){// Attack normally
        // Get the Pokemon and check if it has some PP Lefts
        bool hasPPLefts = attacker->hasAnyPPLeft();
            
        // If it has some PP lefts it attacks normally
        if(hasPPLefts){

            m_ui.addDialog(attacker->getName() + " utilise " + attack->getName() + ".");
            
            // Try to protect the User
            if(attack->isProtectingPokemon())
                tryProtect(Team::allied);
            
            // Cancel if the Ennemi is protected
            if(m_turnContext.ennemyProtected)
                m_ui.addDialog(L"Le " + getEnnemyPokemon()->getName() + L" ennemi est protégé !");
            else{
                // Push Stages for multi-hit Attack
                if(attack->isMultiHitAttack())
                    multiAttackPokemon(attacker, defender, attack, Team::allied);
                // Else attack normally
                else
                    m_turnContext.damageToEnnemy = attackPokemon(attacker, defender, attack, m_turnContext.damageToAlly);
    
                // Update the new Status
                m_turnContext.newEnnemyStatus = getNewStatus(defender, attack);
            }
            
            // Use a single PP
            attack->usePP();
        }
        // Else it uses struggle
        else{
            m_ui.addDialog(attacker->getName() + L" n'a plus de capacités !");
            m_ui.addDialog(attacker->getName() + " utilise Lutte.");
            
            struggle(attacker, defender);
        }
    }
    else{
        cleanQueueUntil(FS_MainMenu, FS_StatusUpdate);
    }
}



void FightState2::ennemyAttack() {
    // Update the current Team
    m_turnContext.currentTeam = Team::ennemy;
    
    // Get the pokemons
    Pokemon* attacker = getEnnemyPokemon();
    Pokemon* defender = getAllyPokemon();
    
    // Get the Attack
    Attack* attack = attacker->getAttackSet().getAttack(m_turnContext.ennemyAttack);
    
    if(canAttackThisTurn(attacker)){// Attack normally
        // Get the Pokemon and check if it has some PP Lefts
        bool hasPPLefts = attacker->hasAnyPPLeft();
        
        // If it has some PP lefts it attacks normally
        if(hasPPLefts){
            m_ui.addDialog(L"Le " + attacker->getName() + " ennemi utilise " + attack->getName() + ".");
            
            // Try to protect the User
            if(attack->isProtectingPokemon())
                tryProtect(Team::ennemy);
            
            
            // Cancel if the Ennemi is protected
            if(m_turnContext.allyProtected)
                m_ui.addDialog(getAllyPokemon()->getName() + L" est protégé !");
            else{
                // Push Stages for multi-hit Attack
                if(attack->isMultiHitAttack())
                    multiAttackPokemon(attacker, defender, attack, Team::ennemy);
                // Else attack normally
                else
                    m_turnContext.damageToAlly = attackPokemon(attacker, defender, attack, m_turnContext.damageToEnnemy);
    
                // Update the new Status
                m_turnContext.newAllyStatus = getNewStatus(defender, attack);
            }
            
            // Use a single PP
            attack->usePP();
        }
        // Else it uses struggle
        else{
            m_ui.addDialog(L"Le " + attacker->getName() + L" ennemi n'a plus de capacités !");
            m_ui.addDialog(L"Le " +attacker->getName() + " ennemi utilise Lutte.");
            
            struggle(attacker, defender);
            
            // Clean the queue until an End Turn State if there is a pokemon KO
            if(attacker->isKO() || defender->isKO())
                endTurnByKO();
        }
    }
}



bool FightState2::canAttackThisTurn(Pokemon* attacker) {
    // Check if the pokemon attacks this turn
    if(!attacker->attackThisTurn()){
        MainStatusName status = attacker->getMainStatus().getName();
        // Freeze
        if(status == MainStatusName::Freeze) // If the attacker is frozen, it can't attack
            m_ui.addDialog(attacker->getName() + L" est gelé !\nIl ne peut pas attaquer.");
        
        // Sleep
        else if(status == MainStatusName::Sleep) // If the attacker is asleep, it can't attack
            m_ui.addDialog(attacker->getName() + L" est endormi !\nIl ne peut pas attaquer.");
        
        // Paralysis
        else if(status == MainStatusName::Paralysis) // If the attacker is paralysed, it might not have attacked
            m_ui.addDialog(attacker->getName() + L" est paralysé !\nIl ne peut pas attaquer.");
        
        return false;
    }
    // Else it attacked correctly
    return true;
}



int FightState2::attackPokemon(Pokemon* attacker, Pokemon* defender, Attack* attack, int previousDamagesToAttacker) {
    int damage = 0;
    
    float coef = defender->getAttackEfficiency(*attack);
    m_turnContext.lastAttackEfficiency = coef;
    
    // Drop the HealthUpdate if the coeff is null
    if(coef == 0)
        cleanQueueUntil(FS_AttackEfficiency);
    // If the Attack deals no damage
    //if(attack->getDamage() == 0)
    //    cleanQueueUntil(FS_StatusGive);
    
    else {
        // Check if we made a critical hit
        bool critical = false;
        if(attack->getDamage() > 0 && attackHitIsCritical(*attacker, *attack)){
            critical = true;
            m_ui.addDialog(sf::String(L"Coup critique !"));
        }

        // Receive the Attack
        damage = defender->receiveAttack(*attacker, *attack, m_turnContext.lastAttackEfficiency, critical, previousDamagesToAttacker);
    
        // If the attack changes stats then set the statChanger vector
        if(!attack->getStatsChanger().nullChanger()){
            m_turnContext.statChangers = attack->getStatChangerAsVector();
        }
    }
    
    // Clean the queue until an End Turn State if there is a pokemon KO
    if(attacker->isKO() || defender->isKO())
        endTurnByKO();
    
    return damage;
}



void FightState2::multiAttackPokemon(Pokemon* attacker, Pokemon* defender, Attack* attack, Team attackerTeam) {
    // Check if we the attack touches the ennemy
    m_turnContext.lastAttackEfficiency = defender->getAttackEfficiency(*attack);
    if(m_turnContext.lastAttackEfficiency == 0)
        cleanQueueUntil(FS_AttackEfficiency);
    
    // Calculate how much hits will be made
    m_turnContext.attackHitsPlanned = randomInt(attack->getMinimumHits(), attack->getMaximumHits());
    m_turnContext.attackHitsDone = 0;     
    
    // Deque of inserted stages
    std::deque<FightStage*> newStages;
    
    // Insert a hit and a health update for each
    for(int i = 0; i < m_turnContext.attackHitsPlanned; i++){
        // Stage for a single hit
        FightStage* fs = new FightStage(FightStageName::FS_Attack, QuitCondition::DialogClosed);
        
        // Choose between hitAlly or hitEnnemy
        if(attackerTeam == Team::allied)
            fs->setStartAction(&FightState2::hitEnnemyOnce);
        else
            fs->setStartAction(&FightState2::hitAllyOnce);
        
        newStages.push_back(fs);
        
        // Stage for a health update
        fs = new FightStage(FightStageName::FS_HealthUpdate, QuitCondition::TimePassed);
        fs->setStartAction(&FightState2::updatePokemonDisplays);
        fs->setLifeTime(0.8);
        newStages.push_back(fs);
    }
    
    // Push a Stage to display the number of hits
    FightStage* fs = new FightStage(FightStageName::FS_Dialog, QuitCondition::DialogClosed);
    fs->setStartAction(&FightState2::displayNbHits);
    newStages.push_back(fs);
    
    // Insert after the current stage
    insertStagesAfter(getCurrentStage().getName(), newStages);
}



void FightState2::hitAllyOnce() {
    // Get the pokemons
    Pokemon* attacker = getEnnemyPokemon();
    Pokemon* defender = getAllyPokemon();
    
    // Get the Attack
    Attack& attack = *(attacker->getAttackSet().getAttack(m_turnContext.ennemyAttack));
    
    // Check if the attack is critical
    bool critical = false;
    if(attack.getDamage() > 0 && attackHitIsCritical(*attacker, attack)){
        critical = true;
        m_ui.addDialog(sf::String(L"Coup critique !"));
    }
    
    // Receive the Attack
    m_turnContext.damageToAlly += defender->receiveAttack(*attacker, attack, m_turnContext.lastAttackEfficiency, critical);
    
    
    // Increase the hit counter
    m_turnContext.attackHitsDone++;
    
    if(attacker->isKO() || defender->isKO()){
        // Show the Hits, but hide the dialog because of the last health update
        displayNbHits();
        m_ui.showDialog(false);
        
        // End the turn
        endTurnByKO();
        
        // Stage for a health update
        FightStage* fs = new FightStage(FightStageName::FS_HealthUpdate, QuitCondition::TimePassed);
        fs->setStartAction(&FightState2::updatePokemonDisplays);
        fs->setLifeTime(0.8);
        insertStageBefore(FS_CheckKOs, fs);
    }
}



void FightState2::hitEnnemyOnce() {
    // Get the pokemons
    Pokemon* attacker = getAllyPokemon();
    Pokemon* defender = getEnnemyPokemon();
    
    // Get the Attack
    Attack& attack = *(attacker->getAttackSet().getAttack(m_turnContext.allyAttack));
    
    // Check if the attack is critical
    bool critical = false;
    if(attack.getDamage() > 0 && attackHitIsCritical(*attacker, attack)){
        critical = true;
        m_ui.addDialog(sf::String(L"Coup critique !"));
    }
    
    // Receive the Attack
    m_turnContext.damageToEnnemy += defender->receiveAttack(*attacker, attack, m_turnContext.lastAttackEfficiency, critical);
    
    
    // Increase the hit counter
    m_turnContext.attackHitsDone++;
    
    if(attacker->isKO() || defender->isKO()){
        // Show the Hits, but hide the dialog because of the last health update
        displayNbHits();
        m_ui.showDialog(false);
        
        // End the turn
        endTurnByKO();
        
        // Stage for a health update
        FightStage* fs = new FightStage(FightStageName::FS_HealthUpdate, QuitCondition::TimePassed);
        fs->setStartAction(&FightState2::updatePokemonDisplays);
        fs->setLifeTime(0.8);
        insertStageBefore(FS_CheckKOs, fs);
    }
}



void FightState2::displayNbHits() {
    m_ui.addDialog(L"Touché " + toWString(m_turnContext.attackHitsDone) + L" fois !");
}



void FightState2::struggle(Pokemon* attacker, Pokemon* defender) {
    // Create an attack for Struggle (Lutte)
    Attack* struggle = AttackFabric::createAttack(AttackID::Lutte);

    // Receive the Attack (coef is 1 for struggle)
    defender->receiveAttack(*attacker, *struggle, 1);
    m_turnContext.lastAttackEfficiency = 1;

    // Delete the struggle Attack to prevent memory leak
    delete struggle;
}



void FightState2::allyRecoil() {
    // Get the pokemon
    Pokemon* attacker = getAllyPokemon();
    
    // Get the Attack
    Attack* attack = getAllyPokemon()->getAttackSet().getAttack(m_turnContext.allyAttack);
    
    // Push a dialog for the recoil
    if(attack->hasRecoil()){
        m_ui.addDialog(L"Le " + attacker->getName() + L" allié subit des dégats de recul.");
        attacker->sufferRecoil(attack->getRecoilPercentage());
    }
    else{
        // Clear the queue until a KO check
        cleanQueueUntil(FightStageName::FS_CheckKOs);
    }
}



void FightState2::ennemyRecoil() {
    // Get the pokemon
    Pokemon* attacker = getEnnemyPokemon();
    
    // Get the Attack
    Attack* attack = attacker->getAttackSet().getAttack(m_turnContext.ennemyAttack);
    
    // Push a dialog for the recoil
    if(attack->hasRecoil()){
        m_ui.addDialog(L"Le " + attacker->getName() + L" ennemi subit des dégats de recul.");
        attacker->sufferRecoil(attack->getRecoilPercentage());
    }
    else{
        // Clear the queue until a KO check
        cleanQueueUntil(FightStageName::FS_CheckKOs);
    }
}



void FightState2::attackEfficiency() {
    float coef = m_turnContext.lastAttackEfficiency;
    
    if(coef == 0) 
        m_ui.addDialog(sf::String(L"Ça n'affecte pas le pokemon adverse..."));
    else if(coef < 1)
        m_ui.addDialog(sf::String(L"Ce n'est pas très efficace."));
    else if(coef > 1)
        m_ui.addDialog(sf::String(L"C'est super efficace !"));
}



void FightState2::attackStatsChange() {
    // If the StatChanger vector is empty then leave
    if(m_turnContext.statChangers.empty())
        return;
    
    // Get the targeted pokemon
    Pokemon* target(0);
    if(m_turnContext.statChangers.front().getTargetedTeam() == Team::allied) // Ally
        target = getAllyPokemon();
    else // Ennemy
        target = getEnnemyPokemon();
    
    // Show the Ability if needed
    if(m_turnContext.showAbility)
        showAbility();
                
    // Apply the stat changes and push dialogs
    for(int i = 0; i < m_turnContext.statChangers.size(); i++){
        // Get the StatChanger
        StatsChanger stc = m_turnContext.statChangers.at(i);
        
        applyStatChanger(target, stc);
    }
    
    // Clear the Stat Changer for the next update
    m_turnContext.statChangers.clear();
}



void FightState2::applyStatChanger(Pokemon* p, StatsChanger& stc) {
    // Get the stat change as an in
    StatName statName = stc.getNonNullStatName();
    int val = stc.getStatChangerValue(statName);
    
    // Get the pokemon current Stat Changer
    StatsChanger pokeStCh = p->getStatChanger();
    
    // Check if we can add the statChanger to the pokemon one
    if(pokeStCh.canIncreaseStat(statName) && val > 0){
        dialogCurrentStatChanger(stc);
        p->addStatChanger(stc);
    } 
    else if(pokeStCh.canDecreaseStat(statName)){
        dialogCurrentStatChanger(stc);
        p->addStatChanger(stc);
    }
    else{
        // Get the wstring corresponding to the targeted team
        sf::String targetStr(L"unknown_target");
        if(stc.getTargetedTeam() == Team::allied)
            targetStr = sf::String("de ") + p->getName() + L" ";
        else if(stc.getTargetedTeam() == Team::ennemy)
            targetStr = sf::String("du ") + p->getName() + L" ennemi ";

        // Get the string corresponding to the stat name
        sf::String statNameStr(stc.getFightWString(statName));

        // Set the dialog
        if(val < 0)
            m_ui.addDialog(statNameStr + targetStr + L" est déjà au\nmaximum !");
        else
            // Set the dialog
            m_ui.addDialog(statNameStr + targetStr + L" est déjà au\nminimum !");
    }
}



void FightState2::dialogCurrentStatChanger(StatsChanger& stc) {    
    // Get the wstring corresponding to the targeted team
    sf::String targetStr(L"unknown_target");
    if(stc.getTargetedTeam() == Team::allied)
        targetStr = sf::String("de ") + getAllyPokemon()->getName();
    else if(stc.getTargetedTeam() == Team::ennemy)
        targetStr = sf::String("du ") + getEnnemyPokemon()->getName() + " ennemi ";
    
    // Stat name and stat value
    StatName statName = stc.getNonNullStatName();
    int changeVal = stc.getStatChangerValue(statName);
    
    // Get the string corresponding to the stat name
    sf::String statNameStr(stc.getFightWString(statName));
    
    // get teh string corresponding to the stat change
    sf::String statChangeStr(stc.getValAsWString(changeVal));
    
    // Set the dialog
    // Attack
    m_ui.addDialog(statNameStr + targetStr + L"\n" + statChangeStr);
}



void FightState2::giveAllyStatus() {
    Pokemon * pokemon = getAllyPokemon();
    MainStatus oldStatus = pokemon->getMainStatus();
    MainStatusName statusName = m_turnContext.newAllyStatus;
    
    if(pokemon->hasStatus())
        return;
    
    if(statusName == MainStatusName::NoMainStatus)
        return;
    
    pokemon->setMainStatus(MainStatus(statusName));
    
    // Set the Dialog
    if(statusName == MainStatusName::BadlyPoison)
        m_ui.addDialog(pokemon->getName() + L" est gravement empoisonné !");
    
    else if(statusName == MainStatusName::Burn)
        m_ui.addDialog(pokemon->getName() + L" est brûlé !");
    
    else if(statusName == MainStatusName::Freeze)
        m_ui.addDialog(pokemon->getName() + L" est gelé !");
    
    else if(statusName == MainStatusName::Paralysis)
        m_ui.addDialog(pokemon->getName() + L" est paralysé !\nIl pourra ne plus attaquer.");
    
    else if(statusName == MainStatusName::Poison)
        m_ui.addDialog(pokemon->getName() + L" est empoisonné !");
    
    else if(statusName == MainStatusName::Sleep)
        m_ui.addDialog(pokemon->getName() + L" est endormi !");
}



void FightState2::giveEnnemyStatus() {
    Pokemon * pokemon = getEnnemyPokemon();
    MainStatus oldStatus = pokemon->getMainStatus();
    MainStatusName statusName = m_turnContext.newEnnemyStatus;
    
    if(pokemon->hasStatus())
        return;
    
    if(statusName == MainStatusName::NoMainStatus)
        return;
    
    pokemon->setMainStatus(MainStatus(statusName));
    
    // Set the Dialog
    if(statusName == MainStatusName::BadlyPoison)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est gravement empoisonné !");
    
    else if(statusName == MainStatusName::Burn)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est brûlé !");
    
    else if(statusName == MainStatusName::Freeze)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est gelé !");
    
    else if(statusName == MainStatusName::Paralysis)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est paralysé !");
    
    else if(statusName == MainStatusName::Poison)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est empoisonné !");
    
    else if(statusName == MainStatusName::Sleep)
        m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi est endormi !");
}



void FightState2::checkKOs() {
    Pokemon * ally = getAllyPokemon();
    Pokemon * ennemy = getEnnemyPokemon();
    
    if(ally->isKO()){
        cleanQueue();
        
        pushStage(FS_Dialog, DialogClosed);
        m_ui.addDialog(ally->getName() + L" est KO !");
        
        if(m_character->hasPokemonsLeft()){
            pushTeamStage();
        }
        else{
            // End the Fight
            pushEndFightStages();
        }
        
    }
    else if(ennemy->isKO()){
        cleanQueue();
        
        // KO Dialog
        pushStage(FS_Dialog, DialogClosed);
        m_ui.addDialog(L"Le " + ennemy->getName() + L" ennemi est KO !");
        
        // Push Stages for XP and attacks if needed
        insertXPStages();
        
        // Send a new Ennemy if there are at least one left
        if(m_ennemyManager->hasPokemonsNotKO()){
            // Add a ui dialog (normally done automatically when sending a new pokemon)
            pushPokemonSwitchStages(Team::ennemy);
            pushMainMenuStage();
        }
        else{
            // End the Fight
            pushEndFightStages();
        }
        
        // We update the Pokedex
        m_character->getPokedex().addPokemonSaw(ennemy->getID());
    }
}



MainStatusName FightState2::getNewStatus(Pokemon * defender, Attack* attack) {
    if(defender->hasStatus())
        return MainStatusName::NoMainStatus;
        
    float coeff = m_turnContext.lastAttackEfficiency;
    if(coeff == 0)
        return MainStatusName::NoMainStatus;
    
    // Try to burn
    if(attack->canBurn() && attack->getBurnChance() > randomFloat(0, 1))
        return MainStatusName::Burn;
    // Try to poison
    if(attack->canPoison() && attack->getPoisonChance() > randomFloat(0, 1))
        return MainStatusName::Poison;
    // Try to badly poison
    if(attack->canBadlyPoison() && attack->getBadlyPoisonChance() > randomFloat(0, 1))
        return MainStatusName::BadlyPoison;
    // Try to paralyse
    if(attack->canParalyse() && attack->getParalyseChance() > randomFloat(0, 1)){
        // Can't paralyse if it's an electirc pokemon
        if(defender->getType().getFirstType() == Type::Electric || defender->getType().getSecondType() == Type::Electric)
            return MainStatusName::NoMainStatus;
        else
            return MainStatusName::Paralysis;
    }
    // Try to paralyse
    if(attack->canFreeze() && attack->getFreezeChance() > randomFloat(0, 1))
        return MainStatusName::Freeze;
    // Try to paralyse
    if(attack->canAsleep() && attack->getAsleepChance() > randomFloat(0, 1))
        return MainStatusName::Sleep;
    
    Log("Reached the end of FightState getNewStatus", Logger::WARNING);
    return MainStatusName::NoMainStatus;
}



const sf::String& FightState2::getTrainerName() {
    std::cout << "Converting the Ennemy manager to get the ennemy name" << std::endl;
    
    return ((FightTrainerManager*)m_ennemyManager)->getTrainerName();
}



bool FightState2::attackHitIsCritical(Pokemon& attacker, Attack& attack) {
    // Get the critial level
    int critLevel = attack.getCriticalLevel();
    
    // Apply the attacker item
    if(attacker.hasItem())
        attacker.getItem()->onCritLevel(critLevel);
    
    // Check if we have a critical hit
    float criticalChance = attacker.getCriticalChance(critLevel);
    
    // A random number to know the critical succes
    int rand = randomInt(1, 100);
    
    // Check if we made a critical hit
    if(attack.isAlwaysCritical() || criticalChance > (rand/100.))
        return true;
    else
        return false;
}



void FightState2::learnAttacks() {
    // Wait for the previous dialog to pop before the next attack
    if(m_ui.isShowingDialog())
        return;
    
    // Get the next attack to learn
    if(!m_turnContext.learntAttacks.empty()){
        // Get the pokemon
        Pokemon* ally = getAllyPokemon();
        
        // And the attack
        AttackID attack = m_turnContext.learntAttacks.front();
        
        
        // Learn the attack
        learnSingleAttack(ally, attack);
        
        // And pop the first element
        m_turnContext.learntAttacks.pop();
    }
}



void FightState2::addEvolutionAttacks(){
    // If some pokemons evolved
    if(m_character->getPokemonTeam()->hasLeveledUpLeft()){
        // Get the pokemon
        Pokemon* ally = m_character->getPokemonTeam()->popLeveledUp();
        
        // Get the attacks
        std::set<AttackID> attacks = ally->getAttacksSinceLevel(ally->getLevel()-1);
        
        // Push tha attack
        for(AttackID id : attacks)
            m_turnContext.learntAttacks.push(id);        
    }
}



void FightState2::learnSingleAttack(Pokemon* p, AttackID attackID) {
    // Directly learn the attack if possible
    if(p->getAttackSet().hasPlaceLeft()){
        Attack* attack = AttackFabric::createAttack(attackID);
        
        // Dialog
        m_ui.addDialog(p->getName() + " apprend " + attack->getName() + ".");
        
        // Put the attack in the Pokemon AttackSet
        p->getAttackSet().addAttack(attack);
    }
    else{
        m_stack->requestStackPush(StateID::LearnAttackS, p, attackID);
        // Push a dialog for the new attack
        Attack* attack = AttackFabric::createAttack(attackID);
        m_stack->requestStackPushDialog(p->getName() + " veut apprendre " + attack->getName());
        delete attack;
    }
}



void FightState2::evolvePokemons() {
    // Find the pokemon
    for(int i = 0; i < m_character->getNbPokemon(); i++){
        Pokemon* p = m_character->getPokemonAt(i);
        // Look if the pokemon can evolve
        if(p->canEvolve()){
            std::cout << p->getName().toAnsiString() << " can evolve " << std::endl;
            PokemonID id = p->getEvolutionID();
            m_stack->requestStackPushEvolutionState(m_character, p, id);
        }
    }
}



void FightState2::showAbility() {
    if(m_turnContext.abilityTeam == allied)
        m_ui.showAbilityDisplay(getAllyPokemon(), allied);
    else
        m_ui.showAbilityDisplay(getEnnemyPokemon(), ennemy);
}



void FightState2::hideAbility() {
    m_ui.hideAbilityDisplay();
}



void FightState2::showMainMenu() {
    
    std::cout << "Show main menu !" << std::endl;
    
    // Reset the choice before showing the menu
    m_ui.getMenu().resetChoice();
    
    m_ui.showMainMenu();
    
    // Reset the context
    setupTurnContext();
}



void FightState2::selectMenu() {    
    // Get the Entry selected
    FightMenuSelector::FightChoice choice = m_ui.getMenu().getChoice();
    
    if(choice == FightMenuSelector::AttacksFC){
        pushAttackMenuStage();
    }
    else if(choice == FightMenuSelector::BagFC){
        pushBagStage();
    }
    else if(choice == FightMenuSelector::PokemonsFC){
        pushTeamStage();
    }
    else if(choice == FightMenuSelector::FleeFC){
        // Check if we can flee
        if(m_ennemyManager->playerCanFlee()){
            m_turnContext.allyAction = FightAction::FA_Flee;
            pushStage(FS_Flee, DialogClosed, &FightState2::flee);
        }
        else{
            m_ui.addDialog(sf::String(L"Vous ne pouvez pas fuir d'un combat\nde dresseurs !"));
            pushMainMenuStage();
        }
    }
    else
        std::cout << "Aucune des 4 entrées selectées ... ?" << std::endl;
}



void FightState2::showAttackMenu() {
    m_ui.showAttackMenu();
}



void FightState2::selectAttack() {
    // Get the attack selected
    int attackSelected = m_ui.getAttackMenu().getChoice();
    
    // Hide The Menu
    m_ui.hideMenu();
    
    // If attack menu is quitted, then return to selectingMenu
    if(attackSelected == 4){
        pushMainMenuStage(); // Push the menu in the vector
        // And reset the Entry
        m_ui.getAttackMenu().setChoice(0);
    }
    else{
        std::cout << "Selected attack number " << attackSelected << std::endl;
        m_turnContext.allyAction = FightAction::FA_Attack;
        m_turnContext.allyAttack = attackSelected;
        
        Attack * attack = getAllyPokemon()->getAttackSet().getAttack(attackSelected);
        
        if(attack->getPP() == 0){
            // Push a stage to say there are no PP Left
            m_ui.addDialog(sf::String(L"Il ne reste pas de PP pour cette capacité !"));
            pushAttackMenuStage();
        }
        else{
            // Push a Dialog showing the attack
            pushNewTurnStages();
        }
    }
}



void FightState2::tryProtect(Team team) {
    if(team == Team::allied){
        // If the protection is successful
        if(checkProtectSuccess(m_fightContext.turnsProtectingAlly)){
            // Protect the User
            m_turnContext.allyProtected = true;
            m_ui.addDialog(getAllyPokemon()->getName() + L" se protège.");
            m_fightContext.turnsProtectingAlly += 1;
        }
        else{
            m_ui.addDialog(getAllyPokemon()->getName() + L" tente de se \nprotèger, mais cela échoue.");
            m_fightContext.turnsProtectingAlly = 0;
        }
    }
    else{
        // If the protection is successful
        if(checkProtectSuccess(m_fightContext.turnsProtectingEnnemy)){
            // Protect the User
            m_turnContext.ennemyProtected = true;
            m_ui.addDialog(L"Le " + getEnnemyPokemon()->getName() + L" ennemi se protège.");
            m_fightContext.turnsProtectingEnnemy += 1;
        }
        else{
            m_ui.addDialog(L"Le " + getEnnemyPokemon()->getName() + L" ennemi tente de se \nprotèger, mais cela échoue.");
            m_fightContext.turnsProtectingEnnemy = 0;
        }
    }
}



bool FightState2::checkProtectSuccess(int previousTurns) {
    // Get the Chance of success
    float successMax = std::max(1/729.f, (float)std::pow(3, -previousTurns));

    float r = randomFloat(0, 1);

    // If successfully defended
    return r <= successMax;
}



void FightState2::retrieveAllyPokemon() {
    // Get the Ally pokemon;
    Pokemon* ally = getAllyPokemon();
    
    // Show a message for the pokemon leaving the fight
    m_ui.addDialog("Reviens " + ally->getName() + ".");


    // Hide the ally display
    m_ui.setPokemonDisplayVisibility(Team::allied, false);
    
    
    // Apply the Ability if not KO
    if(!ally->isKO())
        ally->getAbility().onLeavingSwitch(ally);
}



void FightState2::failRetrieveAllyPokemon() {
    // Get the Ally pokemon;
    Pokemon* ally = getAllyPokemon();
    
    // Show a message for the pokemon leaving the fight
    m_ui.addDialog("Vous ne pouvez pas retirer " + ally->getName() + " !");
}



void FightState2::sendAllyPokemon() {
    std::cout << "Swtich between " << 0 << " and " << m_turnContext.allySelected << std::endl; 
    
    // Switch the Pokemon
    m_character->getPokemonTeam()->switchPokemons(0, m_turnContext.allySelected);
    
    // Set the current ally to 0
    m_turnContext.currentAlly = 0;

    // Show a message for the pokemon joining the fight
    m_ui.addDialog("Vas-y " + getAllyPokemon()->getName() + " !");

    // Show the ally display
    m_ui.setPokemonDisplayVisibility(Team::allied, true);

    // Update the displays
    updatePokemonDisplays();
    // Reset the Menus
    m_ui.getMenu().resetChoice();
    m_ui.getAttackMenu().setChoice(0);
    
    // Update the XP Sharer
    m_xpSharer.addFaced(getEnnemyPokemon(), getAllyPokemon());
    
    // Add the Ally to the list of fighters
    m_fightContext.activeFighters.insert(getAllyPokemon());
    
    // Insert Stages for the Ability if needed
    insertEnteringEffect(Team::allied);
}



void FightState2::retrieveEnnemyPokemon() {
    // Get the Ennemi pokemon;
    Pokemon* ennemy = getEnnemyPokemon();
            
    // Show a message for the pokemon leaving the fight
    m_ui.addDialog(getTrainerName() + " retire " + ennemy->getName() + ".");


    // Hide the ally display
    m_ui.setPokemonDisplayVisibility(Team::ennemy, false);
    
    
    // Apply the Ability
    if(!ennemy->isKO())
        ennemy->getAbility().onLeavingSwitch(ennemy);
}



void FightState2::sendEnnemyPokemon() {
    std::cout << "Converting the Ennemy manager to switch pokemons" << std::endl;
    
    // Switch the Pokemon
    ((FightTrainerManager*)m_ennemyManager)->sendBetterPokemon(getAllyPokemon());
    
    // Show a message for the pokemon leaving the fight
    m_ui.addDialog(getTrainerName() + " envoie " + getEnnemyPokemon()->getName() + " !");

    // Hide the ally display
    m_ui.setPokemonDisplayVisibility(Team::ennemy, true);
    
    // Update the displays
    updatePokemonDisplays();
    
    
    // Update the XP Sharer
    m_xpSharer.addFaced(getEnnemyPokemon(), getAllyPokemon());
    
    
    // Insert Stages for the Ability if needed
    insertEnteringEffect(Team::ennemy);
}



bool FightState2::canSwitch(Team team) {
    if(team == Team::allied){
        // Get the pokemon that would leave
        Pokemon* leaver = getAllyPokemon();
        
        if(leaver->isKO())
            return true;
        else
            return getEnnemyPokemon()->getAbility().allowEnnemySwitch(*leaver);
    }
    else{
        // Get the pokemon that would leave
        Pokemon* leaver = getEnnemyPokemon();
        
        if(leaver->isKO())
            return true;
        else
            return getAllyPokemon()->getAbility().allowEnnemySwitch(*leaver);
    }
}



void FightState2::useAllyItem() {
    // Get the Item and check its effect
    Item* item = new Item(m_turnContext.allyItem);
    Pokemon* pokemon = m_character->getPokemonAt(m_turnContext.allySelected);

    m_ui.addDialog(sf::String(L"Vous utilisez l'objet " + item->getName() + L" ! "));

    if(item->hasEffectOnPokemon(pokemon)){
        auto effects = item->onPokemon(pokemon);

        // Take the Item from the Character and use it
        delete m_character->takeItem(item->getID());

        // While there are effects left
        while(!effects.empty()){
            // Push each effect string into the dialog queue
            if(effects.front()->hasString())
                m_ui.addDialog(effects.front()->getString());
            else
                m_ui.addDialog(sf::String("Missing string for one item effect"));
            
            delete effects.front();
            effects.pop();
        }
    }
    else{
        m_ui.addDialog(sf::String(L"Mais cela n'a aucun effet."));
    }
    
    delete item;
}



void FightState2::usePokeball() {
    if(m_ennemyManager->canBeCaptured()){
        // Check if the ennemy pokemon was captured
        Item* ball = new Item(m_turnContext.allyItem);
        
        // Check if the ennemy pokemon was captured
        FightWildManager* manager = (FightWildManager*)m_ennemyManager;
        int captureRate = manager->captureRate(ball->getCaptureValue());
        
        // Check the number of bounces
        m_turnContext.ballBounces = manager->bouncesNumber(captureRate);
        
        // Hide The Menu
        m_ui.hideMenu();
        
        // Dialog
        m_ui.addDialog(L"Vous lancez une " + ball->getName() + L" ! \nCapture rate : " + toWString(captureRate));
    }
    else{
        m_ui.addDialog(sf::String(L"Vous ne pouvez pas capturer ce pokemon !"));
        m_turnContext.ballBounces = 0;
    }
}



void FightState2::replaceEnnemyWithBall() {
    // Replace the ennemy sprite by the ball thrown
    m_ui.replaceEnnemySprite(m_turnContext.allyItem);
}



void FightState2::replaceEnnemyWithSprite() {
    // Replace the ennemy sprite by the ball thrown
    m_ui.replaceEnnemySprite();
}



void FightState2::captureTry() {
    // Push the Dialog lines for the bounces
    if(m_turnContext.ballBounces >= 1){
        m_ui.addDialog(sf::String(L"..."));
    }
    if(m_turnContext.ballBounces >= 2){
        m_ui.addDialog(sf::String(L"... ..."));
    }
    if(m_turnContext.ballBounces >= 3){
        m_ui.addDialog(sf::String(L"... ... ..."));
    }
    
    if(m_turnContext.ballBounces == 4){
        m_ui.addDialog(L"Le " + getEnnemyPokemon()->getName() + L" sauvage est capturé !");
        
        m_turnContext.ennemyCaptured = true;
        
        // We change the stages to end the fight
        cleanQueue();
        pushStage(FS_Dialog, DialogClosed);
        
        // End the Fight
        pushEndFightStages();
    }
    else{
        m_ui.addDialog(L"Le " + getEnnemyPokemon()->getName() + L" sauvage s'est échappé !");
    }
}



void FightState2::useEnnemyItem() {
    // Get the Item and check its effect
    Item* item = new Item(m_turnContext.ennemyItem);
    Pokemon* pokemon = m_ennemyManager->getCurrentPokemon();

    m_ui.addDialog(getTrainerName() + L" utilise l'objet " + item->getName() + L" ! ");
    
    if(item->hasEffectOnPokemon(pokemon)){
        // TODO
        auto effects = item->onPokemon(pokemon);
        
        // Take off the item
        ((FightTrainerManager*)m_ennemyManager)->useItem(item->getID());
        
        while(!effects.empty()){
            // Push each effect string into the dialog queue
            if(effects.front()->hasString())
                m_ui.addDialog(effects.front()->getString());
            else
                m_ui.addDialog(sf::String("Missing string for one item effect"));
            
            delete effects.front();
            effects.pop();
        }
    }
    else{
        m_ui.addDialog(sf::String(L"Mais cela n'a aucun effet."));
        std::cout << "IA trouble : the Trainer used an item with no effects";
    }
        
    delete item;
}



void FightState2::updatePokemonDisplays() {
    m_ui.setAlly(getAllyPokemon());
    m_ui.setEnnemy(getEnnemyPokemon());
    
    m_ui.updatePokemonDisplays();
    
    // Update the Character Display
    m_character->updateTeamPreview();
}



void FightState2::updateAllyStatus() {
    // Get the ally pokemon, and its status
    Pokemon* pokemon = getAllyPokemon();
    MainStatusName statusName = pokemon->getMainStatus().getName();
    
    if(statusName == MainStatusName::Freeze){
        // If the pokemon is unfreezed show a dialog
        if(pokemon->getMainStatus().statusEnd()){
            m_ui.addDialog(pokemon->getName() + L" n'est plus gelé !");
            pokemon->cureMainStatus();
        }
    }
    else if(statusName == MainStatusName::Sleep){
        // If the pokemon is awake then show a dialog
        if(pokemon->getMainStatus().statusEnd()){
            m_ui.addDialog(pokemon->getName() + L" n'est plus endormi !");
            pokemon->cureMainStatus();
        }
    }
    
    // Update the Displays
    updatePokemonDisplays();
    
    // Update the turns
    pokemon->updateTurns();
}



void FightState2::updateEnnemyStatus() {
    // Get the ally pokemon, and its status
    Pokemon* pokemon = getEnnemyPokemon();
    MainStatusName statusName = pokemon->getMainStatus().getName();
    
    if(statusName == MainStatusName::Freeze){
        // If the pokemon is unfreezed show a dialog
        if(pokemon->getMainStatus().statusEnd()){
            m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi n'est plus gelé !");
            pokemon->cureMainStatus();
        }
    }
    else if(statusName == MainStatusName::Sleep){
        // If the pokemon is awake then show a dialog
        if(pokemon->getMainStatus().statusEnd()){
            m_ui.addDialog(L"Le " + pokemon->getName() + L" ennemi n'est plus endormi !");
            pokemon->cureMainStatus();
        }
    }
    
    // Update the Displays
    updatePokemonDisplays();
    
    // Update the turns
    pokemon->updateTurns();
}



void FightState2::flee() {
    // If the player managed to flee
    if(true){
        // Push a stage for leaving the fight
        pushStage(FS_QuitFight, FightQuitted, &FightState2::quit);

        // Flee Dialog
        m_ui.addDialog(sf::String(L"Vous fuyez le combat !"));
        m_ui.showDialog(true);

        // Set the wild pokemon to defeated
        m_turnContext.flee = true;
    }
    else{
        /*
        m_ui.addDialog(L"Vous tentez de fuir le combat...");
        m_ui.addDialog(L"Mais cela échoue !");
        m_ui.showDialog(true);

        EnnemyStages
        */
    }
}



void FightState2::endFight() {
    std::cout << "Ending Fight" << std::endl;
    // End Dialog
    if(m_character->hasPokemonsLeft()){
        
        std::cout << "Pushing End Dialog" << std::endl;
        
        if(m_turnContext.ennemyCaptured){
            //  Get the ennemy
            Pokemon* ennemy = getEnnemyPokemon();
            m_fightContext.pokemonCaptured = ennemy;
            
            // We update the Pokedex
            m_character->getPokedex().addPokemonSaw(ennemy->getID());
            m_character->getPokedex().addPokemonCaptured(ennemy->getID());
            
            // Set the Pokemon Zone
            ennemy->getMetadata().setCaptureZone(m_character->getZone()->getZoneID());
            
            if(m_character->getPokemonTeam()->canAddPokemon()){
                // Add it to the team
                m_ui.addDialog(ennemy->getName() + L" est ajouté à l'equipe !");
                m_character->getPokemonTeam()->addPokemon(ennemy);
            }
            else{
                // Add it to the Box
                m_ui.addDialog(ennemy->getName() + L" est envoyé dans une\nboîte PC.");
                m_character->getBoxSystem().addPokemon(ennemy);
            }
        }
        
        // Update the trainers defeated
        if(m_ennemyManager->isTrainer()){
            // Get the trainer
            Trainer* trainer = ((FightTrainerManager*)m_ennemyManager)->getTrainer();
            m_character->addTrainerDefeated(trainer->getID());
        }
    }
    else
        m_character->leaveFight();
    
    // Add the End dialog
    addEndDialog(m_character->hasPokemonsLeft());
}



void FightState2::addEndDialog(bool characterWon) {
    // Add a dialog to show we defeated the trainer, and get the money 
    if(m_ennemyManager->isTrainer()){
        // Win money
        if(characterWon){
            // Get the Money
            int money = ((FightTrainerManager*)m_ennemyManager)->getTrainer()->getMoneyGiven();            
            
            // For each pokemon that fought
            for(auto poke : m_fightContext.activeFighters)
                // Apply a booster on the money
                if(poke->hasItem())
                    poke->getItem()->onMoneyGained(money);
            
            // Add a dialog
            m_ui.addDialog(sf::String(L"Vous avez gagné le combat !\nVous récupérez " + toWString(money) + L"$."));

            // Give the money to the Character
            m_character->addMoney(money);
        }
        // Loose money
        else{
            // Get the current character money
            int money = m_character->getMoney();
            
            // Loose half money if it has a 
            if(money > 0){
                // Get the money lost
                int moneyLost = (int)(money+1)/2;
                
                // Show the dialog
                m_ui.addDialog(sf::String(L"Vous n'avez plus de pokemon en forme.\nVous perdez " + toWString(moneyLost) + L"$."));
                
                // Take money from the character
                m_character->pay(moneyLost);
            }
            else
                m_ui.addDialog(sf::String(L"Vous n'avez plus de pokemon en forme."));
        }
    }
    // Else add a simple dialog for the win
    else if(characterWon)
        m_ui.addDialog(sf::String(L"Vous avez gagné le combat !"));
    // Push a dialog for the lost
    else
        m_ui.addDialog(sf::String(L"Vous n'avez plus de pokemon en forme."));
}



void FightState2::quit() {
    // Set the state to completed
    m_isCompleted = true;
}



Pokemon* FightState2::getAllyPokemon() {
    return m_character->getPokemonAt(getAllyIndex());
}



Pokemon* FightState2::getEnnemyPokemon() {
    return m_ennemyManager->getCurrentPokemon();
}



int FightState2::getAllyIndex() {
    return m_turnContext.currentAlly;
}



void FightState2::giveXPAndEVs() {
    // Get the ally concerned
    Pokemon* ally = m_turnContext.xpReceivers.front();
    m_turnContext.xpReceivers.pop();
    
    // Give the EV
    ally->addEVYielded(getEnnemyPokemon()->getID());
    
    // Get the xp point
    int xpPoints = m_xpSharer.getXPGivingEach(getEnnemyPokemon());
    
    // APply the Pokemon Item on the xp
    if(ally->hasItem())
        ally->getItem()->onXPGained(xpPoints);
    
    m_ui.addDialog(ally->getName() + L" gagne " + toWString(xpPoints) + L" points \nd'expérience.");

    // Give XP level by level
    int levelsUp = 0;
    while(xpPoints > 0){
        int xpLeft = ally->giveXp(xpPoints);

        // If there are xp left then it means the pokemon levelled up
        if(xpLeft > 0){
            levelsUp++;
        }

        xpPoints = xpLeft;
    }

    // Get the final level
    int level = ally->getLevel();
    
    // Push a message if there was a level up
    if(levelsUp > 0){
        std::cout << "Levelling Up ! " << std::endl;
        
        if(levelsUp == 1){
            m_ui.addDialog(ally->getName() + L" monte au niveau " + toWString(level) + L" ! ");
        }
        else if(levelsUp > 1){
            m_ui.addDialog(ally->getName() + L" passe du niveau " + toWString(level-levelsUp) + L" à " + toWString(level) + L" ! ");
        }
        
        // Check the attacks it can learn
        std::set<AttackID> newAttacks = ally->getAttacksSinceLevel(level-levelsUp);
        
        if(!newAttacks.empty()){
            // We add the attacks
            for(AttackID id : newAttacks)
                m_turnContext.learntAttacks.push(id); 
            
            // Add the pokemon to learn attacks
            m_fightContext.attackLearner = ally;
        }
    }
    
    // Update the XP Bars and the displays
    m_ui.updatePokemonDisplays();
}



void FightState2::sendFightResultEvent() {
    if(m_character->hasPokemonsLeft())
        m_stack->addGameEvent(new GameEvent(EventType::FightWon));
    else{
        m_stack->addGameEvent(new GameEvent(EventType::FightLost));
        
        // Make the Trainer look the other way to prevent an interaction from trigerring
        if(m_ennemyManager->isTrainer()){
            Trainer* t = static_cast<FightTrainerManager*>(m_ennemyManager)->getTrainer();
            t->setDirection(oppositeDirection(t->getDirection()));
        }
    }
}



bool FightState2::isAllyKO() {
    return getAllyPokemon()->isKO();
}



bool FightState2::isEnnemyKO() {
    return getEnnemyPokemon()->isKO();
}



void FightState2::calculateEnnemyTurn() {
    m_turnContext.ennemyAction = m_ennemyManager->getNextAction(getAllyPokemon(), canSwitch(Team::ennemy));
    
    // Get the Attack
    if(m_turnContext.ennemyAction == FightAction::FA_Attack){
        m_turnContext.ennemyAttack = m_ennemyManager->getNextAttackIndex();
        std::cout << "Choose attack" << m_turnContext.ennemyAttack << std::endl;
    }
    // Get the item
    else if(m_turnContext.ennemyAction == FightAction::FA_Item){
        m_turnContext.ennemyItem = m_ennemyManager->getItemToUse();
    }
} 



const FightStage& FightState2::getCurrentStage() {
    assert(m_stages.size() > 0);
    
    return *(m_stages.front());
}



const FightStage& FightState2::getLastStage() {
    return *(m_stages.back());
}



Character* FightState2::getCharacter() {
    return m_character;
}



bool FightState2::isCharacterDefeated() const {
    return !m_character->hasPokemonsLeft();
}