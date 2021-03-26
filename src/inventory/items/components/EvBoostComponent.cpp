#include "EvBoostComponent.hpp"



EvBoostComponent::EvBoostComponent(int boost, StatName stat, BonusType bonusType) :
m_boost(boost),
m_stat(stat),
m_bonusType(bonusType){

}



ItemEffect* EvBoostComponent::onEvReceived(int& evAmount, StatName stat) const {
    // Apply a boost to the Ev Gained if the stats is the one concerned
    if(stat == m_stat){
        // If the bonus is additive
        if(m_bonusType == BonusType::Additive)
            evAmount += m_boost;
        // If the bonus is multiplicative
        else if(m_bonusType == BonusType::Multiplicative)
            evAmount *= m_boost;
    }
    
    return nullptr;
}
