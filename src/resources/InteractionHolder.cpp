#include <cassert>
#include <cstdlib>
#include <iostream>

#include "InteractionHolder.hpp"
#include "../utility/CSVParser.hpp"
#include "../utility/EnumLoader.hpp"
#include "../utility/Logger.hpp"
#include "../entities/NPCId.hpp"

#include "../entities/interactions/DialogInteraction.hpp"
#include "../entities/interactions/ReactionInteraction.hpp"
#include "../entities/interactions/FightInteraction.hpp"
#include "../entities/interactions/ItemInteraction.hpp"
#include "../entities/interactions/BadgeInteraction.hpp"
#include "../entities/interactions/HealInteraction.hpp"
#include "../entities/interactions/ChoiceInteraction.hpp"
#include "../entities/interactions/MoveInteraction.hpp"

#include "../zones/Zone.hpp"

#include <SFML/System/String.hpp>



const std::map<std::string, ReactionType> InteractionHolder::reactionsStrings = {
    {"HEART", ReactionType::RHeart},
    {"EXCLAMATION", ReactionType::RExclamation},
    {"SAD", ReactionType::RSad},
    {"SMILE", ReactionType::RSmile},
    {"SURPRISED", ReactionType::RSurprised},
};


const std::map<std::string, InteractionCondition> InteractionHolder::conditionStrings {
    {"UNIQUE", InteractionCondition::UNIQUE},
    {"DEFAULT", InteractionCondition::DEFAULT},
};



// Operator to store Interactions
bool InteractionHolder::InteractionIdentifier::operator<(const InteractionIdentifier& right) const {
    long n1 = static_cast<long> (npc);
    long n2 = static_cast<long> (right.npc);
    
    // Allow 1000 interactions by npcID
    return (n1*1000000 + interaction) < (n2*1000000 + right.interaction);
}



InteractionHolder::InteractionHolder(){    
    loadFiles();
}



InteractionHolder::~InteractionHolder() {
    // Delete all the String data
    for(sf::String* str : m_strings)
        delete str;
    
    // Delete all the Interaction
    for(auto it : m_interactions)
        delete it.second;
}



bool InteractionHolder::hasInteraction(NpcID npc, int interactionNum) {
    return m_interactions.find({npc, interactionNum}) != m_interactions.end();
}



Interaction* InteractionHolder::getFirstInteraction(NpcID npc) {
    auto it = m_firstInteractions.find(npc);
    
    // If the first interaction was defined
    if(it != m_firstInteractions.end()){
        return getInteraction(npc, it->second);
    }
    else{
        return getInteraction(npc);
    }
}



Interaction* InteractionHolder::getInteraction(NpcID npc, int interactionNum) {
    std::cout << "Got interaction " << interactionNum << " for npc " << static_cast<int>(npc) << std::endl;
    return m_interactions.at({npc, interactionNum});
}



void InteractionHolder::interactionFinished(Interaction* interaction) {
    // Launch actions
    launchActions(interaction->getNpcID(), interaction->getNumber());
}



void InteractionHolder::loadFiles() {
    // Load each file
    for(auto pair : Zone::zoneFileNames){
        // Create the path
        string path = "data/interactions/" + pair.second + ".csv";
        
        loadSingleFile(path);
    }
    
    // Show the Content of the Interaction Holder
    Log("Interactions Loaded ");
    for(auto it : m_interactions){
        Log(toString(it.first.interaction) + " for Npc " + toString(static_cast<int>(it.first.npc)));
    }
}



void InteractionHolder::loadSingleFile(const std::string& filepath) {
    // Parser
    CSVParser parser(filepath);
    parser.ignoreEmptyElements(false);
    
    // Ignore the first line
    parser.readLine();
    
    // Parse each line
    while(parser.readLine()){
        std::vector<std::string>& elements = parser.getLineElements();
        
        loadInteraction(elements);
    }
}



