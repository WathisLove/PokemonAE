#include "PokemonMetadata.hpp"
#include "../../Utilities.hpp"
#include "../../game_data/TrainerInfo.hpp"
#include "../../game_data/GameInfo.hpp"
#include "../../zones/Zone.hpp"

#include <iostream>


PokemonMetadata::PokemonMetadata() :
m_captureLevel(1),
m_captureZone(L"Zone inconnue"),
m_originalTrainer(gamedata::characterName.toWideString()){
    
}



void PokemonMetadata::readFromString(const std::string& str) {
    
    // Set a stringstream to the string
    std::stringstream stream;
    stream.str(str);
    
    
    // Extract all the values
    int level, zoneID, day, month, year, trainerID;
    
    stream >> level >> zoneID >> day >> month >> year >> trainerID;
    
    // Set the attributes
    m_captureLevel = level;
    m_captureZone = Zone::getZoneName((ZoneID) zoneID).toWideString();
    m_captureDate = Date(day, month, year);
    
    if(trainerID > 0)
        m_originalTrainer = TrainerInfo::getTrainerName(trainerID);
    else
        // Set the original trainer name to the current player name
        m_originalTrainer = gamedata::characterName.toWideString();
}



std::string PokemonMetadata::saveToString() {
    return toString(m_captureLevel) + " " + toString(m_captureZone) + " " + m_captureDate.saveAsString();
}



std::wstring PokemonMetadata::getCaptureDate() {
    return m_captureDate.getAsWString();
}



int PokemonMetadata::getCaptureLevel() {
    return m_captureLevel;
}



std::wstring& PokemonMetadata::getCaptureZone() {
    return m_captureZone;
}



std::wstring& PokemonMetadata::getOriginalTrainer() {
    return m_originalTrainer;
}



void PokemonMetadata::setCaptureLevel(int level) {
    
    // bind the capture level between 1 and 100
    if(level < 1)
        level = 1;
    if(level > 100)
        level = 100;
    
    // Set the attribute
    m_captureLevel = level;
}



void PokemonMetadata::setCaptureDate(int day, int month, int year) {
    m_captureDate = Date(day, month, year);
}



void PokemonMetadata::setToCurrentDate() {
    m_captureDate.setToCurrentDate();
}



void PokemonMetadata::setCaptureZone(ZoneID zoneID) {
    m_captureZone = Zone::getZoneName(zoneID).toWideString();
}



void PokemonMetadata::setOriginalTrainer(std::wstring trainerName) {
    m_originalTrainer = trainerName;
}
