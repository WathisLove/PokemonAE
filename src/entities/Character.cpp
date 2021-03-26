#include <iostream>
#include <cmath>
#include <algorithm>
#include <cassert>

#include "Character.h"
#include "../Constants.hpp"
#include "../pokemons/Pokemon.hpp"
#include "../game_data/GameInfo.hpp"
#include "../zones/Zone.hpp"



HealData::HealData(sf::Vector2i pos, ZoneID zone, Direction dir) :
pos(pos), 
zone(zone), 
dir(dir)
{
    
}



Character::Character(Context& context, sf::Vector2i pos, Zone* zone) :
Entity(context.getTextureHolder()->getTexture(TextureHolder::character), context, pos, zone),
m_teamPreview(context),
m_money(3000),
m_body(m_sprite, PLAYER_SPEED, zone),
m_secondsPlayed(3585),
m_lastHeal(pos, zone->getZoneID(), m_body.getDirection())
{
    // Set the type
    m_type = EntityType::Character_Type;
    
    // Set the Character mover
    setMover(new CharacterMover(1.f/PLAYER_SPEED));
    
    
    m_team = new PokemonTeam();
    
    
    Pokemon* p = new Pokemon(pikachu, 7);
    p->setHP(12);
    p->giveXp(168);
    //p->setMainStatus(MainStatus(MainStatusName::Paralysis));
    //p->setMainStatus(MainStatus(MainStatusName::Sleep));
    m_pokedex.addPokemonSaw(p->getID());
    addCapturedPokemon(p);
    
    Pokemon* m = new Pokemon(marcacrin, 5);
    m->setHP(0);
    m->giveXp(8);
    m->setMainStatus(MainStatus(MainStatusName::BadlyPoison));
    m->giveItem(new Item(ItemID::berryOran));
    m_pokedex.addPokemonSaw(m->getID());
    addCapturedPokemon(m);
    
    m_pokedex.addPokemonSaw(PokemonID::mammochon);
    m_pokedex.addPokemonSaw(PokemonID::galekid);
    
    m_teamPreview.updatePreview(m_team);
    
    // Add some badges for the Character Infos
    for(int i = 2; i < 5; i++)
        addBadge(i);
    addBadge(8);
    
    
    // Set the body position
    setPosition(pos);
}



Character::~Character() {
    delete m_team;
}



void Character::update(float dt) {
    // Update the time since last move
    m_mover->update(dt);
    
    // Manage a move ordered by the Mover
    m_body.manageMove(m_mover->getNextMovement());
    
    
    // If the mover is finished, replace it with a Character mover
    if(!isMoving() && m_mover->isFinished())
        setMover(new CharacterMover(1.f/PLAYER_SPEED));
    
    
    // Update the Body
    m_body.update(dt);
}



void Character::updateTeamPreview() {
    m_teamPreview.updatePreview(m_team);
}



void Character::updateTeamPreviewPos() {
    // Update the Team Preview pos to the top left of the window
    m_teamPreview.setTopLeftPosition();
}



void Character::giveItem(Item* item, int count) {
    m_inventory.addItem(item, count);
}



void Character::giveItem(ItemID id, int count) {
    m_inventory.addItem(id, count);
}



Inventory* Character::getInventory() {
    return &m_inventory;
}



BoxSystem& Character::getBoxSystem() {
    return m_boxSystem;
}



bool Character::metNPC(NpcID id) {
    // We try to find the NPC in the vector
    return std::find(m_npcStoryMet.begin(), m_npcStoryMet.end(), id) != m_npcStoryMet.end();
}



bool Character::defeatedTrainer(NpcID id) {
    // We try to find the Trainer in the vector
    return std::find(m_trainersDefeated.begin(), m_trainersDefeated.end(), id) != m_trainersDefeated.end();
}



bool Character::pickedItem(int itemNum) {
    // We try to find the Trainer in the vector
    return std::find(m_itemsPicked.begin(), m_itemsPicked.end(), itemNum) != m_itemsPicked.end();
}



void Character::addPickedItem(int itemNum) {
    // We check thet we didn't already picked the item
    assert(!pickedItem(itemNum));
    
    // Add the item umber to the vector
    m_itemsPicked.push_back(itemNum);
}



void Character::addNPCEncounter(NpcID id) {
    // Check if the character didn't met the NPC
    if(!metNPC(id)){
        m_npcStoryMet.push_back(id);
    }
}



void Character::addTrainerDefeated(NpcID id) {
    // We check thet we didn't already defeated the trainer
    assert(!defeatedTrainer(id));
    
    // Add the trainer umber to the vector
    m_trainersDefeated.push_back(id);
}



void Character::addBadge(int badgeNumber) {
    // Assert that the character don't already have the badge
    assert(!hasBadge(badgeNumber));
    
    // Add the badge to the vector
    m_badges.push_back(badgeNumber);
}



bool Character::hasBadge(int badgeNumber) {
    // Try to find the badge in the vector
    return std::find(m_badges.begin(), m_badges.end(), badgeNumber) != m_badges.end();
}



