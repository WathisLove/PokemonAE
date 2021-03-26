#include "Utilities.hpp"
#include "pokemons/Pokemon.hpp"
#include <iostream>
#include <algorithm>

std::default_random_engine generator;


float randomFloat(float min, float max){
    std::uniform_real_distribution<float> distribution(min,max);
    return distribution(generator);
}



int randomInt(int min, int max){
    std::uniform_int_distribution<int> distribution(min,max);
    return distribution(generator);
}


template<>
std::string toString<bool>(bool var)
{
    if(var) return "true";
    else return "false";
};


template<>
std::string toString<std::wstring>(std::wstring var)
{
    std::string str(var.begin(), var.end());
    
    return str;
};



template<>
std::wstring toWString<bool>(bool var)
{
    if(var) return L"true";
    else return L"false";
};


template<>
std::wstring toWString<std::string>(std::string var)
{
    std::wstring wstr(L"");
    for(char c : var){
        wstr += toWString(c);
    }
    
    return wstr;
};



void replaceInString(std::wstring& line, const std::wstring& marker, const std::wstring& replacer){
    // Try to find the occurence of the marker
    size_t position = line.find(marker);
    
    // npos is returnd when marker is not found
    if(position < std::wstring::npos){
        // We replace in line
        line.replace(position, marker.size(), replacer);
    }
    else{
        std::cout << "Could not found " << toString(marker) << " in '" << toString(line) << "' dialog" << std::endl;
    }
}



void split(std::vector<std::string>* res, const std::string& str, char separator){
    // Locate the sperator position
    int lastSep(-1);
    int posSep(0);
    
    // If not separator are in the string
    if(str.size() == 0)
        return;
    
    if(str.find(separator) == str.npos){
        // Add the str and return
        res->push_back(str);
        return;
    }
    
    while(posSep != str.npos){
        // Get the position of the next separator
        posSep = str.find(separator, lastSep+1);
        std::cout << "Found one separator at " << posSep << std::endl;
        
        // Push tha sub string in the vector
        res->push_back(str.substr(lastSep+1, posSep-lastSep-1));
        
        // Update the last Separator
        lastSep = posSep;
    }
}



sf::Vector2f operator*(sf::Vector2i const& vec, float const& f){
    return sf::Vector2f(vec.x * f, vec.y * f);
}