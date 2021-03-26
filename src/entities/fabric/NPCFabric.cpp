#include <cassert>
#include <vector>
#include <sstream>

#include "NPCFabric.hpp"

#include "../../inventory/Item.hpp"
#include "../Champion.hpp"
#include "../../zones/Zone.hpp"
#include "../npcs/NpcType.hpp"
#include "../../utility/Logger.hpp"


bool NPCFabric::filesLoaded(false);



NPCFabric::Position::Position(int x, int y)  :
    x(x), y(y) {
}



NPCFabric::NPCFabric(Context& context, Zone* zone) :
m_context(context),
m_zone(zone){
    // Load the maps from files
    loadNpcFiles();
    loadSellerItemsFiles();
    
    filesLoaded = true;
}



Npc* NPCFabric::create(NpcID id) {
    
    Npc* n = nullptr;
    
    // Create the Npc
    if(isJustNPC(id))
        n = createNPC(id);
    else if(isSeller(id))
        n = createSeller(id);
    else if(isChampion(id))
        n = createChampion(id);
    else if(isTrainer(id))
        n = createTrainer(id);
    
    // Just checking
    assert(n != nullptr);
    
    
    //=====// Common things //=====// 
    
    // Id
    n->setID(id);
    
    // Mover
    std::map<NpcID, EntityMover*>::iterator moverIt = movers.find(id);
    if(moverIt != movers.end())
        n->setMover(moverIt->second->copy());
    
    // Directions
    auto directionIt = directions.find(id);
    if(directionIt != directions.end())
        n->setDirection(directionIt->second);
    
    // Speed
    auto speedIt = speeds.find(id);
    if(speedIt != speeds.end())
        n->setSpeed(speedIt->second);
    
    
    return n;
}



const sf::Texture& NPCFabric::texture(NpcID id) const {
    // Assert the id is in the texture map
    if(textures.find(id) == textures.end()){
        std::cout << "Could not find Npc texture for NpcID = " << static_cast<int>(id) << std::endl;
    };
    
    // Get the Texture
    return m_context.getTextureHolder()->getTexture(textures.at(id));
}



sf::Vector2i NPCFabric::position(NpcID id) const {
    // Assert the id is in the position map
    assert(positions.find(id) != positions.end());
    
    // Get the Position
    Position pos = positions.at(id);
    return sf::Vector2i(pos.x, pos.y);
}



void NPCFabric::setupTrainer(Trainer* t) {
    // Trainer ID
    NpcID id = t->getID();
    
    // Team
    t->setPokemonTeam(createTeam(id));
    
    // Items
    giveItems(t);
    
    // Money
    assert(trainersMoney.find(id) != trainersMoney.end());
    t->setMoneyGiven(trainersMoney.at(id));
    
    // Sight
    auto sightIt = trainersSights.find(id);
    if(sightIt != trainersSights.end())
        t->setSightDistance(sightIt->second);
}



const sf::String& NPCFabric::name(NpcID id) const {
    // Assert the id is in the name map
    assert(trainersNames.find(id) != trainersNames.end());
    
    // Get the Name
    return trainersNames.at(id);
}



PokemonTeam* NPCFabric::createTeam(NpcID id) {
    // Create an empty team
    PokemonTeam* team = new PokemonTeam();
    
    
    // Fill it with Strategic pokemons
    auto stratRange = trainerStratPokemons.equal_range(id);
    
    for(auto it = stratRange.first; it != stratRange.second; it++){
        // Get the Data for the Strategic pokemon
        const StrategicPokemon& pokemonData = it->second;
        
        // Create and add the pokemon
        team->addPokemon(StrategicPokemonFabric::create(pokemonData.poke, pokemonData.level));
    }
    
    
    // Fill it with Standard pokemons (until full or no more pokemons)
    auto pokemonRange = trainerPokemons.equal_range(id);
    
    for(auto it = pokemonRange.first; it != pokemonRange.second; it++){
        if(team->getNbPokemon() < 6){
            // Get the Data for the Strategic pokemon
            StandardPokemon pokemonData = it->second;

            // Create and add the pokemon
            team->addPokemon(new Pokemon(pokemonData.poke, pokemonData.level));
        }
        else{
            // Quit the map
            it = pokemonRange.second;
        }
    }
    
    
    // Assert there is at least 1 pokemon and at most 6
    assert(team->getNbPokemon() > 0 && team->getNbPokemon() <= 6);
    
    return team;
}



