#include <map>
#include <cassert>
#include <iostream>
#include <cstdlib>

#include "EnumLoader.hpp"
#include "CSVParser.hpp"



EnumLoader::EnumLoader(const std::string& filename) {
    // Csv parser
    CSVParser parser(filename, ';');
    
    //// Parse
    // Read a line for title (and ignore it)
    parser.readLine();
    
    // Read the following lines
    while(parser.readLine()){
        std::vector<std::string> elements = parser.getLineElements();
        
        if(elements.size() >= 2){
            // Assert the string is not in the map
            std::string str = elements[0];
            assert(!hasString(str));
            
            // Convert the int value
            int value = atoi(elements[1].c_str());
            assert(!hasValue(value));
            
            m_stringToInt[str] = value;
            m_intToString[value] = str;
       }
    }
}



int EnumLoader::stringToInt(const std::string& str) const {
    // Assert the value is in the map
    if(m_stringToInt.find(str) == m_stringToInt.end()){
        throw std::string("Can't find EnumLoader::toInt for " + str);
    }
    
    return m_stringToInt.at(str);
}



std::string EnumLoader::intToString(int i) const {
    // Assert the value is in the map
    if(m_intToString.find(i) == m_intToString.end()){
        throw std::string("Can't find EnumLoader::toString for " + i);
    }
    
    return m_intToString.at(i);
}



bool EnumLoader::hasString(const std::string& str) const {
    return m_stringToInt.find(str) != m_stringToInt.end();
}



bool EnumLoader::hasValue(int i) const {
    return m_intToString.find(i) != m_intToString.end();
}
