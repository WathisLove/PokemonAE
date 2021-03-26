#include "BoxState.hpp"
#include "../Utilities.hpp"


BoxState::BoxState(StateStack* stack, Character* character) :
State(stack),
m_character(character),
m_ui(stack->getContext(), character),
m_cursorInTeam(true),
m_selection(0),
m_isPokeSelected(false),
m_boxTitleSelected(false),
m_currentBox(0),
m_pokemonTaken(nullptr){
    m_id = StateID::BoxS;
    
    
    // Set the UI position
    m_ui.setPosition(stack->getContext().getWindowTopLeftCorner());
}



void BoxState::actionOnCompletion() {
    // Pop the state
    m_stack->requestStackPop();
    
    // Update the Character Team Preview
    m_character->updateTeamPreview();
    m_character->freeze(false);
}



void BoxState::draw() {
    // Draw the UI
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();

    window.draw(m_ui);
}



bool BoxState::handleEvent(sf::Event& event) {

    if(event.type == sf::Event::KeyPressed){
        sf::Keyboard::Key key = event.key.code;
        
        // Pokemon Selected
        if(m_isPokeSelected){
            
            if(key == sf::Keyboard::Space){
                // Drop the pokemon or switch it with the present one
                dropPokemon();
            }
            else{
                // Move the Cursor
                moveCursor(key);
            }
        }
        // Handle Menu events
        else if(m_ui.isMenuOpen()){

            if(key == sf::Keyboard::Space){
                // Choose the menu entry
                selectMenu();
            }
            else if(key == sf::Keyboard::Escape){
                m_ui.showMenu(false);
            }
            else{
                // Move the menu cursor
                m_ui.getMenu().handleKeyPressed(key);
            }
        }
        // Open the Menu
        else if(key == sf::Keyboard::Space && cursorOnPokemon()){
            // Open the Menu
            m_ui.getMenu().open();
        }
        // Close the Box State
        else if(key == sf::Keyboard::Escape){
            m_isCompleted = true;
        }
        // Open the Menu
        else{
            // Move the Cursor
            moveCursor(key);
        }
    }
    
    // Do not handle events with the next State
    return false;
}



bool BoxState::update(float dt) {
    // Do not update next State
    return false;
}



PokemonBox* BoxState::getCurrentBox() {
    return m_character->getBoxSystem().getBox(m_currentBox);
}



int BoxState::getPokemonIndexSelected() {
    return m_selection;
}



void BoxState::setSelectedPokemon(int index) {
    m_selection = index;
    
    setUICursor();
}



void BoxState::updateUI() {
    
    // Select a pokemon if it is not a null pointer
    if(m_isPokeSelected)
        m_ui.selectPokemon(m_pokemonTaken->getID());
    
    // Update the team and box displays
    m_ui.setBox(m_currentBox);
    m_ui.setTeam(*(m_character->getPokemonTeam()));
}



bool BoxState::cursorOnPokemon() {
    if(m_cursorInTeam){
        return m_selection < m_character->getPokemonTeam()->getNbPokemon();
    }
    else if(!m_boxTitleSelected){
        return getCurrentBox()->hasPokemonAtIndex(m_selection);
    }
    else
        return false;
}



void BoxState::moveCursor(sf::Keyboard::Key keyPressed) {
    // Move the cursor Up
    if(keyPressed == sf::Keyboard::Z){
        moveUp();
    }
    // Move the cursor Down
    else if(keyPressed == sf::Keyboard::S){
        moveDown();
    }
    // Move the cursor Left
    else if(keyPressed == sf::Keyboard::Q){
        moveLeft();
    }
    // Move the cursor Right
    else if(keyPressed == sf::Keyboard::D){
        moveRight();
    }
}



void BoxState::moveRight() {
    if(m_cursorInTeam){
        m_cursorInTeam = false;
        
        m_selection *= 6;
    }
    else if(m_boxTitleSelected){
        nextBox();
    }
    else{
        // If we are on the left of the box
        if((m_selection % 6) == 5){
            m_cursorInTeam = true;
            m_selection /= 6;
            
            // Put the cursor back on a team member
            int teamMaxIndex = getTeamMaxSelection();
            if(m_selection >= teamMaxIndex)
                m_selection = teamMaxIndex-1;
        }
        else{
            m_selection++;
        }
    }
    
    setUICursor();
}



