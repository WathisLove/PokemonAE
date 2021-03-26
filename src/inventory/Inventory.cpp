#include "Inventory.hpp"
#include "../inventory/Item.hpp"
#include "../Utilities.hpp"



Inventory::Inventory() {

}



bool Inventory::hasItemOfType(ItemCategory type) {
    // For each item entry of the map
    for(std::map<ItemID, int>::iterator it = m_items.begin(); it != m_items.end(); it++){
        
        // IF the Item Type is the good and it has more than 0
        if(Item::getCategory((*it).first) == type && (*it).second > 0)
            return true;
    }
    
    return false;
}



void Inventory::addItem(Item* item, int count) {
    addItem(item->getID(), count);
}



void Inventory::addItem(ItemID id, int count){
    // We look in the map to find the given ItemID
    std::map<ItemID, int>::iterator it = m_items.find(id);
    
    // If the Item ID was not found
    if(it == m_items.end()){
        // We add the it to the map
        m_items[id] = count;
    }
    // Else we increase the current value
    else{
        m_items[id] += count;
    }
}



bool Inventory::hasItem(ItemID id) {
    // Get an iterator to the given ID
    std::map<ItemID, int>::iterator it = m_items.find(id);
    
    // If the iterator does not point at the end of the table
    if(it != m_items.end()){
        std::pair<ItemID, int> pair = *it;
        
        return pair.second > 0; 
    }
    else
        return false;
}



Item* Inventory::getItem(ItemID id) {
    // If the the item is not in the table
    if(!hasItem(id)){
        throw std::string("Can't find Item of ID " + toString((int)id) + " in inventory");
    }
    
    
    return new Item(id);
}



Item* Inventory::takeItem(ItemID id) {
    Item* i = getItem(id);
    
    m_items[id]--;
    
    return i;
}



void Inventory::removeItems(ItemID item, int count) {
    // Reduce the count in the map
    m_items[item] -= count;
}



int Inventory::getItemCount(ItemID id) {
    // If the the item is not in the table
    if(!hasItem(id)){
        throw std::string("Can't find Item of ID " + toString((int)id) + " in inventory");
    }
    
    
    return m_items[id];
}



std::string Inventory::getInfoString() const {
    std::string s("<-- Inventory (Size : " + toString(m_items.size()) + ")\n");
    
    std::cout << m_items.size() << std::endl;
    // For each item entry of the map
    for(auto it = m_items.begin(); it != m_items.end(); it++){
        s += " - " + Item::getName((*it).first).toAnsiString() + " : " + toString((*it).second) + "\n";
    }
    
    s += "--- Inventory End -->\n\n";
    
    return s;
}



std::vector<ItemID> Inventory::getIDList(ItemCategory type) {
    std::vector<ItemID> ids;
    
    // We look for each item and see if it has the correct type
    for(std::map<ItemID, int>::iterator it = m_items.begin(); it != m_items.end(); it++){
        
        // IF the Item Type is the good and it has more than 0
        if(Item::getCategory((*it).first) == type && (*it).second > 0)
            ids.push_back((*it).first);
    }
    
    return ids;
}



bool Inventory::isEmpty() const {
    return m_items.empty();
}



std::vector<ItemID> Inventory::getItemsWhere(ItemPredicate predicate) const {
    std::vector<ItemID> res;
    
    // We look for each item and see if it has the correct type
    for(auto it = m_items.begin(); it != m_items.end(); it++){
        if(it->second > 0 && predicate(it->first))
            res.push_back(it->first);
    }
    
    return res;
}
