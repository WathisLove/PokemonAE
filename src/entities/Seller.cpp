#include "Seller.hpp"
#include "../resources/TextureHolder.hpp"
#include "../inventory/Item.hpp"
#include "interactions/SellerInteraction.hpp"
#include <cassert>


Seller::Seller(Context& context, sf::Vector2i pos, Zone* zone) :
Npc(context.getTextureHolder()->getTexture(TextureHolder::seller), context, pos, zone),
m_numberItems(0){
    m_type = EntityType::Seller_Type;
}



void Seller::addProduct(ItemID item) {
    // Get the default price
    int price = Item::getDefaultPrice(item);
    
    addProduct(item, price);
}



void Seller::addProduct(ItemID item, int price) {
    // Assert the item is not already in the map
    assert(m_products.find(item) == m_products.end());
    
    // Add the product to the table
    m_products[item] = price;
    
    // Increase the number of items
    m_numberItems += 1;
}



std::vector<ItemID> Seller::getItemList() {
    // The vector result
    std::vector<ItemID> res;
    
    // Iterate and add each ItemID
    for(auto it = m_products.begin(); it != m_products.end(); it++){
        res.push_back(it->first);
    }
    
    return res;
}



int Seller::getNbItems() {
    return m_numberItems;
}



int Seller::getItemPrice(int number) {
    // Find the price at the ItemdID corresponding to number
    return m_products[getItemiD(number)];
}



int Seller::getBuyingPrice(ItemID item) {
    auto it = m_products.find(item);
    
    // get the default price
    int price = Item::getDefaultSellingPrice(item);
    
    // If the seller sells the item, divides the selling price by 2 and keep the minimum
    if(it != m_products.end()){
        // Keep the min
        price = std::min(it->second / 2, price);
    }
    
    return price;
}



ItemID Seller::getItemiD(int number) {
    // Find the number-th item in the map
    auto it = m_products.begin();
    for(int x = 0; x < number; x++)
        it++;
    
    // Return the ItemID
    return it->first;
}



Interaction* Seller::createInteraction() const {
    return new SellerInteraction(m_id, 0);
}
