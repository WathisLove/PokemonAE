#include <SFML/System/Clock.hpp>
#include <iostream>
#include <ctime>
#include <assert.h>


#include "../Context.hpp"
#include "../Constants.hpp"

#include "StateStack.hpp"
#include "GameState.hpp"
#include "DialogState.hpp"
#include "BlackState.hpp"
#include "FightState2.hpp"
#include "TransitionState.hpp"
#include "ReactionState.hpp"
#include "TrainerState.hpp"
#include "ItemState.hpp"
#include "MenuState.hpp"
#include "BagState.hpp"
#include "TeamState.hpp"
#include "ChoiceState.hpp"
#include "TeamInfoState.hpp"
#include "BoxState.hpp"
#include "BoxInfoState.hpp"
#include "LearnAttackState.hpp"
#include "EvolutionState.hpp"
#include "ZoneNameState.hpp"
#include "CharacterInfoState.hpp"
#include "BadgeState.hpp"
#include "SellerState.hpp"
#include "../entities/Champion.hpp"
#include "PokedexState.hpp"
#include "BuyingState.hpp"
#include "SellerActionState.hpp"
#include "ForceMoveState.hpp"
#include "ChooseNameState.hpp"
#include "ChoosePokemonNameState.hpp"
#include "BackHealerState.hpp"
#include "HealState.hpp"
#include "EntityMoveState.hpp"
#include "SelectAttackState.hpp"



// Default constructor for pending change
StateStack::PendingChange::PendingChange() :
poke(nullptr),
character(nullptr),
string(nullptr),
choiceEntries(nullptr){

}



StateStack::StateStack(Context& context) :
m_context(context),
m_gameSpeed(1),
m_debugActivated(false)
{    
    // Class Fille Test
    requestStackPush(StateID::GameS);
    
    // Game loop
    sf::Clock clock;
    
    sf::Event e;
    
    sf::RenderWindow& window = m_context.getRenderWindow();
    
    while(window.isOpen()){
        // Update the stack
        float dt = clock.restart().asSeconds();
        float frameTime = 1.f / FRAME_RATE;
        
        //std::cout << "Update Time" << std::endl;
        if(dt <= 2*frameTime)
            update(dt * m_gameSpeed);
        else
            update(frameTime * m_gameSpeed);
        
        // Manage window = m_context.getRenderWindow(); the events for the stack
        //std::cout << "Events Management" << std::endl;
        manageEvents();
        
        //std::cout << "Change Time" << std::endl;
        // Apply changes to the stack
        applyPendingChanges();
        
        //std::cout << "Draw Time" << std::endl;
        // Draw
        draw();
        
        //std::cout << "Loop Done" << std::endl;
        
        handleGameEvents();
    }
}



StateStack::~StateStack() {
    clearStack();
}



void StateStack::update(float dt) {
    // Standard update
    for(auto s_iterator = m_states.rbegin(); s_iterator != m_states.rend(); s_iterator++)
    {
        State* s = *(s_iterator);
        bool updateNextState = s->update(dt);
        
        if(s->isCompleted()){
            s->actionOnCompletion();
        }
        
        if(!updateNextState) break;
    }
    
    // Late update
    for(auto s_iterator = m_states.rbegin(); s_iterator != m_states.rend(); s_iterator++)
    {
        (*s_iterator)->lateUpdate(dt);
    }
}



void StateStack::draw() {
    sf::RenderWindow& window = m_context.getRenderWindow();
    
    // Draw the stack
    window.clear();
       
    // Draw the States
    for(State* s : m_states){
        s->draw();
    }
        
    // Display
    window.display();
}



void StateStack::manageEvents() {
    sf::RenderWindow& window = m_context.getRenderWindow();
    sf::Event event;
    
    // For each event
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();
        
        // Change Game speed
        if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F10)
            m_gameSpeed = (m_gameSpeed*2)%7;
        
        
        // Take a screen
        if(event.type == sf::Event::KeyPressed){
            sf::Keyboard::Key key =  event.key.code;
            
            if(key == sf::Keyboard::F11)
                takeScreenShot();
            else if(key == sf::Keyboard::F2)
                toggleDebugMessages();
        }
        
        for(int i = 0; i < m_states.size(); i++){
            State* s = m_states.at(m_states.size() - i - 1);
            bool nextStateHandle = s->handleEvent(event);
            if(!nextStateHandle) i = m_states.size();
        }
    }
}



