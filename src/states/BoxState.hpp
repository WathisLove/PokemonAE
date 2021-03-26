#ifndef BOXSTATE_HPP
#define BOXSTATE_HPP

#include "State.hpp"
#include "../ui/states/UIBoxState.hpp"

class BoxState : public State{
public:
//==================// Constructor //=============//
    
    /**
     * Constructor with the Stack and the character
     */
    BoxState(StateStack* stack, Character* character);
    
    
//=================// Public Inherited functions //==================//
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    void actionOnCompletion();

    /**
     * Draw the state
     */
    void draw();

    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    bool handleEvent(sf::Event& event);
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    bool update(float dt);
    
    
//==================// Getters / Setters //=============//
    
    /**
     * Get the current box
     * @return the current box as a PokemonBox pointer
     */
    PokemonBox* getCurrentBox();
    
    
    /**
     * Return the index of the selected pokemon
     * @return the index of the pokemon as an int
     */
    int getPokemonIndexSelected();
    
    
    /**
     * Set the selected pokemon
     * @param index the pokemon index in the box or the team as an int
     */
    void setSelectedPokemon(int index);
    
private:
//=================// Private methods //==================//
    
    
    /**
     * Update the UI after a change in the Team or the box 
     */
    void updateUI();
    
    
//=================// Cursor methods //==================//
    
    /**
     * Check if the cursor is on a pokemon 
     * @return true if the cursor is on a pokemon
     */
    bool cursorOnPokemon();
    
    
    /**
     * Try to move the cursor according to a key pressed
     * @param key the key pressed 
     */
    void moveCursor(sf::Keyboard::Key keyPressed);
    
    
    /**
     * Move the cursor to the right
     */
    void moveRight();   
    
    /**
     * Move the cursor to the left
     */
    void moveLeft();   
    
    /**
     * Move up the cursor 
     */
    void moveUp();   
    
    /**
     * Move down the cursor 
     */
    void moveDown();
    
    
    /**
     * Set the UI cursor position
     */
    void setUICursor();
    
    
    /**
     * Get the maximum index that can be selected in the team
     * @return the max index as an int
     */
    int getTeamMaxSelection();
    
//=================// Menu actions //==================//
    
    /**
     * Select an entry in the menu and act according to it
     */
    void selectMenu();
    
    
    /**
     * Send the selected pokemon to the box
     */
    void sendToBox();
    
    /**
     * Send the selected pokemon to the team
     */
    void sendToTeam();
    
    /**
     * Select the pokemo to move it
     */
    void movePokemon();
    
    /**
     * Open the pokemon infos
     */
    void openPokemonInfos();
    
    
    
//=================// Pokemon Move Actions //==================//
    
    /**
     * Try to drop the pokemon selected
     * Switches it with the already present one if there is one
     */
    void dropPokemon();
    
    /**
     * Switch the selected pokemon with the one the cursor is hovering
     */
    void switchPokemon();
    
    
//=================// Box Move Actions //==================//
    
    
    /**
     * Select the box title
     * @param select true if the box title must be selected
     */
    void selectBoxTitle(bool select);
    
    
    /**
     * Go to the next box
     */
    void nextBox();
    
    /**
     * Go to the previous box
     */
    void previousBox();
    
    
//=================// Attributes //==================//
    
    // A pointer to the character
    Character* m_character;
    
    // The current box selected
    int m_currentBox;
    
    // The cursor selection as an int
    int m_selection;
    
    // True if the cursor is on a team pokemon
    bool m_cursorInTeam;
    
    
    // Boolean to know if a pokemon was selected
    bool m_isPokeSelected;
    
    // A pointer to the taken pokemon
    Pokemon* m_pokemonTaken;
    
    
    // Boolean to know if the box title was selected
    bool m_boxTitleSelected;
    
//=================// UI //==================//
    
    // The BoxState UI
    UIBoxState m_ui;
};

#endif /* BOXSTATE_HPP */

