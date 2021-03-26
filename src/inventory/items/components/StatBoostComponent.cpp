#include "StatBoostComponent.hpp"



StatBoostComponent::StatBoostComponent(StatName stat, float factor, PokemonID holder) :
m_stat(stat),
m_factor(factor),
m_holder(holder){

}



ItemEffect* StatBoostComponent::onStat(int& statValue, StatName stat, PokemonID holder) const {
    // Same stat
    if(m_stat == stat)
    {
        // If pokemon unknown
        if(m_holder == PokemonID::UNKWNOWN)
            statValue *= m_factor;
        // Else if correct Holder
        else if(m_holder == holder)
            statValue *= m_factor;
    }
    
    // Nothing to do
    return nullptr;
}
