#include "SellEntry.hpp"
#include "../../Utilities.hpp"
#include "../../resources/TextureHolder.hpp"
#include "../../resources/FontHolder.hpp"


SellEntry::SellEntry(Context& context, ItemID item, int price) :
m_name("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_price("", context.getFontHolder()->getFont(FontHolder::dialogFont), 20),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_sellerEntry)),
m_item(item),
m_itemDisplay(context)
{
    setupText(item, price);
    
    // Set the Item Display
    Item* it = new Item(item);
    m_itemDisplay.setItem(it);
    delete it;
}



void SellEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_itemDisplay, states);
    target.draw(m_name, states);
    target.draw(m_price, states);
}



void SellEntry::setPosition(sf::Vector2f pos) {
    m_background.setPosition(pos);
    m_itemDisplay.setPosition(pos + sf::Vector2f(20, 20));
    m_name.setPosition(pos + sf::Vector2f(40, 5));
    m_price.setPosition(pos + sf::Vector2f(220, 6));
}



ItemID SellEntry::getItem() {
    return m_item;
}



void SellEntry::setupText(ItemID id, int price) {
    // Set the text Color
    m_name.setFillColor(sf::Color::Black);
    m_price.setFillColor(sf::Color::Black);
    
    // Set the Item Name
    m_name.setString(Item::getName(id));
    m_price.setString(toString(price) + "$");
}
