#include "Stats.hpp"
#include "../Utilities.hpp"


Stats::Stats(int hp, int atk, int def, int spatk, int spdef, int speed) :
m_hp(hp),
m_attack(atk),
m_defense(def),
m_specialAttack(spatk),
m_specialDefense(spdef),
m_speed(speed){
    
}



int Stats::getStatValue(StatName stat) const {
    switch(stat){
        case StatName::health : return m_hp;
        case StatName::attack : return m_attack;
        case StatName::defense : return m_defense;
        case StatName::special_attack : return m_specialAttack;
        case StatName::special_defense : return m_specialDefense;
        case StatName::speed : return m_speed;
    }

    throw std::string("Requesting unknwon stat " + toString(static_cast<int>(stat)));
}



void Stats::setStatValue(StatName stat, int val) {
    switch(stat){
        case StatName::health : m_hp = val; 
        return;
        case StatName::attack : m_attack = val; 
        return;
        case StatName::defense : m_defense = val;
        return;
        case StatName::special_attack : m_specialAttack = val;
        return;
        case StatName::special_defense : m_specialDefense = val;
        return;
        case StatName::speed : m_speed = val;
        return;
    }
}



std::string Stats::getInfoString() const {
    std::string s;
    
    s += "HP  : " + toString<int>(m_hp) + "\n";
    s += "Atk : " + toString<int>(m_attack) + "   |   " + "Def : " + toString<int>(m_defense) + "\n";
    s += "S.A : " + toString<int>(m_specialAttack) + "   |   " + "S.D : " + toString<int>(m_specialDefense) + "\n";
    s += "Spd  : " + toString<int>(m_speed) + "\n";
    
    return s;
}
