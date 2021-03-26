/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UIFightState.hpp
 * Author: Redbuzard
 *
 * Created on 23 août 2019, 16:29
 */

#ifndef UIFIGHTSTATE_HPP
#define UIFIGHTSTATE_HPP

#include <SFML/Graphics.hpp>
#include "../../Context.hpp"
#include "../fight/PokemonFightDisplay.hpp"
#include "../../fight/FightMenuSelector.hpp"
#include "../../fight/FightAttackSelector.hpp"
#include "../../fight/FightDialog.hpp"
#include "../../ItemEnums.hpp"
#include "../../inventory/ItemDisplay.hpp"
#include "../fight/AbilityDisplay.hpp"


enum FightMenu{
    FM_None,
    FM_MainMenu,
    FM_AttackMenu
};



class UIFightState : public sf::Drawable{
public:
//===============// Constructor //===============// 
    
    UIFightState(Context& context, Pokemon* ally, Pokemon* ennemy);
    
    
//===============// Public methods //===============// 
    
    /**
     * Inherited draw method
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    
    /**
     * Update the UI
     * @param dt the elapsed time in seconds
     */
    void update(float dt);
    
    /**
     * Handle the incoming events
     * @param event a reference to the incoming event
     */
    void handleEvent(sf::Event& event);
    
    
    /**
     * Update the pokemon displays
     */
    void updatePokemonDisplays();
    
    
    /**
     * Replace the ennemy sprite by an item
     * @param id the id of the item 
     */
    void replaceEnnemySprite(ItemID id);
    /**
     * Replace the ennemy sprite by the pokemon
     */
    void replaceEnnemySprite();
    
//===============// Menu methods //===============// 
    
    /**
     * Show the main menu
     */
    void showMainMenu();
    
    /**
     * Show the attack selector
     */
    void showAttackMenu();
    
    /**
     * Hide the menus
     */
    void hideMenu();
    
    
    
//===============// Dialog methods //===============// 
    
    /**
     * Add a dialog line for later display
     * @param str the new line of dialog
     */
    void addDialog(std::wstring str);
    /**
     * Add a dialog line for later display
     * @param str the new line of dialog
     */
    void addDialog(sf::String str);
    
    /**
     * Show the next dialog (or close it if there are no dialog string left)
     */
    void nextDialog();
    
    /**
     * Choose wether or not to display the Dialog
     * @param show true if we must show the dialog
     */
    void showDialog(bool show);
    
    /**
     * Check if the UI is showing a dialog line
     * @return true if a dialog is shown
     */
    bool isShowingDialog();
    
    
    
//===============// Getters / Setters //===============// 
    
    /**
     * Set the ally pokemon
     * @param ally a pointer to the ally pokemon
     */
    void setAlly(Pokemon* ally);
    
    
    /**
     * Set the ennemy pokemon
     * @param ennemy a pointer to the ennemy pokemon
     */
    void setEnnemy(Pokemon* ennemy);
    
    
    /**
     * Get the Fight main Menu
     * @return a reference to the main Menu
     */
    FightMenuSelector& getMenu();
    
    /**
     * Get the Fight Attack Menu
     * @return a reference to the AttackMenu
     */
    FightAttackSelector& getAttackMenu();
    
    
    /**
     * Set the visibility of a pokemon display
     * @param team the team of the pokemon
     * @param val true if the PokemonDisplay must be shown
     */
    void setPokemonDisplayVisibility(Team team, bool val);
    
    
    /**
     * Show an ability
     * @param p a pointer to the Ability owner
     * @param team the team of the pokemon
     */
    void showAbilityDisplay(Pokemon* p, Team team);
    
    /**
     * Hide the Ability Display
     */
    void hideAbilityDisplay();
    
    
private:
//===============// Private methods //===============// 
    
    
    /**
     * Set the UI position relative to the camera one
     */
    void setUIPosition();
    
    
//===============// Attributes //===============// 
    
    // A reference to the Context
    Context& m_context;
    
    
    // The current shown menu
    FightMenu m_currentMenu;
    
    
//===============// Graphical Attributes //===============//
    // The FightState Background
    sf::Sprite m_background;
    
    // Pokemon displays
    PokemonFightDisplay m_allyDisplay;
    PokemonFightDisplay m_ennemyDisplay;
    
    // Item Display
    ItemDisplay m_itemDisplay;
    bool m_showItem;
    
    // Menu and Attack selector
    FightMenuSelector m_menuSelector;
    FightAttackSelector m_attackSelector;
    
    // Fight dialog to display in-fight dialogs
    FightDialog m_dialog;
    
    // A Display for the Abilities
    AbilityDisplay m_abilityDisplay;
};

#endif /* UIFIGHTSTATE_HPP */

