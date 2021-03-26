#ifndef NAMECHOOSER_HPP
#define NAMECHOOSER_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../../pokemons/PokemonID.hpp"

class NameChooser : public sf::Drawable{
public:
//=================// Constructors //==================//
    
    NameChooser(Context& context);
    
//=================// Inherited methods //==================//
    
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
//=================// Public methods //==================//
    
    
    /**
     * Handle an event
     * @param event a reference to the Event
     */
    void handleEvent(sf::Event& event);
    
    
    
    /**
     * Display the Character
     */
    void displayCharacter();
    
    /**
     * Set the Displayed Pokemon
     * @param pokemon the Pokemon ID
     */
    void displayPokemon(PokemonID pokemon);
    
    
//=================// Getter //==================//
    
    /**
     * Get the string currently displayed
     * @return the string that is currently displayed
     */
    const sf::String& getString();
    
    
private:
//=================// Private methods //==================//
    
    /**
     * Removes the last character 
     */
    void removeCharacter();
    
    /**
     * Called when a TextEntered events appears
     * @param key the Key pressed on the keyboard
     */
    void addCharacter(sf::Uint32 key);
    
    
    /**
     * Check if there is place for another character
     * @return true if we can add a character
     */
    bool canAddCharacter() const;
    
    /**
     * Setup the Text
     */
    void setupText();
    
//=================// Graphical Attributes //==================//

    // A reference to the context
    Context& m_context;
    
    // Sprite Background
    sf::Sprite m_background;
    
    // The text for the current name
    sf::Text m_currentName;
    
    // The Sprite displayed
    sf::Sprite m_miniDisplay;
};

#endif /* NAMECHOOSER_HPP */

