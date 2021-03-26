/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utilities.hpp
 * Author: Redbuzard
 *
 * Created on 24 juin 2018, 10:29
 */

#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <random>
#include <string>
#include <sstream>
#include <vector>
#include <SFML/System/Vector2.hpp>


/**
 * Generate a random float between min and max
 */
float randomFloat(float min, float max);


/**
 * Generate a random int between min and max
 */
int randomInt(int min, int max);


/**
 * @return the given parameter as a string
 */
template <typename T>
std::string toString(T var){
    std::stringstream stream;
    stream << var;
    return stream.str();
};

template <>
std::string toString(bool var);

template <>
std::string toString(std::wstring var);



template <typename T>
std::wstring toWString(T var){
    std::wstringstream stream;
    stream << var;
    return stream.str();
};

template <>
std::wstring toWString(bool var);

template <>
std::wstring toWString(std::string var);



/**
 * Replace the first occurence of *marker* in *line* by *replacer*
 * @param line the line where we will replace marker
 * @param marker the sequence we try to replace
 * @param replacer the replacer of the marker
 */
void replaceInString(std::wstring& line, const std::wstring& marker, const std::wstring& replacer);


/**
 * Split a string into multiple
 * @param res a pointer to the result vector 
 * @param str a const reference to the String
 * @param separator the character separating the strings
 */
void split(std::vector<std::string>* res, const std::string& str, char separator);



/**
 * Overriden operator used to multiply a Vector2i by a float
 * @param vec a const reference to the Vector2i
 * @param f the float
 * @return a Vector2f, result of the product of vec by f
 */
sf::Vector2f operator*(sf::Vector2i const& vec, float const& f);



/**
 * Limit a value between a min and max value
 * @param val the current value 
 * @param min the minimum value
 * @param max the maximum value
 * @return the final value 
 */
template<typename T>
T limit(const T& val, const T& min, const T& max){
    // Limit val between min and max
    return std::max(min, std::min(val, max));
}



#endif /* UTILITIES_HPP */
