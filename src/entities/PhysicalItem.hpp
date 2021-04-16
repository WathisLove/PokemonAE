/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicalItem.hpp
 * Author: Redbuzard
 *
 * Created on 5 mars 2019, 21:06
 */

#ifndef PHYSICALITEM_HPP
#define PHYSICALITEM_HPP

#include "Entity.hpp"
#include "../inventory/Item.hpp"

class Interaction;

class PhysicalItem : public Entity{
public:
    
    PhysicalItem(Context& context, sf::Vector2i pos, Zone* zone, ItemID id, int count = 1);

    
    /**
     * Get the number of items present on the case
     * @return the number as an int
     */
    int getCount() const;
    
    /**
     * Get an item of the ItemType
     * @return a pointer to the new item
     */
    Item* getItem() const;
    
    
    /**
     * Get the ID of the related Items
     * @return the ID as an ItemID
     */
    ItemID getItemID() const;
    
    
    /**
     * Get the number of the PhysicalItem
     * @return the number of the PhysicalItem
     */
    int getNumber() const;
    
    
    /**
     * Set the PhysicalItem number when created on the Zone
     * @param itemNumber 
     */
    void setNumber(int itemNumber);
    
    
    /**
     * Creates an interaction for the PhysicalItem
     * @return a pointer to the Interaction
     */
    Interaction* createInteraction() const;
    
protected:
    // The number of items present on the case
    int m_count;
    
    // The ItemID present on the case
    ItemID m_ID;
    
    // The item number when picked on the floor
    int m_num;
};

#endif /* PHYSICALITEM_HPP */

