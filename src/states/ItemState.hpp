/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemState.hpp
 * Author: Redbuzard
 *
 * Created on 3 mars 2019, 19:51
 */

#ifndef ITEMSTATE_HPP
#define ITEMSTATE_HPP

#include "DialogState.hpp"
#include "../entities/PhysicalItem.hpp"
#include "../inventory/ItemDisplay.hpp"

class ItemState : public DialogState{
public:
    
    /**
     * Constructor for the ItemState
     * It mostly use the constructor of the DialogState 
     * and also gives items to the character
     */
    ItemState(StateStack* stack, Character* character, ItemID item, int number = 1);
    
    
    virtual ~ItemState();
    
    /**
     * Draw the ItemState
     */
    void draw() override;

    
private:
    // The pointer to the Related Item
    Item* m_item;
    
    // Item Display in the Middle of the screen
    ItemDisplay* m_itemDisplayed;
    
};

#endif /* ITEMSTATE_HPP */

