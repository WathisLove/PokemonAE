#include "InventoryEntry.hpp"
#include "../pokemons/attacks/AttackFabric.hpp"
#include "../resources/FontHolder.hpp"
#include "Item.hpp"


InventoryEntry::InventoryEntry(Context& context, ItemID id, int count) :
m_id(id),
m_count(count),
m_textCount("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24),
m_textName("", context.getFontHolder()->getFont(FontHolder::dialogFont), 24)
{
    m_textCount.setOrigin(-200,0);
    m_textCount.setFillColor(sf::Color::Black);
    m_textName.setFillColor(sf::Color::Black);
    
    // Set the Text
    if(Item::getCategory(id) == ItemCategory::CT){
        // Create the attack for the CT
        Attack* a = AttackFabric::createAttack(Item::getAttackTeached(id));
        m_textName.setString(a->getName());
        delete a;
        
        // Remove the count
        m_textCount.setString(L"");
    }
    else{
        m_textCount.setString("x "+toString(count));
        m_textName.setString(Item::getName(id));
    }
}



void InventoryEntry::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_textCount, states);
    target.draw(m_textName, states);
}



int InventoryEntry::getItemCount() const {
    return m_count;
}



ItemID InventoryEntry::getItemID() const {
    return m_id;
}



sf::String InventoryEntry::getItemName() const {
    return m_textName.getString();
}



void InventoryEntry::setPosition(sf::Vector2f pos) {
    m_textCount.setPosition(pos);
    m_textName.setPosition(pos);
}

