#include "UIBuyingState.hpp"
#include "../../Utilities.hpp"
#include "../../ItemEnums.hpp"
#include "../../resources/TextureHolder.hpp"
#include "../../resources/FontHolder.hpp"


UIBuyingState::UIBuyingState(Context& context) :
m_context(context),
m_background(context.getTextureHolder()->getTexture(TextureHolder::ui_buyingBackground)),
m_text("Combien voulez-vous en vendre ?", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_itemSold("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_totalPrice("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_itemDisplay(context)
{
    // Setup the texts
    setupTexts();
    
    // Set the Item zoom
    m_itemDisplay.setZoomFactor(2.5);
}



void UIBuyingState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background, states);
    target.draw(m_itemDisplay, states);
    target.draw(m_text, states);
    target.draw(m_itemSold, states);
    target.draw(m_totalPrice, states);
}



void UIBuyingState::setItem(ItemID item) {
    m_itemID = item;
    
    // Set the Item Display
    Item* it = new Item(item);
    m_itemDisplay.setItem(it);
    delete it;
}



void UIBuyingState::setItemSold(int number, int maxNumber) {
    // Set the UI Text
    m_itemSold.setString(toString(number) + " / " + toString(maxNumber));
    
    // Get the Unit price
    int price = Item::getDefaultSellingPrice(m_itemID);
    
    // Update the price
    m_totalPrice.setString(toString(price * number));
}



void UIBuyingState::setPosition(sf::Vector2f pos) {
    // Set the positions of the UI items
    m_background.setPosition(pos);
    m_itemDisplay.setPosition(pos + sf::Vector2f(390, 290));
    m_text.setPosition(pos + sf::Vector2f(62, 504));
    m_itemSold.setPosition(pos + sf::Vector2f(640, 460));
    m_totalPrice.setPosition(pos + sf::Vector2f(620, 480));
}



void UIBuyingState::setupTexts() {
    // Fill colors
    m_text.setFillColor(sf::Color::Black);
    m_itemSold.setFillColor(sf::Color::Black);
    m_totalPrice.setFillColor(sf::Color::Black);
}
