#include "HealConfusionComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"



ItemEffect* HealConfusionComponent::onPokemon(Pokemon* pokemon) const {
    if(pokemon->isConfused())
        return new ItemEffect(ItemEffect::Type::HealConfusion);
    
    else 
        return nullptr;
}



bool HealConfusionComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    return pokemon->isConfused();
}