void BoxState::moveLeft() {
    if(m_cursorInTeam){
        m_cursorInTeam = false;
        
        m_selection = m_selection*6 + 5;
    }
    else if(m_boxTitleSelected){
        previousBox();
    }
    else{
        // If we are on the right of the box
        if((m_selection % 6) == 0){
            m_cursorInTeam = true;
            m_selection /= 6;
            
            // Put the cursor back on a team member
            int teamMaxIndex = getTeamMaxSelection();
            if(m_selection >= teamMaxIndex)
                m_selection = teamMaxIndex-1;
        }
        else{
            m_selection--;
        }
    }
    
    setUICursor();
}



void BoxState::moveUp() {
    if(m_cursorInTeam){
        int teamMaxIndex = getTeamMaxSelection();
        m_selection = (m_selection+teamMaxIndex-1) % teamMaxIndex;
    }
    else if(m_boxTitleSelected){
        // Go back to a pokemon in the box
        selectBoxTitle(false);
        
        // Update the cursor for the next move
        m_selection = (m_selection+30) % 36;
    }
    else{
        // If we are on the first line, select the title
        if(m_selection <= 5){
            selectBoxTitle(true);
        }
        else{
            // Update the cursor for the next move
            m_selection = (m_selection+30) % 36;
        }
    }
    
    setUICursor();
}



void BoxState::moveDown() {
    if(m_cursorInTeam){
        int teamMaxIndex = getTeamMaxSelection();
        m_selection = (m_selection+1) % (teamMaxIndex);
    }
    else if(m_boxTitleSelected){
        // Go back to a pokemon in the box
        selectBoxTitle(false);
    }
    else{
        // If we are on the first line, select the title
        if(m_selection >= 30){
            selectBoxTitle(true);
        }
        
        m_selection = (m_selection+6) % 36;
    }
    
    setUICursor();
}



void BoxState::setUICursor() {
    m_ui.setCursorPosition(m_selection, m_cursorInTeam);
}



int BoxState::getTeamMaxSelection() {
    // If a poke is selected 
    if(m_isPokeSelected){
        // We can select the last case +1
        if(m_character->getPokemonTeam()->canAddPokemon())
            return m_character->getNbPokemon()+1;
        else
            return 6;
    }
    else{
        return m_character->getNbPokemon();
    }
}



void BoxState::selectMenu() {
    // Get the text entry selected
    std::wstring entry = m_ui.getMenu().getSelectedText().getString().toWideString();
    
    if(entry == L"Déplacer"){
        movePokemon();
    }
    else if(entry == L"Déposer"){
        sendToBox();
    }
    else if(entry == L"Retirer"){
        sendToTeam();
    }
    else if(entry == L"Résumé"){
        openPokemonInfos();
    }
    
    // Close the menu
    m_ui.getMenu().close();
}



void BoxState::movePokemon() {
    if(m_cursorInTeam){
        // Else if the pokemon is the only one alive
        if(m_character->getPokemonTeam()->getNbNotKO() == 1 && 
                !m_character->getPokemonTeam()->getPokemonAt(m_selection)->isKO()){
            m_stack->requestStackPushDialog(sf::String(L"Vous devez garder au moins un pokemon non KO !"));
        }
        else{
            m_isPokeSelected = true;
            
            // Take from the team
            m_pokemonTaken = m_character->getPokemonTeam()->removePokemonAt(m_selection);
        }
    }
    else{
        // Take from the box
        m_pokemonTaken = getCurrentBox()->removePokemon(m_selection);
        m_isPokeSelected = true;
    }
    
    // Update the UI
    updateUI();
}



