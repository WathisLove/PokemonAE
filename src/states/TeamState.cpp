#include "TeamState.hpp"
#include "BagState.hpp"
#include "ChoiceState.hpp"

TeamState::TeamState(StateStack* stack, Character* c) :
State(stack),
m_character(c),
m_selectedEntry(0),
m_background(stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_teamBackground)),
m_currentStage(TeamStage::TChoosingPokemon),
m_actionMenu(stack->getContext()),
m_objectMenu(stack->getContext()),
m_secondaryState(nullptr),
m_lastSelectedEntry(-1),
m_mustSelectPokemon(false),
m_pokeInFight(-1),
m_learningCt(false){
    // Set the id
    m_id = StateID::TeamS;
    
    
    // Set the background position and origin
    m_background.setOrigin(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.);
    m_background.setPosition(c->getSpriteCenter());
    
    
    setEntries();
    
    setupMenus();
    
    // Check if we must learn an attack to a pokemon
    stateTryToLearnAttack();
}



void TeamState::actionOnCompletion() {
    // Don't pop if we are waiting before closing the state
    if(!m_waitBeforeClosing){
        std::cout << "Popping Team state" << std::endl;
        m_stack->requestStackPop();
    }
}



void TeamState::draw() {
    // Get the window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    // Draw the background
    window.draw(m_background);
    
    
    // Draw the Entries
    for(const TeamEntry& te : m_pokemonTeamEntry){
        window.draw(te);
    }
    
    // Draw the menus (only show when activated
    window.draw(m_actionMenu);
    window.draw(m_objectMenu);
    
}



bool TeamState::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
    // Get the key pressed
    sf::Keyboard::Key key = event.key.code;
    
        // When we choose a pokemon
        if(m_currentStage == TeamStage::TChoosingPokemon){
            eventChoosingPokemon(event);
        }
        // When we choose an action
        else if(m_currentStage == TeamStage::TChoosingAction){
            eventChoosingAction(event);
        }
        else if(m_currentStage == TeamStage::TObjectMenu){
            eventObjectMenu(event);
        }
        else if(m_currentStage == TeamStage::TObjectMoving){
            eventMovingObject(event);
        }
        else if(m_currentStage == TeamStage::TMovingPokemon){
            eventMovingPokemon(event);
        }
    }
    
    return false;
}



void TeamState::eventMovingPokemon(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;

        
        // Quit if Escape is pressed
        if(key == sf::Keyboard::Escape){
            m_currentStage = TeamStage::TChoosingPokemon;
            
            m_lastSelectedEntry = -1;
            //updateEntries();
        }

        // Check the movement of the selector
        else if(key == sf::Keyboard::Z)
            goUp();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Q)
            goLeft();
        // Check the movement of the selector
        else if(key == sf::Keyboard::S)
            goDown();
        // Check the movement of the selector
        else if(key == sf::Keyboard::D)
            goRight();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Space){
            switchTeamMembers();
            m_lastSelectedEntry = -1;
            updateEntries();
            m_currentStage = TeamStage::TChoosingPokemon;
        }
    }
}



void TeamState::eventChoosingPokemon(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;

        
        // Quit if Escape is pressed
        if(key == sf::Keyboard::Escape){
            
            // Push a Dialog if we must select a pokemon
            if(m_mustSelectPokemon)
                m_stack->requestStackPushDialog(sf::String(L"Vous devez choisir un pokemon !"));
            else
                m_isCompleted = true;
        }

        // Check the movement of the selector
        else if(key == sf::Keyboard::Z)
            goUp();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Q)
            goLeft();
        // Check the movement of the selector
        else if(key == sf::Keyboard::S)
            goDown();
        // Check the movement of the selector
        else if(key == sf::Keyboard::D)
            goRight();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Space)
            choosePokemon();
    }
}



