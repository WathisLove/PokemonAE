/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SellerState.hpp
 * Author: Redbuzard
 *
 * Created on 6 mai 2020, 10:48
 */

#ifndef SELLERSTATE_HPP
#define SELLERSTATE_HPP

#include "StateStack.hpp"
#include "State.hpp"

#include "../entities/Seller.hpp"
#include "../entities/Character.h"
#include "../ui/states/UISellerState.hpp"

class SellerState : public State {
public:
    
//=================// Constructor //==================//
    
    /**
     * Constructor
     */
    SellerState(StateStack* stack, Character* character, Seller* seller);
    
    
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
    
//=================// Private methods //==================//
    
    /**
     * Select the next entry
     */
    void next();
    
    /**
     * Select the previous entry
     */
    void previous();
    
    
    /**
     * Select the current entry
     */
    void select();
    
    /**
     * Unselect the current entry
     */
    void unselect();
    
    
    /**
     * Increase the number of items to buy
     * @param the added value
     */
    void increase(int number = 1);
    
    
    /**
     * Decrease the number of items to buy
     * @param the reduced value
     */
    void decrease(int number = 1);
    
    
    /**
     * Buy the current entry selected
     */
    void buy();
    
//=================// Attributes //==================//
    
    // A pointer to the character
    Character* m_character;
    
    // A pointer to the seller
    Seller* m_seller;
    
    // The current entry
    int m_currentEntry;
    
    // A boolean to know if we are buying an item or not
    bool m_isBuying;
    
    // The current quantity that we will buy
    int m_quantity;
    
//=================// Graohical Attributes //==================//
    
    // The State UI
    UISellerState m_ui;
};

#endif /* SELLERSTATE_HPP */

