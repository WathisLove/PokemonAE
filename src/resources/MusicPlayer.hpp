#ifndef POKEMONAE_MUSICPLAYER_HPP
#define POKEMONAE_MUSICPLAYER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include "Musics.h"



class MusicPlayer : public sf::NonCopyable {
public:
    /**
     * Creates a Music player
     */
    MusicPlayer();


    /**
     * Asks the player to play a music
     * @param music the Music ID
     */
    void play(Music::ID music);


    /**
     * Stops the current music
     */
    void stop();


    /**
     * Pause or unpause the music
     */
    void setPaused(bool paused);


    /**
     * Sets the music player volume
     * @param volume
     */
    void setVolume(float volume);


private:
    // The Player music
    sf::Music m_music;

    // The current Music
    Music::ID m_currentID;

    // Music volume
    float m_volume;

    // Map of filenames
    static const std::map<Music::ID, std::string> musicFiles;
};


#endif //POKEMONAE_MUSICPLAYER_HPP
