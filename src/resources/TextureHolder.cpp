#include "TextureHolder.hpp"

#include <iostream>
#include <cassert>


const std::map<std::string, TextureHolder::textureID> TextureHolder::textureFiles {
    // Load all the standard textures
    {"../data/sprites/tilesets/tileset.png", textureID::tileSet},
    {"../data/sprites/tilesets/item_set.png", textureID::itemsTileSet},
    
    // ===== // Character
    {"../data/sprites/characters/brice_texture.png", textureID::character, },
    {"../data/sprites/characters/character_full.png", textureID::characterFull},
    
    // ===== // Entities
    {"../data/sprites/npcs/old_man_1.png", textureID::old_man_1},
    {"../data/sprites/npcs/old_man_2.png", textureID::old_man_2},
    {"../data/sprites/npcs/old_woman_1.png", textureID::old_woman_1},
    {"../data/sprites/npcs/teen_boy_1.png", textureID::teen_boy_1},
    {"../data/sprites/npcs/woman_1.png", textureID::woman_1},
    {"../data/sprites/npcs/ranger_man.png", textureID::ranger_man},
    {"../data/sprites/npcs/professor_oak.png", textureID::professor_oak},
    {"../data/sprites/npcs/scientific_1.png", textureID::scientific_1},
    
    {"../data/sprites/npcs/seller.png", textureID::seller},
    {"../data/sprites/npcs/champion_1.png", textureID::champion_1},
    
    {"../data/sprites/entities/entityItem.png", textureID::entityItem},
    {"../data/sprites/entities/entityPC.png", textureID::entityPC},
    
    {"../data/sprites/ui/npc_reactions/npc_bubble.png", textureID::npc_bubble},
    {"../data/sprites/ui/npc_reactions/npc_reactions.png", textureID::npc_reactions},
    
    // ===== // Pokemons
    {"../data/sprites/pokemons/marcacrin.png", textureID::marcacrinTex},
    {"../data/sprites/pokemons/cochignon.png", textureID::cochignonTex},
    {"../data/sprites/pokemons/mammochon.png", textureID::mammochonTex},
    {"../data/sprites/pokemons/pikachu.png", textureID::pikachuTex},
    {"../data/sprites/pokemons/raichu.png", textureID::raichuTex},
    {"../data/sprites/pokemons/etourmi.png", textureID::etourmiTex},
    {"../data/sprites/pokemons/etourvol.png", textureID::etourvolTex},
    {"../data/sprites/pokemons/etouraptor.png", textureID::etouraptorTex},
    {"../data/sprites/pokemons/mystherbe.png", textureID::mystherbeTex},
    {"../data/sprites/pokemons/galekid.png", textureID::galekidTex},
    {"../data/sprites/pokemons/galegon.png", textureID::galegonTex},
    {"../data/sprites/pokemons/galeking.png", textureID::galekingTex},
    
    // ===== // Pokemon Related
    {"../data/sprites/ui/pokemon_sex.png", textureID::ui_pokemonSex},
    {"../data/sprites/ui/type.png", textureID::ui_type},
    {"../data/sprites/ui/attack_cursor.png", textureID::ui_attackCursor},
    
    // ===== // UI
    {"../data/sprites/ui/dialog.png", textureID::ui_dialog},
    {"../data/sprites/ui/item_gift.png", textureID::ui_itemGift},
    
    // Pokedex
    {"../data/sprites/ui/pokedex_background.png", textureID::ui_pokedexBackground},
    {"../data/sprites/ui/pokedex_entry.png", textureID::ui_pokedexEntry},
    {"../data/sprites/ui/pokedex_cursor.png", textureID::ui_pokedexCursor},
    
    // Seller
    {"../data/sprites/ui/seller_background.png", textureID::ui_sellerBackground},
    {"../data/sprites/ui/seller_entry.png", textureID::ui_sellerEntry},
    {"../data/sprites/ui/seller_entry_cursor.png", textureID::ui_sellerCursor},
    
    // Character Selling Items
    {"../data/sprites/ui/buying_background.png", textureID::ui_buyingBackground},
    
    // Bag
    {"../data/sprites/ui/bag_background.png", textureID::ui_bagBackground},
    {"../data/sprites/ui/bag_category.png", textureID::ui_bagCateg},
    {"../data/sprites/ui/bag_category_selector.png", textureID::ui_bagCategSelector},
    {"../data/sprites/ui/bag_item_selector.png", textureID::ui_bagItemSelector},
    {"../data/sprites/ui/bag_arrows.png", textureID::ui_bagArrows},
    
    // Team
    {"../data/sprites/ui/team_display.png", textureID::ui_teamPreview},
    {"../data/sprites/ui/team_background.png", textureID::ui_teamBackground},
    {"../data/sprites/ui/team_entry.png", textureID::ui_teamEntry},
    {"../data/sprites/ui/team_menu_background.png", textureID::ui_teamMenuBackground},
    {"../data/sprites/ui/team_info.png", textureID::ui_teamInfo},
    
    // Box
    {"../data/sprites/ui/box_background.png", textureID::ui_boxBackground},
    {"../data/sprites/ui/box_cursor.png", textureID::ui_boxCursor},
    {"../data/sprites/ui/box_title_cursor.png", textureID::ui_boxTitleCursor},
    
    // Zone 
    {"../data/sprites/ui/zone_name_bg.png", textureID::ui_zoneNameBackground},
    
    // Attacks & Fight
    {"../data/sprites/ui/attack_background.png", textureID::ui_attackBackground},
    {"../data/sprites/ui/attack_category.png", textureID::ui_attackCategory},
    {"../data/sprites/ui/fight_background.png", textureID::ui_fightBackground},
    {"../data/sprites/ui/fight_menu.png", textureID::ui_fightMenuButtons},
    {"../data/sprites/ui/fight_choice.png", textureID::ui_fightMenuChoice},
    {"../data/sprites/ui/fight_attack_choice.png", textureID::ui_fightAttackChoice},
    {"../data/sprites/ui/fight_dialog.png", textureID::ui_fightDialog},
    {"../data/sprites/ui/fight_health.png", textureID::ui_fightHealth},
    {"../data/sprites/ui/fight/ability_display.png", textureID::ui_fightAbilityDisplay},
    
    // Menu
    {"../data/sprites/ui/menu_icons.png", textureID::ui_menuIcons},
    {"../data/sprites/ui/menu_arrow.png", textureID::ui_menuArrow},
    
    // Tools
    {"../data/sprites/ui/tools/name_chooser.png", textureID::ui_nameChooserBackground},
    
    // Character Infos
    {"../data/sprites/ui/badges.png", textureID::ui_badges},
    {"../data/sprites/ui/character_info_bg.png", textureID::ui_characterInfoBackground},
    
    // Status
    {"../data/sprites/ui/main_status.png", textureID::main_status},
};



