#include "GameState.hpp"

#include <iostream>
#include "../entities/NPC.hpp"
#include "../entities/Trainer.hpp"
#include "../Context.hpp"
#include "../entities/PhysicalItem.hpp"
#include "../entities/Seller.hpp"
#include "../resources/InteractionHolder.hpp"
#include "../entities/interactions/Interaction.hpp"
#include "../entities/interactions/ItemInteraction.hpp"
#include "../utility/EnumLoader.hpp"


GameState::GameState(StateStack* stack) : 
State(stack),
m_zone(ZoneID::city_1, stack->getContext(), m_stack),
m_character(stack->getContext(), sf::Vector2i(49, 20), &m_zone),
m_debugPanel(stack->getContext()),
m_interaction(nullptr),
m_interactionEntity(nullptr)
{
    // Set the ID
    State::m_id = StateID::GameS;
    
    // Give the character to the zone
    m_zone.setCharacter(&m_character);
    
    // And load the zone after
    m_zone.loadZone(m_zone.getZoneID());
    
    // Set the view 
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow(); 
    sf::View v = window.getView();
    v.zoom(1);
    v.setCenter(m_character.getSpriteCenter());
    window.setView(v);
    
    
    // Give a item of each type to the player
    for(int i = 0; i < static_cast<int>(ItemID::LAST_ITEM); i++){
        m_character.giveItem((ItemID)i, randomInt(10, 100));
    }
    
    
    m_music.openFromFile("data/musics/eterna_forest.ogg");
    m_music.setVolume(3);
    m_music.setLoop(true);
    //m_music.play();
}



GameState::~GameState() 
{
    // Reset the view 
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow(); 
    window.setView(window.getDefaultView());
}



bool GameState::update(float dt) {
    // Reset the current interaction if it is finished
    if(m_interaction!= nullptr && m_interaction->isFinished())
        interactionFinished();
    
    // Update the game
    m_character.update(dt);
    m_zone.update(dt);
    
    // Update the camera
    updateCamera(dt);
    
    // Update the position of the TeamPreview once the camera has moved
    m_character.updateTeamPreviewPos();
    
    
    // Try to start story triggers
    if(m_zone.hasTriggeredStory() && !m_stack->hasStateOfID(StateID::ForceMoveS)){
        Npc* n = m_zone.getTriggeredNpc();
        
        // Get the Story Trigger
        StoryTrigger* st = m_zone.getStoryTriggered();
        
        if(st->deactivatesAfterTrigger()){
            // Deactivates the Story Trigger
            st->setActive(false);
        }
        
        // A boolean to know if we must repulse the Character
        bool repulseCharacter(!st->deactivatesAfterTrigger());
        
        // Start a ForceMove State for the Character
        m_stack->requestStackPushForceMove(&m_character, (Entity*)n, repulseCharacter, st->getRepulseDir());
    }
    
    // There should not be any state under GameState
    return false;
}



void GameState::lateUpdate(float dt) {
    // Freeze or Unfreeze the Character
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F6))
        m_character.freeze(true);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F7))
        m_character.freeze(false);
}



void GameState::draw() {
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow(); 

    // Draw the background
    m_zone.drawBackground(window, sf::RenderStates::Default);

    // Draw the Entities and the player
    m_zone.drawEntitiesBelowPlayer(window, sf::RenderStates::Default, m_character.getPosition());
    window.draw(m_character);
    m_zone.drawEntitiesAbovePlayer(window, sf::RenderStates::Default, m_character.getPosition());

    // Draw the foreground
    m_zone.drawForeground(window, sf::RenderStates::Default);
    
    
    // Draw the Team Preview of the player
    m_character.drawTeamPreview(window, sf::RenderStates::Default);
    
    
    // Draw the debug panel
    m_debugPanel.draw(window, sf::RenderStates::Default);
}



void GameState::updateCamera(float dt) {
    // Get the window
    sf::RenderWindow& window = m_stack->getContext().getRenderWindow(); 
    
    // update camera pos
    sf::View v = window.getView();
    v.setCenter(m_character.getSpriteCenter());
    window.setView(v);
    
    // Update the debug panel position
    m_debugPanel.setPosition(m_stack->getContext().getWindowTopLeftCorner() + sf::Vector2f(50, 0));
}



