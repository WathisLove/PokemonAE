#include "BagItemSelector.hpp"
#include "../resources/TextureHolder.hpp"

#include <iostream>
#include <algorithm>

BagItemSelector::BagItemSelector(Context& context, sf::Vector2f offset) :
m_offset(offset),
m_currentEntry(0),
m_context(context),
m_arrowUp(context.getTextureHolder()->getTexture(TextureHolder::ui_bagArrows), sf::IntRect(0,0,32,32)),
m_arrowDown(context.getTextureHolder()->getTexture(TextureHolder::ui_bagArrows), sf::IntRect(0,32,32,32)),
m_selector(context.getTextureHolder()->getTexture(TextureHolder::ui_bagItemSelector)),
m_firstDisplayed(0),
m_changed(false),
m_currentItemType(ItemCategory::Object)
{
    // Set the arrows' origins and positions
    m_arrowUp.setOrigin(16,16);
    m_arrowDown.setOrigin(16,16);
    
    m_arrowUp.setPosition(m_offset + sf::Vector2f(128, -6));
    m_arrowDown.setPosition(m_offset + sf::Vector2f(128, 450));
    
    
    // Set the poisition of the selection Rectangle
    m_selector.setOrigin(10, 5);
    replaceSelector();
}


BagItemSelector::~BagItemSelector() {
    // Clear the old Inventory Entries
    for(InventoryEntry* ie : m_inventoryEntries)
        delete ie;
}



void BagItemSelector::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Draw the 10 correct Entries
    for(int i = m_firstDisplayed; i < m_inventoryEntries.size() && i < m_firstDisplayed+10; i++){
        // Draw the Entry number i
        target.draw(*(m_inventoryEntries.at(i)), states);
    }
    
    
    // Draw the Arrows
    if(canGoUp())
        target.draw(m_arrowUp, states);
    if(canGoDown())
        target.draw(m_arrowDown, states);
    
    
    // Draw the selection uf there is at least one Item
    if(m_inventoryEntries.size() > 0)
        target.draw(m_selector, states);
}



void BagItemSelector::handleEvent(sf::Event& event) {
    if(event.type == sf::Event::KeyPressed){
        // We get the pressed key
        sf::Keyboard::Key key = event.key.code;
        
        if(key == sf::Keyboard::S){
            goDown();
        }
        if(key == sf::Keyboard::Z){
            goUp();
        }
    }
}



void BagItemSelector::goDown() {
    // Increase the num of the selected Entry
    m_currentEntry++;
    
    if(m_currentEntry >= m_inventoryEntries.size())
        m_currentEntry--;
    else
        // Set change to true
        m_changed = true;
    
    // If we are at the fifth entry or more, and if we can go down
    if(m_currentEntry-m_firstDisplayed >= 6 && canGoDown()){
        m_firstDisplayed++;
        
        replaceEntries();
    }
    
    replaceSelector();
}



void BagItemSelector::goUp() {
    // Decrease the num of the selected Entry
    m_currentEntry--;
    
    if(m_currentEntry < 0)
        m_currentEntry++;
    else
        // Set change to true
        m_changed = true;
    
    // If we are at the fifth entry or more, and if we can go down
    if(m_currentEntry-m_firstDisplayed <= 3 && canGoUp()){
        m_firstDisplayed--;
        
        replaceEntries();
    }
    
    replaceSelector();
}



InventoryEntry* BagItemSelector::getCurrentInventoryEntry() {
    return m_inventoryEntries.at(m_currentEntry);
}



ItemID BagItemSelector::getCurrentItemID() {
    return getCurrentInventoryEntry()->getItemID();
}



bool BagItemSelector::isEmpty() {
    return m_inventoryEntries.empty();
}



void BagItemSelector::setIDList(Inventory* inventory, ItemCategory type) {
    // Clear the old Inventory Entries
    for(InventoryEntry* ie : m_inventoryEntries)
        delete ie;
    m_inventoryEntries.clear();
    
    
    // We get the list of IDs
    std::vector<ItemID> idList = inventory->getIDList(type);

    
    // We add the new entries
    for(int i = 0; i < idList.size(); i++){
        // Get the ID
        ItemID id = idList.at(i);
        
        // Set and add the Inventory entry
        InventoryEntry* ie = new InventoryEntry(m_context, id, inventory->getItemCount(id));
        ie->setPosition(m_offset + sf::Vector2f(0, 46*i));
        m_inventoryEntries.push_back(ie);
    }
    
    
    // Select the first item if there was a change, or try to keep the last entry
    if(m_currentItemType != type){
        m_currentEntry = 0;
        m_firstDisplayed = 0;
        m_currentItemType = type;
    }
    // Else if the current entry is greater than the new size
    else if(m_currentEntry >= m_inventoryEntries.size()-1){
        m_currentEntry--;
        m_firstDisplayed--;
    }
    
    // Move up the entries
    replaceEntries();
    
    // We replace the selector
    replaceSelector();
}



bool BagItemSelector::canGoDown() const{
    return (m_inventoryEntries.size() - m_firstDisplayed) > 10;
}



bool BagItemSelector::canGoUp() const{
    return m_firstDisplayed > 0;
}



void BagItemSelector::replaceEntries() {
    // We place each entry
    for(int i = 0; i < m_inventoryEntries.size(); i++){

        // Get the Entry
        InventoryEntry* ie = m_inventoryEntries.at(i);

        // Move the Entry
        ie->setPosition(m_offset + sf::Vector2f(0, 46*(i-m_firstDisplayed)));
    }
}



void BagItemSelector::replaceSelector() {
    // Get the index offset from the first displayed to the current selected
    int variation = m_currentEntry - m_firstDisplayed;
    
    m_selector.setPosition(m_offset + sf::Vector2f(0, 46*variation));
}



bool BagItemSelector::changed() {
    if(m_changed){
        m_changed = false;
        return true;
    }
    
    else
        return false;
}



int BagItemSelector::getItemCount() {
    return m_inventoryEntries.size();
}
