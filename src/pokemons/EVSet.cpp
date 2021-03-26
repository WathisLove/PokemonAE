#include "EVSet.hpp"

#include <cassert>
#include <algorithm>
#include <sstream>


//===================// Operator //===================//


std::ostream& operator<<(std::ostream &flux, EVSet const& set )
{
    std::string str;
    
    // Add the values
    str += " H : " + toString(set.getValue(health)) +  + " | A  : " + toString(set.getValue(attack))
        + " | D  : " + toString(set.getValue(defense)) + " | SA : " + toString(set.getValue(special_attack)) 
        + " | SD : " + toString(set.getValue(special_defense)) + " | V : " + toString(set.getValue(speed)) + "\n";
    
    flux << str;
    
    return flux;
}



//===================// Class //===================//


const unsigned int EVSet::maxEvValue = 252;
const unsigned int EVSet::maxTotalEv = 510;


EVSet::EVSet() {
    // Create each stat starting at 0
    m_values.emplace(StatName::health,          0);
    m_values.emplace(StatName::attack,          0);
    m_values.emplace(StatName::special_attack,  0);
    m_values.emplace(StatName::defense,         0);
    m_values.emplace(StatName::special_defense, 0);
    m_values.emplace(StatName::speed,           0);
}



EVSet::EVSet(std::initializer_list<unsigned int> list) {
    // Check that the list is 6 elements long
    assert(list.size() == 6);
    
    // Get an iterator to the first element
    std::initializer_list<unsigned int>::iterator it = list.begin();
    
    // Add each IV and cap them between 0 and 31
    m_values.emplace(health, limit(*it++, 0u, maxEvValue));
    m_values.emplace(attack, limit(*it++, 0u, maxEvValue));
    m_values.emplace(defense, limit(*it++, 0u, maxEvValue));
    m_values.emplace(special_attack, limit(*it++, 0u, maxEvValue));
    m_values.emplace(special_defense, limit(*it++, 0u, maxEvValue));
    m_values.emplace(speed, limit(*it++, 0u, maxEvValue));
}



void EVSet::add(StatName stat, unsigned int value) {
    assert(canIncrease(stat));
    
    // Get the points we can add to this stat
    unsigned int pointsLeft = std::min(maxTotalEv - getTotal(), maxEvValue - m_values.at(stat));
    
    // Increase the EV value
    m_values.at(stat) += std::min(value, pointsLeft);
}



bool EVSet::isMax(StatName stat) const {
    return m_values.at(stat) == maxEvValue;
}



bool EVSet::canIncrease(StatName stat) const{
    // Check the stat is not max, and the total sum was not reached
    return m_values.at(stat) < maxEvValue && getTotal() < maxTotalEv;
}



void EVSet::setMaxValue(StatName stat) {
    m_values.at(stat) = maxEvValue;
}



unsigned int EVSet::getValue(StatName stat) const {
    return m_values.at(stat);
}



std::string EVSet::toString() const {
    std::ostringstream stream;
    
    stream << *this;
    
    return stream.str();
}



unsigned int EVSet::getTotal() const {
    unsigned int sum(0);
    
    for(auto it : m_values){
        sum += it.second;
    }
    
    return sum;
}
