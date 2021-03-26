/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BagState.hpp
 * Author: Redbuzard
 *
 * Created on 8 avril 2019, 15:42
 */

#ifndef BAGSTATE_HPP
#define BAGSTATE_HPP

#include "State.hpp"
#include "../inventory/InventoryEntry.hpp"
#include "../inventory/BagItemSelector.hpp"
#include "../inventory/ItemDisplay.hpp"
#include "../ui/ChoiceMenu.hpp"


// An enum used to know what we are currently doing with the bag
enum BagStage{
    Bag_SelectingItem,
    Bag_SelectingUse,
    Bag_GivingToPokemon,
    Bag_UsingOnPokemon,
    Bag_Dialog,
    Bag_ChoiceReplacingItem,
    Bag_ItemEffects,
    SelectingAttack
};



class BagState : public State{
public:
    
    BagState(StateStack* stack, Character* c);

    //==================// Public Methods //===================//
    
    
    /**
     * Draw the state
     */
    virtual void draw();
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false if the next State in the stack must not be updated
     */
    virtual bool update(float dt);
    
    
    /**
     * @return true if the State must be popped
     */
    virtual bool isCompleted() const;
    
    /**
     * Act on the stack when the goal of the state is achieved
     */
    virtual void actionOnCompletion();
    
    /**
     * Manage an incoming Event
     * @return false if the next State must not handle Events
     */
    virtual bool handleEvent(sf::Event& event);
    
    
    /**
     * Handles an incoming game Event
     * @param event a const reference to the event
     */
    void handleGameEvent(const GameEvent& event) override;
    
    
    /**
     * Check if the state has selected an item
     * @return true if an item was selected
     */
    bool hasSelectedItem();
    
    /**
     * Get the ID of the Item selected
     * @return the ItemID of the selected item
     */
    ItemID getItemIDSelected();
    
    
    /**
     * Get the index of the selected pokemon, in case it was a secondary state
     * @return the ItemID of the selected item
     */
    int getSelectedPokemonIndex();
    
    /**
     * Get a pointer to the selected pokemon
     * @return a pointer to the selected pokemon
     */
    Pokemon* getSelectedPokemon();
    
    
    /**
     * Unselect the current item
     */
    void unselectItem();
    
    
    /**
     * Deactivates the menu (for example when the BagState is used a secondary state
     */
    void deactivateMenu();
    
    /**
     * Set the menu entries to be used during a fight
     */
    void setFightEntries();
    
    
    /**
     * Get the attackID corresponding to the selected CT 
     * @warning throw an error if no CT was selected
     * @return the AttackID
     */
    AttackID getCTAttack();
    
    
    /**
     * Update the Item list when the category changes
     */
    void updateItemList();
    
private:

    //==================// Private Methods //===================//
    
    
    /**
     * Update the sprite for the category selected
     */
    void updateCategorySelector(sf::Keyboard::Key keyPressed);
    
    
    /**
     * Select the current Item
     * @warning if there is no item selected, then the BagStage stays at SelectingITem
     */
    void selectCurrentItem();
    
    
    /**
     * Select the use for the selected item
     */
    void selectItemUse();
    
    
    /**
     * Get the Selected item type (equivalent to the category)
     */
    ItemCategory getItemCategorySelected();
    
    
    
    /**
     * Update the graphical attributes used to display the item selected
     */
    void updateItemDisplay();
    
    
    /**
     * Update the category sprites
     */
    void updateCategorySprites();
    
    
    /**
     * Build the Menu entries
     */
    void buildMenu();
    
    
    /**
     * Find the secondary state if needed
     */
    void findSecondaryState();
    
    
    /**
     * Take the selected Item from the Character inventory
     * @return a pointer to the Item taken
     */
    Item* takeSelectedItem();
    
    
    /**
     * A funciton called when a Pokemon was selected from a TeamState
     */
    void onPokemonSelected();
    
    
    /**
     * Close the secondary State and reset the pointer to a null value
     */
    void closeSecondaryState();
    
    
    /**
     * Give the selected item to the Pokemon selected in the TeamState (m_secondaryState)
     */
    void givePokemonSelectedItem();
    
    
    /**
     * Use the sleected item on the selected pokemon
     */
    void useSelectedItem();
    
    
    /**
     * Use the item on the attack
     * @param attack a pointer to the attack
     */
    void useItemOnAttack(Attack* attack);
    
    
    /**
     * Push a state to LearnAttack to learn the current CT
     * @param p a pointer to the pokemon that will learn the Attack
     */
    void pushLearnCTState(Pokemon* p);
    
    
    /**
     * Removes a single ItemEffect from the queue
     */
    void removeSingleItemEffect();
    
    
    /**
     * Remove all ItemEffects from the Queue
     */
    void clearItemEffects();
    
    
    //==================// Attributes //===================//
    
    // Bag Stage
    BagStage m_currentStage;
    
    
    // The ItemSelector
    BagItemSelector m_itemSelector;
    
    
    // A pointer to the character, used to update the inventory and for example
    Character* m_character;
    
    // The number of the selected Category
    int m_selectedCategory;
    
    // A boolean that stores if the item was selected at the end or not
    bool m_isSelected;
    
    
    // The index of the selected pokemon
    int m_pokemonIndexSelected;
    
    // A menu
    ChoiceMenu m_menu;
    
    
    // A pointer to a state that can either be a BagState or a PokemonState
    // This pointer is used to get some info about what Pokemon we want to give an item to
    State* m_secondaryState;
    
    
    std::queue<ItemEffect*> m_itemEffects;
    
    //==================// Graphical Attributes //===================//
    
    // Sprite for the background
    sf::Sprite m_background;

    // Selector for the Category
    sf::Sprite m_categorySelector;
    
    
    // Selected Item Display & Infos
    sf::Text m_itemName;
    sf::Text m_itemCount;
    sf::Text m_itemDescription;
    ItemDisplay m_itemDisplay;
    
    // Vector of sprites for the categories
    std::vector<sf::Sprite> m_categories;
};

#endif /* BAGSTATE_HPP */

