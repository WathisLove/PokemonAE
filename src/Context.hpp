/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Context.hpp
 * Author: Redbuzard
 *
 * Created on 4 juillet 2018, 10:50
 */

#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Graphics.hpp>

class TextureHolder;
class FontHolder;
class InteractionHolder;
class SoundPlayer;
class MusicPlayer;


class Context {
public:
    Context();
    
    virtual ~Context();

    /**
     * Return a reference to the Render Window
     */
    sf::RenderWindow& getRenderWindow();
    
    /**
     * Return a pointer to the texture holder
     * @return 
     */
    TextureHolder* getTextureHolder();
    
    /**
     * Return a pointer to the font holder
     * @return 
     */
    FontHolder* getFontHolder();
    
    /**
     * Return a pointer to the font holder
     * @return a pointer to the Interaction Holder
     */
    InteractionHolder* getInteractionHolder();


    /**
     * Return a pointer to the SoundBuffer holder
     * @return a pointer to the SoundBuffer holder
     */
    SoundPlayer* getSoundPlayer();


    /**
     * Returns a pointer to the Music Player
     * @return
     */
    MusicPlayer* getMusicPlayer();
    
    
    /**
     * Return the coordinates of the top left corner of the window
     */
    sf::Vector2f getWindowTopLeftCorner() const;
    
    
    /**
     * Return the coordinates at the middle of the window
     */
    sf::Vector2f getWindowCenter() const;
    
    
private:
//================// Attributes //=======================//
    // Render window
    sf::RenderWindow m_window;
    
    // Texture Holder
    TextureHolder* m_textureHolder;
    
    // Font Holder
    FontHolder* m_fontHolder;

    // Interaction Holder
    InteractionHolder* m_interactionHolder;

    // Sound Buffer Holder
    SoundPlayer* m_soundPlayer;

    // Music Player
    MusicPlayer* m_musicPlayer;

};

#endif /* CONTEXT_HPP */

