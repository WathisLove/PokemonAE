#ifndef UIBOXSTATE_HPP
#define UIBOXSTATE_HPP

#include <SFML/Graphics.hpp>

#include "../../Context.hpp"
#include "../../entities/Character.h"
#include "../../ui/pokemon/PokemonMiniDisplay.hpp"
#include "../../ui/ChoiceMenu.hpp"
#include "../../ui/tools/CenteredText.hpp"

class UIBoxState : public sf::Drawable{
public:
//==================// Constructor //=============//
    
    /**
     * Constructor with the context and the character
     */
    UIBoxState(Context& context, Character* character);
    
    
//==================// Inherited methods //=============//
    
    
    /**
     * Overriden function
     */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//==================// Public Methods //=============//
    
    
    /**
     * Check if the menu is open
     * @return true if the menu is open
     */
    bool isMenuOpen();
    
    
//==================// Setters //=============//
    
    /**
     * Set the UI to display a specific box
     * @param boxNumber the box number as an int
     */
    void setBox(int boxNumber);
    
    
    /**
     * Set the UI to display a pokemon team
     * @param team a reference to the pokemon team
     */
    void setTeam(PokemonTeam& team);
    
    
    /**
     * Set the UI position
     * @param pos the top left position as a Vector2f
     */
    void setPosition(sf::Vector2f pos);
    
    
    /**
     * Select a pokemon
     * @param id the pokemon id to display
     */
    void selectPokemon(PokemonID id);
    
    /**
     * Unselect the pokemon
     */
    void unselectPokemon();
    
    
    /**
     * Set the cursor position in the UI
     * @param pos the position in the team or box as an int
     * @param inTeam true if the cursor is on the team, false otherwise
     */
    void setCursorPosition(int pos, bool inTeam);
    
    /**
     * Choose wether or not we must show the menu
     * @param show true if we must show the menu
     */
    void showMenu(bool show);
    
    
    /**
     * Choose wether or not we must show the cursor
     * @param show true if we must show the cursor
     */
    void showCursor(bool show);
    
    
    /**
     * Show the title cursor or not
     * @param show true if we must show the cursor
     */
    void showTitleCursor(bool show);
    
    /**
     * Get the menu
     * @return a reference to the ChoiceMenu
     */
    ChoiceMenu& getMenu();
    
    
private:
//==================// Private methods //=============//
    
    /**
     * Set the box displays UI position
     * @param offset the top left position of the first pokemon as a Vector2f
     */
    void setBoxPosition(sf::Vector2f offset);
    
    /**
     * Set the team displays position
     * @param offset the top left position of the first pokemon as a Vector2f
     */
    void setTeamPosition(sf::Vector2f offset);
    
    
    /**
     * Setup the pokemon mini displays
     */
    void setupPokemonDisplays();
    
    
    /**
     * Set the menu entries when hoverring the team
     */
    void setInTeamEntries();
    
    /**
     * Set the menu entries when hoverring the box
     */
    void setInBoxEntries();
    
//==================// Attributes //=============//
    
    // A reference to the context for graphical uses
    Context& m_context;
    
    // A pointer to the character
    Character* m_character;
    
    // A reference to the box system
    BoxSystem& m_boxes;
    
    // Show the cursor or not
    bool m_showCursor;
    
    // Show the title or not
    bool m_showTitleCursor;
    
//==================// Graphical Attributes //=============//
    
    // Background Sprite
    sf::Sprite m_background;
    
    // Pokemon cursor
    sf::Sprite m_cursor;
    
    // Title cursor
    sf::Sprite m_titleCursor;
    
    // Text for the box title
    CenteredText m_boxTitle;
    
    // Choice menu
    ChoiceMenu m_menu;
    
    // Disply for the selected pokemon
    PokemonMiniDisplay* m_selectedPokemon;
    
    // An array of 36 pokemons display for the box
    std::array<PokemonMiniDisplay*, 36> m_boxDisplays;
    
    // An array of 6 pokemons display for the team
    std::array<PokemonMiniDisplay*, 6> m_teamDisplays;
};

#endif /* UIBOXSTATE_HPP */

