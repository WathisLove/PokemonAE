#include "ZoneDialogLoader.hpp"
#include "../zones/Zone.hpp"
#include <algorithm>
#include <iostream>

ZoneDialogLoader::ZoneDialogLoader(const std::string& filename) :
CSVParser(filename),
m_zoneID(ZoneID::undefined_zone){
    // Keep the Empty elements
    ignoreEmptyElements(false);
    
    // Ignore the first line
    readLine();
    
    // Read each line
    while(readLine()){
        // Get the elements
        std::vector<std::string>& elements = getLineElements();
        
        if(elements.size() == 6){
            createZoneDialog(elements[0], elements[1], elements[2], elements[3], elements[4], new sf::String(elements[5]));
        }
        else
            std::cout << "Found " << elements.size() << " elements when creating ZoneDialogs" << std::endl;
    }
}



ZoneDialogLoader::~ZoneDialogLoader() {
    // Delete each Zone Dialog
    for(auto it = m_allZoneDialogs.begin(); it != m_allZoneDialogs.end(); it++){
        delete it->second;
    }
}



void ZoneDialogLoader::loadZoneDialogs(ZoneID zoneID) {
    // Exit if we already have the correct ID
    if(zoneID == m_zoneID)
        return;
    
    // Update the current zone ID
    m_zoneID = zoneID;
    
    // Find the Map range
    auto itRange = m_allZoneDialogs.equal_range(zoneID);
    
    // Put each ZoneDialog in the vector
    for(auto it = itRange.first; it != itRange.second; it++){
        m_zoneDialogs.push_back(it->second);
    }
}



const std::vector<ZoneDialog*>& ZoneDialogLoader::getZoneDialogs() const {
    return m_zoneDialogs;
}



void ZoneDialogLoader::createZoneDialog(std::string zone, std::string x, std::string y, std::string width, std::string height, sf::String* string) {
    // Get the X an Y values
    int xCoord = atoi(x.c_str());
    int yCoord = atoi(y.c_str());
    
    // Convert Width and Height
    int w = atoi(width.c_str());
    int h = atoi(height.c_str());
    
    // Get the Zone ID
    ZoneID id = Zone::fromFilenameToID(zone);
    
    // Create the Zone Dialog and put it in the map
    m_allZoneDialogs.insert(std::make_pair(id, new ZoneDialog(string, xCoord, yCoord, w, h)));
}
