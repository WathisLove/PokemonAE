#include <cassert>

#include "AttackSet.hpp"
#include "AttackFabric.hpp"
#include "SFML/System/String.hpp"

AttackSet::AttackSet() :
m_nbAttacks(0){
    for(int i = 0; i < 4; i++){
        m_attacks.at(i) = 0;
    }
}



AttackSet::~AttackSet() {
    // Delete each attack
    for(int i = 0; i < m_nbAttacks; i++){
        delete m_attacks.at(i);
    }
}



bool AttackSet::hasPlaceLeft() const {
    return m_nbAttacks < 4;
}



void AttackSet::addAttack(Attack* attack) {
    if(m_nbAttacks > 4) throw ("Can't add an new attack " + attack->getName().toAnsiString() + " [Array full]");
    
    m_attacks.at(m_nbAttacks) = attack;
    
    m_nbAttacks++;
}



Attack* AttackSet::getAttack(int index) {
    if(index < 0 || index > 4) throw ("Can't get attack at index " + toString<int>(index) + " out of bounds");
    
    return m_attacks.at(index);
}



Attack* AttackSet::removeAttack(int index) {
    if(index < 0 || index > 4) throw ("Can't remove attack at index " + toString<int>(index) + " out of bounds");
    
    Attack* returnedAttack = m_attacks.at(index);
    
    // We reorganise the attacks left
    for(int i = m_nbAttacks; i < 4; i++){
        m_attacks.at(i-1) = m_attacks.at(i);
    }
    
    return returnedAttack;
}



void AttackSet::clear() {
    for(int i = 0; i < m_nbAttacks; i++){
        delete m_attacks.at(i);
        m_attacks.at(i) = nullptr; 
    }
    
    m_nbAttacks = 0;
}



int AttackSet::getNbAttacks() const {
    return m_nbAttacks;
}



std::string AttackSet::getInfoString() const {
    std::string s;
    
    s += " - ATTACKS -   Nb: " + toString(m_nbAttacks) + "\n";
    for(int i = 0; i < m_nbAttacks; i++){
        s += toString(i+1) + ") " + m_attacks.at(i)->getInfoString() + "\n";
    }
    
    return s;
}



void AttackSet::replaceAttack(int index, AttackID newAttack) {
    // Delete the old Attack
    Attack* oldAttack = m_attacks[index];
    delete oldAttack;
    
    m_attacks[index] = AttackFabric::createAttack(newAttack);
}



bool AttackSet::contains(AttackID id) {
    // Look at the attacks to find one with the same id
    for(int i = 0; i < m_nbAttacks; i++){
        if(m_attacks.at(i)->getID() == id)
            return true;
    }
    
    // Else we found none
    return false;
}



void AttackSet::setAttacks(std::initializer_list<AttackID> attackList) {
    assert(attackList.size() > 0 && attackList.size() <= 4);
    
    // Clear
    clear();
    
    // Get an iterator to the first element
    std::initializer_list<AttackID>::iterator it = attackList.begin();
    
    // loop over the list of attacks
    for(int i = 0; i < attackList.size(); i++){
        addAttack(AttackFabric::createAttack(*it++));
    }
}



bool AttackSet::hasAttackWhere(AttackPredicate predicate) const {
    // Look for an attack that match the predicate
    for(int i = 0; i < m_nbAttacks; i++){
        if(predicate(m_attacks.at(i)->getID()))
            return true;
    }
    
    // Else
    return false;
}



std::vector<int> AttackSet::getAttacksWhere(AttackPredicate predicate) const {
    std::vector<int> indexes;
    
    // Look for the attacks that match the predicate
    for(int i = 0; i < m_nbAttacks; i++){
        if(predicate(m_attacks.at(i)->getID()))
            indexes.push_back(i);
    }
    
    // Else
    return indexes;
}
