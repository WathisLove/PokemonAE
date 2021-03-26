#include "AttackPredicate.hpp"
#include "../pokemons/attacks/AttackFabric.hpp"


// A predicate for the healing items
const std::function<bool(AttackID)> AttackPredicate::priority = 
[](AttackID id) {
    Attack* atk = AttackFabric::createAttack(id);
    // Check if the priority is higher than one
    bool res = atk->getPriority() > 0;
    
    delete atk;
    return res;
};



// A predicate for the stat reducing attacks
const std::function<bool(AttackID)> AttackPredicate::statReduceEnnemy = 
[](AttackID id) {
    Attack* atk = AttackFabric::createAttack(id);
    // Check if the priority target the ennemy and is < 0 
    bool res = atk->getStatsChanger().getTargetedTeam() == Team::ennemy && atk->getStatsChanger().isNegativeChanger();
    
    delete atk;
    return res;
};



// A predicate for the stat raising attacks
const std::function<bool(AttackID)> AttackPredicate::statRaiseEnnemy = 
[](AttackID id) {
    Attack* atk = AttackFabric::createAttack(id);
    // Check if the priority target the ennemy and is < 0 
    bool res = atk->getStatsChanger().getTargetedTeam() == Team::allied && atk->getStatsChanger().isPositiveChanger();
    
    delete atk;
    return res;
};
    
    

AttackPredicate::AttackPredicate(AttackSearched search) :
m_target(search){

}



bool AttackPredicate::operator()(AttackID id) {
    switch(m_target){
        case AttackSearched::Priority:
            return priority(id);
        case AttackSearched::StatReduceEnnemy:
            return statReduceEnnemy(id);
        case AttackSearched::StatRaiseAlly:
            return statRaiseEnnemy(id);
        default:
            throw std::string("Not known function for attack predicate ") + toString((int)m_target);
    }
}