void TeamState::eventChoosingAction(sf::Event& event) {

    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;
        
        m_actionMenu.handleKeyPressed(key);

        if(key == sf::Keyboard::Space){
            chooseAction();
        }
        else if(key == sf::Keyboard::Escape){
            m_actionMenu.close();
            m_currentStage = TeamStage::TChoosingPokemon;
            std::cout << "Choosing Pokemon" << std::endl;
        } 
    }
}



void TeamState::eventObjectMenu(sf::Event& event) {

    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;
        
        m_objectMenu.handleKeyPressed(key);

        if(key == sf::Keyboard::Space){
            chooseObjectAction();
        }
        else if(key == sf::Keyboard::Escape){
            m_objectMenu.close();
            m_currentStage = TeamStage::TChoosingAction;
            m_actionMenu.open();
        }
    }
}



void TeamState::eventMovingObject(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // Get the key pressed
        sf::Keyboard::Key key = event.key.code;

        
        // Quit if Escape is pressed
        if(key == sf::Keyboard::Escape)
            m_isCompleted = true;

        // Check the movement of the selector
        else if(key == sf::Keyboard::Z)
            goUp();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Q)
            goLeft();
        // Check the movement of the selector
        else if(key == sf::Keyboard::S)
            goDown();
        // Check the movement of the selector
        else if(key == sf::Keyboard::D)
            goRight();
        // Check the movement of the selector
        else if(key == sf::Keyboard::Space){
            Pokemon* target = getSelectedPokemon();
            if(target->hasItem()){
                m_stack->requestStackPushChoice(target->getName() + L" tient déjà l'objet " + target->getItem()->getName() + L".\nEchanger les deux objets ?");
            }
            else{
                target->swapItem(getLastSelectedPokemon());
                m_lastSelectedEntry = -1;
                updateEntries();
                m_currentStage = TeamStage::TChoosingPokemon;
            }
        }
    }
}



void TeamState::choosePokemon() {
    
    // Put the Stage in every case so we know we selected a pokemon
    m_currentStage = TeamStage::TChoosingAction;
    
    
    // Select a use if the menu is activated
    if(m_actionMenu.isActivated()){
        m_actionMenu.open();
    }
    else {
        m_isCompleted = true;
        m_actionMenu.close();
    }
}



void TeamState::chooseAction() {
    
    // Get the string to choose the selected action
    const std::wstring& action = m_actionMenu.getSelectedText().getString().toWideString();
    
    if(action == L"Résumé"){
        openPokemonInfos();
    }
    else if(action == L"Ordre"){
        m_currentStage = TeamStage::TMovingPokemon;
        m_lastSelectedEntry = m_selectedEntry;
    }
    else if(action == L"Echanger"){
        // Cancel if the Selected pokemon is KO
        if(getSelectedPokemon()->isKO()){
            m_currentStage = TeamStage::TChoosingPokemon;
            m_stack->requestStackPushDialog(sf::String(L"Vous ne pouvez pas choisir un pokemon KO !"));
        }
        // Cancel if the Selected pokemon is already in the fight
        else if(getSelectedPokemonIndex() == m_pokeInFight){
            m_currentStage = TeamStage::TChoosingPokemon;
            m_stack->requestStackPushDialog(getSelectedPokemon()->getName() + L" est déjà au combat.");
        }
        else{
            // The stage is finished
            m_isCompleted = true;
        }
    }
    else if(action == L"Objet"){
        m_currentStage = TeamStage::TObjectMenu;
        m_objectMenu.open();
    }
    else if(action == L"Annuler"){
        std::cout << "Annuler" << std::endl;
        m_currentStage = TeamStage::TChoosingPokemon;
    }

    // Close the menu at the end to reset its selection
    m_actionMenu.close();
}



