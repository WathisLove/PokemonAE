#include "MoverFabric.hpp"

#include "../movements/MoverHeaders.hpp"

#include <sstream>
#include <iostream>


const std::map<std::string, MovementType> MoverFabric::movementStrings{
    {"NO", MovementType::NoMove},
    {"LU", MovementType::LookUp},
    {"LR", MovementType::LookRight},
    {"LD", MovementType::LookDown},
    {"LL", MovementType::LookLeft},
    {"GU", MovementType::GoUp},
    {"GR", MovementType::GoRight},
    {"GD", MovementType::GoDown},
    {"GL", MovementType::GoLeft},
};



EntityMover* MoverFabric::createMover(const std::string& str) const {
    // Extract the first parameter (2 letters : mover type)
    std::string moverType = str.substr(0, 2);
    
    // Extract the parameters
    std::string params;
    if(str.size() > 2){
        params = str.substr(2);
    }
    
    // Create the correct mover
    if(moverType == "CM")
        return createContinuousMover(params);
    else if(moverType == "NM")
        return createNoMover();
    else if(moverType == "ZM")
        return createRandomMover(params);
    else if(moverType == "RM")
        return createRotationnalMover(params);
    else if(moverType == "SM")
        return createSequenceMover(params);
    else{
        std::cout << "No corresponding mover found for " << str << std::endl;
        std::cout << "Returned NoMover instead" << std::endl;
        return createNoMover();
    }
}



EntityMover* MoverFabric::createContinuousMover(const std::string& params) const {
    // String stream
    std::istringstream stream(params);
    
    // Buffer for the move strings
    std::string firstMove;
    
    // Break time
    float breakTime;
    
    // Get the first move
    stream >> firstMove >> breakTime;
    
    // Create the Mover
    return new ContinuousMover(getMovement(firstMove), breakTime);
}



EntityMover* MoverFabric::createNoMover() const {
    return new NoMover();
}



EntityMover* MoverFabric::createRandomMover(const std::string& params) const {
    // String stream
    std::istringstream stream(params);
    
    // Parmeters extracted
    sf::IntRect rect;
    float pauseTime;
    
    // Extract
    stream >> rect.left >> rect.top >> rect.width >> rect.height >> pauseTime;
 
    // Create the Mover
    return new RandomMover(rect, sf::Vector2i(rect.left, rect.top), pauseTime);
}



EntityMover* MoverFabric::createRotationnalMover(const std::string& params) const {
    // String stream
    std::istringstream stream(params);
    
    // Buffer for the move strings
    std::string firstMove;
    
    // Break time
    float breakTime;
    
    // Clockwise (1 == true or 0)
    bool clockwise;
    
    // Get the first move
    stream >> firstMove >> breakTime >> clockwise;
    
    
    // Create the Mover
    return new RotationnalMover(getMovement(firstMove), breakTime, clockwise);
}



EntityMover* MoverFabric::createSequenceMover(const std::string& params) const {
    // String stream
    std::istringstream stream(params);
    
    // The resulting Mover
    SequenceMover* mover = new SequenceMover();
    
    // Extract the break time
    float breakTime;
    stream >> breakTime;
    
    // Repeat
    bool repeat = false;
    if(stream >> repeat) {
        mover->setLoop(repeat);
    }
    
    // The last Move extracted
    std::string moveStr("");
    
    std::cout << "Sequence Mover : ";
    // Extract each Movement
    while(stream >> moveStr){
        std::cout << moveStr << " ";
        
        // Add the movement
        mover->pushMove(getMovement(moveStr), breakTime);
    }
    std::cout << std::endl;
 
    // Create the Mover
    return mover;
}



MovementType MoverFabric::getMovement(const std::string& str) const {
    // Try to locate the move in the map
    auto it = movementStrings.find(str);
    
    // Return the movement found in the zone
    if(it != movementStrings.end())
        return it->second;
    else
        return MovementType::NoMove;
}
