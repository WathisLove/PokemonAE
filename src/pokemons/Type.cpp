#include <cmath>
#include "Type.hpp"
#include "../Utilities.hpp"
#include "../utility/Logger.hpp"

// Set the TypeChart
float Type::typeChart[18][18] = 
{   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 0.5, 1},
    {1, 0.5, 0.5, 1, 2, 2, 1, 1, 1, 1, 1, 2, 0.5, 1, 0.5, 1, 2, 1},
    {1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 1, 1},
    {1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 2, 1, 1, 1, 1, 0.5, 1, 1, 1},
    {1, 0.5, 2, 1, 0.5, 1, 1, 0.5, 2, 0.5, 1, 0.5, 2, 1, 0.5, 1, 0.5, 1},
    {1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 0.5, 1},
    {2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 0.5},
    {1, 1, 1, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 0, 2},
    {1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1},
    {1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1},
    {1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1},
    {1, 0.5, 1, 1, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 1, 2, 0.5, 0.5},
    {1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 0.5, 1},
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0},
    {1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5},
    {1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2},
    {1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}
};



int Type::typeNameToInt(TypeName t) {
    return (int)t;
}


Type::Type() :
m_firstType(TypeName::None),
m_secondType(TypeName::None){

}


Type::Type(TypeName t1) :
m_firstType(t1),
m_secondType(TypeName::None){
    
}



Type::Type(TypeName t1, TypeName t2) :
m_firstType(t1),
m_secondType(t2){
    
}



Type::TypeName Type::getFirstType() const {
    return m_firstType;
}



Type::TypeName Type::getSecondType() const {
    return m_secondType;
}



bool Type::hasSecondType() const {
    return m_secondType != TypeName::None;
}



float Type::getDamageMultiplicator(Type attacker, Type defender) {
    // If the defender has a second type, use it in calculation
    if(defender.hasSecondType()){
        int atkInt = typeNameToInt(attacker.getFirstType());
        int defInt1 = typeNameToInt(defender.getFirstType());
        int defInt2 = typeNameToInt(defender.getSecondType());
        
        return typeChart[atkInt][defInt1] * typeChart[atkInt][defInt2];
    }
    else{
        int atkInt = typeNameToInt(attacker.getFirstType());
        int defInt1 = typeNameToInt(defender.getFirstType());
        
        return typeChart[atkInt][defInt1];
    }
}



std::string Type::typeToString(TypeName tn) {
    switch(tn){
        case TypeName::Bug: return "Bug";
        case TypeName::Dark: return "Dark";
        case TypeName::Dragon: return "Dragon";
        case TypeName::Electric: return "Electric";
        case TypeName::Fairy: return "Fairy";
        case TypeName::Fighting: return "Fighting";
        case TypeName::Fire: return "Fire";
        case TypeName::Flying: return "Flying";
        case TypeName::Ghost: return "Ghost";
        case TypeName::Grass: return "Grass";
        case TypeName::Ground: return "Ground";
        case TypeName::Ice: return "Ice";
        case TypeName::None: return "NONE";
        case TypeName::Normal: return "Normal";
        case TypeName::Poison: return "Poison";
        case TypeName::Psychic: return "Psychic";
        case TypeName::Rock: return "Rock";
        case TypeName::Steel: return "Steel";
        case TypeName::Water: return "Water";
    }

    Log("Unknown type requested " + toString(static_cast<int>(tn)));
    return "Water";
}



std::string Type::getInfoString() const {
    if(m_firstType == TypeName::None) return "NONE";
    
    if(m_secondType == TypeName::None) return typeToString(m_firstType);
    
    return typeToString(m_firstType) + " | " + typeToString(m_secondType);
}



bool Type::isSuperEfficient(Type receiverType, TypeName attackType) {
    return getDamageMultiplicator(Type(attackType), receiverType);
}



float Type::getGlobalEfficiency(Type attacker, Type defender){
    // If the Attacker has two types
    if(attacker.hasSecondType()){
        // Get the Damage multiplication of the two types
        float mul1 = getDamageMultiplicator(Type(attacker.getFirstType()), defender);
        float mul2 = getDamageMultiplicator(Type(attacker.getSecondType()), defender);
        
        // Return the maximum of the two multiplicator, as the attacker will probably use the attacks with the highest efficiency
        return std::max(mul1, mul2);
    }
    else
        return getDamageMultiplicator(attacker, defender);
}