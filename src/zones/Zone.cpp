#include "Zone.hpp"
#include "../entities/NPC.hpp"
#include "../entities/Character.h"
#include "../entities/Trainer.hpp"
#include "../entities/PhysicalItem.hpp"
#include "../entities/BoxPC.hpp"
#include "../Constants.hpp"
#include "../states/StateStack.hpp"
#include "../utility/CSVParser.hpp"
#include "../utility/Logger.hpp"

#include <iostream>
#include <cassert>



const std::map<ZoneID, std::string> Zone::zoneFileNames{
    {city_1, "city_1"},
    {city_1_inside, "city_1_inside"},
    {road_1, "road_1"},
    {farm_meuh, "farm_meuh"},
    {city_2, "city_2"},
};



const std::map<ZoneID, sf::String> Zone::zoneNames{
    {city_1, sf::String("Ville 1")},
    {road_1, sf::String("Route 1")},
    {farm_meuh, sf::String("Ferme Meuh-Meuh")},
    {city_2, sf::String("Ville 2")},
};



std::multimap<ZoneID, ZoneChanger*> Zone::zoneChangersStorage{};



Zone::Zone(ZoneID id, Context& context, StateStack* stack) :
m_id(id),
m_texture(context.getTextureHolder()->getTexture(TextureHolder::tileSet)),
m_textureHolder(context.getTextureHolder()),
m_context(context),
m_character(nullptr),
m_background(nullptr),
m_backgroundDeco(nullptr),
m_foreground(nullptr),
m_foregroundDeco(nullptr),
m_collisionLayer(nullptr),
m_activatedZoneChanger(nullptr),
m_mustLoadZone(false),
m_stack(stack),
m_entityLoader(context, this),
m_zoneDialogLoader("data/entities/zone_dialogs.csv")
{
    loadZoneChangerFiles();
}



Zone::~Zone() {
    deleteZoneLayers();
    
    clearEntities();
    
    clearZoneChangers();
}



string Zone::fromIDtoFilename(ZoneID id) {
    // Check the Zone is in the 
    auto it = zoneFileNames.find(id);
    
    // If the Zone ID is in the map
    if(it != zoneFileNames.end()){
        return it->second;
    }
    else
        throw string("Not known filename for Zone ") + toString((int)id);
}



ZoneID Zone::fromFilenameToID(string str) {
    // Check in the map
    for(auto it : zoneFileNames){
        if(it.second == str)
            return it.first;
    }
    
    throw string("Not known ZoneID int conversion for ") + str;
}



sf::String Zone::getZoneName(ZoneID id) {
    // Check the Zone is in the 
    auto it = zoneNames.find(id);
    
    // If the Zone ID is in the map
    if(it != zoneNames.end()){
        return it->second;
    }
    else
        throw string("Not known ZoneName for Zone ") + toString((int)id);
}



sf::Vector2f Zone::getCaseCenter(sf::Vector2i index) const {
    return sf::Vector2f(GAME_ZOOM*(0.5+index.x)*ZoneLayer::tileSize.x, GAME_ZOOM*(0.5+index.y)*ZoneLayer::tileSize.y);
}



void Zone::drawBackground(sf::RenderTarget& target, sf::RenderStates states) const {
    m_background->draw(target, states);
    m_backgroundDeco->draw(target, states);
}



void Zone::drawForeground(sf::RenderTarget& target, sf::RenderStates states) const {
    m_foreground->draw(target, states);
    m_foregroundDeco->draw(target, states);
}



bool Zone::hasEntityOnCase(sf::Vector2i index) {
    // Get Npcs
    std::vector<Npc*>& npcs = m_entityLoader.getNpcs();
    
    for(Npc* n : npcs){
        if(n->isOccupingPosition(index)) return true;
    }
    
    // Get trainers
    std::vector<Trainer*>& trainers = m_entityLoader.getTrainers();
    for(Trainer* t : trainers){
        if(t->isOccupingPosition(index)) return true;
    }
    
    // Get PhysicalItems
    std::vector<PhysicalItem*>& items = m_entityLoader.getPhysicalItems();
    for(PhysicalItem* it : items){
        if(it->isOccupingPosition(index)) return true;
    }
    
    // Get PhysicalItems
    std::vector<BoxPC*>& pcs = m_entityLoader.getBoxPCs();
    for(BoxPC* pc : pcs){
        if(pc->isOccupingPosition(index)) return true;
    }
    
    return false;
}



bool Zone::canSurfOnCase(sf::Vector2i index) const{
    // Check if the index is correct
    if(isOutOfBounds(index)) return false;
    
    return m_collisionLayer->canSurfOnCase(index);
}