void TeamState::chooseObjectAction() {
    
    // Get the string to choose the selected action
    std::wstring action = m_objectMenu.getSelectedText().getString().toWideString();

    if(action == L"Donner"){
        openBag();
    }
    else if(action == L"Déplacer"){
        std::cout << "Deplacer" << std::endl;
        if(getSelectedPokemon()->hasItem()){
            m_currentStage = TeamStage::TObjectMoving;
            m_lastSelectedEntry = m_selectedEntry;
            m_pokemonTeamEntry.at(m_lastSelectedEntry).setLastSelected();
        }
        else{
            m_stack->requestStackPushDialog(getSelectedPokemon()->getName() + L" ne tient aucun objet.");
            m_currentStage = TeamStage::TChoosingPokemon;
        }
    }
    else if(action == L"Retirer"){
        std::cout << "Retirer" << std::endl;
        takeObject();
    }
    else if(action == L"Annuler"){
        std::cout << "Annuler" << std::endl;
        choosePokemon();
    }

    // Close the menu at the end to reset its selection
    m_objectMenu.close();
}



void TeamState::openBag() { 
    // Set the stage type
    m_currentStage = TeamStage::TObjectChoosing;
    
    // Open a Bagstate
    m_stack->requestStackPush(StateID::BagS, m_character);
}



void TeamState::takeObject() {
    // Get the pokemon and take its item
    Pokemon* p = getSelectedPokemon();
    Item* i = p->takeItem();
    
    // Give it to the character
    m_character->giveItem(i);
    
    // Push a Dialog Stage to display a message
    m_stack->requestStackPushDialog(L"Vous retirez l'objet " + i->getName() + L" à " + p->getName() + L".");
    
    // Set the Stage to SelectingPokemon
    m_currentStage = TeamStage::TChoosingPokemon;
}



void TeamState::openPokemonInfos() {
    std::cout << "Pokemon Infos !" << std::endl;
    
    // Set the stage type
    // Go back directly to choosing pokemon as we don't need it as a secondaryState
    m_currentStage = TeamStage::TChoosingPokemon;
    m_actionMenu.close();
    std::cout << m_character << std::endl;
    
    // Open PokemonState
    m_stack->requestStackPush(StateID::TeamInfoS, m_character);
}


bool TeamState::isCompleted() const {
    return m_isCompleted;
}



bool TeamState::update(float dt) {
    
    if(m_secondaryState == nullptr){
        findSecondaryState();
    }
    
    else if(m_secondaryState->isCompleted()){
        // Get the value returned by the secondary state
        if(m_secondaryState->getID() == StateID::BagS){
            BagState* bs = (BagState*)m_secondaryState;
            if(bs->hasSelectedItem()){
                // Get the Item ID and give it to the pokemon
                Item* item = m_character->takeItem(bs->getItemIDSelected());
                Pokemon* p = getSelectedPokemon();
                
                m_secondaryState->waitBeforeClosing(false);
                m_secondaryState->actionOnCompletion();
                
                if(!p->hasItem()){
                    p->giveItem(item);
                    // Push a small dialog
                    m_stack->requestStackPushDialog(p->getName() + L" tient maintenant l'objet " + item->getName() + L".");
                    m_currentStage = TeamStage::TChoosingPokemon;
                }
                else{
                    m_stack->requestStackPushChoice(p->getName() + L" tient déjà l'objet " + p->getItem()->getName() + L".\nEchanger les deux objets ?");
                    m_currentStage = TeamStage::TObjectReplacing;
                    m_itemBuffer = item;
                }
            }else{
                std::cout << "No item was ever selected" << std::endl;
                
                m_secondaryState->waitBeforeClosing(false);
                m_secondaryState->actionOnCompletion();
                
                m_currentStage = TeamStage::TChoosingPokemon;
            }
        }
        else if(m_secondaryState->getID() == StateID::ChoiceS){
            // Get the choice state and its result
            int entry = ((ChoiceState*)m_secondaryState)->getEntrySelected();
            
            // Replacing the object of a pokemon
            if(m_currentStage == TeamStage::TObjectReplacing){
                if(entry == 0){ // Yes
                    replaceObject();
                }
                else{ // No
                    m_secondaryState->waitBeforeClosing(false);
                    m_secondaryState->actionOnCompletion();
                    m_character->giveItem(m_itemBuffer);
                }
            }
            // Moving an object from a pokemon to another
            else if(m_currentStage == TeamStage::TObjectMoving){
                if(entry == 0){ // Yes
                    getSelectedPokemon()->swapItem(getLastSelectedPokemon());
                    
                    m_secondaryState->waitBeforeClosing(false);
                    m_secondaryState->actionOnCompletion();
                }
                else{ // No
                    m_secondaryState->waitBeforeClosing(false);
                    m_secondaryState->actionOnCompletion();
                }
                
                // Unselect the last pokemon
                m_lastSelectedEntry = -1;
            }
            
            m_itemBuffer = nullptr;
            m_currentStage = TeamStage::TChoosingPokemon;
        }
        
        m_secondaryState = nullptr;
        updateEntries();
    }
    
    return true;
}



