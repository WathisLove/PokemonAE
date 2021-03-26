/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EnumLoader.hpp
 * Author: Redbuzard
 *
 * Created on 16 octobre 2020, 10:51
 */

#ifndef ENUMLOADER_HPP
#define ENUMLOADER_HPP

#include <string>
#include <map>


/**
 * Class used to load enums from files and then allow conversion between string and int
 */
class EnumLoader {
public:   
    
    //=================// Constructor //==================//
    /**
     * Load an enum from a file
     */
    EnumLoader(const std::string& filename);
    
    
    //=================// Methods //==================//
    
    /**
     * Converts a enum string value to its numerical value
     * @param str a const reference to the string
     * @return the value corresponding to the string
     */
    int stringToInt(const std::string& str) const;
    
    
    /**
     * Converts a int value to the enum string
     * @param i the value 
     * @return a std string corresponding to the value
     */
    std::string intToString(int i) const;
    
    
    /**
     * Check if the Enum loaded the corresponding string
     * @param str a const reference to the String
     * @return true if the string was in the map
     */
    bool hasString(const std::string& str) const;
    
    
    /**
     * Check if the Enum loaded the corresponding int
     * @param i the value we are looking for
     * @return true if one string has the associated value
     */
    bool hasValue(int i) const;
    
    
private:
    //=================// Attributes //==================//
    
    // Map associating string with values
    std::map<std::string, int> m_stringToInt;
    
    // Map associating string with values
    std::map<int, std::string> m_intToString;
};

#endif /* ENUMLOADER_HPP */