bool Zone::canWalkOnCase(sf::Vector2i index) {
    // Check if the index is correct
    if(isOutOfBounds(index)) return false;
    
    // Check if an Entity occupies the case
    if(hasEntityOnCase(index)) return false;
    
    if(m_character->isOccupingPosition(index)) return false;
    
    return m_collisionLayer->canWalkOnCase(index);
}



bool Zone::canJumpOverCase(sf::Vector2i index, Direction dir) const {
    return m_collisionLayer->canJumpOver(index, dir);
}



void Zone::triggerEncounter(sf::Vector2i index) {
    // Check if we can encounter pokemons on the case
    if(m_collisionLayer->canEncounterPokemon(index)){
        // Check if a wild encounter occurs
        if(m_wildManager.hasEncounteredPokemon(m_id)){
            // Start a wild encounter
            Pokemon* p = m_wildManager.getEncounteredPokemon();
            std::cout << p->getName().toAnsiString() << " : N." << p->getLevel() << " (" << toString(p->getNature().toFormattedString()) << ") " << std::endl;
            
            // Start a fight
            m_stack->requestStackPushFight(m_character, p);
        }
    }
}



bool Zone::isOutOfBounds(sf::Vector2i pos) const{
    
    // If negative coordinates : out of bounds
    if(pos.x < 0 || pos.y < 0) return true;
    
    sf::Vector2i zoneSize = getZoneSize();
    
    // If coordinates are equals or greater than the size
    if(pos.x >= zoneSize.x || pos.y >= zoneSize.y) return true;
    
    return false;
}



sf::Vector2i Zone::getZoneSize() const {
    return m_background->getLayerSize();
}



void Zone::loadZone(ZoneID id) {
    deleteZoneLayers();
    
    m_id = id;
    
    // Find the Zone name
    string zoneName = fromIDtoFilename(id);
    string dirPath = "data/zones/" + zoneName + "/"+zoneName+"_";
    
    // Load the layers
    m_background = new ZoneLayer(dirPath+"bg.csv", m_texture);
    m_backgroundDeco = new ZoneLayer(dirPath+"bg_dec.csv", m_texture);
    m_foreground = new ZoneLayer(dirPath+"fg.csv", m_texture);
    m_foregroundDeco = new ZoneLayer(dirPath+"fg_dec.csv", m_texture);
        
    m_collisionLayer = new CollisionLayer(dirPath+"collisions.csv");
        
    
    // Load Entities
    m_entityLoader.load(m_id);
    
    // Load ZoneChangers
    loadZoneChangers(id);
    
    // Load the Zone dialogs
    m_zoneDialogLoader.loadZoneDialogs(id);
    
    
    // Send a Game event to alert a new zone was loaded
    m_stack->addGameEvent(new GameEvent(EventType::ZoneLoaded));
    
    // Update the Character zones
    m_character->addVisitedZone(id);
}



void Zone::loadZoneChangers(ZoneID id) {
    // Range of jump border
    auto itRange = zoneChangersStorage.equal_range(id);
    
    // Add each of them
    for(auto it = itRange.first; it != itRange.second; it++){
        m_zoneChangers.push_back(it->second);
    }
}



void Zone::update(float dt) {
    // Load the new zone if needed
    if(m_mustLoadZone)
        applyZoneChange();
    
    // Update the Entities
    for(Npc* n : m_entityLoader.getNpcs()){
        n->update(dt);
    }
    for(Trainer* t : m_entityLoader.getTrainers()){
        t->update(dt);
    }
    for(PhysicalItem* i : m_entityLoader.getPhysicalItems()){
        i->update(dt);
    }
    for(BoxPC* b : m_entityLoader.getBoxPCs()){
        b->update(dt);
    }
    
    // Check the zoneChangers and change the zone if needed
    checkZoneChangers();
    
    // Check if one of the Entity see the Character
    checkTrainerSight();
    
    // Try to trigger an encounter
    if(!m_character->isMoving() && m_character->getBody().wasMoving())
        triggerEncounter(m_character->getPosition());
}