void InteractionHolder::loadInteraction(const std::vector<std::string>& elements) {
    // At least a Npc, Interaction number and interactions type / info
    if(elements.size() < 5){
        std::cout << "Not enough elements for Interaction. Got " << elements.size() << std::endl;
        return;
    }
    
    // Get the Npc ID
    NpcID id = static_cast<NpcID>(atoi(elements[1].c_str()));
    
    // Exit if the Npc is undefined
    if(id == NpcID::not_defined_NPC)
        return;
    
    // Get the interaction number
    int interactionNum = atoi(elements[2].c_str());
    
    // Get the Interction Type
    std::string interactionType = elements[3];
    
    // Interaction data
    std::string data = elements[4];
    
    // Data for the next interaction
    std::string nextData = elements[5];
    
    if(interactionType == "DIALOG"){
        addDialogInteraction(id, interactionNum, data, nextData);
    }
    else if(interactionType == "FIGHT"){
        addFightInteraction(id, interactionNum, nextData);
    }
    else if(interactionType ==  "ITEM_GIFT"){
        addItemGiftInteraction(id, interactionNum, data, nextData);
    }
    else if(interactionType ==  "REACTION"){
        addReactionInteraction(id, interactionNum, data, nextData);
    }
    else if(interactionType ==  "BADGE_GIFT"){
        addBadgeInteraction(id, interactionNum, data, nextData);
    }
    else if(interactionType ==  "HEAL"){
        addHealInteraction(id, interactionNum, nextData);
    }
    else if(interactionType == "CHOICE"){
        addChoiceInteraction(id, interactionNum, data, nextData);
    }
    else if(interactionType == "MOVE"){
        addMoveInteraction(id, interactionNum, data);
    }
    else
        std::cout << "Unknown Interaction type " << interactionType << std::endl;
    
    // Set the Interaction Condition
    std::string actionsString = elements.at(6);
    setActions(id, interactionNum, actionsString);
}



