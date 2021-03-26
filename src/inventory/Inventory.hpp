/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Inventory.hpp
 * Author: Redbuzard
 *
 * Created on 13 mars 2019, 13:13
 */

#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <map>
#include <functional>

#include "Item.hpp"
#include "../predicates/ItemPredicate.hpp"


/**
 * A Class used to store the items of an entity, for example the Character or a Trainer
 * Items are stored thanks to their ID and their count
 */

class Inventory {
public:
    
    Inventory();
    
    /**
     * Add an item to the Inventory
     * @param item the item that will be added
     * @param count the number of items added
     */
    void addItem(Item* item, int count = 1);
    
    /**
     * Add an item to the Inventory
     * @param id the item ID that will be added
     * @param count the number of items added
     */
    void addItem(ItemID id, int count = 1);
    
    /**
     * Check if there is an item of the given ID in the inventory
     * @param id the ID of the item searched
     * @return true if there is more than 0 items of the ID
     */
    bool hasItem(ItemID id);
    
    
    /**
     * Check if there is an item of the given type in the inventory
     * @param type ITemCategory we look for
     * @return true if an item of the given type was found
     */
    bool hasItemOfType(ItemCategory type);
    
    
    /**
     * Get an item of the given ID from the Inventory
     * @param id the ID of the item we want from the Invenotyr
     * @return a pointer to a new Item
     * @warning throws an exception if there is no item of such ID in the inventory
     */
    Item* getItem(ItemID id);
    
    /**
     * Take an item of the given ID from the Inventory
     * @param id the ID of the item we want from the Inventory
     * @return a pointer to a new Item
     * @warning throws an exception if there is no item of such ID in the inventory
     */
    Item* takeItem(ItemID id);
    
    
    /**
     * Remove a given number of a certain item from the player inventory
     * @param item the ItemID of the Character 
     * @param count the item count
     */
    void removeItems(ItemID item, int count);
    
    
    /**
     * Get the item count of the given ID from the given Inventory
     * @param id the ID of the item we want from the Inventory
     * @return the number of items as an int
     * @warning throws an exception if there is no item of such ID in the inventory
     */
    int getItemCount(ItemID id);
    
    
    /**
     * Returns a string that can be used to display infos about the inventory
     * @return a string
     */
    virtual std::string getInfoString() const;
    
    
    /**
     * Get the ID List of a given Type
     * @param type the type of the items
     * @return a vector corresponding to all the ID of the given type
     */
    std::vector<ItemID> getIDList(ItemCategory type);
    
    
    /**
     * Check if the inventory is empty
     * @return true if empty
     */
    bool isEmpty() const;
    
    
    /**
     * Get all items that return true to a predicate
     * @param pred the predicate defined to find the items
     * @return a vector of items that returned true to the predicate
     */
    std::vector<ItemID> getItemsWhere(ItemPredicate predicate) const;
    
    
private:
    
    // Map that stores the items of the inventory
    std::map<ItemID, int> m_items;

};

#endif /* INVENTORY_HPP */

