/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Logger.hpp
 * Author: Redbuzard
 *
 * Created on 2 décembre 2020, 16:15
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger {
public:
    Logger();
    
//=================// Public enum //==================//
    
    enum LogType{
        INFO = 0,
        FILE_INFO = 1,
        NPC_INFO = 2,
        WARNING = 10,
        WARNING_CODE = 11,
        ERROR = 20,
        FILE_ERROR = 21,
        
        NEVER_DISPLAYED = 1000
    };
    
//=================// Static methods //==================//
    
    /**
     * Log a string with INFO level
     * @param str a const reference to the string that will be displayed
     */
    static void Log(const std::string& str, LogType type = INFO);
    
    
    /**
     * Set the minimal level of the displayed infos
     * @param type the LogType level
     */
    static void setMinimalLevel(LogType type);
    
    
private:
//=================// Static Attributes //==================//
   
    // Minimal level
    static LogType m_minLevel;
};



// Shortcut call
void Log(const std::string& str, Logger::LogType type = Logger::INFO);


#endif /* LOGGER_HPP */

