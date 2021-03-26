#include "Logger.hpp"

#include <iostream>


Logger::LogType Logger::m_minLevel = Logger::INFO;


void Log(const std::string& str, Logger::LogType type){
    // Shortcut
    Logger::Log(str, type);
}



void Logger::Log(const std::string& str, LogType type) {
    if(static_cast<int>(type) >= static_cast<int>(m_minLevel)){
        std::cout << str << std::endl;
    }
}



void Logger::setMinimalLevel(LogType type) {
    m_minLevel = type;
}
