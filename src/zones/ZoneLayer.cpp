#include "ZoneLayer.hpp"
#include "Zone.hpp"
#include "../Constants.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <sstream>

// Set the constants of the ZoneLayer Class
sf::Vector2i ZoneLayer::tileSize = sf::Vector2i(16, 16); // Size of a single tile



ZoneLayer::ZoneLayer(const string& layerPath, const sf::Texture& texture) : 
Drawable(),
m_vertices(sf::Quads),
m_tilesetTexture(texture)
{
    loadLayerFromFile(layerPath);
    loadVertexArray();
    
    // Store the map Size
    m_zoneSize = sf::Vector2i((m_cases[0]).size(), m_cases.size());
}



void ZoneLayer::loadLayerFromFile(const std::string& layerPath) {

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



std::vector<int> ZoneLayer::loadLineFromString(const std::string& string) {

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



void ZoneLayer::loadVertexArray() {    
    //Resize VertexArray to contain all the Quads
    m_vertices.resize(m_zoneSize.x * m_zoneSize.y * 4);
    
    
    //Load each Quad
    for(unsigned int y = 0; y < m_zoneSize.y; y++)
        for(unsigned int x = 0; x < m_zoneSize.x; x++)
        {
            sf::Vertex* quad = &m_vertices[(x + y * m_zoneSize.x) * 4];
            // Get the case value
            int caseValue = getCaseValue(sf::Vector2i(x, y));
            if(caseValue != -1)
                loadQuad(quad, sf::Vector2i(x, y), caseValue);
        }
}


void ZoneLayer::loadQuad(sf::Vertex* quad, sf::Vector2i caseNumber, int caseValue)
{    
    unsigned int x = caseNumber.x;
    unsigned int y = caseNumber.y;
    
    sf::Vector2i tileSetSize(m_tilesetTexture.getSize().x/tileSize.x, m_tilesetTexture.getSize().y/tileSize.y);
    
    // Case Top Right position
    sf::Vector2f quadPosition(GAME_ZOOM*x*tileSize.x, GAME_ZOOM*y*tileSize.y);

    
    quad[0].position = quadPosition;
    quad[1].position = quadPosition + sf::Vector2f(GAME_ZOOM*tileSize.x, 0.f);
    quad[2].position = quadPosition + sf::Vector2f(GAME_ZOOM*tileSize.x, GAME_ZOOM*tileSize.y);
    quad[3].position = quadPosition + sf::Vector2f(0.f, GAME_ZOOM*tileSize.y);

    // Top Right Pixel of the corresponding coordinates
    sf::Vector2f texturePosition((int)((caseValue%tileSetSize.x) * (tileSize.x)), 
                                 (int)((caseValue/tileSetSize.x) * (tileSize.y)));
    
    quad[0].texCoords = texturePosition;
    quad[1].texCoords = texturePosition + sf::Vector2f(tileSize.x, 0.f);
    quad[2].texCoords = texturePosition + sf::Vector2f(tileSize.x, tileSize.y);
    quad[3].texCoords = texturePosition + sf::Vector2f(0.f, tileSize.y);
}



int ZoneLayer::getCaseValue(sf::Vector2i index) const {
    return (m_cases.at(index.y)).at(index.x); // y is before x : [line][column]
}



sf::Vector2i ZoneLayer::getLayerSize() const {
    return m_zoneSize;
}



void ZoneLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // Apply texture
    states.texture = &m_tilesetTexture;

    // Draw the VertexArray
    target.draw(m_vertices, states);
}
