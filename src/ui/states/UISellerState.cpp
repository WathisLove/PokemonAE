#include "UISellerState.hpp"
#include "../../inventory/Item.hpp"
#include "../../Utilities.hpp"
#include "../../resources/TextureHolder.hpp"
#include "../../resources/FontHolder.hpp"

UISellerState::UISellerState(Context& context, Seller* seller, int characterMoney) :
m_money("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_sellerBackground)),
m_cursor(context.getTextureHolder()->getTexture(TextureHolder::ui_sellerCursor)),
m_quantity("1", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_totalPrice("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_currentItemName("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_itemDisplay(context),
m_isSelected(false),
m_currentEntry(0)
{
    createEntries(context, seller);
    setupTexts(characterMoney);
    
    m_itemDisplay.setZoomFactor(2.5);
    
    setSelected(false);
}



void UISellerState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    
    target.draw(m_money);
    target.draw(m_currentItemName);
    target.draw(m_itemDisplay);
    
    if(m_isSelected){
        target.draw(m_quantity);
        target.draw(m_totalPrice);
    }

    // Draw the entries
    for(int i = getFirstEntryDisplayed(); i < m_entries.size() && i < getFirstEntryDisplayed()+8; i++){
        target.draw(m_entries.at(i), states);
    }
    
    // Draw the cursor
    target.draw(m_cursor, states);
}



void UISellerState::setCurrentEntry(int entryNumber) {
    // Get the current ItemID
    ItemID id = m_entries.at(entryNumber).getItem();
    
    // Set the ItemDisplay
    Item* item = new Item(id);
    m_itemDisplay.setItem(item);
    delete item;
    
    // Set the first entry
    m_currentEntry = entryNumber;
    
    // Set the entries positions
    setEntriesPositions();
    
    // Set the current item name
    m_currentItemName.setString(Item::getName(id));
}



void UISellerState::setQuantity(int number, int totalPrice) {
    m_totalPrice.setString(toString(totalPrice));
    m_quantity.setString(toString(number));
}



void UISellerState::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    
    m_currentItemName.setPosition(pos + sf::Vector2f(120, 440));
    m_money.setPosition(pos + sf::Vector2f(150, 545));
    m_quantity.setPosition(pos + sf::Vector2f(140, 463));
    m_totalPrice.setPosition(pos + sf::Vector2f(200, 505));
    m_itemDisplay.setPosition(pos + sf::Vector2f(60, 480));
    
    setEntriesPositions();
}



void UISellerState::setCharacterMoney(int money) {
    m_money.setString(toString(money));
}



int UISellerState::getFirstEntryDisplayed() const{
    // If we are in the first 5 entries
    if(m_currentEntry < 4)
        return 0;
    else if(m_currentEntry >= m_entries.size()-4)
        return m_entries.size() - std::min(8, (int)m_entries.size());
    else{
        return m_currentEntry - 4;
    }
}



void UISellerState::setEntriesPositions() {
    // Get the position of the background
    sf::Vector2f topLeft = m_background.getPosition();
    
    // Get the index of the first entry displayed
    int first = getFirstEntryDisplayed();
    
    // Set the position of each Entry
    for(int i = 0; i < m_entries.size(); i++){
        m_entries.at(i).setPosition(topLeft + sf::Vector2f(28, 28 + 42 * (i-first)));
    }
    
    
    // Set the cursor position
    m_cursor.setPosition(topLeft + sf::Vector2f(28, 28 + 42*(m_currentEntry-first)));
}



void UISellerState::createEntries(Context& context, Seller* seller) {    
    // For each item sold by the Seller
    for(ItemID id : seller->getItemList()){
        // Get the Item price
        int price = seller->getItemPrice(m_entries.size());
        
        // Create an entry
        m_entries.push_back(SellEntry(context, id, price));
    }
    
    // Set the ItemDisplay
    Item* item = new Item(m_entries.at(0).getItem());
    m_itemDisplay.setItem(item);
    delete item;
}



void UISellerState::setSelected(bool selected) {
    m_isSelected = selected;
    
    // Set the UI Rectangle
    if(selected)
        m_background.setTextureRect(sf::IntRect(0, 600, 800, 600));
    else
        m_background.setTextureRect(sf::IntRect(0, 0, 800, 600));
}



void UISellerState::setupTexts(int characterMoney) {
    // Colors
    m_money.setFillColor(sf::Color::Black);
    m_quantity.setFillColor(sf::Color::Black);
    m_totalPrice.setFillColor(sf::Color::Black);
    m_currentItemName.setFillColor(sf::Color::Black);
    
    // Text
    m_money.setString(toString(characterMoney));
    m_currentItemName.setString(Item::getName(m_entries.at(m_currentEntry).getItem()));
}
