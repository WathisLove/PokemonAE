#include <cassert>

#include "Trainer.hpp"

Trainer::Trainer(const sf::String& name, const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone, NpcID id) :
Npc(texture, context, pos, zone),
m_name(name),
m_isDefeated(false),
m_lastAttack(0),
m_sightDistance(0),
m_moneyGiven(0),
m_waitAtPosition(false)
{
    // Set the type
    m_type = EntityType::Trainer_Type;
    
    m_team = new PokemonTeam;
    
    // Set the Id
    m_id = id;
}



Trainer::~Trainer() {
    // Delete team
    delete m_team;
}


void Trainer::setPokemonTeam(PokemonTeam* team) {
    delete m_team;

    m_team = team;
}



const sf::String& Trainer::getName() const {
    return m_name;
}



PokemonTeam* Trainer::getPokemonTeam() {
    return m_team;
}



bool Trainer::isDefeated() const {
    return m_isDefeated;
}



void Trainer::setDefeated(bool val) {
    m_isDefeated = val;
}



int Trainer::getNbPokemons() const {
    return m_team->getNbPokemon();
}


bool Trainer::canAddPokemon() const {
    return m_team->canAddPokemon();
}


void Trainer::addPokemon(Pokemon* p) {
    m_team->addPokemon(p);
}



std::string Trainer::getInfoString() const {
    std::string s("Dresseur " + m_name.toAnsiString() + "\n");
    s += "Defeated : " + toString<bool>(m_isDefeated) + "\n\n";
    
    s += m_team->getInfoString();
    
    return s;
}



bool Trainer::hasPokemonsLeft() const {
    // check for pokemon alives
    for(int i = 0; i < m_team->getNbPokemon(); i++){
        if(!m_team->getPokemonAt(i)->isKO())
            return true;
    }
    
    // Else 
    return false;
}



int Trainer::getNbPokemon() const {
    return m_team->getNbPokemon();
}



Pokemon* Trainer::getPokemonAt(int index) {
    return m_team->getPokemonAt(index);
}



int Trainer::getFirstPokemonNotKO() {
    
    // Check for pokemon alives
    for(int i = 0; i < m_team->getNbPokemon(); i++){
        if(!m_team->getPokemonAt(i)->isKO())
            return i;
    }
    
    // Throw an exception if there are no pokemon left in the Team
    throw "All pokemons of this trainer are KO !";
}



int Trainer::getRandomIntAttack(int pokemonIndex) {
    Pokemon* p = m_team->getPokemonAt(pokemonIndex);
    
    m_lastAttack = p->getRandomIntAttack();
    return m_lastAttack;
}



int Trainer::getLastIntAttack() const {
    return m_lastAttack;
}



void Trainer::healTeam() {
    m_team->heal();
}



void Trainer::update(float dt) {
    // Call the entity function
    Entity::update(dt);
    
    // Update the Texture rectangle
    updateTextureRect(dt);
    
    // Update the sprite
    updateSpritePos();
    
    // Get the next Move if we are not waiting
    if(!m_waitAtPosition){
        MovementType nextMove = m_mover->getNextMovement();
        move(nextMove);
    }
}



unsigned int Trainer::getSightDistance() const {
    return m_sightDistance;
}



void Trainer::setSightDistance(unsigned int length) {
    // If the sight distance is inferior to 0, we throw an exception
    if(m_sightDistance < 0)
        throw std::string("Sight Distance is less than 0" + toString(length));
    
    // Give a sight of 0 to a defeated Trainer
    if(!m_isDefeated)
        m_sightDistance = length;
    else
        m_sightDistance = 0;
}



bool Trainer::seeCharacter(sf::Vector2i characterPos) const {
    // Check if the X coords or the Y is the same
    if(m_oldPos.x == characterPos.x){
        // Get the distance 
        int dist = std::abs(characterPos.y - m_oldPos.y);
        
        // If the Trainer is looking south
        if(m_dir == Direction::South)
            // Return true if the Character is on the good side, and the distance is not too much
            return dist <= m_sightDistance && characterPos.y > m_oldPos.y;
        
        // If the Trainer is looking north
        else if(m_dir == Direction::North)
            // Return true if the Character is on the good side, and the distance is not too much
            return dist <= m_sightDistance && characterPos.y < m_oldPos.y;
        
        else // We can't see the trainer
            return false;
    }
    else if(m_oldPos.y == characterPos.y){
        // Get the distance 
        int dist = std::abs(characterPos.x - m_oldPos.x);
        
        // If the Trainer is looking south
        if(m_dir == Direction::East)
            // Return true if the Character is on the good side, and the distance is not too much
            return dist <= m_sightDistance && characterPos.x > m_oldPos.x;
        
        // If the Trainer is looking north
        else if(m_dir == Direction::West)
            // Return true if the Character is on the good side, and the distance is not too much
            return dist <= m_sightDistance && characterPos.x < m_oldPos.x;
        
        else // We can't see the trainer
            return false;
    }
    else 
        return false;
}



void Trainer::giveItem(Item* item, int count) {
    m_inventory.addItem(item, count);
}



void Trainer::giveItem(ItemID id, int count) {
    m_inventory.addItem(id, count);
}



Inventory* Trainer::getInventory() {
    return &m_inventory;
}



Item* Trainer::takeItem(ItemID id) {
    return m_inventory.takeItem(id);
}



bool Trainer::isChampion() {
    return false;
}



void Trainer::setMoneyGiven(int money) {
    m_moneyGiven = money;
}



int Trainer::getMoneyGiven() {
    return m_moneyGiven;
}



void Trainer::waitAtPosition(bool waitAtPos) {
    m_waitAtPosition = waitAtPos;
}

