#ifndef UITEAMINFOSTATE_HPP
#define UITEAMINFOSTATE_HPP

#include "UIPokemonInfo.hpp"
#include "../../pokemons/PokemonTeam.hpp"
#include "../../pokemons/teamPreview/TeamPreview.hpp"

/**
 * A Pokemon Info State with a display for the Team
 */
class UITeamInfoState : public UIPokemonInfo{
public:
//==================// Constructor //=============//
    
    UITeamInfoState(Context& context, PokemonTeam* team);
    
    
//==================// Public Functions //=============//
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//==================// Getters / Setters //=============//
    
    /**
     * Set the position of the graphical elements relative to the given position
     * @param pos the position of the topLeft corner
     */
    void setPosition(sf::Vector2f pos);
    
    /**
     * Set the current pokemon to display
     * @param pokemonIndex the index of the pokemon in the team as an int
     */
    void setCurrentPokemon(int pokemonIndex);
    
private:
//==================// Attributes //=============//

    // A pointer to the Character's team
    PokemonTeam* m_team;
    
    // The current pokemon displayed
    int m_currentPokemon;
    
//==================// Graphical attributes //=============//
    
    // Team Display
    TeamPreview m_teamDisplay;
};

#endif /* UITEAMINFOSTATE_HPP */

