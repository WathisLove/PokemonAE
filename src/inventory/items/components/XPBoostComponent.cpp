#include "XPBoostComponent.hpp"

XPBoostComponent::XPBoostComponent(float boostFactor) :
m_boostFactor(boostFactor){

}



ItemEffect* XPBoostComponent::onXPGained(int& xpGained) const {
    xpGained *= m_boostFactor;
    
    // Nothing to return
    return nullptr;
}
