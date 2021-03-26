#ifndef POKEMONSTATGRAPH_HPP
#define POKEMONSTATGRAPH_HPP

#include <SFML/Graphics.hpp>
#include "../../pokemons/Stats.hpp"
#include "../../Context.hpp"

class PokemonStatGraph : public sf::Drawable{
    
public:
    
//===============// Constructor //===============//
    
    PokemonStatGraph(Context& context, const Stats& stats);
    
    
//===============// Public Inherited methods //===============//
    
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//===============// Public setters//===============//
    
    
    /**
     * Set the Graph according to the given stats
     * @param stats a const reference to the pokemon stats
     */
    void setStats(const Stats& stats);
    
    
    /**
     * Set the position of the center of the graph 
     * @param position the position as a Vector2
     */
    void setPosition(sf::Vector2f position);
    
    
    /**
     * Set the graph color
     * @param color the color as a sf::Color
     */
    void setColor(sf::Color color);
    
    
    
    /**
     * Get the direction vector given by index
     * @param index the index of the vector (from 0 to 5)
     * @return the direction as a Vector2f
     */
    static sf::Vector2f getDirectionVector(int index);
    
    
private:
    
//===============// Static Attributes //===============//
    
    const static float MAX_HEALTH;
    const static float MAX_STAT;


    // Minimum distance of each point to the center
    const static float minDist;

    // Max length of each stats branch
    const static float maxL;
    
//===============// Attributes //===============//
    
    // A vertex array used to draw the graph
    sf::VertexArray m_array;
    
    // The Graph background
    sf::Sprite m_background;

};

#endif /* POKEMONSTATGRAPH_HPP */