void NPCFabric::giveItems(Trainer* trainer) {
    // Get the Trainer ID
    NpcID id = trainer->getID();
    
    // Find the Item Range
    auto itemRange = trainersItems.equal_range(id);
    
    // Add the Items
    for(auto it = itemRange.first; it != itemRange.second; it++){
        // Get the Item
        TrainerItem item = it->second;
        
        // Give the item
        trainer->giveItem(item.id, (int)item.num);
    }
}



void NPCFabric::setItemsSold(Seller* s) {
    // Get the Seller Id
    NpcID id = s->getID();
    
    //// Find the Items range with defined prices
    auto itemRange = itemsSold.equal_range(id);
    
    // Add the Items sold 
    for(auto it = itemRange.first; it != itemRange.second; it++){
        s->addProduct(it->second.item, it->second.price);
    }
    
    
    //// Find the items at default prices
    auto defItemRange = itemsSoldDefaultPrice.equal_range(id);
    
    // Add the Items sold 
    for(auto it = defItemRange.first; it != defItemRange.second; it++){
        s->addProduct(it->second, Item::getDefaultPrice(it->second));
    }
    
    // Assert there is at least 1 item
    assert(s->getItemList().size() > 0);
}



Npc* NPCFabric::createNPC(NpcID id) {
    return new Npc(texture(id), m_context, position(id), m_zone);
}



Npc* NPCFabric::createSeller(NpcID id) {
    Seller* s = new Seller(m_context, position(id), m_zone);
    s->setID(id);
    
    // Set the items sold
    setItemsSold(s);
    
    return s;
}



Npc* NPCFabric::createChampion(NpcID id) {
    Champion* c = new Champion(name(id), texture(id), m_context, position(id), m_zone, id);
    
    setupTrainer(c);
    
    return c;
}



Npc* NPCFabric::createTrainer(NpcID id) {
    Trainer* t = new Trainer(name(id), texture(id), m_context, position(id), m_zone, id);
    
    setupTrainer(t);
    
    return t;
}



void NPCFabric::loadSellerItemsFiles() {
    // Do not load Files if already loaded
    if(filesLoaded)
        return;
    
    // Load each file
    for(auto pair : Zone::zoneFileNames){
        // Create the path
        string path = "data/entities/seller_items/" + pair.second + ".csv";
        
        // Open the file
        CSVParser parser(path);
        
        // Ignore first line
        parser.readLine();
        
        while(parser.readLine()){
            // Get the elements
            auto elements = parser.getLineElements();
            
            // Get the ID
            std::istringstream idStream(elements.at(0));
            NpcID npc(NpcID::not_defined_NPC);
            int idTemp;
            
            // Extract the Npc
            if(idStream >> idTemp)
                npc = static_cast<NpcID>(idTemp);
            else
                Log("Failed to load Seller ID " + elements.at(0), Logger::FILE_ERROR);
            
            
            // Get the ItemID
            ItemID itemID = Item::getID(elements.at(1));
            
            // If price is precised
            if(!elements.at(2).empty()){
                SoldItem item;
                item.item = itemID;
            
                // Get the price
                std::istringstream priceStream(elements.at(2));
                
                // Extract price and ID
                if(priceStream >> item.price){
                    itemsSold.emplace(npc, item);
                }
            }
            else{
                // Place default priced item
                itemsSoldDefaultPrice.emplace(npc, itemID);
            }
        }
    }
}



void NPCFabric::loadNpcFiles() {
    // Do not load Files if already loaded
    if(filesLoaded)
        return;
    
    // Load each file
    for(auto pair : Zone::zoneFileNames){
        // Create the path
        string path = "data/entities/npcs/" + pair.second + ".csv";
        
        // Load the NPCs from the file
        loadNpcFile(path, pair.first);
    }
}



void NPCFabric::loadNpcFile(const std::string& filePath, ZoneID zone) {
    std::cout << "<=> Opening " << filePath << std::endl;
    
    //CSV Parser to the file
    CSVParser parser(filePath);
    
    // Ignore first line
    parser.readLine();
            
    // Get the data
    while(parser.readLine()){
        loadNpc(parser.getLineElements(), zone);
    }
}



