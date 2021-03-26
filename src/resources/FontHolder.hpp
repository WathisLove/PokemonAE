/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FontHolder.hpp
 * Author: Redbuzard
 *
 * Created on 10 juillet 2018, 11:27
 */

#ifndef FONTHOLDER_HPP
#define FONTHOLDER_HPP


#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class FontHolder {
public:
    
    enum FontID{
        dialogFont,
    };
    
    virtual ~FontHolder();

       
//================// Public Functions //=======================//    
    /**
     * Returns a constant reference to the texture corresponding to the id
     * @param id of the texture
     * @return a const reference to the texture
     */
    const sf::Font& getFont(FontID id) const;
    
    /**
     * Load a single texture from the disk into the map
     * @param id of the new texture
     * @param texturePath path to the texture file
     */
    void loadFromFile(FontID id, std::string fontPath);
    
    /**
     * Construct the standard TextureHolder used by the game
     * @return a pointer to the TextureHolder
     */
    static FontHolder* buildStandardFH();
    
private:
//================// Attributes //=======================//   
    // Map of textures
    std::map<FontID, sf::Font*> m_fontMap;
    
};

#endif /* FONTHOLDER_HPP */