TextureHolder* TextureHolder::buildStandardTH() {
    TextureHolder* textureHolder = new TextureHolder();
    
    // A boolean to know if all the textures were loaded
    bool texturesLoaded(true);
    
    // Load each item of the map
    for(auto it : textureFiles){
        // Update if a texture can't bea loaded
        texturesLoaded = textureHolder->loadFromFile(it.second, it.first) && texturesLoaded;
    }
    
    if(!texturesLoaded)
        throw(std::string("Some textures could not be loaded : \n") + textureHolder->m_missingTextures);
    
    // Return the standard texture holder
    return textureHolder;
}



TextureHolder::textureID TextureHolder::getNpcTexture(const std::string& str) {
    // Check if the string is in the map
    std::string texture = "../data/sprites/npcs/" + str + ".png";
    
    if(textureFiles.find(texture) == textureFiles.end())
        throw std::string("Can not find Npc Texture  : ") + texture;
    
    // Get the texture in the map
    return textureFiles.at(texture);
}



TextureHolder::~TextureHolder() {
    for(auto it = m_textureMap.begin(); it != m_textureMap.end(); it++){
        delete (*it).second;
    }
}



bool TextureHolder::loadFromFile(textureID id, const std::string& texturePath) {
    sf::Texture* newTexture = new sf::Texture;
    
    // Try to load the texture
    if(!newTexture->loadFromFile(texturePath)){
        m_missingTextures += std::string("Can't load texture : " + texturePath + "\n");
        return false;
    }
    
    // Insert the texture and get the return
    auto inserted = m_textureMap.insert(std::make_pair(id, newTexture));
    
    // Check if it was inserted correctly
    bool insertedCorrectly = inserted.second;
    
    if(!insertedCorrectly){
        // If the ID is already in the map show a related message
        if(m_textureMap.find(id) != m_textureMap.end())
            m_missingTextures += std::string("Can't insert texture " + texturePath + ". The TextureID is already in the TextureMap \n");
        else
            m_missingTextures += std::string("Can't insert texture " + texturePath + ". Reason unknown \n");
    }
    
    return insertedCorrectly;
}



const sf::Texture& TextureHolder::getTexture(textureID id) const {
    // Check that the texture is well in the Map
    assert(m_textureMap.find(id) != m_textureMap.end());
    
    // Returns the texture at id    
    // Throw an exception if nothing was found
    return *(m_textureMap.at(id));
}
