/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Seller.hpp
 * Author: Redbuzard
 *
 * Created on 4 mai 2020, 17:04
 */

#ifndef SELLER_HPP
#define SELLER_HPP

#include "NPC.hpp"
#include "../ItemEnums.hpp"

#include <map>

class Interaction;

class Seller : public Npc{
public:
//=================// Constructor //==================//
    /**
     * Constructor
     */
    Seller(Context& context, sf::Vector2i pos, Zone* zone);
    
    
//=================// Public methods //==================//
    
    
    /**
     * Adds an item to be sold at default price
     * @param item the ItemID of the item the seller will sell
     */
    void addProduct(ItemID item);
    
    
    
    /**
     * Adds an item to be sold at a given price
     * @param item the ItemID of the item the seller will sell
     * @param price the price of the new item
     */
    void addProduct(ItemID item, int price);
    
    
    /**
     * Get the list of items sold
     * @return a vector of ItemID corresponding to the items sold
     */
    std::vector<ItemID> getItemList();
    
    
    /**
     * Get the number of items the seller sells
     * @return the number of different item that can be sold
     */
    int getNbItems();
    
    
    /**
     * Get the price of an item sold by the seller
     * @param number the number of the item in the ItemList
     * @return the price as an int
     */
    int getItemPrice(int number);
    
    
    /**
     * Get the price at which the seller buys an item
     * @return the buying price of a single item
     */
    int getBuyingPrice(ItemID item);
    
    
    /**
     * Get the ItemID of an item sold by the seller
     * @param number the number of the item in the ItemList
     * @return the item ItemID
     */
    ItemID getItemiD(int number);
    
    
    /**
     * Creates an interaction for the Seller
     * @return a pointer to the Interaction
     */
    Interaction* createInteraction() const;
    
private:
//=================// Attributes //==================//
    // A map of product and their prices
    std::map<ItemID, int> m_products;
    
    // The number of items that will be sold
    int m_numberItems;
};

#endif /* SELLER_HPP */