void BoxState::sendToBox() {
    // If there are more than 1 alive or the one sent to the box is one KO
    if(m_character->getPokemonTeam()->getNbNotKO() > 1 || 
       m_character->getPokemonTeam()->getPokemonAt(m_selection)->isKO()){
        // Take the pokemon from the team
        Pokemon* p = m_character->getPokemonTeam()->removePokemonAt(m_selection);

        // Heal it
        p->healEverything();

        // Put it into the box system
        m_character->getBoxSystem().addPokemon(p);

        // Show a dialog
        m_stack->requestStackPushDialog(p->getName() + sf::String(L" est envoyé dans le PC !"));
        
        // Update the UI
        updateUI();
    }
    else{
        // Show a dialog has the player needs at least 1 pokemon
        m_stack->requestStackPushDialog(sf::String(L"Vous devez garder au moins un pokemon non KO!"));
    }
}


    
void BoxState::sendToTeam() {
    if(m_character->getPokemonTeam()->canAddPokemon()){
        // Take the pokemon from the box
        Pokemon* p = getCurrentBox()->removePokemon(m_selection);
        
        // Add the pokemon from the box to the team
        m_character->getPokemonTeam()->addPokemon(p);
        
        // Show a dialog
        m_stack->requestStackPushDialog(p->getName() + sf::String(L" est ajouté à l'équipe !"));
        
        // Update the UI
        updateUI();
    }
    else{
        // Show a dialog if there is no place
        m_stack->requestStackPushDialog(sf::String(L"Votre équipe est déjà pleine ! \nVeuillez retirer un pokemon."));
    }
}



void BoxState::openPokemonInfos() {
    if(m_cursorInTeam){
        m_stack->requestStackPush(StateID::TeamInfoS, m_character);
    }
    else{
        m_stack->requestStackPush(StateID::BoxInfoS, m_character);
    }
}



void BoxState::dropPokemon() {
    // Switch 
    if(cursorOnPokemon()){
        // Heal it
        m_pokemonTaken->healEverything();
        
        switchPokemon();
    }
    // Put it in the team
    else if(m_cursorInTeam){
        // Heal it
        m_pokemonTaken->healEverything();
        
        // Put the pokemon in the team
        m_character->getPokemonTeam()->addPokemon(m_pokemonTaken);
        
        // Unselect the pokemon
        m_pokemonTaken = nullptr;
        m_isPokeSelected = false;
        
        m_ui.unselectPokemon();
    }
    // If there is place left in the Box
    else if(getCurrentBox()->hasPlace()){ 
        // Heal it
        m_pokemonTaken->healEverything();
        
        // Put the pokemon in the box
        m_currentBox = m_character->getBoxSystem().addPokemon(m_pokemonTaken, m_currentBox, m_selection);
        
        // Unselect the pokemon
        m_pokemonTaken = nullptr;
        m_isPokeSelected = false;
        
        m_ui.unselectPokemon();
    }
    
    // Update the UI
    updateUI();
}



void BoxState::switchPokemon() {
    if(m_cursorInTeam){
        // Remove the pokemon from the team
        m_pokemonTaken = m_character->getPokemonTeam()->replacePokemonWith(m_pokemonTaken, m_selection);
    }
    else{
        // Remove the pokemon from the box
        Pokemon* p = getCurrentBox()->removePokemon(m_selection);
        
        // Put the old pokemon in the box
        getCurrentBox()->addPokemon(m_pokemonTaken, m_selection);
        
        // Update the pokemon taken
        m_pokemonTaken = p;
    }
}



void BoxState::selectBoxTitle(bool select) {
    // Go back to a pokemon in the box
    m_boxTitleSelected = select;

    m_ui.showTitleCursor(select);
    
    // Do not show the cursor if we already have the title cursor
    m_ui.showCursor(!select);
}



void BoxState::nextBox() {
    // Get the number of boxes
    int nbBox = m_character->getBoxSystem().size();
    
    // Go to the next box
    m_currentBox = (m_currentBox+1) % nbBox;
    
    
    updateUI();
}



void BoxState::previousBox() {
    // Get the number of boxes
    int nbBox = m_character->getBoxSystem().size();
    
    // Go to the previous box
    m_currentBox = (m_currentBox+nbBox-1) % nbBox;
    
    
    updateUI();
}
