#include "HealHPComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"



HealHPComponent::HealHPComponent(int hpAmount) :
ItemComponent(),
m_hpAmount(hpAmount),
m_isPercentage(false){

}



HealHPComponent::HealHPComponent(float hpPercentage) :
ItemComponent(),
m_percentage(hpPercentage),
m_isPercentage(true){

}



ItemEffect* HealHPComponent::onPokemon(Pokemon* pokemon) const {
    // Only heal non KO pokemons or without full HP
    if(!pokemon->isKO() && !pokemon->isFullHP())
    {
        int hpRestored;
        // Heal by a percentage 
        if(m_isPercentage)
            hpRestored = pokemon->healRatio(m_percentage / 100.);
        // Heal by a fix amount
        else
            hpRestored = pokemon->healHP(m_hpAmount);
        
        // Return an effect with the HP healed
        return new ItemEffect(ItemEffect::Type::HealHP, new sf::String(pokemon->getName() + L" récupère " + toString(hpRestored) + "PV."));
    }
    
    
    return nullptr;
}



bool HealHPComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    return !pokemon->isKO() && !pokemon->isFullHP();
}
