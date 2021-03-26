/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ZoneDialogLoader.hpp
 * Author: Redbuzard
 *
 * Created on 12 novembre 2020, 18:04
 */

#ifndef ZONEDIALOGLOADER_HPP
#define ZONEDIALOGLOADER_HPP

#include <vector>
#include <map>
#include "../utility/CSVParser.hpp"
#include "../zones/ZoneDialog.hpp"
#include "ZoneID.hpp"


class ZoneDialogLoader : public CSVParser{
public:
//===============// Constructor //===============//
        
    /**
     * Constructor
     */
    ZoneDialogLoader(const std::string& filename);
    
    
    /**
     * Destructor
     */
    virtual ~ZoneDialogLoader();
    
    
//===============// Public method //===============//
    
    
    /**
     * Load the ZoneDialogd of a given zone
     * @param zoneID the Zone ID we want to load
     */
    void loadZoneDialogs(ZoneID zoneID);
    
    
//===============// Getters //===============//
    
    /**
     * Get the ZoneDialogs loaded by the 
     * @return a const reference to the vector of pointers
     */
    const std::vector<ZoneDialog*>& getZoneDialogs() const;
    
private:
//===============// Private method //===============//
    
    /**
     * Creates a zone Dialog from 4 strings and add it to the map
     * @param zone the zone name
     * @param x the x coord
     * @param y the y coord
     * @param width the width of the ZoneDialog
     * @param height the height of the ZoneDialog
     * @param string a pointer to the String
     */
    void createZoneDialog(std::string zone, std::string x, std::string y, std::string width, std::string height, sf::String* string);
    
    
//===============// Attributes //===============//
    
    // The current Zone
    ZoneID m_zoneID;
    
    // Vector of ZoneDialogs
    std::vector<ZoneDialog*> m_zoneDialogs;
    
    // Multimap for all the ZoneDialogs
    std::multimap<ZoneID, ZoneDialog*> m_allZoneDialogs;
};

#endif /* ZONEDIALOGLOADER_HPP */

