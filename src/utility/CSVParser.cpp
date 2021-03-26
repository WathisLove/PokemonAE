#include "CSVParser.hpp"
#include "Logger.hpp"

#include <iostream>
#include <cassert>
#include <vector>

CSVParser::CSVParser(const std::string& filename, char separator) :
m_separator(separator),
m_file(filename),
m_ignoreEmpty(false){
    
    // Check the file was opened
    if(!m_file){
        std::cout << "Could not open " << filename << std::endl;
    }
}



CSVParser::~CSVParser() {
    // Close the file
    if(m_file)
        m_file.close();
}



bool CSVParser::readLine() {
    // Compute the line elements if a line was read
    if(std::getline(m_file, m_currentLine)){
        computeLineElements();
        return true;
    }
    
    return false;
}



std::vector<std::string>& CSVParser::getLineElements() {
    return m_currentElements;
}



void CSVParser::ignoreEmptyElements(bool ignore) {
    m_ignoreEmpty = ignore;
}



void CSVParser::computeLineElements() {
    // CLear the previous elements
    m_currentElements.clear();
    
    
    // Find the differents elements
    std::string element;
    char c;
    
    for(size_t i = 0; i < m_currentLine.size(); i++){
        
        // Get the character
        c = m_currentLine[i];
        
        // If c is the separator
        if(c == m_separator){
            addSingleElement(element);
            element.clear();
        }
        else{
            // Add the character to the element
            element += c;
        }
    }
    
    // Add the last element that might not be finished
    addSingleElement(element);
}



void CSVParser::addSingleElement(const std::string& element) {
    // Ignore empty element if needed
    if(element.empty()){
        if(!m_ignoreEmpty)
            m_currentElements.push_back(element);
    }
    else
        m_currentElements.push_back(element);
}
