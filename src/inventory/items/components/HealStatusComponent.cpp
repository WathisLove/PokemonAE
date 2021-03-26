#include "HealStatusComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"



HealStatusComponent::HealStatusComponent() :
m_healAnyStatus(true){

}



HealStatusComponent::HealStatusComponent(MainStatusName statusCured) :
m_healAnyStatus(false),
m_statusHealed(statusCured){

}



ItemEffect* HealStatusComponent::onPokemon(Pokemon* pokemon) const {
    if(pokemon->hasStatus())
    {
        // Status healed
        MainStatusName statusHealed = MainStatusName::NoMainStatus;
        
        // Get the status
        MainStatus status = pokemon->getMainStatus();
        
        // Cure if heal any status
        if(m_healAnyStatus)
            statusHealed = cure(pokemon);
        
        // Check if the same status
        else if(status.getName() == m_statusHealed)
            statusHealed = cure(pokemon);
        
        // Cure poison
        else if(status.isPoison() && m_statusHealed == MainStatusName::Poison)
            statusHealed = cure(pokemon);
        
        
        // If the Item cured the status
        if(statusHealed != MainStatusName::NoMainStatus)
            return new ItemEffect(ItemEffect::Type::HealMainStatus, getCureMessage(pokemon, statusHealed));
    }
    
    return nullptr;
}



bool HealStatusComponent::hasEffectOnPokemon(Pokemon* pokemon) const {

    if(pokemon->hasStatus())
    {
        // Get the status
        MainStatus status = pokemon->getMainStatus();
        
        // Cure if heal any status
        if(m_healAnyStatus)
            return true;
        
        // Check if the same status
        else if(status.getName() == m_statusHealed)
            return true;
        
        // Cure poison
        else if(status.isPoison() && m_statusHealed == MainStatusName::Poison)
            return true;
    }
    
    return false;
}



MainStatusName HealStatusComponent::cure(Pokemon* p) const {
    // Status healed
    MainStatusName statusHealed = p->getMainStatus().getName();
    
    p->cureMainStatus();
    
    return statusHealed;
}



sf::String* HealStatusComponent::getCureMessage(Pokemon* p, MainStatusName status) const {
    // Create the string and its beginning
    sf::String* str = new sf::String(p->getName() + " n'est plus ");
    
    // Add the message relative to the status
    if(status == MainStatusName::Burn)
        *str += L"brûlé.";
    else if(status == MainStatusName::Freeze)
        *str += L"gelé.";
    else if(status == MainStatusName::Paralysis)
        *str += L"paralysé.";
    else if(status == MainStatusName::Sleep)
        *str += L"endormi.";
    else if(status == MainStatusName::BadlyPoison || status == MainStatusName::Poison)
        *str += L"empoisonné.";
    
    return str;
}
