#include "SoundBufferHolder.hpp"
#include "../utility/Logger.hpp"
#include "../Utilities.hpp"


SoundBufferHolder::SoundBufferHolder() {
    // Load the sounds
    // ...
}



const sf::SoundBuffer & SoundBufferHolder::get(SoundEffect::ID sound) const {
    if(m_soundBuffers.find(sound) != m_soundBuffers.end()){
        return m_soundBuffers.at(sound);
    }
    else
        Log("Can't find sound for SoundID " + toString(sound));
}



void SoundBufferHolder::loadFromFile(SoundEffect::ID sound, const std::string &soundPath) {
    sf::SoundBuffer buffer;

    if(buffer.loadFromFile(soundPath))
        m_soundBuffers[sound] = buffer;
    else
        Log("Can't load sound for SoundID " + toString(sound));
}