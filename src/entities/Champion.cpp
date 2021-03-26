#include "Champion.hpp"
#include <iostream>


Champion::Champion(const sf::String& name, const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone, NpcID id) :
Trainer(name, texture, context, pos, zone, id){
    
}



bool Champion::isChampion() {
    return true;
}