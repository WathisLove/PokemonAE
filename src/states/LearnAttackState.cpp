#include "LearnAttackState.hpp"
#include "ChoiceState.hpp"

LearnAttackState::LearnAttackState(StateStack* stack, Pokemon* p, AttackID attackLearning) :
State(stack),
m_ui(stack->getContext(), p, attackLearning),
m_newAttackID(attackLearning),
m_attackSelected(0),
m_pokemon(p),
m_secondaryState(nullptr),
m_currentStage(LearnStage::ls_SelectingAttack),
m_attackWasLearnt(false){
    m_id = StateID::LearnAttackS;
    
    // Set the UI position
    m_ui.setPosition(stack->getContext().getWindowTopLeftCorner());
}



void LearnAttackState::actionOnCompletion() {
    // Quit if there is still the ChoiceState
    if(m_stack->hasStateOfID(StateID::ChoiceS))
        return;
    
    // Pop the State
    m_stack->requestStackPop();
    
    //// Push a Dialog for the result
    
    // Get the new Attack
    Attack* newAttack = AttackFabric::createAttack(m_newAttackID);
        
    // Show a Dialog message
    if(m_attackWasLearnt){
        // Get the old Attack
        Attack* oldAttack = AttackFabric::createAttack(m_oldAttackID);
        
        // The Attack was learnt
        m_stack->requestStackPushDialog(m_pokemon->getName() + L" oublie " + oldAttack->getName() + 
                                    L" et apprend \ndésormais " + newAttack->getName() + L" !");
        
        // Delete the old attack
        delete oldAttack;
    }
    else{
        // The Attack was not learnt
        m_stack->requestStackPushDialog(m_pokemon->getName() + L" n'a pas appris " +newAttack->getName() + L".");
    }
    
    // Delete the attack
    delete newAttack;
}



void LearnAttackState::draw() {
    // Draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();

    window.draw(m_ui);
}



bool LearnAttackState::handleEvent(sf::Event& event) {
    
    if(event.type == sf::Event::KeyPressed){
        // Select an attack
        if(m_currentStage == LearnStage::ls_SelectingAttack){
            
            sf::Keyboard::Key key = event.key.code;
        
            // Change the current attack
            if(key == sf::Keyboard::Z)
                previousAttack();
            else if(key == sf::Keyboard::S)
                nextAttack();
            
            // Select the current attack
            else if(key == sf::Keyboard::Space)
                selectAttack();
            
            // Or quit
            else if(key == sf::Keyboard::Escape)
                quit();
        }
    }
    return false;
}



bool LearnAttackState::update(float dt) {

    // If we must find a secondary state
    if(m_currentStage != LearnStage::ls_SelectingAttack){
        // try to find a secondary state
        if(m_secondaryState == nullptr){
            // Find the choice state
            if(m_stack->hasStateOfID(StateID::ChoiceS)){
                m_secondaryState = m_stack->getStateOfID(StateID::ChoiceS);
            }
        }
        else{
            ChoiceState* cs = (ChoiceState*)m_secondaryState;
            
            // If we made a choice
            if(cs->isCompleted()){
                if(m_currentStage == LearnStage::ls_ReplaceConfirmation)
                    choiceReplace();
                else if(m_currentStage == LearnStage::ls_QuitConfirmation)
                    choiceQuit();
            }
        }
    }
    
    return false;
}



void LearnAttackState::nextAttack() {
    // change the attack selected by +1
    m_attackSelected = (m_attackSelected+1)%5;
    
    m_ui.selectAttack(m_attackSelected);
}



void LearnAttackState::previousAttack() {
    // change the attack selected by -1
    m_attackSelected = (m_attackSelected+4)%5;
    
    m_ui.selectAttack(m_attackSelected);
}



void LearnAttackState::selectAttack() {
    // Only push a ChoiceState if we are not on the new attack
    if(m_attackSelected != 4){
        // Change the current stage
        m_currentStage = LearnStage::ls_ReplaceConfirmation;

        // Get the Attack
        Attack* attack = m_pokemon->getAttackSet().getAttack(m_attackSelected);
        
        // Push a ChoiceState
        m_stack->requestStackPushChoice(L"Remplacer " + attack->getName() + L" ? ");
    }
}



void LearnAttackState::quit() {
    // Change the current stage
    m_currentStage = LearnStage::ls_QuitConfirmation;
    
    // Push a ChoiceState
    m_stack->requestStackPushChoice(L"Etes-vous sûr de vouloir abandonner ?");
}



void LearnAttackState::choiceReplace() {
    // Get the result of the ChoiceState
    ChoiceState* cs = (ChoiceState*)m_secondaryState;
    
    if(cs->getResultString() == L"Oui"){
        
        // Get the Old Attack ID
        m_oldAttackID = m_pokemon->getAttackSet().getAttack(m_attackSelected)->getID();
        
        // We replace the attack
        m_pokemon->replaceAttack(m_attackSelected, m_newAttackID);
        m_attackWasLearnt = true;
        
        // We quit the LearnAttack State
        m_isCompleted = true;
    }
    
    // Go back to do not look after another secondary State)
    m_currentStage = LearnStage::ls_SelectingAttack;
    
    // Close the secondary state
    m_secondaryState->waitBeforeClosing(false);
    m_secondaryState = nullptr;
}



void LearnAttackState::choiceQuit() {
    // Get the result of the ChoiceState
    ChoiceState* cs = (ChoiceState*)m_secondaryState;
    
    if(cs->getResultString() == L"Oui"){
        // We quit the LearnAttack State
        m_isCompleted = true;
    }
    
    // Go back to do not look after another secondary State)
    m_currentStage = LearnStage::ls_SelectingAttack;
    
    // Close the secondary state
    m_secondaryState->waitBeforeClosing(false);
    m_secondaryState = nullptr;
}
