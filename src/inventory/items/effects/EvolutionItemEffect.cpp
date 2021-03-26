#include "EvolutionItemEffect.hpp"



EvolutionItemEffect::EvolutionItemEffect(PokemonID evolution) :
ItemEffect(ItemEffect::Type::Evolution),
m_evolution(evolution){

}



PokemonID EvolutionItemEffect::getEvolutionID() const {
    return m_evolution;
}
