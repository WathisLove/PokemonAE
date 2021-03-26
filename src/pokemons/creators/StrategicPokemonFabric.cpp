#include <cassert>

#include "StrategicPokemonFabric.hpp"
#include "../PokemonCreator.hpp"
#include "../../inventory/Item.hpp"
#include "../../utility/Logger.hpp"

    
// Map for the strategic pokemon string
const std::map<std::string, StrategicPokemonID> 
StrategicPokemonFabric::pokemonStratString = {
    {"MAMOSWINE_LIFE_ORB", StrategicPokemonID::MAMOSWINE_LIFE_ORB} 
};



// Map for the pokemon IDs
const std::map<StrategicPokemonID, PokemonID> 
StrategicPokemonFabric::pokemonIDs = {
    {StrategicPokemonID::MAMOSWINE_LIFE_ORB, mammochon} 
};



// Map for the Abilities
const std::map<StrategicPokemonID, AbilityID> 
StrategicPokemonFabric::abilityIDs = {
    
};



// Map for the Items
const std::map<StrategicPokemonID, ItemID> 
StrategicPokemonFabric::itemIDs{
    
};



// Map for the Natures
const std::map<StrategicPokemonID, PokemonNature::NatureID> 
StrategicPokemonFabric::natureIDs{
    {StrategicPokemonID::MAMOSWINE_LIFE_ORB, PokemonNature::Jovial} 
};



// Map for the EVs
const std::map<StrategicPokemonID, std::initializer_list<unsigned int>> 
StrategicPokemonFabric::evs{
    // Reminder : H Att Def SAtt SDef Sp
    {StrategicPokemonID::MAMOSWINE_LIFE_ORB, {0, 252, 4, 0, 0, 252}} 
};



// Map for the Attacks (there must be at least 1 attack, and maximum 4 - it won't crash but won't be used )
const std::map<StrategicPokemonID, std::initializer_list<AttackID>> 
StrategicPokemonFabric::attackIDs{
    {StrategicPokemonID::MAMOSWINE_LIFE_ORB, {EclatGlace, Seisme, Avalanche, Surpuissance}} 
};


// Map for the strategic roles
const std::map<StrategicPokemonID, StrategicRole> 
StrategicPokemonFabric::roles{
    {StrategicPokemonID::MAMOSWINE_LIFE_ORB, StrategicRole::WALL_BREAKER} 
};


//===============// Method //==================//


Pokemon* StrategicPokemonFabric::create(StrategicPokemonID id, unsigned int level) {
    // Get the pokemon ID
    auto pokemonIdIt = StrategicPokemonFabric::pokemonIDs.find(id);
    
    // Assert the pokemon exists
    assert(pokemonIdIt != StrategicPokemonFabric::pokemonIDs.end());
    
    // Create the pokemon
    Pokemon* p = createPokemon(pokemonIdIt->second, level);
    
    
    // Ability
    auto abilityIt = abilityIDs.find(id);
    if(abilityIt != abilityIDs.end())
        p->setAbility(abilityIt->second);
    
    
    // Items
    auto itemIt = itemIDs.find(id);
    if(itemIt != itemIDs.end())
        p->giveItem(new Item(itemIt->second));
    
    
    // Nature
    auto natureIt = natureIDs.find(id);
    if(natureIt != natureIDs.end())
        p->setNature(natureIt->second);
    
    
    // Max IVs and set EVs
    p->getIVs().setMaxValues();
    
    auto evsIt = evs.find(id);
    if(evsIt != evs.end())
        p->setEVSet(evsIt->second);
    
    
    // Attacks
    auto attacksIt = attackIDs.find(id);
    if(attacksIt != attackIDs.end()){
        p->getAttackSet().setAttacks(attacksIt->second);
    }
    
    
    // Role
    auto roleIt = roles.find(id);
    if(roleIt != roles.end()){
        p->setRole(roleIt->second);
    }
    
    
    return p;
}



StrategicPokemonID StrategicPokemonFabric::getStrategicID(const std::string& str) {
    auto it = pokemonStratString.find(str);
    
    // If the pokemon was found in the map
    if(it != pokemonStratString.end()){
        return it->second;
    }
    else{
        Log("Could not find strategic pokemon " + str, Logger::FILE_ERROR);
        return StrategicPokemonID::MAMOSWINE_LIFE_ORB;
    }
}
