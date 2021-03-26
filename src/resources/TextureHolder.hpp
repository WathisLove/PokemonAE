/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TextureHolder.hpp
 * Author: Redbuzard
 *
 * Created on 18 juin 2018, 09:04
 */

#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP


#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class TextureHolder {
public:
//================// Public Functions //=======================//
    enum textureID{
        // ===== // Tilesets
        tileSet,
        itemsTileSet,
        // ===== // Character
        character,
        characterFull,
        // ===== // NPCs
        old_man_1,
        old_man_2,
        old_woman_1,
        teen_boy_1,
        woman_1,
        ranger_man,
        professor_oak,
        scientific_1,
        // Champions
        champion_1,
        // Others
        seller,
        // Entities
        entityItem,
        entityPC,
        // NPC Reactions
        npc_bubble,
        npc_reactions,
        // ===== // Pokemons
        marcacrinTex,
        cochignonTex,
        mammochonTex,
        pikachuTex,
        raichuTex,
        etourmiTex,
        etourvolTex,
        etouraptorTex,
        mystherbeTex,
        galekidTex,
        galegonTex,
        galekingTex,
        // ===== // Pokemon Related
        ui_pokemonSex,
        ui_type,
        ui_attackCursor,
        // ===== // UI
        ui_dialog,
        ui_itemGift,
        ui_bagBackground,
        ui_bagCateg,
        ui_bagCategSelector,
        ui_bagItemSelector,
        ui_bagArrows,
        ui_teamPreview,
        ui_teamBackground,
        ui_teamEntry,
        ui_teamMenuBackground,
        ui_teamInfo,
        ui_boxBackground,
        ui_boxCursor,
        ui_boxTitleCursor,
        ui_zoneNameBackground,
        ui_pokedexBackground,
        ui_pokedexEntry,
        ui_pokedexCursor,
        ui_sellerBackground,
        ui_sellerEntry,
        ui_sellerCursor,
        ui_buyingBackground,
        // Fight UI
        ui_attackBackground,
        ui_attackCategory,
        ui_fightBackground,
        ui_fightMenuButtons,
        ui_fightMenuChoice,
        ui_fightAttackChoice,
        ui_fightDialog,
        ui_fightHealth,
        ui_fightAbilityDisplay,
        ui_menuIcons,
        ui_menuArrow,
        // Tools textures
        ui_nameChooserBackground,
        // Character Infos
        ui_badges,
        ui_characterInfoBackground,
        // ===== // Status
        main_status,
        
    };
    
    
    virtual ~TextureHolder();

    
//================// Public Functions //=======================//    
    /**
     * Returns a constant reference to the texture corresponding to the id
     * @param id of the texture
     * @return a const reference to the texture
     */
    const sf::Texture& getTexture(textureID id) const;
    
    /**
     * Load a single texture from the disk into the map
     * @param id of the new texture
     * @param texturePath path to the texture file
     * @return true if the texture was loaded
     */
    bool loadFromFile(textureID id, const std::string& texturePath);
    
    /**
     * Construct the standard TextureHolder used by the game
     * @return a pointer to the TextureHolder
     */
    static TextureHolder* buildStandardTH();
    
    
    /**
     * Get the Npc Texture corresponding to the string stored in Npc Files
     * @param str a const reference to the string in the file
     * @return the Texture ID
     */
    textureID getNpcTexture(const std::string& str);
    
private:
//================// Attributes //=======================//    
    
    // A static map for the texture files
    const static std::map<std::string, textureID> textureFiles; 
    
    // Map of textures
    std::map<textureID, sf::Texture*> m_textureMap;
    
    // A string for the potential missing textures
    std::string m_missingTextures;
};

#endif /* TEXTUREHOLDER_HPP */

