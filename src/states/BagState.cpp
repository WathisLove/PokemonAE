#include "BagState.hpp"
#include "../resources/TextureHolder.hpp"
#include "../resources/FontHolder.hpp"
#include "../Constants.hpp"
#include "../inventory/Item.hpp"
#include "../pokemons/attacks/AttackFabric.hpp"
#include "TeamState.hpp"
#include "ChoiceState.hpp"
#include "../utility/Logger.hpp"



BagState::BagState(StateStack* stack, Character* c) :
State(stack),
m_character(c),
m_background(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_bagBackground)),
m_categorySelector(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_bagCategSelector)),
m_selectedCategory(0),
m_currentStage(BagStage::Bag_SelectingItem),
m_itemSelector(m_stack->getContext(), c->getSpriteCenter()+sf::Vector2f(115, -265)),
m_itemName("", m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont), 28),
m_itemCount("", m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont), 28),
m_itemDescription("", m_stack->getContext().getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_itemDisplay(m_stack->getContext(), new Item(ItemID::pokeball)),
m_isSelected(false),
m_menu(stack->getContext()),
m_secondaryState(nullptr),
m_pokemonIndexSelected(-1){
    // We set the ID
    m_id = StateID::BagS;
    
    // Set the Background
    m_background.setOrigin(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.f);
    m_background.setPosition(m_character->getSpriteCenter());
    
    // Set the CategorySelector
    updateCategorySelector(sf::Keyboard::Unknown);
    
    // Set the graphical attributes for the item display
    m_itemName.setFillColor(sf::Color::Black);
    m_itemCount.setFillColor(sf::Color::Black);
    m_itemDescription.setFillColor(sf::Color::Black);
    m_itemDisplay.setZoomFactor(GAME_ZOOM);
    
    // Update the Display
    updateItemDisplay();
    
    // Add the sprites for the categories
    for(int i = 0; i < 6; i++){
        sf::Sprite s(m_stack->getContext().getTextureHolder()->getTexture(TextureHolder::ui_bagCateg), sf::IntRect(78*i,0,78,78));
        s.setPosition(c->getSpriteCenter() + sf::Vector2f(-289 + 100*i, 200));
        m_categories.push_back(s);
    }
    
    updateCategorySprites();
    
    buildMenu();
}



void BagState::actionOnCompletion() {
    
    // Don't pop if we are waiting before closing the state
    if(!m_waitBeforeClosing){
        std::cout << "Popping Bag state" << std::endl;
        m_stack->requestStackPop();
    }
}



void BagState::draw() {
    // Quit if the state is not shown
    if(!m_isShown)
        return;
    
    // Get the RenderWindow
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow();
    
    
    // Draw the Background
    window.draw(m_background);
    
    // Draw the categories
    for(int i = 0; i < 6; i++){
        window.draw(m_categories.at(i));
    }
    // Draw the Category Selector
    window.draw(m_categorySelector);
    
    
    if(m_itemSelector.getItemCount() > 0){
        window.draw(m_itemName);
        window.draw(m_itemCount);
        window.draw(m_itemDescription);
        window.draw(m_itemDisplay);
    }
    window.draw(m_itemSelector);
    
    window.draw(m_menu);
}



bool BagState::handleEvent(sf::Event& event) {
    // quit if we should ignore events
    if(m_ignoreEvents)
        return m_letEventsPass;
    
    else if(event.type == sf::Event::KeyPressed){
        // We get the pressed key
        sf::Keyboard::Key key = event.key.code;
        
        
        if(m_currentStage == BagStage::Bag_SelectingItem){
            if(key == sf::Keyboard::Escape)
                m_isCompleted = true;

            else if(key == sf::Keyboard::Space)
                selectCurrentItem();

            else if(key == sf::Keyboard::D || key == sf::Keyboard::Q){
                if(m_currentStage == BagStage::Bag_SelectingItem){
                    updateCategorySelector(key);
                    updateCategorySprites();
                }
                else
                    m_currentStage = BagStage::Bag_SelectingItem;
            }

            // ItemSelector handles events too
            m_itemSelector.handleEvent(event);
            // If the item selector changed updtate the displayed item
            if(m_itemSelector.changed())
                updateItemDisplay();
        }
        else if(m_currentStage == BagStage::Bag_SelectingUse){
            m_menu.handleKeyPressed(key);
            
            if(key == sf::Keyboard::Escape){
                m_menu.close();
                m_currentStage = BagStage::Bag_SelectingItem;
            }
            if(key == sf::Keyboard::Space){
                selectItemUse();
            }
        }
        else{
            std::cout << "Je suis perdu la " << m_currentStage << std::endl;
        }
    }
    
    return m_letEventsPass;
}



void BagState::handleGameEvent(const GameEvent& event) {
    if(m_currentStage == BagStage::SelectingAttack){
        if(event.getType() == EventType::SelectingAttack){
            // Get the Attack
            useItemOnAttack(event.attack);
        }
        else if(event.getType() == EventType::StatePopped && event.stateID == StateID::SelectAttackS)
            unselectItem();
    }
}



bool BagState::isCompleted() const {
    return m_isCompleted;
}



bool BagState::update(float dt) {    
    if(m_secondaryState == nullptr)
        findSecondaryState();
    
    // If we want to give or use an item
    else if(m_currentStage == BagStage::Bag_GivingToPokemon ||
            m_currentStage == BagStage::Bag_UsingOnPokemon){
        
        // We check if the secondary state is completed
        if(m_secondaryState->isCompleted()){
        
            // We get the TeamStage
            TeamState* ts = (TeamState*)m_secondaryState;
        
            // We Check if the TeamState has selected a pokemon
            if(ts->hasSelectedPokemon()){
                onPokemonSelected();
            }
            else{
                std::cout << "No pokemon was selected" << std::endl;

                m_currentStage = BagStage::Bag_SelectingUse;
            
                closeSecondaryState();
                
                m_menu.open();
            }
        }
    }
    // Dialogs for the ITem effects
    else if(m_currentStage == BagStage::Bag_ItemEffects){
        if(!m_itemEffects.empty()){
            Pokemon* p = getSelectedPokemon();
            
            // Show the next effect 
            if(m_itemEffects.front()->hasString())
                m_stack->requestStackPushDialog(m_itemEffects.front()->getString());
            else
                Log("ItemEffect without string in BagState !");
            removeSingleItemEffect();
        }
        else{
            std::cout << "Closing Secondary state" << std::endl;
            // Close the TeamState
            closeSecondaryState();
            
            // Change the Stage
            m_currentStage = BagStage::Bag_SelectingItem;
            std::cout << "Item effects done" << std::endl;
        }
    }
    // If we have had Dialog and an update, then the Dialo is off and we close the TeamState
    else if(m_currentStage == BagStage::Bag_Dialog){
        // Close the Team State
        closeSecondaryState();
        
        // Now we want to select another item
        m_currentStage = BagStage::Bag_SelectingItem;
    }
    
    // If we want ask to replace an item
    else if(m_currentStage == BagStage::Bag_ChoiceReplacingItem){
        
        if(m_secondaryState->isCompleted()){
            // Get the choice state and its result
            int entry = ((ChoiceState*)m_secondaryState)->getEntrySelected();
            
            // We close the ChoiceState
            closeSecondaryState();
            m_currentStage = BagStage::Bag_GivingToPokemon;

            // We find the TeamState
            findSecondaryState();
            
            if(entry == 0){ // Yes
                // We get the selected Pokemon
                Pokemon* p = ((TeamState*)m_secondaryState)->getSelectedPokemon();
                
                // We take of his item, and then give him the new one
                m_character->giveItem(p->takeItem());
                
                givePokemonSelectedItem();
            }
            else{
                // We close the TeamState
                closeSecondaryState();
                
                // We now want to select another item
                m_currentStage = BagStage::Bag_SelectingItem;
            }
        }
    }
    // Allow under states like the TeamState to update
    return true;
}



void BagState::onPokemonSelected() {
    // Get the Secondary state
    TeamState* ts = (TeamState*)m_secondaryState;
    
    // And get the concerned Pokemon
    m_pokemonIndexSelected = ts->getSelectedPokemonIndex();
    Pokemon * pokemon = getSelectedPokemon();
    
    // Give an item
    if(m_currentStage == BagStage::Bag_GivingToPokemon){

        if(!pokemon->hasItem()){
            givePokemonSelectedItem();
        }
        else{
            m_stack->requestStackPushChoice(pokemon->getName() + L" tient déjà un objet !\nEchanger les deux objets ?");
            m_currentStage = BagStage::Bag_ChoiceReplacingItem;
            m_secondaryState = nullptr;
        }
    }
    // Give an item
    else if(m_currentStage == BagStage::Bag_UsingOnPokemon){
        // We check if we are in a fight -> let the FightState use the item
        if(m_isSecondaryState){
            closeSecondaryState();
            m_isCompleted = true;
        }
        else
            useSelectedItem();
    }
}



void BagState::selectCurrentItem() {
    // Only select if there is at list 1 item
    if(m_itemSelector.getItemCount() > 0){
        m_isSelected = true;
        
        
        // Select a use if the menu is activated
        if(m_menu.isActivated()){
            m_currentStage = BagStage::Bag_SelectingUse;
            m_menu.open();
        }
        // We are a secondary State of a TeamState, and we close when an item is selected
        else{
            m_isCompleted = true;
        }
    }
}



void BagState::selectItemUse() {
    std::wstring menuEntry = m_menu.getSelectedText().getString().toWideString();
    
    if(menuEntry == L"Utiliser"){
        m_currentStage = BagStage::Bag_UsingOnPokemon;
        
        Item* it = new Item(getItemIDSelected());
        
        // If we are not in a fight
        if(!m_waitBeforeClosing){
            if(it->isUsable()){
                // Open a TeamState
                std::cout << "Utilisabe" << std::endl;
                m_stack->requestStackPush(StateID::TeamS, m_character);
            }
            else {
                std::cout << "Pas utilisabe" << std::endl;
                m_stack->requestStackPushDialog(sf::String(L"Vous ne pouvez pas utiliser l'objet ") + it->getName() + sf::String(L" maintenant."));
                m_currentStage = BagStage::Bag_SelectingItem;
            }
        }
        // In a fight
        else{
            if(it->isUsableInFight()){
                if(it->getUseInBattle() == UseInBattle::POKEBALL){
                    std::cout << "Utilisabe" << std::endl;
                    m_isCompleted = true;
                }
                else{
                    // Open a TeamState
                    std::cout << "Utilisable : selection d'un pokemon" << std::endl;
                    m_stack->requestStackPush(StateID::TeamS, m_character);
                }
            }
            else {
                std::cout << "Pas utilisabe" << std::endl;
                m_stack->requestStackPushDialog(sf::String(L"Vous ne pouvez pas utiliser l'objet ") + it->getName() + sf::String(L" maintenant."));
                m_currentStage = BagStage::Bag_SelectingItem;
            }
        }
        delete it;
        
        m_menu.close();
    }
    
    else if(menuEntry == L"Donner"){        
        m_currentStage = BagStage::Bag_GivingToPokemon;
        
        Item* it = new Item(getItemIDSelected());
        
        if(it->isGivable()){
            std::cout << "Donnable" << std::endl;
            m_stack->requestStackPush(StateID::TeamS, m_character);
        }
        else {
            std::cout << "Pas donnable" << std::endl;
            m_stack->requestStackPushDialog(sf::String(L"Vous ne pouvez pas donner cet objet !"));
            m_currentStage = BagStage::Bag_SelectingItem;
        }
        delete it;
        
        m_menu.close();
    }
    else if(menuEntry == L"Annuler"){
        std::cout << "Annuler" << std::endl;
        m_currentStage = BagStage::Bag_SelectingItem;
        m_menu.close();
    }
}



bool BagState::hasSelectedItem() {
    return m_isSelected;
}



int BagState::getSelectedPokemonIndex() {
    return m_pokemonIndexSelected;
}



Pokemon* BagState::getSelectedPokemon() {
    if(m_pokemonIndexSelected == -1)
        throw "No pokemon was ever selected to a selected pokemon";
    
    return m_character->getPokemonAt(m_pokemonIndexSelected);
}



void BagState::unselectItem() {
    // Unselect the Item and go back to the selecting Stage
    m_isSelected = false;
    m_currentStage = BagStage::Bag_SelectingItem;
    
    // Uncomplete now
    m_isCompleted = false;
}



ItemID BagState::getItemIDSelected() {
    // Check if have selected the item, an excpetion is thrown otherwise
    if(!hasSelectedItem())
        throw std::string("The item with ID " + toString(static_cast<int>(m_itemSelector.getCurrentItemID())) + " was not selected");
    
    return m_itemSelector.getCurrentItemID();
}



void BagState::updateCategorySelector(sf::Keyboard::Key keyPressed) {
    // We update the number of the categor yselected
    if(keyPressed == sf::Keyboard::Q)
        m_selectedCategory = (m_selectedCategory+5)%6;
    else if(keyPressed == sf::Keyboard::D)
        m_selectedCategory = (m_selectedCategory+1)%6;
    
    // We set the position of the Selection Sprite
    sf::Vector2f pos(100 * (1+m_selectedCategory), (SCREEN_SIZE.y)-100);
    sf::Vector2f delta = m_character->getSpriteCenter() - sf::Vector2f(SCREEN_SIZE.x/2., SCREEN_SIZE.y/2.);
    
    m_categorySelector.setPosition(pos + delta);
    
    
    updateItemList();
}



void BagState::updateItemDisplay() {
    // Quit if there is no item in the list
    if(m_itemSelector.getItemCount() == 0){
        return;
    }
    
    // Get the Item
    Item* i = new Item(m_itemSelector.getCurrentItemID());
    int count = m_itemSelector.getCurrentInventoryEntry()->getItemCount();
    
    
    //===// Position the Attributes
    
    // Item Name
    // Set the Attack Name for the CT, and remove the number
    if(getItemCategorySelected() == ItemCategory::CT){
        // Create the attack for the CT
        Attack* a = AttackFabric::createAttack(Item::getAttackTeached(i->getID()));
        m_itemName.setString(a->getName());
        delete a;
        
        // Remove the count
        m_itemCount.setString(L"");
    }
    else{
        m_itemName.setString(i->getName());
        m_itemCount.setString(L"x " + toWString(count));
    }
    
    // Item Name and Count position
    m_itemName.setPosition(m_character->getSpriteCenter() + sf::Vector2f(-250, 12) - sf::Vector2f(m_itemName.getLocalBounds().width/2., 0));
    m_itemCount.setPosition(m_character->getSpriteCenter() + sf::Vector2f(-150, -106));
    
    // ITem Description
    m_itemDescription.setString(i->getItemDescription());
    m_itemDescription.setPosition(m_character->getSpriteCenter() + sf::Vector2f(-375, 90));
    
    // Use ItemDisplay instead
    m_itemDisplay.setItem(i);
    m_itemDisplay.setPosition(m_character->getSpriteCenter() + sf::Vector2f(-250, -85));
}



void BagState::updateItemList() {
    // We get a pointer to the Character Inventory
    Inventory* inventory = m_character->getInventory();
    
    // Update the ItemSelector
    m_itemSelector.setIDList(inventory, getItemCategorySelected());
    
    // Update the Item Display
    updateItemDisplay();
}



void BagState::givePokemonSelectedItem() {
    // Get the scondary state
    TeamState* ts = (TeamState*)m_secondaryState;

    // Get the item we want to give
    Item* item = takeSelectedItem();
    
    // Get the pokemon
    Pokemon* pokemon = getSelectedPokemon();
    
    pokemon->giveItem(item);
    m_stack->requestStackPushDialog(pokemon->getName() + sf::String(L" tient maintenant l'objet " + item->getName()));
    m_currentStage = BagStage::Bag_Dialog;

    ts->updateTeamDislay();
}



void BagState::useSelectedItem() {
    // Get the teamState and the Item
    TeamState* ts = (TeamState*)m_secondaryState;
    Item* item = takeSelectedItem();
    Pokemon* pokemon = getSelectedPokemon();

    // Use the item on the pokemon
    if(item->getUseOutBattle() == UseOutBattle::CONSUMED_ON_ATTACK){
        m_currentStage = BagStage::SelectingAttack;
        
        // Close the secondary state
        closeSecondaryState();
        
        m_stack->requestStackPush(StateID::SelectAttackS, pokemon);
    }
    else if(item->hasEffectOnPokemon(pokemon)){
        // Set the Stage
        m_currentStage = BagStage::Bag_ItemEffects;
        
        if(item->getCategory() == ItemCategory::CT){
            // Push a State to learn the CT Attack
            pushLearnCTState(pokemon);
        }
        else{
            // Set the Stage
            m_currentStage = BagStage::Bag_ItemEffects;
            
            // Use the item and start displaying the messages
            m_itemEffects = item->onPokemon(pokemon);

            ts->updateTeamDislay();
        
            // Add the first dialog
            m_stack->requestStackPushDialog(m_itemEffects.front()->getString());
            removeSingleItemEffect();
        }
    }
    else{
        // Set the Stage
        m_currentStage = BagStage::Bag_Dialog;
        
        // Message for no effects
        m_stack->requestStackPushDialog(sf::String(L"Cela n'aura aucun effet."));
        
        // Give it back to the character
        m_character->giveItem(item);
    }
}



void BagState::useItemOnAttack(Attack* attack) {
    // Get the item
    Item* item = new Item(getItemIDSelected());
    
    if(item->hasEffectOnAttack(attack)){
        std::queue<ItemEffect*> effects = item->onAttack(attack);
        
        // Push a dialog for each effect
        while(!effects.empty()){
            
            ItemEffect* e = effects.front();
            effects.pop();
            
            if(e->hasString())
                m_stack->requestStackPushDialog(e->getString());
            
            delete e;
        }
    }
    else{
        m_stack->requestStackPushDialog("Cela n'aura aucun effet.");
        
        // Give the item back
        m_character->giveItem(item);
        
        // Change the stage to selection
        unselectItem();
    }
    
    // Dele the item
    delete item;
}



void BagState::pushLearnCTState(Pokemon* p) {
    
    // If the pokemon has place for a new attack just add a dialog
    if(p->getAttackSet().hasPlaceLeft()){
        // Create the Attack
        Attack* a = AttackFabric::createAttack(getCTAttack());
        
        // Add the Attack to the Pokemon AttackSet
        p->getAttackSet().addAttack(a);
        
        // Push a dialog
        m_stack->requestStackPushDialog(p->getName() + " apprend " + a->getName() + ".");
    }
    else{
        // Push a LearnState with the pokemon and the CT
        m_stack->requestStackPush(StateID::LearnAttackS, p, getCTAttack());
    }
}



void BagState::removeSingleItemEffect() {
    delete m_itemEffects.front();
    m_itemEffects.pop();
}



void BagState::clearItemEffects() {
    while(!m_itemEffects.empty()){
        removeSingleItemEffect();
    }
}



void BagState::updateCategorySprites() {
    // Set the texture rect to show the selected category
    for(int i = 0; i < 6; i++){
        if(m_selectedCategory == i)
            m_categories.at(i).setTextureRect(sf::IntRect(78*i, 78, 78, 78));
        else
            m_categories.at(i).setTextureRect(sf::IntRect(78*i, 0, 78, 78));
    }
}



ItemCategory BagState::getItemCategorySelected() {
    switch(m_selectedCategory){
        case 0:
            return ItemCategory::Object;
        case 1:
            return ItemCategory::Medecine;
        case 2:
            return ItemCategory::Pokeball;
        case 3:
            return ItemCategory::Berry;
        case 4:
            return ItemCategory::CT;
        default:
            return ItemCategory::RareObject;
    }
}



void BagState::findSecondaryState() {
    // We need a TeamState to give or use an item
    if(m_currentStage == BagStage::Bag_GivingToPokemon ||
       m_currentStage == BagStage::Bag_UsingOnPokemon){
        
        // Look for a TeamState
        if(m_stack->hasStateOfID(StateID::TeamS)){
            m_secondaryState = m_stack->getStateOfID(StateID::TeamS);
            
            // Setup the TeamState
            TeamState* ts = (TeamState*)m_secondaryState;
            ts->waitBeforeClosing(true);
            ts->deactivateMenus();
            
            // If we are selecting a CT then switch the TeamState mode
            if(getItemCategorySelected() == ItemCategory::CT){
                ts->setToLearnCT(getCTAttack());
            }
        }
    }
    // We look for the ChoiceState
    else if(m_currentStage == BagStage::Bag_ChoiceReplacingItem){
        
        // Look for a TeamState
        if(m_stack->hasStateOfID(StateID::ChoiceS)){
            m_secondaryState = m_stack->getStateOfID(StateID::ChoiceS);
        }
    }
}



void BagState::buildMenu() {
    m_menu.addEntry(L"Utiliser");
    m_menu.addEntry(L"Donner");
    m_menu.addEntry(L"Annuler");
    
    m_menu.setPosition(m_character->getSpriteCenter() + sf::Vector2f(200, 120));
}



Item* BagState::takeSelectedItem() {
    Item* item = m_character->takeItem(getItemIDSelected());
    
    // If the item is a CT we give it back to the player 
    // do not update the Item List because it reset the selected CT to the first one in the list
    if(item->getCategory() == ItemCategory::CT)
        m_character->giveItem(item);
    else{
        // Update the graphical attributes of the BagState
        updateItemList();
    }
    
    return item;
}



void BagState::closeSecondaryState() {
    m_secondaryState->waitBeforeClosing(false);
    m_secondaryState->actionOnCompletion();
    m_secondaryState = nullptr;
}



void BagState::deactivateMenu() {
    m_menu.setActivated(false);
}



void BagState::setFightEntries() {
    // Clear the old entries
    m_menu.clearEntries();
    
    // Add the new one used by a FightState
    m_menu.addEntry(L"Utiliser");
    m_menu.addEntry(L"Annuler");
}



AttackID BagState::getCTAttack() {
    if(getItemCategorySelected() != ItemCategory::CT)
        throw "No CT was selected. ItemID selected " + toString(static_cast<int>(getItemIDSelected()));
    
    // Else just return the AttackID linked to the CT
    return Item::getAttackTeached(getItemIDSelected());
}
