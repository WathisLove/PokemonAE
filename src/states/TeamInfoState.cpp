#include "TeamInfoState.hpp"
#include "TeamState.hpp"
#include "BoxState.hpp"

#include <iostream>

TeamInfoState::TeamInfoState(StateStack* stack, Character* character) :
State(stack),
m_character(character),
m_ui(stack->getContext(), m_character->getPokemonTeam()),
m_currentPanel(PokemonInfoPanel::TI_GlobalInfoPanel),
m_currentPokemon(0),
m_showAttackDetails(false),
m_currentAttack(0){
    // Set the ID
    m_id = StateID::TeamInfoS;
    
    // Set the UI Position
    m_ui.setPosition(m_character->getSpriteCenter() - sf::Vector2f(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.));
    
    // Set the current pokemon
    setupCurrentPokemon();
}



void TeamInfoState::actionOnCompletion() {
    // Pop the state
    m_stack->requestStackPop();
    
    // Update the BoxState cursor if there is such a State
    if(m_stack->hasStateOfID(StateID::BoxS)){
        // Get the team state and the index of the pokemon selected from the BoxState
        BoxState* bs = (BoxState*) m_stack->getStateOfID(StateID::BoxS);
        bs->setSelectedPokemon(m_currentPokemon);
    }
}



void TeamInfoState::draw() {
    // Draw the main sprite
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();

    window.draw(m_ui);
}



bool TeamInfoState::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Get the Key pressed
        sf::Keyboard::Key key = event.key.code;
        
        if(m_showAttackDetails){
            if(key == sf::Keyboard::S){
                std::cout << "Showing next attack" << std::endl;
                showNextAttack();
            }
            else if(key == sf::Keyboard::Z){
                std::cout << "Showing previous attack" << std::endl;
                showPreviousAttack();
            }
            else if(key == sf::Keyboard::Escape || key == sf::Keyboard::Space){
                std::cout << "Unselecting attacks" << std::endl;
                unshowAttacks();
            }
        }
        else{
            if(key == sf::Keyboard::S){
                std::cout << " - Next Pokemon" << std::endl;
                showNextPokemon();
            }
            else if(key == sf::Keyboard::Z){
                std::cout << " - Previous Pokemon" << std::endl;
                showPreviousPokemon();
            }
            else if(key == sf::Keyboard::D){
                std::cout << " - Next Panel" << std::endl;
                showNextInfoPanel();
            }
            else if(key == sf::Keyboard::Q){
                std::cout << " - Previous Panel" << std::endl;
                showPreviousInfoPanel();
            }
            else if(key == sf::Keyboard::Escape){
                m_isCompleted = true;
            }
            else if(key == sf::Keyboard::Space && m_currentPanel == PokemonInfoPanel::TI_AttacksPanel){
                showAttacksDetails();
                std::cout << "Showing Attack Details"<< std::endl;
            }
        }
    }
    
    return false;
}



bool TeamInfoState::update(float dt) {
    
    return false;
}



void TeamInfoState::showAttacksDetails() {
    // Reset the attack shown to 0
    m_currentAttack = 0;
    
    m_showAttackDetails = true;
    m_ui.showAttackDetails(true);
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void TeamInfoState::showNextAttack() {
    // Get the index of the next attack
    int nbAttacks = getCurrentPokemon()->getAttackSet().getNbAttacks();
    m_currentAttack = (m_currentAttack+1)%nbAttacks;
    
    // Update the UI
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void TeamInfoState::showPreviousAttack() {
    // Get the index of the next attack
    int nbAttacks = getCurrentPokemon()->getAttackSet().getNbAttacks();
    m_currentAttack = (m_currentAttack+nbAttacks-1) % nbAttacks;
    
    // Update the UI
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void TeamInfoState::unshowAttacks() {
    m_showAttackDetails = false;
    m_ui.showAttackDetails(false);
}



void TeamInfoState::showNextPokemon() {
    // Get the index of the next pokemon
    int nbPokemons = m_character->getPokemonTeam()->getNbPokemon();
    m_currentPokemon = (m_currentPokemon+1)%nbPokemons;
    
    // Update the ui
    m_ui.setCurrentPokemon(m_currentPokemon);
}



void TeamInfoState::showPreviousPokemon() {
    // Get the index of the previous pokemon
    int nbPokemons = m_character->getPokemonTeam()->getNbPokemon();
    m_currentPokemon = (m_currentPokemon+nbPokemons-1) % nbPokemons;
    
    // Update the ui
    m_ui.setCurrentPokemon(m_currentPokemon);
}



void TeamInfoState::showPreviousInfoPanel() {
    if(m_currentPanel == PokemonInfoPanel::TI_GlobalInfoPanel){
        m_currentPanel = PokemonInfoPanel::TI_AttacksPanel;
        m_ui.showAttacks();
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_StatsPanel){
        m_currentPanel = PokemonInfoPanel::TI_GlobalInfoPanel;
        m_ui.showGlobalInfos();
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_AttacksPanel){
        m_currentPanel = PokemonInfoPanel::TI_StatsPanel;
        m_ui.showStats();
    }
}



void TeamInfoState::showNextInfoPanel() {
    if(m_currentPanel == PokemonInfoPanel::TI_GlobalInfoPanel){
        m_currentPanel = PokemonInfoPanel::TI_StatsPanel;
        m_ui.showStats();
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_StatsPanel){
        m_currentPanel = PokemonInfoPanel::TI_AttacksPanel;
        m_ui.showAttacks();
    }
    else if(m_currentPanel == PokemonInfoPanel::TI_AttacksPanel){
        m_currentPanel = PokemonInfoPanel::TI_GlobalInfoPanel;
        m_ui.showGlobalInfos();
    }
}



Pokemon* TeamInfoState::getCurrentPokemon() {
    return m_character->getPokemonAt(m_currentPokemon);
}



Attack* TeamInfoState::getCurrentAttack() {
    return m_character->getPokemonAt(m_currentPokemon)->getAttackSet().getAttack(m_currentAttack);
}



void TeamInfoState::setupCurrentPokemon() {
    if(m_stack->hasStateOfID(StateID::TeamS)){
        // Get the team state and the index of the pokemon selected
        TeamState* ts = (TeamState*) m_stack->getStateOfID(StateID::TeamS);
        m_currentPokemon = ts->getSelectedPokemonIndex();
    }
    else if(m_stack->hasStateOfID(StateID::BoxS)){
        // Get the team state and the index of the pokemon selected from the BoxState
        BoxState* bs = (BoxState*) m_stack->getStateOfID(StateID::BoxS);
        m_currentPokemon = bs->getPokemonIndexSelected();
    }
    else{
        m_currentPokemon = 0;
    }
    
    m_ui.setCurrentPokemon(m_currentPokemon);
}