void Character::addCapturedPokemon(Pokemon* p) {
    m_pokedex.addPokemonCaptured(p->getID());
    m_team->addPokemon(p);
}



bool Character::visited(ZoneID zone) {
    // Try to find the Zone in the vector
    return std::find(m_zoneVisited.begin(), m_zoneVisited.end(), zone) != m_zoneVisited.end();
}



void Character::addVisitedZone(ZoneID zone) {
    if(!visited(zone))
        m_zoneVisited.push_back(zone);
}



Pokedex& Character::getPokedex() {
    return m_pokedex;
}



int Character::getMoney() {
    return m_money;
}



void Character::pay(int amount) {
    assert(amount <= m_money);
    
    m_money -= amount;
}



void Character::addMoney(int amount) {
    m_money += amount;
}



void Character::toggleRun() {
    // Allow change if the character is not jumping
    if(!m_body.isJumping())
        m_body.toggleRun();
}



void Character::setTimePlayed(unsigned int seconds) {
    m_secondsPlayed = seconds;
}



std::string Character::getTimePlayed() {
    // Get the total time played in seconds
    int seconds = m_secondsPlayed + (int)m_timeClock.getElapsedTime().asSeconds();
    
    // Compute hours and minutes
    int hours = seconds/3600;
    int minutes = (seconds - hours * 3600)/60;
    
    // Convert to string
    std::string hoursStr, minutesStr;
    
    // Hours
    if(hours < 10)
        hoursStr = "0";
    hoursStr += toString(hours);
            
    // Minutes
    if(minutes < 10)
        minutesStr = "0";
    minutesStr += toString(minutes);
        
        
    return hoursStr + ":" + minutesStr;
}



const sf::String& Character::getName() const {
    return gamedata::characterName;
}



void Character::setName(const sf::String& name) {
    // Check the name is not empty
    assert(name.getSize() > 0);
    
    // Set the GameData name
    gamedata::characterName = name;
}



const CharacterBody& Character::getBody() {
    return m_body;
}



Direction Character::getDirection() const {
    return m_body.getDirection();
}



void Character::setDirection(Direction dir) {
    m_body.setDirection(dir);
}



Item* Character::takeItem(ItemID id) {
    return m_inventory.takeItem(id);
}



void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the character body
    target.draw(m_body, states);
}



void Character::drawTeamPreview(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_teamPreview, states);
}



sf::Vector2i Character::getFacedCase(int distance) const {
    return m_body.getFrontCase(distance);
}



void Character::setPosition(sf::Vector2i pos) {
    m_body.setPosition(pos);
}



sf::Vector2i Character::getPosition() const {
    return m_body.getPosition();
}



bool Character::isOccupingPosition(sf::Vector2i pos) const {
    // Check the current position
    if(m_body.isMoving())
        return m_body.getPosition() == pos || m_body.getNextPosition() == pos;
    else
        return m_body.getPosition() == pos;
}



PokemonTeam* Character::getPokemonTeam() {
    return m_team;
}



std::string Character::getInfoString() const {
    std::string s("<===> CHARACTER <===>\n");
    s += "Pos  [" + toString(m_body.getPosition().x) + " ; " + toString(m_body.getPosition().y) + "]\n\n";
    
    s += m_team->getInfoString();
    
    s += m_inventory.getInfoString();
    
    // The NPC met in order
    s += "\nNPC met (in order) : ";
    for(NpcID id : m_npcStoryMet)
        s += toString(static_cast<int>(id)) + " ";
    s += "\n";
    
    // The Trainers defeated in order
    s += "\nTrainers defeated (in order) : ";
    for(NpcID id : m_trainersDefeated)
        s += toString(static_cast<int>(id)) + " ";
    s += "\n";
    
    // The PhysicalItem recovered in order
    s += "\nItems recovered (in order) : ";
    for(int i : m_itemsPicked)
        s += toString(i) + " ";
    s += "\n";
    
    
    return s;
}



HealData Character::getLastHealData() const {
    return m_lastHeal;
}



void Character::saveHealData() {
    m_lastHeal.dir = m_body.getDirection();
    m_lastHeal.pos = m_body.getPosition();
    m_lastHeal.zone = m_zone->getZoneID();
}



void Character::healTeam() {
    m_team->heal();
    
    m_teamPreview.updatePreview(m_team);
}



bool Character::hasPokemonsLeft() const {
    // check for pokemon alives
    for(int i = 0; i < m_team->getNbPokemon(); i++){
        if(!m_team->getPokemonAt(i)->isKO())
            return true;
    }
    
    // Else 
    return false;
}



int Character::getNbPokemon() const {
    return m_team->getNbPokemon();
}



Pokemon* Character::getPokemonAt(int index) {
    return m_team->getPokemonAt(index);
}



void Character::leaveFight() {
    m_team->leaveFight();
}



void Character::freeze(bool value) {
    m_body.freeze(value);
}



bool Character::isFrozen() const {
    return m_body.isFrozen();
}



bool Character::isMoving() {
    return m_body.isMoving();
}
