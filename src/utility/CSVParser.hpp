/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CSVParser.hpp
 * Author: Redbuzard
 *
 * Created on 15 octobre 2020, 09:02
 */

#ifndef CSVPARSER_HPP
#define CSVPARSER_HPP

#include <fstream>
#include <vector>
#include <string>


class CSVParser {
public:
    //=================// Constructor //==================//
    
    /**
     * Open a file and be ready for reading it
     */
    CSVParser(const std::string& filename, char separator = ';');
    
    
    /**
     * Destructor
     */
    virtual ~CSVParser();    
    
    
    //=================// Public methods //==================//
    
    
    /**
     * Read the next line in the file
     * @return true if a line was read
     */
    bool readLine();
    
    
    /**
     * Get the elements containd in the line 
     * @return a vector of string elements
     */
    std::vector<std::string>& getLineElements();
    
    
    /**
     * Set the CSV Parser to ignore or not the empty elements
     * @param ignore true if the Element must be ignored
     */
    void ignoreEmptyElements(bool ignore);
    
    
    
private:
    //=================// Private methods //==================//
    
    
    /**
     * Computes the elements of the current line
     */
    void computeLineElements();
    
    
    /**
     * Add a single element to the vector
     * @param element a constant reference to the element
     * @warning the element won't be added if empty
     */
    void addSingleElement(const std::string& element);
    
    
    //=================// Attributes //==================//

    // The file reader
    std::ifstream m_file;
    
    // The current Line
    std::string m_currentLine;
    
    // The current vector of result
    std::vector<std::string> m_currentElements;
    
    // The element separator
    char m_separator;
    
    // A boolean to know if we must ignore empty Elements
    bool m_ignoreEmpty;
};

#endif /* CSVPARSER_HPP */