bool GameState::handleEvent(sf::Event& event) {
// Check if the player try to interact
    if(event.type == sf::Event::KeyPressed){
        switch(event.key.code){
            // Check if the player wants to interact
            case sf::Keyboard::Space:
                interactionEvent();
                break;
                
            //=======// DEBUG KEYS
                // Toggle the Debug panel
            case sf::Keyboard::F1:
                m_debugPanel.toggleDisplay();
                break;
            // Recreate the GameState
            case sf::Keyboard::F12:
                std::cout << " <=> Game Restart <=> " << std::endl;
                m_stack->requestStackClear();
                m_stack->requestStackPush(StateID::GameS);
                break;
            // Display the info string
            case sf::Keyboard::F9:
                std::cout << m_character.getInfoString() << std::endl;
                break;
            // Display the info string
            case sf::Keyboard::F3:
                std::cout << " <=> Heal Team <=> " << std::endl;
                m_stack->requestStackPushHeal();
                break;
            // Level up the Pokemons
            case sf::Keyboard::F4:
                std::cout << " <=> Level up Team <=> " << std::endl;
                for(int i = 0; i < m_character.getNbPokemon(); i++)
                    m_character.getPokemonAt(i)->levelUp();
                m_character.updateTeamPreview();
                
                // Try to evolve
                for(int i = 0; i < m_character.getNbPokemon(); i++){
                    Pokemon* p = m_character.getPokemonAt(i);
                    // Look if the pokemon can evolve
                    if(p->canEvolve()){
                        std::cout << "Can evolve" << std::endl;
                        PokemonID id = p->getEvolutionID();
                        std::cout << "Evolution : " << pokemonIDtoString(id) << std::endl;
                        m_stack->requestStackPushEvolutionState(&m_character, p, id);
                        // quit
                        i = m_character.getNbPokemon();
                    }
                }
                break;
            // Display the info string
            case sf::Keyboard::F5:
                std::cout << " <=> Music changer <=> " << std::endl;
                if(m_music.getStatus() == sf::Music::Playing)
                    m_music.pause();
                else
                    m_music.play();
                break;
            case sf::Keyboard::F8:
                std::cout << " <=> Learn Attack State <=> " << std::endl;
                m_stack->requestStackPush(StateID::LearnAttackS, m_character.getPokemonAt(0), AttackID::Flammeche);
                break;
            // Toggle Running
            case sf::Keyboard::R:
                m_character.toggleRun();
                break;
            // Push the menu
            case sf::Keyboard::Escape:
                m_stack->requestStackPushMenu(&m_character);
                break;
        }
    }
        
    return false;
}



void GameState::handleGameEvent(const GameEvent& event) {
    // Handle it by default
    State::handleGameEvent(event);
    
    // If the Event request to start an interaction
    if(event.getType() == EventType::RequestInteraction && m_interaction == nullptr){
        startInteraction(event.entity);
    }
    else if(event.getType() == EventType::FightWon){
        // Fight Won
        std::cout << "Fight Won" << std::endl;
    }
    else if(event.getType() == EventType::FightLost){
        // Fight lost
        m_stack->requestStackPush(StateID::BackHealerS, &m_character);
        
        // Reset the Interaction
        m_interaction->reset();
        m_interaction = nullptr;
    }
    // Send it to the Interaction
    else if(m_interaction != nullptr)
        m_interaction->handleGameEvent(event);
    else{
        // If no Interaction and a DialogState popped => unfreeze
        if(event.getType() == EventType::StatePopped && event.stateID == StateID::DialogS){
            m_character.freeze(false);
        }
    }
}



void GameState::interactionEvent() {
    // check if the Character is facing an Entity
    if(m_zone.hasEntityOnCase(m_character.getFacedCase())){
        Entity* e = m_zone.getEntityAtCase(m_character.getFacedCase());

        startInteraction(e);
    }
    // Check if there is a seller over 1 block
    else if(m_zone.hasEntityOnCase(m_character.getFacedCase(2))){
        // Get the Entity
        Entity* e = m_zone.getEntityAtCase(m_character.getFacedCase(2));
        
        // Check if is is a Seller
        if(e->getType() == EntityType::Seller_Type){
            std::cout << "Interaction with a seller !" << std::endl;
            
            // Start the interaction
            startInteraction(e);
        }
    }
    else{
        // Try to find a zone Dialog at the faced case
        m_zone.tryPushZoneDialog(m_character.getFacedCase());
    }
}



