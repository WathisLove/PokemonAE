/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SellerActionState.hpp
 * Author: Redbuzard
 *
 * Created on 30 mai 2020, 16:54
 */

#ifndef SELLERACTIONSTATE_HPP
#define SELLERACTIONSTATE_HPP

#include "ChoiceState.hpp"
#include "SellerState.hpp"

#include "SellerState.hpp"
#include "BuyingState.hpp"

/**
 * Choose the Action when talking to a Seller
 */
class SellerActionState : public ChoiceState{
public:
    
//=================// Constructors //==================//
    
    /**
     * Constructor
     */
    SellerActionState(StateStack* stack, Character* character, Seller* seller);
    
    
    
//=================// Overriden methods //==================//
    

    /**
     * Act when the State is completed 
     * Push a Seller State, a Buying State or quit
     */
    virtual void actionOnCompletion() override;
    
    
    /**
     * Update the State
     * @param dt time elapsed since last frame
     * @return false as we don't want the lower states to update
     */
    virtual bool update(float dt);

    /**
     * Handle the incoming Events
     * @param event a reference to the current Event
     * @return true if the next state must handle the event
     */
    virtual bool handleEvent(sf::Event& event) override;
    
private:
//=================// Attributes //==================//
    
    // A pointer to the seller
    Seller* m_seller;
};

#endif /* SELLERACTIONSTATE_HPP */

