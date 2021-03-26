#include "ReviveComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"



ReviveComponent::ReviveComponent(float hpPercentage) :
m_healthPercentage(hpPercentage){

}



ItemEffect* ReviveComponent::onPokemon(Pokemon* pokemon) const {
    // Revive if KO only
    if(pokemon->isKO())
    {
        // Heal 
        pokemon->healRatio(m_healthPercentage / 100.);
        
        // An item effect
        return new ItemEffect(ItemEffect::Type::HealKO, new sf::String(pokemon->getName() + " n'est plus KO !"));
    }
    
    // Nothing done
    return nullptr;
}



bool ReviveComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    return pokemon->isKO();
}
