#ifndef POKEMONFIGHTDISPLAY_HPP
#define POKEMONFIGHTDISPLAY_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../../Enums.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "../../fight/PokemonDisplay.hpp"
#include "../../fight/FightPokemonBar.hpp"

class PokemonFightDisplay : public sf::Drawable{
public:
//===============// Constructor //===============// 
    PokemonFightDisplay(Context& context, Pokemon* p, Team team);
    
    
//===============// Public methods //===============// 
    /**
     * Overriden draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
    /**
     * Update the Display
     */
    void update();
    
    
//===============// Getters / Setters //===============// 
    
    /**
     * Set the displayed pokemon
     * @param p a pointer to the new pokemon
     */
    void setPokemon(Pokemon* p);
    
    
    /**
     * Set the position of the Display
     * @param pos the position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Set if the display is visible or not
     * @param val true if the display is visible
     */
    void setVisibility(bool val);
    
private:
    
//===============// Attributes //===============// 
    // A reference to the context
    Context& m_context;
    
    // A Pointer to the Pokemon displayed
    Pokemon* m_pokemon;
    
    // The actual team of the Pokemon : ennemy or ally
    Team m_team;
    
    // A boolean to know if the display is visible or not
    bool m_isVisible;
    
//===============// Graphical Attributes //===============// 
    // A Pokemon Display
    PokemonDisplay m_pokeDisplay;
    
    // The Fight Health bar
    FightPokemonBar m_healthBar;
};

#endif /* POKEMONFIGHTDISPLAY_HPP */

