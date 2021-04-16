#ifndef POKEMONAE_SOUNDPLAYER_HPP
#define POKEMONAE_SOUNDPLAYER_HPP

#include <SFML/Audio.hpp>
#include <list>
#include "SoundEffects.hpp"
#include "SoundBufferHolder.hpp"


class SoundPlayer : public sf::NonCopyable{
public:

    /**
     * Constructor
     */
    SoundPlayer();


    /**
     * Plays a specific sound
     * @param sound the Sound ID
     */
    void play(SoundEffect::ID sound);

    /**
     * Removes the finished sounds to free Memory
     */
    void removeStoppedSounds();

private:
    // Sound Buffer holder
    SoundBufferHolder m_soundBuffers;

    // List of currently playing sounds
    std::list<sf::Sound> m_sounds;
};


#endif //POKEMONAE_SOUNDPLAYER_HPP