int TeamState::getMaxIndex() {
    return m_character->getPokemonTeam()->getNbPokemon()-1;
}



void TeamState::goDown() {
    m_selectedEntry = (m_selectedEntry+2) % (getMaxIndex()+1);
        
    updateEntries();
}



void TeamState::goLeft() {
    m_selectedEntry = (m_selectedEntry+getMaxIndex()) % (getMaxIndex()+1);
    
    updateEntries();
}



void TeamState::goRight() {
    m_selectedEntry = (m_selectedEntry+1) % (getMaxIndex()+1);
    
    updateEntries();
}



void TeamState::goUp() {
    // Get the offset when going up
    int offset;
    
    if(getMaxIndex() < 4)
        offset = 2;
    else
        offset = 4;
    
    m_selectedEntry = (m_selectedEntry+offset) % (getMaxIndex()+1);
    
    updateEntries();
}



Pokemon* TeamState::getSelectedPokemon() {
    return m_character->getPokemonAt(m_selectedEntry);
}



int TeamState::getSelectedPokemonIndex() {
    return m_selectedEntry;
}



Pokemon* TeamState::getLastSelectedPokemon() {
    return m_character->getPokemonAt(m_lastSelectedEntry);
}



bool TeamState::hasSelectedPokemon() {
    // We have selected a pokemon once we leave the corresponding stage
    return m_currentStage != TeamStage::TChoosingPokemon;
}



void TeamState::unselectPokemon() {
    // we change the Satge to select a pokemon
    m_currentStage = TeamStage::TChoosingPokemon;
    
    // The stage is not completed anymore
    m_isCompleted = false;
}



void TeamState::findSecondaryState() {
    // Get the BagStatey
    if(m_currentStage == TeamStage::TObjectChoosing){
        m_secondaryState = m_stack->getStateOfID(StateID::BagS);
        m_secondaryState->waitBeforeClosing(true);
        
        BagState* bs = (BagState*) m_secondaryState;
        bs->setAsSecondaryState(true);
        bs->deactivateMenu();
    }
    else if(m_currentStage == TeamStage::TObjectReplacing){
        m_secondaryState = m_stack->getStateOfID(StateID::ChoiceS);
    }
    else if(m_currentStage == TeamStage::TObjectMoving){
        // The Choice state only pop when the pokemon already holds an item and we try to switch it
        if(m_stack->hasStateOfID(StateID::ChoiceS))
            m_secondaryState = m_stack->getStateOfID(StateID::ChoiceS);
    }
}



void TeamState::switchTeamMembers() {
    PokemonTeam* team = m_character->getPokemonTeam();
    
    team->switchPokemons(m_lastSelectedEntry, m_selectedEntry);
    
    updateTeamDislay();
}



void TeamState::replaceObject() {
    // Take the item and give it to the Character
    Item* oldItem = getSelectedPokemon()->takeItem();
    m_character->giveItem(oldItem);

    // Give the new item to the Pokemon
    Pokemon* p = getSelectedPokemon();
    p->giveItem(m_itemBuffer);
    m_secondaryState->waitBeforeClosing(false);
    m_secondaryState->actionOnCompletion();
    m_stack->requestStackPushDialog(p->getName() + L" tient maintenant l'objet " + m_itemBuffer->getName() + L".");
}



