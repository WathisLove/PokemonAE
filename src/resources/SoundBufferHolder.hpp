
#ifndef POKEMONAE_SOUNDBUFFERHOLDER_HPP
#define POKEMONAE_SOUNDBUFFERHOLDER_HPP

#include <SFML/Audio.hpp>
#include <map>

#include "SoundEffects.hpp"

class SoundBufferHolder : sf::NonCopyable{
public:
    /**
     * Creates a Holder and loads the SoundBuffers in a map
     */
    SoundBufferHolder();


    /**
     * Gets the sound buffer for a specific sound
     * @param sound the SoundEffect ID
     * @return a const reference to the Sound buffer
     */
    const sf::SoundBuffer& get(SoundEffect::ID sound) const;

private:
    /**
     * Load a single Sound buffer from the disk into the map
     */
    void loadFromFile(SoundEffect::ID sound, const std::string& soundPath);


    // Map of sound buffers
    std::map<SoundEffect::ID, sf::SoundBuffer> m_soundBuffers;
};


#endif //POKEMONAE_SOUNDBUFFERHOLDER_HPP
