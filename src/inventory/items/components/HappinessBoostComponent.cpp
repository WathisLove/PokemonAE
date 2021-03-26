#include "HappinessBoostComponent.hpp"



HappinessBoostComponent::HappinessBoostComponent(float factor) :
m_boostFactor(factor){

}



ItemEffect* HappinessBoostComponent::onHappinessReceived(int& happinessAmount) const {
    happinessAmount *= m_boostFactor;
    
    // No need to send an item Effect
    return nullptr;
}
