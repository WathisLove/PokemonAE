#include "BoxInfoState.hpp"
#include "BoxState.hpp"

BoxInfoState::BoxInfoState(StateStack* stack, Character* character) :
State(stack),
m_ui(stack->getContext(), character->getPokemonTeam()->getPokemonAt(0)),
m_currentPanel(PokemonInfoPanel::TI_GlobalInfoPanel),
m_showAttackDetails(false),
m_currentAttack(0){
    // Find the selected box
    BoxState* boxState = (BoxState*) m_stack->getStateOfID(StateID::BoxS);
    m_box = boxState->getCurrentBox();
    m_currentPokemon = boxState->getPokemonIndexSelected();
    
    
    // Set the UI Position
    m_ui.setPosition(character->getSpriteCenter() - sf::Vector2f(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.));
    
    // Set the UI with the current pokemon
    m_ui.setPokemon(m_box->getPokemonAt(m_currentPokemon));
}



void BoxInfoState::actionOnCompletion() {
    // Pop the state
    m_stack->requestStackPop();
    
    // Update the BoxState cursor 
    // Get the team state and the index of the pokemon selected from the BoxState
    BoxState* bs = (BoxState*) m_stack->getStateOfID(StateID::BoxS);
    bs->setSelectedPokemon(m_currentPokemon);
}



void BoxInfoState::draw() {
    // Draw the main sprite
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();

    window.draw(m_ui);
}



bool BoxInfoState::handleEvent(sf::Event& event) {

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



bool BoxInfoState::update(float dt) {
    return false;
}



Attack* BoxInfoState::getCurrentAttack() {
    return getCurrentPokemon()->getAttackSet().getAttack(m_currentAttack);
}



Pokemon* BoxInfoState::getCurrentPokemon() {
    return m_box->getPokemonAt(m_currentPokemon);
}



void BoxInfoState::showAttacksDetails() {
    // Reset the attack shown to 0
    m_currentAttack = 0;
    
    m_showAttackDetails = true;
    m_ui.showAttackDetails(true);
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void BoxInfoState::showNextPokemon() {
    // Get the next pokemon index 
    m_currentPokemon = m_box->getNextPokemonIndex(m_currentPokemon);
    
    // Set the UI with the next pokemon
    m_ui.setPokemon(m_box->getPokemonAt(m_currentPokemon));
}



void BoxInfoState::showPreviousPokemon() {
    // Get the next pokemon index 
    m_currentPokemon = m_box->getPreviousPokemonIndex(m_currentPokemon);
    
    // Set the UI with the previous pokemon
    m_ui.setPokemon(m_box->getPokemonAt(m_currentPokemon));
}



void BoxInfoState::showNextInfoPanel() {
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



void BoxInfoState::showPreviousInfoPanel() {
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



void BoxInfoState::showNextAttack() {
    // Get the index of the next attack
    int nbAttacks = getCurrentPokemon()->getAttackSet().getNbAttacks();
    m_currentAttack = (m_currentAttack+1)%nbAttacks;
    
    // Update the UI
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void BoxInfoState::showPreviousAttack() {
    // Get the index of the next attack
    int nbAttacks = getCurrentPokemon()->getAttackSet().getNbAttacks();
    m_currentAttack = (m_currentAttack+nbAttacks-1) % nbAttacks;
    
    // Update the UI
    m_ui.setAttackDetails(getCurrentAttack());
    m_ui.setAttackGreyExcept(m_currentAttack);
}



void BoxInfoState::unshowAttacks() {
    m_showAttackDetails = false;
    m_ui.showAttackDetails(false);
}