void StateStack::addGameEvent(GameEvent* event) {
    m_gameEvents.push(event);
}



Context& StateStack::getContext() {
    return m_context;
}



void StateStack::applyPendingChanges() {
    // for each pending change
    for(PendingChange change : m_changes){
        switch(change.action){
            // Clear
            case StackAction::Clear:
                if(m_debugActivated)
                    std::cout << "Clear States" << std::endl;
                clearStack();
                if(m_debugActivated)
                    std::cout << "States Cleared" << std::endl;
                break;
            // Pop
            case StackAction::Pop:
                if(m_debugActivated)
                    std::cout << "Pop stageID " << m_states.at(m_states.size()-1)->getID() << std::endl;
                popState();
                if(m_debugActivated)
                    std::cout << "Stage Popped"<< std::endl;
                break;
            // Push
            case StackAction::Push:
                if(m_debugActivated)
                    std::cout << "Push stateID " << change.id << std::endl;
                pushState(change);
                if(m_debugActivated)
                    std::cout << "State Pushed" << std::endl;
                break;
        }
    }
    
    // clear the list
    m_changes.clear();
}



void StateStack::requestStackClear() {
    PendingChange change;
    change.action = StackAction::Clear;
    m_changes.push_back(change);
}



void StateStack::requestStackPop() {
    PendingChange change;
    change.action = StackAction::Pop;
    m_changes.push_back(change);
}



void StateStack::requestStackPush(StateID id) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    m_changes.push_back(change);
}



void StateStack::requestStackPush(StateID id, Pokemon* p){
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    change.poke = p;
    m_changes.push_back(change);
}

    
    
void StateStack::requestStackPush(StateID id, Character* character) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    change.character = character;
    m_changes.push_back(change);
}



void StateStack::requestStackPush(StateID id, Entity* e) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    change.entity = e;
    m_changes.push_back(change);
}



void StateStack::requestStackPush(StateID id, Character* character, Entity* e) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    change.character = character;
    change.entity = e;
    m_changes.push_back(change);
}



void StateStack::requestStackPushDialog(const sf::String& str) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::DialogS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    change.string = new sf::String(str);
    m_changes.push_back(change);
}



void StateStack::requestStackPushChoice(const sf::String& str) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ChoiceS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    change.string = new sf::String(str);
    m_changes.push_back(change);
}



void StateStack::requestStackPushChoice(const sf::String& str, std::vector<sf::String*>* entries) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ChoiceS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    change.string = new sf::String(str);
    change.choiceEntries = entries;
    m_changes.push_back(change);
}



void StateStack::requestStackPushReaction(Entity* e, ReactionType reaction) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ReactionS;
    change.entity = e;
    change.reaction = reaction;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    m_changes.push_back(change);
}



void StateStack::requestStackPushBlack(float time) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::BlackS;
    change.duration = time;
    m_changes.push_back(change);
}



void StateStack::requestStackPushFight(Character* character, Entity* trainer) {
    if(((Trainer*)trainer)->isDefeated()) return;
    
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::TrainerFightS;
    change.entity = trainer;
    change.character = character;
    m_changes.push_back(change);
}



void StateStack::requestStackPushFight(Character* character, Pokemon* wildPokemon) {    
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::WildFightS;
    change.poke = wildPokemon;
    change.character = character;
    m_changes.push_back(change);
}



