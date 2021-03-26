#include "FightTrainerManager.hpp"

#include <iostream>

FightTrainerManager::FightTrainerManager(Trainer* trainer) :
m_trainer(trainer),
m_bestOption(nullptr),
m_itemOption(ItemID::LAST_ITEM),
m_attackOption(-1){

}



void FightTrainerManager::switchPokes(int index1, int index2) {
    m_trainer->getPokemonTeam()->switchPokemons(index1, index2);
}



ItemID FightTrainerManager::getItemToUse() const {
    // For the moment, a trainer only uses potions
    return m_itemOption;
}



void FightTrainerManager::useItem(ItemID id) {
    // Display a message if the trainer does not have the item
    if(!m_trainer->getInventory()->hasItem(id))
        std::cout << "No item of ID " + toString(static_cast<int>(id)) + " in the trainer inventory" << std::endl;
    
    else
        delete m_trainer->takeItem(id);
}



void FightTrainerManager::sendBetterPokemon(Pokemon* ennemy) {
    // Check the switch option is not null
    m_bestOption = getBestPokemonAgainst(ennemy);
    
    // Switch
    m_trainer->getPokemonTeam()->switchPokemons(getCurrentPokemon(), m_bestOption);
}



const sf::String& FightTrainerManager::getTrainerName() {
    return m_trainer->getName();
}



Trainer* FightTrainerManager::getTrainer() {
    return m_trainer;
}



void FightTrainerManager::endFight(bool winner) {
    if(winner){
        m_trainer->healTeam();
    }
    else{
        m_trainer->setDefeated(true);
    }
}



FightAction FightTrainerManager::getNextAction(Pokemon* ennemy, bool canSwitch) {
    // If the trainer should switch
    if(canSwitch && shouldSwitch(ennemy)){
        return FightAction::FA_Switch;
    }
    else if(shouldUseItem(ennemy))
        return FightAction::FA_Item;
    else{
        calculateBestAttack(ennemy);
        return FightAction::FA_Attack;
    }
}



int FightTrainerManager::getNextAttackIndex() {
    // For the moment, a trainer uses a random attack of the first pokemon
    return m_attackOption;
}



bool FightTrainerManager::hasPokemonsNotKO() {
    return m_trainer->hasPokemonsLeft();
}



int FightTrainerManager::getFirstPokemonNotKO() {
    return m_trainer->getFirstPokemonNotKO();
}



Pokemon* FightTrainerManager::getCurrentPokemon() {
    // The first pokemon of the trainer team is always the one fighting
    return m_trainer->getPokemonAt(0);
}



bool FightTrainerManager::playerCanFlee() {
    return false;
}



bool FightTrainerManager::canBeCaptured() {
    return false;
}



bool FightTrainerManager::isTrainer() {
    return true;
}



bool FightTrainerManager::shouldSwitch(Pokemon* ennemy) {
    // The ally pokemon
    Pokemon* ally = m_trainer->getPokemonAt(getFirstPokemonNotKO());
    
    // Do not switch if we have more levels
    if(ennemy->getLevel() + 5 < ally->getLevel())
        return false;
    
    std::cout << "Level is high enough to switch" << std::endl;
    
    // Get the pokemon types
    Type allyType = ally->getType();
    Type ennemyType = ennemy->getType();
    
    // If the ennemy has a type advantage, look for a better option
    if(Type::getGlobalEfficiency(allyType, ennemyType) > 1){
        // Switch if there is a better option then
        std::cout << "Getting a better option ! " << std::endl;
        m_bestOption = getBestPokemonAgainst(ennemy);
        return m_bestOption != ally;
    }
    
    return false;
}



bool FightTrainerManager::shouldUseItem(Pokemon* ennemy) {
    if(m_trainer->getInventory()->isEmpty()){
        std::cout << "Trainer inventory is empty" << std::endl;
        return false;
    }
    
    // Check if the enemy is low life and our pokemon has a priority
    AttackPredicate priority(AttackPredicate::AttackSearched::Priority);
    if(ennemy->getHealthPercentage() < 20. && getCurrentPokemon()->getAttackSet().hasAttackWhere(priority))
        return false;
    
    // Check if the pokemon needs heal or cure
    return shouldHeal() || shouldCureStatus();// REMEMBER : store item when doing so !
}



