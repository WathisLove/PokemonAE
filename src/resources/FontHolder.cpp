#include "FontHolder.hpp"


#include <iostream>

FontHolder* FontHolder::buildStandardFH() {
    FontHolder* fontHolder = new FontHolder;
    // Load all the stadard textures
    fontHolder->loadFromFile(FontID::dialogFont, "../data/fonts/calibri.ttf");
    
    // Return the standard texture holder
    return fontHolder;
}



FontHolder::~FontHolder() {
    for(auto it = m_fontMap.begin(); it != m_fontMap.end(); it++){
        delete (*it).second;
    }
}



void FontHolder::loadFromFile(FontID id, std::string fontPath) {
    sf::Font* newFont = new sf::Font;
    
    // Try to load the texture
    if(!newFont->loadFromFile(fontPath))
        throw std::string("Can't load texture : " + fontPath);
    
    // Insert the texture and get the return
    auto inserted = m_fontMap.insert(std::make_pair(id, newFont));
    
    // Check if it was inserted correctly
    bool insertedCorrectly = inserted.second;
    
    if(!insertedCorrectly)
        throw std::string("Can't insert texture " + fontPath);
}



const sf::Font& FontHolder::getFont(FontID id) const {
    // Returns the texture at id
    // Throw an exception if nothing was found
    return *(m_fontMap.at(id));
}
