#include "WildPokemonManager.hpp"
#include "../../Utilities.hpp"
#include "../../pokemons/PokemonCreator.hpp"


WildPokemonManager::WildPokemonManager() {
    
    //===// Build the Multimap
    
    // City 1
    addEncounter(ZoneID::city_1, createEncounter(PokemonID::marcacrin, Very_Common, 1, 1));
    addEncounter(ZoneID::city_1, createEncounter(PokemonID::pikachu, Common, 2, 3));
    
    // Road 1
    addEncounter(ZoneID::road_1, createEncounter(PokemonID::pikachu, Very_Common, 1, 3));
    addEncounter(ZoneID::road_1, createEncounter(PokemonID::marcacrin, Uncommon, 4, 6));
}



bool WildPokemonManager::hasEncounteredPokemon(ZoneID zone) {
    // Variable for the result
    std::pair<std::multimap<ZoneID, PossibleEncounter>::iterator, std::multimap<ZoneID, PossibleEncounter>::iterator> res;
    
    // Find all the elements linked to zone
    res = m_possibleEncounters.equal_range(zone);
    
    // Get a random number from 0 to 1 to know if we found a pokemon
    float rand = randomFloat(0, 1);
    
    // Sum of the encountered probabilities
    float sum = 0;
    
    
    // Iterate on the result
    for(std::multimap<ZoneID, PossibleEncounter>::iterator it = res.first; it != res.second; it++){
        // Get the encounter
        PossibleEncounter& encounter = it->second;
        
        // Add the probability
        sum += getEncounterProbability(encounter.rarity);
        
        // If the encounter happens
        if(rand <= sum){
            updateLastEncounter(encounter);
            return true;
        }
    }
    
    
    // Else no encounter happened
    return false;
}



Pokemon* WildPokemonManager::getEncounteredPokemon() {
    // Get the PokemonID
    PokemonID id = m_lastEncounter.id;
    
    // Get the level
    int level = randomInt(m_lastEncounter.minLevel, m_lastEncounter.maxLevel);
    
    // Create a new pokemon
    return createPokemon(id, level);
}



std::vector<PokemonID> WildPokemonManager::getPossiblePokemons(ZoneID zone) {
    // Variable for the result
    std::pair<std::multimap<ZoneID, PossibleEncounter>::iterator, std::multimap<ZoneID, PossibleEncounter>::iterator> res;
    
    // Find all the elements linked to zone
    res = m_possibleEncounters.equal_range(zone);
    
    // Add them to a vector
    std::vector<PokemonID> ids;
    
    // Iterate through the result and add each PokemonID
    for(std::multimap<ZoneID, PossibleEncounter>::iterator it = res.first; it != res.second; it++){
        ids.push_back(it->second.id);
    }
    
    return ids;
}



std::vector<ZoneID> WildPokemonManager::getPossibleZones(PokemonID pokemonID) {
    std::vector<ZoneID> zones;
    
    // Iterate through the result and add each ZoneID
    for(std::multimap<ZoneID, PossibleEncounter>::iterator it = m_possibleEncounters.begin(); it != m_possibleEncounters.end(); it++){
        // If we find the PokemonID, we add the zone to the result
        if(it->second.id == pokemonID){
            zones.push_back(it->first);
        }
    }
    
    return zones;
}



WildPokemonManager::PossibleEncounter WildPokemonManager::createEncounter(PokemonID id, EncounterRarity rarity, int minLevel, int maxLevel) {
    PossibleEncounter encounter;
    
    // Fill the encounter with the given infos
    encounter.id = id;
    encounter.rarity = rarity;
    encounter.minLevel = minLevel;
    encounter.maxLevel = maxLevel;
    
    return encounter;
}



float WildPokemonManager::getEncounterProbability(EncounterRarity rarity) {
    // X is proportionnal to the probability
    float x = 0;
    
    switch(rarity){
        case EncounterRarity::Very_Common:
            x = 10.;
            break;
        case EncounterRarity::Common:
            x = 8.5;
            break;
        case EncounterRarity::Uncommon:
            x = 6.75;
            break;
        case EncounterRarity::Rare:
            x = 3.33;
            break;
        case EncounterRarity::Very_Rare:
            x = 1.25;
            break;
    }
    
    // Formula given by the French Pokepedia
    return x / 187.5;
}



void WildPokemonManager::addEncounter(ZoneID zone, PossibleEncounter encounter) {
    // Insert the pair into the multimap
    m_possibleEncounters.insert(std::pair<ZoneID, PossibleEncounter>(zone, encounter));
}



void WildPokemonManager::updateLastEncounter(PossibleEncounter encounter) {
    m_lastEncounter = encounter;
}
