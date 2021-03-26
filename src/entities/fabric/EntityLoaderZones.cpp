#include "../EntityLoader.hpp"



// Npcs for the Zone
std::multimap<ZoneID, NpcID> EntityLoader::zoneNpcs = {};



// PhysicalItems for the Zone 
std::multimap<ZoneID, EntityLoader::PhysicalItemData> EntityLoader::zoneItems = {};



std::multimap<ZoneID, sf::Vector2i> EntityLoader::zoneBoxPCs= {};



std::multimap<ZoneID, EntityLoader::StoryTriggerData> EntityLoader::zoneStoryTriggers = {
    
};