void TeamState::updateTeamDislay() {
    // Update the Team Preview and the entries
    setEntries();
    
    // Also update the Character Preview
    m_character->updateTeamPreview();
}



void TeamState::updateEntries() {
    for(int i = 0; i < m_pokemonTeamEntry.size(); i++){
        m_pokemonTeamEntry.at(i).select(i == m_selectedEntry);
        
        // Update the Items displayed
        m_pokemonTeamEntry.at(i).updateItem();
    }
    
    // Select the Last entry to display which one it is
    if(m_lastSelectedEntry != -1){
        m_pokemonTeamEntry.at(m_lastSelectedEntry).setLastSelected();
    }
}



void TeamState::setEntries() {
    PokemonTeam* team = m_character->getPokemonTeam();
    
    // Clear the vector
    m_pokemonTeamEntry.clear();
    
    // Get the offset to the top left corner of the screen
    sf::Vector2f topLeft(m_character->getSpriteCenter() - sf::Vector2f(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.));
    
    int nbPokemons = team->getNbPokemon();
    
    // Add the correct number of entries
    for(int i = 0; i < nbPokemons; i++){
        // Get the pokemon
        Pokemon* p = team->getPokemonAt(i);
        
        // Choose the position
        sf::Vector2f pos(30 + 400 * (i%2), 30 + 200 * (i/2));
        
        // Add a new Entry
        TeamEntry te(m_stack->getContext(), p, topLeft + pos);
        m_pokemonTeamEntry.push_back(te);
    }
    
    // Update the entries to show the selected
    updateEntries();
}



void TeamState::setupMenus() {

    // Set the Action Menu
    m_actionMenu.setPosition(m_character->getSpriteCenter() + sf::Vector2f(200, 120));
    m_actionMenu.addEntry(L"Résumé");
    m_actionMenu.addEntry(L"Ordre");
    m_actionMenu.addEntry(L"Objet");
    m_actionMenu.addEntry(L"Annuler");
    
    // Set the Object Menu
    m_objectMenu.setPosition(m_character->getSpriteCenter() + sf::Vector2f(200, 120));
    m_objectMenu.addEntry(L"Donner");
    m_objectMenu.addEntry(L"Déplacer");
    m_objectMenu.addEntry(L"Retirer");
    m_objectMenu.addEntry(L"Annuler");
}



void TeamState::deactivateMenus() {
    m_actionMenu.setActivated(false);
    m_objectMenu.setActivated(false);
}



void TeamState::setFightEntries() {
    // Clear the old entries
    m_actionMenu.clearEntries();
    
    // Add the new one used by a FightState
    m_actionMenu.addEntry(L"Echanger");
    m_actionMenu.addEntry(L"Résumé");
    m_actionMenu.addEntry(L"Annuler");
}



void TeamState::forceSelection() {
    m_mustSelectPokemon = true;
    
    // Push a DialogState
    m_stack->requestStackPushDialog(sf::String(L"Choisissez un pokemon à envoyer au combat."));
}



void TeamState::setPokeInFight(int index) {
    m_pokeInFight = index;
}



void TeamState::stateTryToLearnAttack() {
    // Try to find a bag to get the CT
    if(m_stack->hasStateOfID(StateID::BagS)){
        BagState* bs = (BagState*) m_stack->getStateOfID(StateID::BagS);
        
        // Get the Item Category
        if(Item::getCategory(bs->getItemIDSelected()) == ItemCategory::CT){
            // Get the attack linked to the CT
            AttackID id = Item::getAttackTeached(bs->getItemIDSelected());

            // Setup to learn the CT
            setToLearnCT(id);
        }
    }
}



void TeamState::setToLearnCT(AttackID ctAttack) {
    // Set the mode to LearnCT
    m_learningCt = true;
    
    // Update the UI
    for(int i = 0; i < m_pokemonTeamEntry.size(); i++){
        m_pokemonTeamEntry[i].setToLearnCT(ctAttack);
    }   
}
