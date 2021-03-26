#include "EvoluStatComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"


EvoluStatComponent::EvoluStatComponent(StatName stat, float factor)  :
StatBoostComponent(stat, factor) {
    
}



ItemEffect* EvoluStatComponent::onStat(int& statValue, StatName stat, PokemonID holder) const {
    // Apply the Stat boost if there is an evolution
    if(Pokemon::hasEvolution(holder)){
        StatBoostComponent::onStat(statValue, stat, holder);
    }
    
    // No need to send an item effect
    return nullptr;
}