void NPCFabric::loadNpc(const std::vector<std::string>& elements, ZoneID zone) {
    
    std::cout << "Loading " << elements[0] << std::endl;
    
    // Checking the size
    assert(elements.size() > 8);
    
    
    // Get the Npc ID
    NpcID id = static_cast<NpcID>(atoi(elements[1].c_str()));
    assert(id != NpcID::not_defined_NPC);
    
    // Get the Npc Type
    std::string type = elements[2];
    
    // Get the position
    int x = atoi(elements[3].c_str());
    int y = atoi(elements[4].c_str());
    
    // Direction
    Direction dir = directionStrings[elements[5]];
    
    // Get the Texture
    TextureHolder::textureID texture = m_context.getTextureHolder()->getNpcTexture(elements[6]);
    
    // Get the Mover
    EntityMover* mover = m_moverFabric.createMover(elements[7]);
    
    // Add Condition if needed
    std::string condString = elements[8];
    if(!condString.empty()){
        Condition* condition = new Condition(condString);
        EntityLoader::addNpcCondition(id, condition);
    }
    
    // Save the type
    npcTypes.emplace(id, npcTypeStrings.at(type));
    
    // Fill the NPC Fabric Maps
    NPCFabric::positions.emplace(id, Position(x, y));
    NPCFabric::textures.emplace(id, texture);
    NPCFabric::directions.emplace(id, dir);
    NPCFabric::movers.emplace(id, mover);
    
    // Fill maps in EntityLoaderZone 
    EntityLoader::addNpcZone(zone, id);
    
    
    // Load additionnal Data for different Npc
    if(type == "TRAINER"){
        NPCFabric::trainersNames.emplace(id, elements[0]);
        loadTrainer(elements, id);
    }
}



void NPCFabric::loadTrainer(const std::vector<std::string>& elements, NpcID trainerID) {
    // Get the other values
    int money = atoi(elements[9].c_str());
    int sight = atoi(elements[10].c_str());
    
    NPCFabric::trainersMoney.emplace(trainerID, money);
    NPCFabric::trainersSights.emplace(trainerID, sight);
    
    // Get the Pokemons
    std::string teamString = elements[11];
    std::string teamStratString = elements[12];
    
    // Get the items
    std::string itemString = elements[13];
    
    Log("Loading team " + teamString, Logger::FILE_INFO);
    Log("Loading team strat " + teamStratString, Logger::FILE_INFO);
    Log("Loading items " + itemString, Logger::FILE_INFO);
    
    addTeam(teamString, trainerID);
    addStrategicTeam(teamStratString, trainerID);
    addItems(itemString, trainerID);
}



void NPCFabric::addItems(const std::string& itemStr, NpcID trainerID) {
    // Split the string for each item
    std::vector<std::string>* res = new std::vector<std::string>();
    
    split(res, itemStr, '+');
    
    // For each item
    for(const std::string& str : *res){
        // Find the separator
        int sepPos = str.find(':');
        
        if(sepPos != str.npos){
            // Trainer item result
            TrainerItem item;
            
            // Get the item
            item.id = Item::getID(str.substr(0, sepPos));
            
            // Get the count
            std::istringstream stream(str.substr(sepPos+1));
            if(! (stream >> item.num))
                item.num = 1;
            
            trainersItems.emplace(trainerID, item);
        }
    }
    
    delete res;    
}



void NPCFabric::addTeam(const std::string& teamStr, NpcID trainerID) {
    // Split the string for each pokemons
    std::vector<std::string>* res = new std::vector<std::string>();
    
    split(res, teamStr, '+');
    
    // For each pokemon
    for(const std::string& str : *res){
        // Find the separator
        int sepPos = str.find(':');
        
        if(sepPos != str.npos){
            StandardPokemon poke;
            
            // Get the pokemon Data
            poke.poke = pokemonID(str.substr(0, sepPos));
            
            // Get the pokemon level
            std::string levelStr = str.substr(sepPos+1);
            std::istringstream stream(levelStr);
            
            // Defautl level : 5
            if(! (stream >> poke.level))
                poke.level = 5;
            
            trainerPokemons.emplace(trainerID, poke);
            
            Log("Loaded " + str.substr(0, sepPos) + "  lvl " + toString(poke.level), Logger::FILE_INFO);
        }
    }
    
    delete res;
}



void NPCFabric::addStrategicTeam(const std::string& teamStr, NpcID trainerID) {
    // Split the string for each pokemons
    std::vector<std::string>* res = new std::vector<std::string>();
    
    split(res, teamStr, '+');
    
    // For each pokemon
    for(const std::string& str : *res){
        // Find the separator
        int sepPos = str.find(':');
        
        if(sepPos != str.npos){
            StrategicPokemon poke;
            
            // Get the pokemon Data
            poke.poke = StrategicPokemonFabric::getStrategicID(str.substr(0, sepPos));
            
            // Get the pokemon level
            std::string levelStr = str.substr(sepPos+1);
            std::istringstream stream(levelStr);
            
            // Defautl level : 5
            if(! (stream >> poke.level))
                poke.level = 5;
            
            trainerStratPokemons.emplace(trainerID, poke);
            
            Log("Loaded strategic " + str.substr(0, sepPos) + "  lvl " + toString(poke.level), Logger::FILE_INFO);
        }
    }
    
    delete res;
}
