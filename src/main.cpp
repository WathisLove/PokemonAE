#include "states/StateStack.hpp"
#include "Context.hpp"
#include <iostream>
#include <SFML/Audio.hpp>
#include <fstream>
#include "Utilities.hpp"

#include "pokemons/XPCurves.hpp"
#include "utility/Date.hpp"


template <typename C>
void printCrash(const C& ref){
    std::ofstream crashFile("crash_reports/"+toString(std::time(0))+".txt");
    
    if(!crashFile) // If the file did not open correctly
        std::cout << "Can't write in crash file" << std::endl;
    else{
        crashFile << ref;
        
        // Close the file
        crashFile.close();
    }
}


int main()
{
    
    try{
        Context context;
        StateStack stack(context);
    }
    catch(std::string s){
        std::cout << s << std::endl;
        printCrash(s);
    }
    catch(const char* c){
        std::cout << "Threw a const char" << std::endl;
        std::cout << toString(c) << std::endl;
    }
    
    return 0;
}