#include "NPCFabric.hpp"


// Localisation of the NPCs
std::map<NpcID, NPCFabric::Position> NPCFabric::positions = {};



// NPC Textures ID
std::map<NpcID, TextureHolder::textureID> NPCFabric::textures = {};



// NPC Movers
// NoMovers are not declared because default
std::map<NpcID, EntityMover*> NPCFabric::movers = { 
    
    // City 1
    //{NpcID::city1_randomNPC_1, new RandomMover(sf::IntRect(24, 10, 22, 10), sf::Vector2i(30, 26), 3)},
};



// NPC Directions
std::map<NpcID, Direction> NPCFabric::directions = {};



// Npc Speeds
std::map<NpcID, float> NPCFabric::speeds = {
    //{NpcID::road1_trainer_1, 4.},
};



// Sellers

// Items sold at default price
std::multimap<NpcID, ItemID> NPCFabric::itemsSoldDefaultPrice = {};



std::multimap<NpcID, NPCFabric::SoldItem> NPCFabric::itemsSold = {};
    



//// Trainers

// Money given by trainers when defeated
std::map<NpcID, sf::String> NPCFabric::trainersNames = {
    // City 1
    //{NpcID::city1_trainer_1, sf::String("Philippe")},
};



// Money given by trainers when defeated
std::map<NpcID, unsigned int> NPCFabric::trainersMoney = {
    // City 1
    //{NpcID::city1_trainer_1, 300},
};



// Trainers sight
std::map<NpcID, unsigned int> NPCFabric::trainersSights = {
    // City 1
    //{NpcID::city1_trainer_1, 6},
};



// Trainer Items
std::multimap<NpcID, NPCFabric::TrainerItem> NPCFabric::trainersItems = {
    // City 1
    //{NpcID::city1_trainer_1, {ItemID::i_potion, 2}},
};



// Pokemons
std::multimap<NpcID, NPCFabric::StandardPokemon> NPCFabric::trainerPokemons = {
    // City 1
    //{NpcID::city1_trainer_1, {pikachu, 3}},
};



// Strategic Pokemons
std::multimap<NpcID, NPCFabric::StrategicPokemon> NPCFabric::trainerStratPokemons = {
    // City 1
    
};
