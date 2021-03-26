#include "PokemonStatGraph.hpp"

#include <cmath>
#include <complex>

#include <iostream>

const float PokemonStatGraph::MAX_HEALTH = 715.;
const float PokemonStatGraph::MAX_STAT = 615.;
    

// Minimum distance of each point to the center
const float PokemonStatGraph::minDist = 10.;

// Max length of each stats branch
const float PokemonStatGraph::maxL = 90.;
    


PokemonStatGraph::PokemonStatGraph(Context& context, const Stats& stats) :
m_array(sf::TriangleFan, 8){
    
    setColor(sf::Color(0, 240, 150));
    
    // Set the position of the center
    m_array[0].position = sf::Vector2f(0,0);
    
    setStats(stats);
}



void PokemonStatGraph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_array, states);
}



void PokemonStatGraph::setStats(const Stats& stats) {
    // Get the center of the graph
    sf::Vector2f basePos = m_array[0].position;
    
    // Set each of the Graph Points
    
    m_array[1].position = basePos + (minDist + maxL * stats.getStatValue(health) / MAX_HEALTH) * getDirectionVector(0);
    m_array[7].position = m_array[1].position;
    
    m_array[2].position = basePos + (minDist + maxL * stats.getStatValue(attack) / MAX_STAT) * getDirectionVector(1);
    
    m_array[3].position = basePos + (minDist + maxL * stats.getStatValue(defense) / MAX_STAT) * getDirectionVector(2);
    
    m_array[4].position = basePos + (minDist + maxL * stats.getStatValue(speed) / MAX_STAT) * getDirectionVector(3);
    
    m_array[5].position = basePos + (minDist + maxL * stats.getStatValue(special_defense) / MAX_STAT) * getDirectionVector(4);
    
    m_array[6].position = basePos + (minDist + maxL * stats.getStatValue(special_attack) / MAX_STAT) * getDirectionVector(5);
}



void PokemonStatGraph::setPosition(sf::Vector2f position) {
    // Get the position offset relative to the graph center
    sf::Vector2f dPos = position - m_array[0].position;
    
    // Set the position offset for each of the vertex
    for(int i = 0; i < m_array.getVertexCount(); i++){
        m_array[i].position += dPos;
    }
}



void PokemonStatGraph::setColor(sf::Color color) {
    for(int i = 0; i < m_array.getVertexCount(); i++){
        m_array[i].color = color;
    }
}



sf::Vector2f PokemonStatGraph::getDirectionVector(int index) {
    
    // Map index to be between 0 and 5
    int finalNum = index % 6;
    
    if(finalNum == 0)
        return sf::Vector2f(0, -1);
    else if (finalNum == 1)
        return sf::Vector2f(std::sqrt(3.)/2., -1/2.);
    else if (finalNum == 2)
        return sf::Vector2f(std::sqrt(3.)/2., 1/2.);
    else if (finalNum == 3)
        return sf::Vector2f(0, 1);
    else if (finalNum == 4)
        return sf::Vector2f(-std::sqrt(3.)/2., 1/2.);
    else if (finalNum == 5)
        return sf::Vector2f(-std::sqrt(3.)/2., -1/2.);
}
