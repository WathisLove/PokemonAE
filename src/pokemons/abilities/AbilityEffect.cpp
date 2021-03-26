#include "AbilityEffect.hpp"
#include <cassert>

AbilityEffect::AbilityEffect() :
m_type(AbilityEffectType::AE_NOT_DEFINED){

}



AbilityEffect::AbilityEffect(StatsChanger changer) :
m_type(AbilityEffect::AE_ChangeStats){
    m_statChanger = changer;
}



void AbilityEffect::setChangeStats(StatsChanger changer) {
    m_type = AbilityEffectType::AE_ChangeStats;
    m_statChanger = changer;
}



AbilityEffect::AbilityEffectType AbilityEffect::getType() {
    return m_type;
}



StatsChanger& AbilityEffect::getStatChanger() {
    // Assure we have the correct type
    assert(m_type == AbilityEffectType::AE_ChangeStats);
    
    // Return the Stat Changer
    return m_statChanger;
}
