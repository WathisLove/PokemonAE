#ifndef STATDISPLAY_HPP
#define STATDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <array>

#include "../../Context.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "PokemonStatGraph.hpp"
#include "../tools/CenteredText.hpp"

class StatDisplay : public sf::Drawable{
public:
    
    StatDisplay(Context& context, Pokemon* p);
    
//===============// Public Inherited methods //===============//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
//===============// Getters / Setters //===============//
    
    /**
     * Set the new pokemon to display its stats
     * @param p a pointer to the new pokemon
     */
    void setPokemon(Pokemon* p);
    
    /**
     * Set the position of the graphical attributes
     * @param pos the position of the topLeft corner as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
private:
    
//===============// private methods //===============//
    
    /**
     * Setup the different texts
     */
    void setupTexts(Context& context);
    
    
    /**
     * Get the Vector director to one of the number Display
     * @param statNum the stat number
     * @return the vector director as a Vector2f
     */
    sf::Vector2f getNumDirectionVector(int statNum);
    
//===============// Graphical Attributes //===============//
    
    // A static int corresponding to the distance to the text
    const static float m_textValueDistance;
    const static float m_textNameDistance;
    
    
    // An array containing the text for the stat names
    std::array<CenteredText, 6> m_statNames;
    
    // An array containing the text for the stat values
    std::array<CenteredText, 6> m_statValues;
    
    // A Stat graph
    PokemonStatGraph m_statGraph;
};

#endif /* STATDISPLAY_HPP */