void Zone::drawEntities(sf::RenderTarget& target, sf::RenderStates states) {
    // Draw Npcs
    std::vector<Npc*>& npcs = m_entityLoader.getNpcs();
    for(Npc* n : npcs){
        n->draw(target, states);
    }
    
    // Draw trainers
    std::vector<Trainer*>& trainers = m_entityLoader.getTrainers();
    for(Trainer* t : trainers){
        t->draw(target, states);
    }
    
    // Draw PhysicalItems
    std::vector<PhysicalItem*>& items = m_entityLoader.getPhysicalItems();
    for(PhysicalItem* i : items){
        i->draw(target, states);
    }
    
    // Draw BoxPCs
    std::vector<BoxPC*>& boxPCs = m_entityLoader.getBoxPCs();
    for(BoxPC* b : boxPCs){
        b->draw(target, states);
    }
}



void Zone::clearEntities() {
    m_entityLoader.deleteDeadEntities();
}



void Zone::clearZoneChangers() {
    // Don't delete, they are stored in a map
    m_zoneChangers.clear();
}



void Zone::setCharacter(Character* c) {
    m_character = c;
    
    m_entityLoader.setCharacter(c);
}



Entity* Zone::getEntityAtCase(sf::Vector2i index) {
    for(Npc* n : m_entityLoader.getNpcs()){
        if(n->isOccupingPosition(index)) return n;
    }
    for(Trainer* t : m_entityLoader.getTrainers()){
        if(t->isOccupingPosition(index)) return t;
    }
    for(PhysicalItem* i : m_entityLoader.getPhysicalItems()){
        if(i->isOccupingPosition(index)) return i;
    }
    for(BoxPC* b : m_entityLoader.getBoxPCs()){
        if(b->isOccupingPosition(index)) return b;
    }
    
    throw std::string("Not any Entity found at the given case !");
}



void Zone::checkZoneChangers() {
    for(ZoneChanger* zc : m_zoneChangers){
        if(zc->isinsideRect(m_character->getPosition())){
            
            // Remember to load the next zone
            m_mustLoadZone = true;
            m_activatedZoneChanger = zc;
            
            // Start a transition state
            m_stack->requestStackPushTransition(m_character->getDirection());
            
            return;
        }
    }
}



void Zone::deleteZoneLayers() const {
    delete m_background;
    delete m_backgroundDeco;
    delete m_foreground;
    delete m_foregroundDeco;
    delete m_collisionLayer;
}



void Zone::characterBackToHeal() {
    // Get the data of the last heal
    HealData data = m_character->getLastHealData();
    
    
    loadZone(data.zone);
    m_character->setPosition(data.pos);
    m_character->setDirection(data.dir);
    m_character->healTeam();
    
    clearZoneChangers();
    loadZoneChangers(m_id);
}



void Zone::applyZoneChange() {
    loadZone(m_activatedZoneChanger->getNewZoneID());

    // Set the direction, and its position of the Character
    m_character->setDirection(m_activatedZoneChanger->getNewDirection());
    m_character->update(0);
    m_character->setPosition(m_activatedZoneChanger->getNewCharacterPos(m_character->getPosition()));

    // Then delete the zoneChangers, and reload them 
    //(some old ones are not deleted by the LoadZone method, as they must be kept in memory to get position)
    clearZoneChangers();
    loadZoneChangers(m_id);
    
    
    // Push a State for the ZoneName
    if(mustShowZoneName())
        m_stack->requestStackPush(StateID::ZoneNameS, m_character);
    
    // Desactivate the change of zone
    m_activatedZoneChanger = nullptr;
    m_mustLoadZone = false;
}



void Zone::checkTrainerSight() {
    if(m_character->isMoving())
        return;
    
    // Check if the trainer was defeated
    for(Trainer* t : m_entityLoader.getTrainers()){
        if(!t->isDefeated() && t->seeCharacter(m_character->getPosition()) &&
           !hasBlockBetween(t->getFacedCase(), m_character->getPosition())) {
            // Freeze the character and reset it sprite so it doesn't move
            m_character->freeze(true);

            if(t->getFacedCase() == m_character->getPosition()){
                GameEvent* event = new GameEvent(EventType::RequestInteraction);
                event->entity = t;
                m_stack->addGameEvent(event);
            }
            else{
                // Push a trainer state so the trainer can move to the character
                m_stack->requestStackPushTrainerState(m_character, t);
            }
        }
    }
}



