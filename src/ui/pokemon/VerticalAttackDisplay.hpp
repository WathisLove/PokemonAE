#ifndef VERTICALATTACKDISPLAY_HPP
#define VERTICALATTACKDISPLAY_HPP

#include "../../Context.hpp"
#include "../../pokemons/Pokemon.hpp"
#include "../../pokemons/attacks/AttackDisplay.hpp"
#include <iostream>


class VerticalAttackDisplay : public sf::Drawable{
public:
    VerticalAttackDisplay(Context& context, Pokemon* p);
    
    
//===============// Public Inherited methods //===============//
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    
//===============// Public Methods //===============//
    
    
    /**
     * Set all attacks to a grey color except a single one
     * @param index the index of the attack we want to show
     */
    void setGreyExcept(int index);
    
    /**
     * Set all attacks to be displayed normally
     */
    void removeGreyColors();
    
    
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
    
    /**
     * Selects the next Attack
     */
    void selectNext();
    
    /**
     * Selects the previous attack
     */
    void selectPrevious();
    
    /**
     * Get the attack selected
     * @return the attack index as an int
     */
    int getSelected() const;
    
private:
//===============// Attributes //===============//
    
    // The top left positon of the AttackDisplays
    sf::Vector2f m_pos;
    
    
//===============// Graphical Attributes //===============//
    // A reference to the context when updated
    Context& m_context;
    
    // A vector containing the attack displays
    std::vector<AttackDisplay> m_attackDisplays;
    
    // Current Attack selected
    int m_currentSelected;
    
};

#endif /* VERTICALATTACKDISPLAY_HPP */

