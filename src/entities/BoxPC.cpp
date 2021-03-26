#include "BoxPC.hpp"
#include "../resources/TextureHolder.hpp"
#include "interactions/BoxInteraction.hpp"
#include "NPCId.hpp"


BoxPC::BoxPC(Context& context, sf::Vector2i pos, Zone* zone) :
Entity(context.getTextureHolder()->getTexture(TextureHolder::entityPC), context, pos, zone){

    // Set the type
    m_type = EntityType::BoxPC_Type;
    
    m_sprite.setTextureRect(sf::IntRect(0,0,16,31));
    m_sprite.setOrigin(8,23);
}



Interaction* BoxPC::createInteraction() const {
    return new BoxInteraction(NpcID::not_defined_NPC, 0);
}