void StateStack::requestStackPushTransition(Direction dir) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::TransitionS;
    change.dir = dir;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushTrainerState(Character* character, Entity* trainer) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::TrainerS;
    change.entity = trainer;
    change.character = character;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushItemGiftState(ItemID item, int number) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ItemS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    change.item = item;
    change.i_value = number;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushBadge(int badgeNumber) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::BadgeS;
    change.i_value = badgeNumber;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushEvolutionState(Character* character, Pokemon* pokemonUnevolved, PokemonID evolutionID) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::EvolutionS;
    change.character = character;
    change.poke = pokemonUnevolved;
    change.pokeID = evolutionID;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushBox() {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::BoxS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushSeller(Entity* seller) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::SellerActionS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    change.entity = seller;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushNameCharacter() {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ChooseNameS;
    change.val = false; // False to name the Character
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushNamePokemon(Pokemon* pokemon) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ChooseNameS;
    change.poke = pokemon;
    change.val = true; // True to name a Pokemon
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushEntityMove(Entity* entity, EntityMover* mover) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::EntityMoveS;
    change.entity = entity;
    change.mover = mover;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPush(StateID id, Pokemon* poke, AttackID attackID){
    PendingChange change;
    change.action = StackAction::Push;
    change.id = id;
    change.poke = poke;
    change.attackID = attackID;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushForceMove(Character* character, Entity* entity, bool repulseCharacter, Direction dir) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::ForceMoveS;
    change.character = character;
    change.val = repulseCharacter;
    change.entity = entity;
    change.dir = dir;
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushHeal() {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::HealS;
    change.character = ((GameState*)getStateOfID(StateID::GameS))->getCharacter();
    
    m_changes.push_back(change);
}



void StateStack::requestStackPushMenu(Character* character) {
    PendingChange change;
    change.action = StackAction::Push;
    change.id = StateID::MenuS;
    change.character = character;
    
    m_changes.push_back(change);
}



void StateStack::popState() {
    // Send a GameEvent for popping a state
    GameEvent* event = new GameEvent(EventType::StatePopped);
    event->stateID = m_states.at(m_states.size()-1)->getID();
    addGameEvent(event);
    
    // Delete and pop the State
    delete m_states.at(m_states.size()-1);
    m_states.pop_back();
}



void StateStack::pushState(PendingChange change) {
    switch(change.id){
        case StateID::GameS:{
            GameState* s = new GameState(this);
            m_states.push_back(s);
        }break;
        case StateID::DialogS:{
            DialogState* s = new DialogState(this, change.character, change.string);
            m_states.push_back(s);
        }break;
        case StateID::BlackS:{
            BlackState* s = new BlackState(this, change.duration);
            m_states.push_back(s);
        }break;
        case StateID::TrainerFightS:{
            FightState2* s = new FightState2(this, change.character, (Trainer*)change.entity);
            m_states.push_back(s);
        }break;
        case StateID::WildFightS:{
            FightState2* s = new FightState2(this, change.character, change.poke);
            m_states.push_back(s);
        }break;
        case StateID::TransitionS:{
            TransitionState* s = new TransitionState(this, change.dir);
            m_states.push_back(s);
        }break;
        case StateID::ReactionS:{
            ReactionState* s = new ReactionState(this, change.character, change.entity, change.reaction);
            m_states.push_back(s);
        }break;
        case StateID::TrainerS:{
            TrainerState* s = new TrainerState(this, change.character, (Trainer*)change.entity);
            m_states.push_back(s);
        }break;
        case StateID::ItemS:{
            ItemState* s = new ItemState(this, change.character, change.item, change.i_value);
            m_states.push_back(s);
        }break;
        case StateID::MenuS:{
            MenuState* s = new MenuState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::BagS:{
            BagState* s = new BagState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::TeamS:{
            TeamState* s = new TeamState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::ChoiceS:{
            if(change.choiceEntries == nullptr){
                ChoiceState* s = new ChoiceState(this, change.character, change.string);
                m_states.push_back(s);
            }
            else{
                ChoiceState* s = new ChoiceState(this, change.character, change.string, change.choiceEntries);
                s->waitBeforeClosing(false);
                m_states.push_back(s);
            }                
        }break;
        case StateID::TeamInfoS:{
            TeamInfoState* s = new TeamInfoState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::BoxS:{
            BoxState* s = new BoxState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::BoxInfoS:{
            BoxInfoState* s = new BoxInfoState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::LearnAttackS:{
            LearnAttackState* s = new LearnAttackState(this, change.poke, change.attackID);
            m_states.push_back(s);
        }break;
        case StateID::EvolutionS:{
            EvolutionState* s = new EvolutionState(this, change.character, change.poke, change.pokeID);
            m_states.push_back(s);
        }break;
        case StateID::ZoneNameS:{
            // We only push a new ZoneName State if there is no other
            if(!hasStateOfID(StateID::ZoneNameS)){
                ZoneNameState* s = new ZoneNameState(this, change.character);
                m_states.push_back(s);
            }
        }break;
        case StateID::CharacterInfoS:{
            CharacterInfoState* s = new CharacterInfoState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::BadgeS:{
            BadgeState* s = new BadgeState(this, change.character, change.i_value);
            m_states.push_back(s);
        }break;
        case StateID::PokedexS:{
            PokedexState* s = new PokedexState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::SellerS:{
            SellerState* s = new SellerState(this, change.character, (Seller*)change.entity);
            m_states.push_back(s);
        }break;
        case StateID::BuyingS:{
            BuyingState* s = new BuyingState(this, change.character, (Seller*)change.entity);
            m_states.push_back(s);
        }break;
        case StateID::SellerActionS:{
            SellerActionState* s = new SellerActionState(this, change.character, (Seller*)change.entity);
            m_states.push_back(s);
        }break;
        case StateID::ForceMoveS:{
            ForceMoveState* s = new ForceMoveState(this, (Npc*)change.entity, change.character, change.character->getPosition(), change.val, change.dir);
            m_states.push_back(s);
        }break;
        case StateID::BackHealerS:{
            BackHealerState* s = new BackHealerState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::ChooseNameS:{
            ChooseNameState* s(nullptr);
            
            // Choose to display the character or a pokemon
            if(change.val)
                s = new ChoosePokemonNameState(this, change.poke);
            else{
                std::cout << "Character Naming not done YET" << std::endl;
                s->displayCharacter();
            }
            
            m_states.push_back(s);
        }break;
        case StateID::HealS:{
            HealState* s = new HealState(this, change.character);
            m_states.push_back(s);
        }break;
        case StateID::EntityMoveS:{
            EntityMoveState* s = new EntityMoveState(this, change.entity, change.mover);
            m_states.push_back(s);
        }break;
        case StateID::SelectAttackS:{
            SelectAttackState* s = new SelectAttackState(this, change.poke);
            m_states.push_back(s);
        }break;
        default:
            std::cout << "Trying to push an State not managed yet" << std::endl;
    }
}



void StateStack::clearStack() {
    for(State* s : m_states){
        delete s;
    }
    
    m_states.clear();
}



void StateStack::takeScreenShot() const {
    sf::RenderWindow& window = m_context.getRenderWindow();
    
    sf::Texture copy;
    copy.create(window.getSize().x, window.getSize().y);
    copy.update(window);
    
    copy.copyToImage().saveToFile("screenshots/"+toString(std::time(0))+".png");
}



void StateStack::toggleDebugMessages() {
    m_debugActivated = !m_debugActivated;
}



void StateStack::handleGameEvents() {
    // While there are GameEvents left
    while (!m_gameEvents.empty()) {
        // Get the Event
        GameEvent* event = m_gameEvents.front();
        m_gameEvents.pop();
        
        // Handle the Event
        handleEvent(event);
        
        // Delete the Event
        delete event;
    }
}



void StateStack::handleEvent(GameEvent* event) {
    for(State* s : m_states){
        s->handleGameEvent(*event);
    }
}



bool StateStack::hasStateOfID(StateID id) {
    for(State* s : m_states){
        if(s->getID() == id) return true;
    }
    
    return false;
}



State* StateStack::getStateOfID(StateID id) {
    for(State* s : m_states){
        if(s->getID() == id) return s;
    }
    
    // Else throw an exception
    throw("No state of ID " + toString(id));
}
