#include "ItemComponent.hpp"
#include "../../pokemons/Pokemon.hpp"


ItemComponent::ItemComponent() {

}



ItemEffect* ItemComponent::onStat(int& statValue, StatName stat, PokemonID holder) const {
    // Nothing to do by default
    return nullptr;
}



ItemEffect* ItemComponent::onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const {
    // Nothing to do by default
    return nullptr;
}



ItemEffect* ItemComponent::onPokemon(Pokemon* pokemon) const {
    // Nothing to do by default
    return nullptr;
}



ItemEffect* ItemComponent::onAttack(Attack* attack) const {
    return nullptr;
}



ItemEffect* ItemComponent::onCritLevel(int& critLevel) const {
    return nullptr;
}



ItemEffect* ItemComponent::onXPGained(int& xpGained) const {
    return nullptr;
}



ItemEffect* ItemComponent::onMoneyGained(int& xpGained) const {
    return nullptr;
}



ItemEffect* ItemComponent::onHappinessReceived(int& happinessAmount) const {
    return nullptr;
}



ItemEffect* ItemComponent::onEvReceived(int& evAmount, StatName stat) const {
    return nullptr;
}



bool ItemComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    return false;
}



bool ItemComponent::hasEffectOnAttack(Attack* attack) const {
    return false;
}
