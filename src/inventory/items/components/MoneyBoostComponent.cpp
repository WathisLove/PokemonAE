#include "MoneyBoostComponent.hpp"


MoneyBoostComponent::MoneyBoostComponent(float boostFactor) :
m_boostFactor(boostFactor){

}



ItemEffect* MoneyBoostComponent::onMoneyGained(int& moneyGained) const {
    moneyGained *= m_boostFactor;
    
    // No need to display
    return new ItemEffect(ItemEffect::Type::MoneyBoost);
}
