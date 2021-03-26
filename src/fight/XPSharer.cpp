#include "XPSharer.hpp"
#include <iostream>

XPSharer::XPSharer() {

}



void XPSharer::addFaced(Pokemon* ennemy, Pokemon* ally) {
    std::cout << "Adding facing" << std::endl;
    
    // Check if this encounter is already in the map
    if(m_facedAllies.find(ennemy) != m_facedAllies.end()){
        // Get the range
        auto range = m_facedAllies.equal_range(ennemy);
        
        // Check if we find the ally
        for(auto it = range.first; it != range.second; it++)
            if(it->second == ally)
                return;
    }
    
    // Do not add the encounter if the ennemy i salready KO
    if(ennemy->isKO())
        return;
    
    // Add the encounter otherwise
    m_facedAllies.emplace(std::make_pair(ennemy, ally));
    
    std::cout << ennemy->getName().toAnsiString() << " facing : " << ally->getName().toAnsiString() << std::endl;
}



int XPSharer::getXPGivingEach(Pokemon* ennemy) {
    // Count the number of pokemons not KO
    int count(0);
    
    auto it_range = m_facedAllies.equal_range(ennemy);
    
    // Check each pokemon faced
    for(auto it = it_range.first; it != it_range.second; it++){
        if(!it->second->isKO())
            count++;
    }
    
    
    return ennemy->getExperiencePointsYield(false, false) / count;
}



std::queue<Pokemon*> XPSharer::getFacedNotKO(Pokemon* ennemy) {
    // Vector for the result
    std::queue<Pokemon*> faced;
    
    auto it_range = m_facedAllies.equal_range(ennemy);
    
    
    std::cout << ennemy->getName().toAnsiString() << " ennemy faced : ";
    // Check each pokemon faced
    for(auto it = it_range.first; it != it_range.second; it++){
        if(!it->second->isKO()){
            faced.push(it->second);
            std::cout << it->second->getName().toAnsiString() << "   ";
        }
    }
    
    std::cout << std::endl;
    
    return faced;
}
