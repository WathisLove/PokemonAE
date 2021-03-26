/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Type.hpp
 * Author: Redbuzard
 *
 * Created on 29 juillet 2018, 18:37
 */

#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>

class Type {
public:
//===============// Type Names //===============//
    enum TypeName{
        Normal,
        Fire,
        Water,
        Electric,
        Grass,
        Ice,
        Fighting,
        Poison,
        Ground,
        Flying,
        Psychic,
        Bug,
        Rock,
        Ghost,
        Dragon,
        Dark,
        Steel,
        Fairy,
        None        
    };
    
    /**
     * Return the TypeName as an int
     */
    static int typeNameToInt(TypeName t);
    
    // the type chart as a float array
    static float typeChart[18][18];
    
    
//===============// Constructors //===============//
    Type();
    Type(TypeName t1);
    Type(TypeName t1, TypeName t2);
    
    
//===============// Getters / Setters //===============//
    /**
     * @return the first type
     */
    TypeName getFirstType() const;
    
    /**
     * @return the second type
     */
    TypeName getSecondType() const;
    
    
    
//===============// Public Functions //===============//
    /**
     * @return true if the second type is not None
     */
    bool hasSecondType() const;
    
    /**
     * @param attacker the type of the offensive attack (only first type counts)
     * @param defender the type of the defending pokemon (both types count)
     * @return the damage multiplication as a float 
     */
    static float getDamageMultiplicator(Type attacker, Type defender);
    
    
    /**
     * Return the given typeName as a string
     */
    static std::string typeToString(TypeName tn);
    
    
    /**
     * Returns a string that can be used to display infos about the pokemon
     * @return a const reference to a string
     */
    std::string getInfoString() const;
    
    
    /**
     * Check if an attack is super efficient on a pokemon or not
     * @param receiverType the type of the receiver
     * @param attackType the type of the attack
     * @return true if the damage multiplicator is at least 2
     */
    static bool isSuperEfficient(Type receiverType, TypeName attackType);
    
    
    /**
     * Get the global efficiency of a type against an other
     * The result is different from getDemageMultiplicator as it take in account the two types of the attacker
     * A higher result means the attacker has a higher type advantage against the defender
     * @param attacker the Type of the Attacker
     * @param defender the Type of the Defender
     * @return the global efficiency of attacker against defender
     */
    static float getGlobalEfficiency(Type attacker, Type defender);
    
    
private:
    
//===============// Attributes //===============//
    TypeName m_firstType;
    
    TypeName m_secondType;
    
    
};

#endif /* TYPE_HPP */

