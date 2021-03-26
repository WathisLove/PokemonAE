#include "CollisionLayer.hpp"

#include <string>
#include <fstream>
#include <exception>
#include <sstream>


// Value of collision tiles
const int CollisionLayer::collisionTile(2490);

// Value of water tiles
const int CollisionLayer::waterTile(2492);

// Value of wild grass tiles
const int CollisionLayer::wildGrassTile(2493);

// Jump values
const int CollisionLayer::jumpUp(2504);
const int CollisionLayer::jumpRight(2505);
const int CollisionLayer::jumpDown(2506);
const int CollisionLayer::jumpLeft(2507);



CollisionLayer::CollisionLayer(const std::string& layerPath) {
    loadLayerFromFile(layerPath);
}



bool CollisionLayer::canSurfOnCase(sf::Vector2i index) {
    int caseValue = getCaseValue(index);
    
    return (caseValue == waterTile); // CONSTANTS
}



bool CollisionLayer::canJumpOver(sf::Vector2i index, Direction dir) {
    // Case value
    int value = getCaseValue(index);
    
    // Check the case according ti the direction
    switch(dir){
        case Direction::North:
            return value == jumpUp;
        case Direction::East:
            return value == jumpRight;
        case Direction::South:
            return value == jumpDown;
        case Direction::West:
            return value == jumpLeft;
    };
    
    // Else
    return false;
}



bool CollisionLayer::canEncounterPokemon(sf::Vector2i index) {
    int caseValue = getCaseValue(index);
    
    return (caseValue == wildGrassTile);
}



bool CollisionLayer::canWalkOnCase(sf::Vector2i index) {
    int caseValue = getCaseValue(index);
    
    return (caseValue == -1 || caseValue == wildGrassTile);
}



void CollisionLayer::loadLayerFromFile(const std::string& layerPath) {

    // File stream
    std::ifstream mapFile(layerPath.c_str());
    
    // Unabled to open file
    if(!mapFile)
    {
        throw std::string("Can't open mapFile " + layerPath);
    }
    
    // Read the file line by line
    std::string line;
    while(std::getline(mapFile, line))
    {
        // Add the converted lines to the vector array
        m_cases.push_back(loadLineFromString(line));
    }
    
    // Set size of the zone
    m_zoneSize = sf::Vector2i(m_cases[0].size(), m_cases.size());
}



std::vector<int> CollisionLayer::loadLineFromString(const std::string& string) {

    // Contain the caseValues
    std::vector<int> line;
    int caseValue; // Case buffer
    
    // Separator buffer
    char separator;
    bool hasSeperator;
    
    // String iterators, used to read values from the string
    std::stringstream stringReader;
    stringReader.str(string);
    
    // While we didn't reach end of line
    do
    {
        // Get a single caseValue
        stringReader >> caseValue;
        line.push_back(caseValue);
        
        // Read the separator, and check it is the end of the line
        stringReader >> separator;
        
    }while(!stringReader.eof());
    
    return line;
}



int CollisionLayer::getCaseValue(sf::Vector2i index) const {
    return (m_cases.at(index.y)).at(index.x); // y is before x : [line][column]
}
