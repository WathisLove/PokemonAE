#include "EvolutionComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"
#include "../effects/EvolutionItemEffect.hpp"


EvolutionComponent::EvolutionComponent(PokemonID unevolved, PokemonID evolution) :
m_unevolved(unevolved),
m_evolution(evolution){

}



ItemEffect* EvolutionComponent::onPokemon(Pokemon* pokemon) const {
    // If the pokemon has the correct ID
    if(pokemon->getID() == m_unevolved)
        return new EvolutionItemEffect(m_evolution);
    
    // Else return no effect
    return nullptr;
}



bool EvolutionComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    return pokemon->getID() == m_unevolved;
}
