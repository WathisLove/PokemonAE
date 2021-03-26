#include "EvolutionState.hpp"
#include "State.hpp"

#include <iostream>



EvolutionState::EvolutionState(StateStack* stack, Character* character, Pokemon* pokemonUnevolved, PokemonID evolutionID) :
State(stack),
m_pokemon(pokemonUnevolved),
m_character(character),
m_evolved(false),
m_timePassed(0.),
m_ui(stack->getContext(), pokemonUnevolved),
m_stage(EvolutionStage::DialogBegin){
    // Set the State ID
    m_id = StateID::EvolutionS;
    
    // Create the evolved pokemon
    m_pokemonEvolved = m_pokemon->evolve(evolutionID);
    
    // Set the UI Position
    m_ui.setPosition(m_stack->getContext().getWindowTopLeftCorner());
}



void EvolutionState::actionOnCompletion() {
    // Pop the evolution state
    m_stack->requestStackPop();
    
    // If the pokemon didn't evolved delete the evolution
    if(!m_evolved)
        delete m_pokemonEvolved;
    else{
        m_character->getPokemonTeam()->addLeveledUp(m_pokemonEvolved);
        delete m_pokemon;
    }
}



void EvolutionState::draw() {
    // Get the render window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // Draw the UI
    window.draw(m_ui);
}



bool EvolutionState::handleEvent(sf::Event& event) {
    
    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;
        
        // If the player press escape and the evolution is not done yet
        if(key == sf::Keyboard::Escape && canCancel()){
            cancelEvolution();
        }
    }
    
    
    // Unable lower states to handle events
    return false;
}



bool EvolutionState::isCompleted() const {
    
    // Wait before the dialog closes
    if(m_stack->hasStateOfID(StateID::DialogS))
        return false;
    
    return m_isCompleted;
}



bool EvolutionState::update(float dt) {
    // Update the time passed
    m_timePassed += dt;
    
    if(!m_isCompleted){
        /// Check which stage we are in
        if(m_stage == EvolutionStage::DialogBegin){
            // Push a Dialog
            m_stack->requestStackPushDialog(m_pokemon->getName() + sf::String(L" évolue !"));
            
            // Resetting the Time and changin the State
            m_timePassed = 0;
            m_stage = PreEvolution;
        }
        else if(m_stage == EvolutionStage::PreEvolution){
            // Wait a second for the first dialog to pop
            if(m_timePassed > 2.0){
                m_timePassed = 0;
                evolvePokemon();
                std::cout << "Evolving !" << std::endl;
            }
        }
        else if(m_stage == EvolutionStage::Evolution){
            // Wait a second for the first dialog to pop
            if(m_timePassed > 2.0){
                m_timePassed = 0;
                m_stage = DialogEnd;
                // Push a Dialog
                m_stack->requestStackPushDialog(m_pokemon->getName() + sf::String(L" a évolué en ") + pokemonIDtoString(m_pokemonEvolved->getID()) + " !");
                std::cout << "Evolution finished !" << std::endl;
            }
        }
        else if(m_stage == EvolutionStage::DialogEnd){
            // Wait a second for the first dialog to pop
            if(m_timePassed > 1.0){
                // End the State
                m_isCompleted = true;
                std::cout << "Dialog ended and closing state !" << std::endl;
            }
        }
    }    
    
    
    // Unable lower states to update
    return false;
}



void EvolutionState::evolvePokemon() {
    // Find the pokemon in the character team
    for(int i = 0; i < m_character->getPokemonTeam()->getNbPokemon() && !m_evolved; i++){
        Pokemon* p = m_character->getPokemonAt(i);
        
        // IF we found the pokemon
        if(p == m_pokemon)
        {
            // Replace it with the evolution
            m_character->getPokemonTeam()->replacePokemonWith(m_pokemon, m_pokemonEvolved);
            
            // Update the UI
            m_ui.setPokemonDisplayed(m_pokemonEvolved);
                    
            // The pokemon evolved
            m_evolved = true;
        }
    }
    
    // Update the TeamPreview
    m_character->updateTeamPreview();
    
    // Update the Stage
    m_stage = Evolution;
}




void EvolutionState::cancelEvolution() {
    // Push a Dialog
    m_stack->requestStackPushDialog(m_pokemon->getName() + L" a cessé d'évoluer !");
    
    // Wait for the dialog push before quitting
    m_stage = DialogEnd;
}



bool EvolutionState::canCancel() {
    // Check if the evoltuion is not done or cancelled yet
    return notEvolvedYet();
}



bool EvolutionState::notEvolvedYet() {
    return m_stage == DialogBegin || m_stage == PreEvolution;
}