void GameState::startInteraction(Entity* e){
    // Do not start the interaction if the Entity is moving
    if(e->isMoving())
        return;
    
    // Check the Entity type
    switch(e->getType()){
        // Box PC
        case EntityType::BoxPC_Type:
            startInteraction((BoxPC*)e);
            break;
            
        // Physical Items
        case EntityType::PhysicalItem_Type:
            startInteraction((PhysicalItem*)e);
            break;
            
            
        case EntityType::Seller_Type:
            startInteraction((Seller*)e);
            break; 
            
        // NPCS
        case EntityType::NPC_Type:
        case EntityType::Trainer_Type:
            startInteraction((Npc*)e);
            break;
        
        // Default : not managed
        default:
            std::cout << "Entity type not managed" << std::endl;
    }
}



void GameState::startInteraction(Npc* n) {
    // Get the npc ID
    NpcID id = n->getID();

    // If the NPC has an interaction
    if(m_stack->getContext().getInteractionHolder()->hasInteraction(id)){
        m_interaction = m_stack->getContext().getInteractionHolder()->getFirstInteraction(id);
        m_interactionEntity = n;

        std::cout << "Starting Interaction with Npc! " << std::endl;

        // Change the Npc direction
        n->setDirection(closestDirection(n->getPosition(), m_character.getPosition()));
        m_character.setDirection(closestDirection(m_character.getPosition(), n->getPosition()));
        
        startInteractionOrReset();
    }
    else{
        std::cout << "No interaction for Npc " << static_cast<int>(id) << std::endl;
    }
}



void GameState::startInteraction(PhysicalItem* item){
    // Add the Encounter 
    m_character.addPickedItem(item->getNumber());
    
    
    // Create the Interaction
    m_interaction = item->createInteraction();
    m_interactionEntity = item;
    
    std::cout << "Starting Interaction with Physical Item! " << std::endl;
    
    startInteractionOrReset();
    
    
    // Kill the Physical Item
    item->killEntity();
    m_zone.deleteDeadEntities();
}



void GameState::startInteraction(BoxPC* pc){
    // Create the Interaction
    m_interaction = pc->createInteraction();
    m_interactionEntity = pc;
    
    
    std::cout << "Starting Interaction with Box PC! " << std::endl;
    
    startInteractionOrReset();
}



void GameState::startInteraction(Seller* seller){
    // Create the Interaction
    m_interaction = seller->createInteraction();
    m_interactionEntity = seller;
    
    std::cout << "Starting Interaction with Seller ! " << std::endl;
    
    // Change the Seller direction
    seller->setDirection(oppositeDirection(m_character.getDirection()));
    
    startInteractionOrReset();
}



void GameState::interactionFinished() {
    std::cout << "Finished Interaction ! " << std::endl;
    
    // Alert the interaction holder
    m_stack->getContext().getInteractionHolder()->interactionFinished(m_interaction);
    
    // Reset
    m_interaction->reset();

    // Switch to the next if possible
    NpcID npc = m_interaction->getNpcID();
    int nextInteraction = m_interaction->getNext();
    
    // Try to delete to avoid memory leaks
    tryDeleteInteraction();
    
    // If there is a following interaction
    if(m_stack->getContext().getInteractionHolder()->hasInteraction(npc, nextInteraction)){
        std::cout << "Starting next interaction" << std::endl;
        
        // Start the Interaction
        m_interaction = m_stack->getContext().getInteractionHolder()->getInteraction(npc, nextInteraction);
                
        // Start the Interaction
        startInteractionOrReset();
    }
    else{
        m_interaction = nullptr;
        m_interactionEntity = nullptr;
        
        // Unfreeze
        m_character.freeze(false);
        
        // Remember the Character
        m_character.addNPCEncounter(npc);
        
        // Send a GameEvent for the end of the interactions
        m_stack->addGameEvent(new GameEvent(EventType::InteractionsFinished));
    }
}



void GameState::tryDeleteInteraction() {
    // Get the current Entity type
    EntityType type = m_interactionEntity->getType();
    
    if(type == EntityType::BoxPC_Type || type == EntityType::PhysicalItem_Type || type == EntityType::Seller_Type){
        std::cout << "Deleting Interaction" << std::endl;
        delete m_interaction;
    }
}



void GameState::startInteractionOrReset() {
    if(m_interaction->conditionValid(&m_character)){
        m_interaction->startInteraction(m_stack, m_interactionEntity);
    }
    else{
        // Try to delete the Interaction
        tryDeleteInteraction();
        
        // Reset it
        m_interaction->reset();
        m_interaction = nullptr;
        
        // Unfreeze the character
        m_character.freeze(false);
    }
}



bool GameState::isCompleted() const {
    return false;
}



void GameState::actionOnCompletion() {

}



Character* GameState::getCharacter() {
    return &m_character;
}