bool Zone::hasBlockBetween(sf::Vector2i startPos, sf::Vector2i endPos) {
    // Get the variables that will be used to figure out if there is an obstacle
    int x = startPos.x; int y = startPos.y;
    
    // Get the variation of x
    int dx(0); int dy(0);
    if(endPos.x > startPos.x) dx = 1;
    else if (endPos.x < startPos.x) dx = -1;
    
    // Get the variation of y
    if(endPos.y > startPos.y) dy = 1;
    else if (endPos.y < startPos.y) dy = -1;
    
    
    // Check if there is an obstacle on x
    for(x; x != endPos.x; x += dx){
        // If the Entity can't walk on a case on the path, return tru (there is a block)
        if(!canWalkOnCase(sf::Vector2i(x, y))){
            // Return false if we get to the end case, false otherwise
            return sf::Vector2i(x, y) != endPos;
        }
    }
    // Check if there is an obstacle on y
    for(y; y != endPos.y; y += dy){
        // If the Entity can't walk on a case on the path, return tru (there is a block)
        if(!canWalkOnCase(sf::Vector2i(x, y))){
            // Return false if we get to the end case, false otherwise
            return sf::Vector2i(x, y) != endPos;
        }
    }
    
    // Else there is no blocks on the path
    return false;
}



void Zone::deleteDeadEntities() {
    m_entityLoader.deleteDeadEntities();
}



ZoneID Zone::getZoneID() {
    return m_id;
}



bool Zone::mustShowZoneName() {
    // True if the name is in the map
    return zoneNames.find(m_id) != zoneNames.end();
}



bool Zone::hasTriggeredStory() {
    // Do not trigger Story if the Character is moving
    if(m_character->isMoving())
        return false;
    
    // Check each of the Story Triggers
    for(StoryTrigger* st : m_entityLoader.getStoryTriggers()){
        if(st->isinsideRect(m_character->getPosition()))
            return true;
    }
    
    return false;
}



StoryTrigger* Zone::getStoryTriggered() {
    // Get the Npc ID each of the Story Triggers
    for(StoryTrigger* st : m_entityLoader.getStoryTriggers()){
        if(st->isinsideRect(m_character->getPosition()))
            return st;
    }
    
    // Nothing found
    Log("Didn't found the storyTrigger", Logger::ERROR);
    return nullptr;
}



Npc* Zone::getTriggeredNpc() {
    // The Npc ID
    NpcID npcId(NpcID::not_defined_NPC);
    
    // The Npc
    Npc* npc(nullptr);
    
    // Get the Story Trigger and NpcID
    StoryTrigger* st = getStoryTriggered();
    npcId = st->getNpc();
    
    // Assert we triggered a StoryTrigger
    assert(npcId != NpcID::not_defined_NPC);
    
    
    // Find the Npc
    for(Npc* n : m_entityLoader.getNpcs()){
        if(n->getID() == npcId){
            npc = n;
        }
    }
    
    // Check a Npc was found
    assert(npc != nullptr);
    
    return npc;
}



void Zone::tryPushZoneDialog(sf::Vector2i pos) {
    auto zoneDialogs = m_zoneDialogLoader.getZoneDialogs();
    
    // Check all the Zone Dialogs
    for(ZoneDialog* zd : zoneDialogs){
        if(zd->occupies(pos)){
            m_stack->requestStackPushDialog(zd->getDialog());
            return;
        }
    }
}



void Zone::loadZoneChangerFiles() {
    // If some zone changers were already loaded
    if(!zoneChangersStorage.empty()){
        Log("Already loaded the ZoneChangers. Restart the game if changes were made.", Logger::FILE_INFO);
        return;
    }
    
    // For each file
    for(auto it : zoneFileNames){
        std::string path = "data/zone_changers/" + it.second + ".csv";
        
        // Try to load the file
        Log("Loading " + path, Logger::FILE_INFO);
        CSVParser parser(path);
        
        // Ignore first line
        parser.readLine();
        
        while(parser.readLine()){
            // Elements
            auto elements = parser.getLineElements();
            
            // Rect for the source and target
            sf::IntRect src, dest;
            
            // Get the destination zone
            ZoneID destZone = fromFilenameToID(elements.at(1));
            
            // Direction
            Direction dir = Direction::North;
            
            // If in the map get the direction value
            auto itDir = directionStrings.find(elements.at(3));
            if(itDir != directionStrings.end())
                dir = itDir->second;
            
            // Get the elements
            std::istringstream srcStream(elements.at(0));
            std::istringstream destStream(elements.at(2));
            
            if(srcStream >> src.left && srcStream >> src.top && srcStream >> src.width && srcStream >> src.height && 
               destStream >> dest.left && destStream >> dest.top && destStream >> dest.width && destStream >> dest.height){
                // Emplace
                zoneChangersStorage.emplace(it.first, new ZoneChanger(src, destZone, dest, dir));
            }
            else{
                Log("Invalid zone changer " + elements.at(0) + " " + elements.at(1) + " " + elements.at(2) + " " + elements.at(3), Logger::FILE_ERROR );
            }
        }
    }
}
