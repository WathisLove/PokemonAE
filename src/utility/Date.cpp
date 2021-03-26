#include "Date.hpp"
#include "../Utilities.hpp"

#include <ctime>
#include <sstream>

#include <iostream>

Date::Date() :
Date(1,1,1999){

}



Date::Date(int day, int month, int year) :
m_day(day),
m_month(month),
m_year(year){
    m_formatedDate = getFormatedDate(day, month, year);
} 



std::string Date::saveAsString() {
    return toString(m_day) + " " + toString(m_month) + " " + toString(m_month);
} 



void Date::setToCurrentDate() {
    std::string date = getCurrentDate();
    
    // Set a stringstream to the date
    std::stringstream stream;
    stream.str(date);
    
    // Extract the Day, the Month and the Year
    stream >> m_day >> m_month >> m_year;
    
    
    // Set the formated date wstring
    m_formatedDate = getFormatedDate(m_day, m_month, m_year);
}



std::string Date::getCurrentDate(){
    
    // A time_t to hold the raw time in seconds
    time_t rawtime;
    
    // A structure to hold the local time 
    struct tm * timeinfo;

    // Get the time
    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    
    
    // Convert the time into a buffer as "27 12 2019" ("December, 27 of 2019")
    char res[80];
    strftime(res,80,"%d %m %Y",timeinfo);
    
    
    return std::string(res);
}



std::wstring Date::getCurrentFormatedDate(){
    std::string date = getCurrentDate();
    
    
    // Set a stringstream to the date
    std::stringstream stream;
    stream.str(date);
    
    // Extract the Day, the Month and the Year
    int day, month, year;
    
    stream >> day >> month >> year;
    
    
    // Return the date as a string
    return getFormatedDate(day, month, year);
}



std::wstring Date::getFormatedDate(int day, int month, int year){
    
    // Array to months from number to string
    std::wstring monthTab[] = { L"Janvier",L"Février",L"Mars",L"Avril",L"Mai",L"Juin",
                                L"Juillet",L"Août",L"Septembre",L"Octobre",L"Novembre",L"Décembre"};
    
    return toWString(day) + L" " + monthTab[month-1] + L" " + toWString(year);
}



std::wstring Date::getAsWString() {
    return m_formatedDate;
}
