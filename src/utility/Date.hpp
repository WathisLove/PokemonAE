#ifndef DATE_HPP
#define DATE_HPP

#include <string>



class Date{
public:
    
//===================// Constructors //===================//
    
    /**
     * Default constructor
     * @warning set the Date to 01/01/1999
     */
    Date();
    
    /**
     * A constructior initializing the Date to a defined date
     * @param day the day as an int (1-31) 
     * @param month the month as an int (1-12) 
     * @param year the year as an int
     */
    Date(int day, int month, int year);
    
    
//===================// Public Methods //===================//
    
    
    /**
     * Set the date object to the current date
     */
    void setToCurrentDate();
    
    
    /**
     * Save the current Date as a string
     * @return the date as a string to be saved
     */
    std::string saveAsString();
    
    
    
//===================// Getters //===================//
    
    /**
     * Return the Date as a wstring
     * @return the Date as a wstring
     */
    std::wstring getAsWString();
    
//===================// Static Public Methods //===================//
   
    
    /**
     * Get the current date without formatting it 
     * The date will come as : "27 12 2019" ("December, 27 of 2019")
     * @return the current date as a wstring
     */
    static std::string getCurrentDate();


    /**
     * Get the current date with a french format 
     * @return the formated current date as a wstring
     */
    static std::wstring getCurrentFormatedDate();


    /**
     * Get the current date with a french format 
     * @param day the day as an int (1-31)
     * @param month the month as an int (1-12)
     * @param year the year as an int
     * @return the formated current date as a wstring
     */
    static std::wstring getFormatedDate(int day, int month, int year);
    
    
private:
    
//===================// Attributes  //===================//
    
    // Day, month and year as int
    int m_day, m_month, m_year;
    
    // The Date as a string
    std::wstring m_formatedDate;
};



#endif /* DATE_HPP */
