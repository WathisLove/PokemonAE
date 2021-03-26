#include "CritBoosterComponent.hpp"



CritBoosterComponent::CritBoosterComponent(int boostLevel) :
m_critBoost(boostLevel){

}



ItemEffect* CritBoosterComponent::onCritLevel(int& critLevel) const {
    // Add boost and cap the crit level to 5
    critLevel = std::min(5, critLevel + m_critBoost);
    
    // No need to Send a ItemEffect
    return nullptr;
}
