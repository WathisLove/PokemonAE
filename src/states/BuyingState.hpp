/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BuyingState.hpp
 * Author: Redbuzard
 *
 * Created on 21 mai 2020, 13:08
 */

#ifndef BUYINGSTATE_HPP
#define BUYINGSTATE_HPP

#include "State.hpp"
#include "BagState.hpp"
#include "../entities/Seller.hpp"
#include "../ui/states/UIBuyingState.hpp"

class BuyingState : public State{
public:
    
//=================// Constructor //==================//
    
    /**
     * Constructor
     */
    BuyingState(StateStack* stack, Character* character, Seller* seller);
    
    
//=================// Public inherited methods //==================//
    
    /**
     * Overriden draw method
     */
    virtual void draw() override;

    /**
     * Handle the incoming Events
     * @param event a reference to the current Event
     * @return true if the next state must handle the event
     */
    virtual bool handleEvent(sf::Event& event) override;
    
    /**
     * Check if a choice was made by the player
     * @return true if a choice was made
     */
    virtual bool isCompleted() const override;

    /**
     * Act when the State is completed 
     * As we are in a DialogState we wait until a state request our result
     */
    virtual void actionOnCompletion() override;
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return true as we want the next states to be updated
     */
    virtual bool update(float dt);

    
private:
//==================// Private methods //===================//
    
    /**
     * Open a BagState
     */
    void openBag();
    
    /**
     * Close the BagState
     */
    void closeBag();
    
    /**
     * Function that look for the secondary state
     */
    void findBagState();
    
    
    /**
     * Increase the current quantity
     */
    void increase();
    
    /**
     * Decrease the current quantity
     */
    void decrease();
    
    
    /**
     * Called when an item is selected in the bag
     */
    void select();
    
    /**
     * Confirm the quantity that will be sold
     */
    void confirmQuantity();
    
    /**
     * Unselect the item in the bag
     */
    void unselect();
    
    
//==================// Attributes //===================//
    // A pointer to the character
    Character* m_character;

    // A pointer to the Seller
    Seller* m_seller;            
    
    // A pointer to the BagState
    BagState* m_bagState;
    
    // A boolean to know if we are choosing the item quantity
    bool m_isChoosingQuantity;
    
    // The current quantity and current max Quantity
    int m_currentQuantity, m_maxQuantity;
    
//==================// Graphical Attributes //===================//
    
    // The State UI
    UIBuyingState m_ui;
};

#endif /* BUYINGSTATE_HPP */

