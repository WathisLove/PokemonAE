#include "IVSet.hpp"

#include <cassert>
#include <algorithm>
#include <iostream>


//===================// Operator //===================//


std::ostream& operator<<(std::ostream &flux, IVSet const& set )
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

const unsigned int IVSet::maxIvValue = 31;


IVSet::IVSet() {
    // Create each stat with a random value
    m_values.emplace(StatName::health,          randomInt(0, maxIvValue));
    m_values.emplace(StatName::attack,          randomInt(0, maxIvValue));
    m_values.emplace(StatName::special_attack,  randomInt(0, maxIvValue));
    m_values.emplace(StatName::defense,         randomInt(0, maxIvValue));
    m_values.emplace(StatName::special_defense, randomInt(0, maxIvValue));
    m_values.emplace(StatName::speed,           randomInt(0, maxIvValue));
}



IVSet::IVSet(const IVSet& set1, const IVSet& set2) {
    // Mergea each statistic
    m_values.emplace(StatName::health,          mergeIV(set1.getValue(StatName::health),            set2.getValue(StatName::health)));
    m_values.emplace(StatName::attack,          mergeIV(set1.getValue(StatName::attack),            set2.getValue(StatName::attack)));
    m_values.emplace(StatName::special_attack,  mergeIV(set1.getValue(StatName::special_attack),    set2.getValue(StatName::special_attack)));
    m_values.emplace(StatName::defense,         mergeIV(set1.getValue(StatName::defense),           set2.getValue(StatName::defense)));
    m_values.emplace(StatName::special_defense, mergeIV(set1.getValue(StatName::special_defense),   set2.getValue(StatName::special_defense)));
    m_values.emplace(StatName::speed,           mergeIV(set1.getValue(StatName::speed),             set2.getValue(StatName::speed)));
}



IVSet::IVSet(std::initializer_list<unsigned int> list) {
    // Check that the list is 6 elements long
    assert(list.size() == 6);
    
    // Get an iterator to the first element
    std::initializer_list<unsigned int>::iterator it = list.begin();
    
    // Add each IV and cap them between 0 and 31
    m_values.emplace(health, limit(*it++, 0u, maxIvValue));
    m_values.emplace(attack, limit(*it++, 0u, maxIvValue));
    m_values.emplace(defense, limit(*it++, 0u, maxIvValue));
    m_values.emplace(special_attack, limit(*it++, 0u, maxIvValue));
    m_values.emplace(special_defense, limit(*it++, 0u, maxIvValue));
    m_values.emplace(speed, limit(*it++, 0u, maxIvValue));
}



void IVSet::add(StatName stat, unsigned int value) {
    // Check that the stat is not at the maximum value
    assert(!isMax(stat));
    
    // Add the value
    m_values.at(stat) += value;
}



bool IVSet::isMax(StatName stat) const{
    return getValue(stat) == maxIvValue;
}



std::string IVSet::toString() const {
    std::ostringstream stream;
    
    stream << *this;
    
    return stream.str();
}



void IVSet::setMaxValues() {
    for(auto it : m_values){
        it.second = maxIvValue;
    }
}



int IVSet::getValue(StatName stat) const{
    // Check the stat is in the map
    assert(m_values.find(stat) != m_values.end());
    
    // Return the value
    return m_values.at(stat);
}



int IVSet::mergeIV(unsigned int v1, unsigned int v2) {
    // Get the mean
    unsigned int mean = (v1 + v2)/2;
    
    // Get the max and min value
    unsigned int max = std::max(v1, v2);
    unsigned int min = std::min(v1, v2);
    
    // Calculate the result
    // It starts from mean, and we add a value from (-min to +max)/6 to help increasing IV by breeding
    return std::max(mean + randomInt(-min, max)/6, maxIvValue);
}
