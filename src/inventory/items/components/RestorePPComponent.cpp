#include "RestorePPComponent.hpp"
#include "../../../pokemons/Pokemon.hpp"



RestorePPComponent::RestorePPComponent() :
m_restoreAll(true){

}



RestorePPComponent::RestorePPComponent(int ppRestored) :
m_restoreAll(false),
m_ppRestored(ppRestored){

}



ItemEffect* RestorePPComponent::onPokemon(Pokemon* pokemon) const {
    // Number of attack with PP restored
    int nAttackRestored = 0;
    
    // For each attack
    for(int i = 0; i < pokemon->getAttackSet().getNbAttacks(); i++){
        // Get the Attack
        Attack* attack = pokemon->getAttackSet().getAttack(i);
        
        // Apply the effect on the Attack and delete the returned effect
        ItemEffect* effect = onAttack(attack);
        
        if(effect != nullptr){
            nAttackRestored++;
            delete effect;
        }
    }
    
    // If the item restored PP
    if(nAttackRestored > 0){
        if(m_ppRestored > 150)
            return new ItemEffect(ItemEffect::Type::HealPP, new sf::String(pokemon->getName() + L" récupère tous ses PP."));
        else
            return new ItemEffect(ItemEffect::Type::HealPP, new sf::String(pokemon->getName() + L" récupère " + toString(m_ppRestored) + L" PP à chaque capacité."));
    }
    else
        return nullptr;
}



ItemEffect* RestorePPComponent::onAttack(Attack* attack) const {
    // If there isn't the max amount of PP
    if(attack->getPP() < attack->getPPMax()){
        sf::String* str = new sf::String(attack->getName() + " regagne ");

        if(m_restoreAll){
            attack->restorePPs();
            *str += "tous ses PP.";
        }
        else{
            // Store the previous amount
            int prevPP = attack->getPP();
            
            // Restore
            attack->restorePPs(m_ppRestored);
            
            // Update the string
            *str += toString(attack->getPP() - prevPP) + " PP.";
        }
        
        return new ItemEffect(ItemEffect::Type::HealPP, str);
    }
    
    // Nothing done
    return nullptr;
}



bool RestorePPComponent::hasEffectOnPokemon(Pokemon* pokemon) const {
    // For each attack
    for(int i = 0; i < pokemon->getAttackSet().getNbAttacks(); i++){
        // Check if there is an effect on at least 1 attack
        if(hasEffectOnAttack(pokemon->getAttackSet().getAttack(i)))
            return true;
    }
    
    return false;
}



bool RestorePPComponent::hasEffectOnAttack(Attack* attack) const {
    return attack->getPP() < attack->getPPMax();
}
