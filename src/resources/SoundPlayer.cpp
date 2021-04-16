#include "SoundPlayer.hpp"


SoundPlayer::SoundPlayer() {

}



void SoundPlayer::play(SoundEffect::ID sound) {
    // Creates a Sound and add it to the list
    m_sounds.push_back(sf::Sound(m_soundBuffers.get(sound)));

    // Play the last sound
    m_sounds.back().play();
}



void SoundPlayer::removeStoppedSounds() {
    m_sounds.remove_if([](const sf::Sound& sound)
    {
        return sound.getStatus() == sf::Sound::Stopped;
    });
}