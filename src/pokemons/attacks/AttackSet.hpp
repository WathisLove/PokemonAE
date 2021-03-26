/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackSet.hpp
 * Author: Redbuzard
 *
 * Created on 1 août 2018, 18:08
 */

#ifndef ATTACKSET_HPP
#define ATTACKSET_HPP

#include <array>
#include "Attack.hpp"
#include "../../predicates/AttackPredicate.hpp"


class AttackSet {
public:
//===============// Constructor //===============//
    AttackSet();
    
    /**
     * Destructor
     */
    virtual ~AttackSet();
    
//===============// Public functions //===============//
    /**
     * @return true if the array is not full
     */
    bool hasPlaceLeft() const;
    
    /**
     * Add an attack to the array
     * @param attack a pointer to the new attack
     */
    void addAttack(Attack* attack);
    
    /**
     * Return a pointer to the attack at the given index
     * @param index index of the attack 
     * @return a pointer ti the attack
     */
    Attack* getAttack(int index);
    
    /**
     * Remove the attack at the given index
     * @param index index of the attack
     * @return a pointer to the removed attack
     * @warning the returned Attack is not removed !
     */
    Attack* removeAttack(int index);
    
    
    /**
     * Clear the AttackSet
     */
    void clear();
    
    /**
     * Returns the number of attacks stored in the array
     */
    int getNbAttacks() const;
    
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    virtual std::string getInfoString() const;
    
    
    /**
     * Replace one of the Attacks by a new one
     * @param index the index of the old attack
     * @param newAttack the AttackID of the new attack
     */
    void replaceAttack(int index, AttackID newAttack);
    
    
    /**
     * Chekc if the AttackSet contains an attack
     * @param id the AttackID of the Attack
     */
    bool contains(AttackID id);
    
    
    /**
     * Set the Attacks from an initializer list
     * @param attacksIDs an initializer list with 1 to 4 attacks
     */
    void setAttacks(std::initializer_list<AttackID> attackList);
    
    
    /**
     * Check if there is at least 1 attack that match the predicate
     * @param predicate the AttackPRedicate we want to check
     * @return true if at least 1 attack is 
     */
    bool hasAttackWhere(AttackPredicate predicate) const;
    
    /**
     * Get the attack indexes that match the predicate
     * @param predicate the AttackPRedicate we want to check
     * @return a vector of attack indexes
     */
    std::vector<int> getAttacksWhere(AttackPredicate predicate) const;
    
    
private:
//===============// Attributes //===============//
    // Nb of pointers in the array
    int m_nbAttacks;
    
    // Array of attacks
    std::array<Attack*, 4> m_attacks;
};

#endif /* ATTACKSET_HPP */

