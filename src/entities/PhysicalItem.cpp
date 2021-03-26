#include "PhysicalItem.hpp"
#include "../resources/TextureHolder.hpp"
#include "interactions/Interaction.hpp"
#include "interactions/ItemInteraction.hpp"
#include "NPCId.hpp"
#include "../inventory/Item.hpp"
#include <iostream>
#include <cassert>

PhysicalItem::PhysicalItem(Context& context, sf::Vector2i pos, Zone* zone, ItemID id, int count) :
Entity(context.getTextureHolder()->getTexture(TextureHolder::itemsTileSet), context, pos, zone),
m_ID(id),
m_count(count),
m_num(-1){
    
    // Set the type
    m_type = EntityType::PhysicalItem_Type;
    
    // Set the texture Rect
    m_textureRect = Item::getTextureRect(id);
    m_sprite.setTextureRect(m_textureRect);
    m_sprite.setOrigin(16,16);
    m_sprite.setScale(1.2, 1.2);
}



int PhysicalItem::getCount() const {
    return m_count;
}



ItemID PhysicalItem::getItemID() const {
    return m_ID;
}



Item* PhysicalItem::getItem() const {
    return new Item(m_ID);
}



int PhysicalItem::getNumber() const {
    // Assertion to be sure the num was set
    assert(m_num != -1);
    
    return m_num;
}



void PhysicalItem::setNumber(int itemNumber) {
    m_num= itemNumber;
}



Interaction* PhysicalItem::createInteraction() const {
    return new ItemInteraction(NpcID::not_defined_NPC, 0, m_ID, m_count);
}
