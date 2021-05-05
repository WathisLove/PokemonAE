#include "MusicPlayer.hpp"
#include "../Utilities.hpp"
#include "../utility/Logger.hpp"



const std::map<Music::ID, std::string> MusicPlayer::musicFiles{
        {Music::City_1, "data/musics/city_1.ogg"},
        {Music::Road_1, "data/musics/road_1.ogg"},
};



MusicPlayer::MusicPlayer() :
m_currentID(Music::NONE){
    setVolume(35);
}



void MusicPlayer::play(Music::ID music) {
    if(music != m_currentID){
        // Stop if requesting NONE
        if(music == Music::NONE)
            m_music.stop();

        // If the music file is in the map
        else if(musicFiles.find(music) != musicFiles.end()){
            m_music.openFromFile(musicFiles.at(music));
            m_music.play();
            m_music.setLoop(true);
        }
        else
            Log("Can't find music path for music ID " + toString(music));

        // Update the current music playing
        m_currentID = music;
    }
}



void MusicPlayer::stop() {
    m_music.stop();

    m_currentID = Music::NONE;
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
