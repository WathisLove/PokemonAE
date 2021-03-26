#include "EvolutionCondition.hpp"
#include "../pokemons/Pokemon.hpp"
#include "../Utilities.hpp"
#include "../utility/Logger.hpp"


EvolutionCondition::EvolutionCondition(PokemonID evolutionID) :
m_evolutionID(evolutionID){

}



void EvolutionCondition::addAttackLearnedCondition(AttackID attackID) {
    // Create a condition for the Attack
    EvolveCond cond;
    cond.type = EvolveConditionType::AttackLearned_C;
    cond.value = (int)attackID;
    
    // Push it to the vector
    m_conditions.push_back(cond);
}



void EvolutionCondition::addItemUseCondition(ItemID itemID) {
    // Create a condition for the Attack
    EvolveCond cond;
    cond.type = EvolveConditionType::ItemUse_C;
    cond.value = (int)itemID;
    
    // Push it to the vector
    m_conditions.push_back(cond);
}



void EvolutionCondition::addLevelCondition(int level) {
    // Create a condition for the Attack
    EvolveCond cond;
    cond.type = EvolveConditionType::LevelUp_C;
    cond.value = level;
    
    // Push it to the vector
    m_conditions.push_back(cond);
}



bool EvolutionCondition::completesConditions(Pokemon* pokemon) {
    // Check each condition
    for(EvolveCond& cond : m_conditions){
        // Return false if we do not validate a condition
        if(!checkSingleCondition(cond, pokemon)){
            return false;
        }
    }
    
    // Return true once all conditions were tested
    return true;
}



PokemonID EvolutionCondition::getEvolutionID() {
    return m_evolutionID;
}



bool EvolutionCondition::checkSingleCondition(EvolveCond& cond, Pokemon* pokemon) {
    // Check if the pokemon knows the attack
    if(cond.type == EvolveConditionType::AttackLearned_C){
        return pokemon->getAttackSet().contains((AttackID)cond.value);
    }
    // Check if we use the Item on the pokemon
    else if(cond.type == EvolveConditionType::ItemUse_C){
        return pokemon->getLastItemUsed() == (ItemID)cond.value;
    }
    // Check if we use the Item on the pokemon
    else if(cond.type == EvolveConditionType::ItemWear_C){
        return pokemon->getItem()->getID() == (ItemID)cond.value;
    }
    // Check the pokemon level
    else if(cond.type == EvolveConditionType::LevelUp_C){
        return pokemon->getLevel() >= cond.value;
    }
    
    Log("No known EvolutionCondition " + toString(static_cast<int>(cond.type)));
    return false;
}
