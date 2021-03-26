/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneLayer.hpp
 * Author: Redbuzard
 *
 * Created on 17 juin 2018, 15:28
 */

#ifndef ZONELAYER_HPP
#define ZONELAYER_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;


class ZoneLayer : public sf::Drawable{
    
public:
//===============// Constants //===============//
    static sf::Vector2i tileSize; // Size of a single tile
    
    
//===============// Public Methods //===============//
    
    /**
     * Construct a LayerZone
     * @param layerPath is the path to the .csv file that contains the cases
     * @param texture is the tileSet texture
     */
    ZoneLayer(const string& layerPath, const sf::Texture& texture);
    
    
    /**
     * Load a LayerZone from the disk
     * @param layerPath is the path to the .csv file that contains the cases
     */
    void loadLayerFromFile(const std::string& layerPath);
    
    
    /**
     * Get the size of the Layer
     * @return the size as a Vector2i
     */
    sf::Vector2i getLayerSize() const;
    
    /**
     * Return the value stored in the case at index
     * @param index of the case
     */
    int getCaseValue(sf::Vector2i index) const;
    
    
    /**
     * Inherited draw function, used to render the VertexArray
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    

private:
    
//===============// Private methods //===============//
    /**
     * Load the Vertex array according to the tileset texture
     * and the 2D vector m_cases
     */
    void loadVertexArray();
    
    
    /**
     * Load a single quad that represents a game case
     * Called by the loadVertexArray function
     * @param quad Quad that is changed by the function
     * @param casePosition coords of the case in the grid
     * @param caseValue value of the case in the grid
     */
    void loadQuad(sf::Vertex* quad, sf::Vector2i casePosition, int caseValue);
    
    
    /**
     * Load a line of the .csv file and convert it into a vector
     * @param str String that contains a line of the map
     * @return vector<int> that contains all the cases of the line
     */
    std::vector<int> loadLineFromString(const std::string& string);
    
    
    
//===============// Attributes //===============//
    // Vertex array that contains all the cases
    sf::VertexArray m_vertices;
    
    // Texture of the Tile set
    const sf::Texture& m_tilesetTexture;
    
    // 2D array that stocks the values of the cases
    // First vector is the line, the second one give the case
    // PAY ATTENTION : m_cases[x][y] returns the case at line x, column y
    std::vector<std::vector<int> > m_cases;

    // Store the MapSize
    sf::Vector2i m_zoneSize;

};

#endif /* ZONELAYER_HPP */