void InteractionHolder::addDialogInteraction(NpcID id, int interactionNumber, std::string& dialogLine, std::string& nextIntData) {
    // Create a SFML String
    sf::String* str = new sf::String(dialogLine);
    
    // Store the String
    m_strings.push_back(str);
    
    // Create the Interaction
    Interaction* interaction = new DialogInteraction(id, interactionNumber, *str);
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addReactionInteraction(NpcID id, int interactionNumber, std::string& reactionData, std::string& nextIntData) {
    // Check the reactionData is in the map
    if(reactionsStrings.find(reactionData) == reactionsStrings.end()){
        std::cout << "No correct reaction for " << reactionData << std::endl;
        return;
    }
    
    // Create the Interaction
    Interaction* interaction = new ReactionInteraction(id, interactionNumber, reactionsStrings.at(reactionData));
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addFightInteraction(NpcID id, int interactionNumber, std::string& nextIntData) {
    // Create the Interaction
    Interaction* interaction = new FightInteraction(id, interactionNumber);
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addItemGiftInteraction(NpcID id, int interactionNumber, std::string& data, std::string& nextIntData) {
    std::string itemName;
    std::string itemNumberStr;
        
    // Split between name and number
    int sepPos = data.find(':');
    if(sepPos != data.npos){
        itemName = data.substr(0, sepPos);
        itemNumberStr = data.substr(sepPos+1);
    }
    else
        return;
    
    // Get the Item ID
    ItemID item = Item::getID(itemName);
    
    // Get the item number
    int number = atoi(itemNumberStr.c_str());
    
    // Create the Interaction
    Interaction* interaction = new ItemInteraction(id, interactionNumber, item, number);
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addBadgeInteraction(NpcID id, int interactionNumber, std::string& badgeNumStr, std::string& nextIntData) {
    // Get the item number
    int number = atoi(badgeNumStr.c_str());
    
    // Create the Interaction
    Interaction* interaction = new BadgeInteraction(id, interactionNumber, number);
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);   
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addHealInteraction(NpcID id, int interactionNumber, std::string& nextIntData) {
    // Create the Interaction
    Interaction* interaction = new HealInteraction(id, interactionNumber);
    
    // Set the next Interaction
    setNextInteraction(interaction, nextIntData);
    
    // Try to add it in the map
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addChoiceInteraction(NpcID id, int interactionNumber, std::string& dialog, std::string& dataChoice) {
    // Create a Choice Interaction
    Interaction* interaction = new ChoiceInteraction(id, interactionNumber, dialog, dataChoice);
    
    // Try to add it
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::addMoveInteraction(NpcID id, int interactionNumber, std::string& moveData) {
    // Create an Entity Mover
    EntityMover* mover = m_moverFabric.createMover(moveData);
    
    
    // Create the Move Interaction
    Interaction* interaction = new MoveInteraction(id, interactionNumber, mover);
    
    
    // Try to add it
    tryAddInMap(id, interactionNumber, interaction);
}



void InteractionHolder::setNextInteraction(Interaction* interaction, std::string& nextIntData) {
    // If the next interaction is set
    if(!nextIntData.empty()){
        // Stream to extract
        std::istringstream stream(nextIntData);
        int nextInteraction;
        
        // Extract the 
        if(stream >> nextInteraction)
            interaction->setNext(nextInteraction);
    }
}



void InteractionHolder::setActions(NpcID id, int interactionNumber, std::string& actionsStr) {
    if(actionsStr.size() == 0)
        return;
    
    // Get the Interaction iterator
    auto it = m_actionsStrings.find({id, interactionNumber});
    
    // Save the string if not already one
    if(it == m_actionsStrings.end()){
        m_actionsStrings.emplace(InteractionIdentifier(id, interactionNumber), actionsStr);
        
        Log("Added action : " + actionsStr);
    }
    else
        Log("Already an action string for " + toString(static_cast<int>(id)
        + "   " + toString(static_cast<int>(interactionNumber))));
}



void InteractionHolder::setCondition(std::string condition, NpcID id, int interactionNumber) {
    // Get the Interaction iterator
    auto it = m_interactions.find({id, interactionNumber});
    
    if(it != m_interactions.end()){
        // Check if the Condition is in the map
        auto itCond = conditionStrings.find(condition);
        if(itCond != conditionStrings.end()){
            // Get the Condition
            InteractionCondition intCond = itCond->second;
            
            // Set the condition
            it->second->setCondition(intCond);
        }
    }
    else{
        std::cout << "Interaction Condition " << condition << " not in the map" << std::endl;
    }
}



void InteractionHolder::tryAddInMap(NpcID id, int interactionNumber, Interaction* interaction) {
    // Check if in the map
    if(m_interactions.find({id, interactionNumber}) != m_interactions.end()){
        std::cout << "already an interaction  " << interactionNumber << "for NPC ID" << static_cast<int>(id) << std::endl;
        delete interaction;
    }
    else
        m_interactions[{id, interactionNumber}] = interaction;
}



void InteractionHolder::launchActions(NpcID id, int interactionNumber) {
    auto it = m_actionsStrings.find(InteractionIdentifier(id, interactionNumber));
    
    if(it != m_actionsStrings.end()){
        // Split the string
        std::vector<std::string>* actions = new std::vector<std::string>();
        
        // Split and get all the actions
        split(actions, it->second, '+');
        
        // Start each action
        for(const std::string& str : *actions)
            action(id, str);
        
        // Delete the vector
        delete actions;
    }
}



void InteractionHolder::action(NpcID id, const std::string& actionstr) {
    // Try to find a separator
    int sepPos = actionstr.find(':');
    
    // If the separator was found
    if(sepPos != actionstr.npos){
        // Get the command string
        std::string command = actionstr.substr(0, sepPos);
        
        // Get the command data
        std::string data = actionstr.substr(sepPos+1);
        
        // Data stream
        istringstream stream(data);
        
        if(command == "SETFIRST"){
            int interactionNum;
            
            // If we managed to extract a number, put it in the map
            if(stream >> interactionNum){
                m_firstInteractions[id] = interactionNum;
                Log("Setting first interaction for " + toString(static_cast<int>(id)) + " as : " + toString(interactionNum));
            }
        }
    }
}



InteractionHolder::InteractionIdentifier::InteractionIdentifier(NpcID npcID, int num) :
npc(npcID),
interaction(num){
   
}
