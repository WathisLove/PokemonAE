#include "MusicPlayer.hpp"
#include "../Utilities.hpp"
#include "../utility/Logger.hpp"



const std::map<Music::ID, std::string> MusicPlayer::musicFiles{

};



MusicPlayer::MusicPlayer() :
m_volume(100){

}



void MusicPlayer::play(Music::ID music) {
    // If the music file is in the map
    if(musicFiles.find(music) != musicFiles.end()){
        m_music.openFromFile(musicFiles.at(music));
        m_music.play();
    }
    else
        Log("Can't find music path for music ID " + toString(music));
}



void MusicPlayer::stop() {
    m_music.stop();
}



void MusicPlayer::setPaused(bool paused) {
    if(paused)
        m_music.pause();
    else
        m_music.play();
}



void MusicPlayer::setVolume(float volume) {
    m_volume = volume;

    m_music.setVolume(volume);
}
