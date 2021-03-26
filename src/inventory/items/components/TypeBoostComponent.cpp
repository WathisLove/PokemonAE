#include "TypeBoostComponent.hpp"



TypeBoostComponent::TypeBoostComponent(float factor, Type type, PokemonID attacker) :
m_factor(factor),
m_type(type),
m_poke(attacker){

}



ItemEffect* TypeBoostComponent::onDamagesOfType(int& damages, Type attackType, PokemonID attacker) const {
    // If the first type correspond
    if(attackType.getFirstType() == m_type.getFirstType()){
        // If the pokemon is not specified
        if(m_poke == PokemonID::UNKWNOWN)
            damages *= m_factor;
        // Else if it is the specified pokemon
        else if(m_poke == attacker)
            damages *= m_factor;
    }
    
    // Nothing to return
    return nullptr;
}