bool FightTrainerManager::shouldHeal() {
    std::cout << "Health % : " << getCurrentPokemon()->getHealthPercentage() << std::endl;
    
    if(getCurrentPokemon()->getHealthPercentage() < 25.){
        // Get healing items
        ItemPredicate healingPred(ItemPredicate::ItemSearched::Healing);
        std::vector<ItemID> items = m_trainer->getInventory()->getItemsWhere(healingPred);
        
        std::cout << "TRying to heal. Available : " << items.size() << " items to heal" << std::endl;
        
        if(items.size() == 0)
            return false;
        else{
            m_itemOption = items.at(0);
            return true;
        }
    }
    else{
        return false;
    }
}



bool FightTrainerManager::shouldCureStatus() {
    if(getCurrentPokemon()->hasStatus()){
        // Get healing items
        ItemPredicate curingPred(ItemPredicate::ItemSearched::CuringStatus, getCurrentPokemon()->getMainStatus().getName());
        std::vector<ItemID> items = m_trainer->getInventory()->getItemsWhere(curingPred);
        
        std::cout << "Trying to cure the status. Available : " << items.size() << " items to cure" << std::endl;
        
        if(items.size() == 0)
            return false;
        else{
            m_itemOption = items.at(0);
            return true;
        }
    }
    else{
        return false;
    }
}



Pokemon* FightTrainerManager::getBestPokemonAgainst(Pokemon* ennemy) {
    // The Ennemy type
    Type ennemyType = ennemy->getType();
    
    // By default, put the current pokemon
    Pokemon* best = m_trainer->getPokemonAt(getFirstPokemonNotKO());
    float currentEfficiency = Type::getGlobalEfficiency(ennemyType, best->getType());
    int currentLevel = best->getLevel();
    
    // Check each pokemon
    for(int i = 0; i < m_trainer->getPokemonTeam()->getNbPokemon(); i++){
        // Get the pokemon
        Pokemon* p = m_trainer->getPokemonAt(i);
        
        // Get the coeff for the pokemon
        float efficiency = Type::getGlobalEfficiency(ennemyType, p->getType());
    
        // Switch if not KO and if the coeff is lower or if p has more levels
        if(!p->isKO() && (efficiency < currentEfficiency || (efficiency == currentEfficiency && p->getLevel() >= currentLevel + 5))){
            best = p;
            currentEfficiency = efficiency;
            currentLevel = p->getLevel();
        }
    }
    
    return best;
}



void FightTrainerManager::calculateBestAttack(Pokemon* ennemy) {
    // Check if the enemy is low life and our pokemon has a priority
    if(ennemy->getHealthPercentage() < 20.){
        // Lok for priorities
        AttackPredicate priority(AttackPredicate::AttackSearched::Priority);
        std::vector<int> priorityIndex = getCurrentPokemon()->getAttackSet().getAttacksWhere(priority);
        
        for(int i = 0; i < priorityIndex.size(); i++){
            // Get the attack
            Attack* a = getCurrentPokemon()->getAttackSet().getAttack(priorityIndex.at(i));
            
            // Check we can touch with one attack
            if(a->getPP() > 0 && ennemy->calculateDamages(*getCurrentPokemon(), *a, false, 0) > ennemy->getHealth()){
                m_attackOption = priorityIndex.at(i);
                return;
            }
        }
    }
    
    // Else get tha attack that will make the most damage
    int maxDamage = 0;
    m_attackOption = 0;
    for(int i = 0; i < getCurrentPokemon()->getAttackSet().getNbAttacks(); i++){
        // Create the attack
        Attack* a = getCurrentPokemon()->getAttackSet().getAttack(i);
        
        // Get the damage
        int damage = ennemy->calculateDamages(*getCurrentPokemon(), *a, false, 0);
        
        if(a->getPP() > 0 && damage > maxDamage){
            maxDamage = damage;
            m_attackOption = i;
        }
    }
}
