/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PokemonMetadata.hpp
 * Author: Redbuzard
 *
 * Created on 27 novembre 2019, 21:49
 */

#ifndef POKEMONMETADATA_HPP
#define POKEMONMETADATA_HPP

#include "../../zones/ZoneID.hpp"
#include "../../utility/Date.hpp"
#include <string>

class PokemonMetadata {
public:
    
//===================// Constructor //===================//
    
    /**
     * Fill the attributes with blank data
     */
    PokemonMetadata();
    
    
//===================// Public Methods //===================//
    
    
    /**
     * Read the pokemon Metadata from a string
     * @param str a constant reference to the wstring
     */
    void readFromString(const std::string& str);
    
    
    /**
     * Save the Metadatas as a string
     * @return a string containing the metadata
     */
    std::string saveToString();
    
    
    
//===================// Getters / Setters //===================//
    
    /**
     * Set the capture level 
     * @param level the level at which the pokemon was captured D of the new Zone
     */
    void setCaptureLevel(int level);
    
    /**
     * Set the capture zone 
     * @param zoneID the ID of the new Zone
     */
    void setCaptureZone(ZoneID zoneID);
    
    /**
     * Set the original trainer name 
     * @param trainerName the trainer name as a wstring
     */
    void setOriginalTrainer(std::wstring trainerName);
    
    /**
     * Set the capture date
     * @param day the day at which the pokemon was captured as an int (1-31)
     * @param month the month at which the pokemon was captured as an int (1-12)
     * @param year the year at which the pokemon was captured as an int
     */
    void setCaptureDate(int day, int month, int year);
    
    /**
     * Set the Capture Date to the current Date
     */
    void setToCurrentDate();
    
    
    
    /**
     * Get the capture zone 
     * @return a reference to the wstring containing the capture zone
     */
    std::wstring& getCaptureZone();
    
    /**
     * Get the original trainer 
     * @return a reference to the wstring containing the original trainer name
     */
    std::wstring& getOriginalTrainer();
    
    /**
     * Get the capture date 
     * @return a reference to the wstring containing the capture date
     */
    std::wstring getCaptureDate();
    
    /**
     * Get the level at which the pokemon was captured
     * @return the level as an int
     */
    int getCaptureLevel();
    
    
private:
    
//===================// Attributes //===================//
    
    // Capture level
    int m_captureLevel;
    
    // Capture zone
    std::wstring m_captureZone;
    
    // Capture Date
    Date m_captureDate;
    
    // Dresseur d'origine
    std::wstring m_originalTrainer;
};

#endif /* POKEMONMETADATA_HPP */

