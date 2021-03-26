/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InteractionHolder.hpp
 * Author: Redbuzard
 *
 * Created on 17 octobre 2020, 10:54
 */

#ifndef INTERACTIONHOLDER_HPP
#define INTERACTIONHOLDER_HPP

#include <set>
#include <map>
#include <vector>
#include <string>

#include <SFML/System/String.hpp>

#include "../Enums.hpp"
#include "../entities/interactions/InteractionCondition.hpp"
#include "../entities/fabric/MoverFabric.hpp"


class EnumLoader;
class Interaction;


enum class NpcID;

class InteractionHolder {
public:
    //=================// Constructor / Destructor //==================//
    
    /**
     * Constructor
     */
    InteractionHolder();
    
    
    /**
     * Destructor
     */
    virtual ~InteractionHolder();

    
    //=================// Public methods //==================//
    
    /**
     * Check if a Npc has a requested interaction
     * @param npc the NpcID
     * @param interactionNum the Interaction number as an int
     * @return true if a corresponding interaction was found
     */
    bool hasInteraction(NpcID npc, int interactionNum = 0);
    
    
    /**
     * Get the first interaction for a given Npc
     * @param npc the Npc ID
     * @return a pointer to the interaction
     */
    Interaction* getFirstInteraction(NpcID npc);
    
    
    /**
     * Check Npc interaction
     * @param npc the NpcID
     * @param interactionNum the Interaction number as an int
     * @return a pointer to the Interaction
     */
    Interaction* getInteraction(NpcID npc, int interactionNum = 0);
    
    
    /**
     * Called when an interaction is finished
     * @param interaction a pointer to the finished interaction
     */
    void interactionFinished(Interaction* interaction);
    
    
private:
    //=================// Private methods //==================//
    
    /**
     * Load all the files in the set
     */
    void loadFiles();
    
    
    /**
     * Load a single file
     * @param filepath a const reference to the file path
     */
    void loadSingleFile(const std::string& filepath);
    
    
    /**
     * Load the Interactions stored in a line
     * @param elements a const reference to a vector of string elements
     */
    void loadInteraction(const std::vector<std::string>& elements);
    
    
    
    /**
     * Add a dialog line reaction
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param dialogLine a string reference to the dialog line
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addDialogInteraction(NpcID id, int interactionNumber, std::string& dialogLine, std::string& nextIntData);
    
    
    /**
     * Add a reaction interaction 
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param reactionData a string containing the data for the Interaction
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addReactionInteraction(NpcID id, int interactionNumber, std::string& reactionData, std::string& nextIntData);
    
    /**
     * Add a fight Interaction
     * @param id the Trainer ID
     * @param interactionNumber
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addFightInteraction(NpcID id, int interactionNumber, std::string& nextIntData);
    
    
    /**
     * Add an item gift interaction 
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param itemNumberStr the number of items contained in a string
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addItemGiftInteraction(NpcID id, int interactionNumber, std::string& intemNumberStr, std::string& nextIntData);
    
    
    /**
     * Add a Bagde Gift Interaction
     * @param id the Npc ID
     * @param interactionNumber the Interaction Number
     * @param badgeNumStr a reference to a string containing the badge number
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addBadgeInteraction(NpcID id, int interactionNumber, std::string& badgeNumStr, std::string& nextIntData);
    
    
    /**
     * Add a heal Interaction
     * @param id the Trainer ID
     * @param interactionNumber
     * @param nextIntData the string for the next interaction (empty is next by default)
     */
    void addHealInteraction(NpcID id, int interactionNumber, std::string& nextIntData);
    
    
    /**
     * Add a Choice Interaction
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param dialogLine a string reference to the dialog line
     * @param dataChoice a string containing the data for the different choices
     */
    void addChoiceInteraction(NpcID id, int interactionNumber, std::string& dialog, std::string& dataChoice);
    
    
    /**
     * Add a Move interaction
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param moveData a string containing the move data
     */
    void addMoveInteraction(NpcID id, int interactionNumber, std::string& moveData);
    
    
    /**
     * Set the next interaction for a given one
     * @param interaction a pointer to the current interaction
     * @param nextIntData a string containing the int for the next interaction
     */
    void setNextInteraction(Interaction* interaction, std::string& nextIntData);
    
    
    /**
     * Set the actions at the end of an interaction
     * @param id the Npc ID
     * @param interactionNumber the Interaction number
     * @param actionsStr a reference to the string containing the actions
     */
    void setActions(NpcID id, int interactionNumber, std::string& actionsStr);
    
    
    /**
     * Try to start actions for a given interaction
     * @param id the NpcID of the interaction
     * @param interactionNumber the interactionNumber of the interaction
     */
    void launchActions(NpcID id, int interactionNumber);
    
    /**
     * Start a single action
     * @param id the Npc ID
     * @param actionStr a const reference to the action string
     */
    void action(NpcID id, const std::string& actionstr);
    
    
    
    /**
     * Set the condition for the interaction
     * @param condition the string containing the condition
     * @param id the Npc ID for the Interaction
     * @param interactionNumber the Interaction number
     */
    void setCondition(std::string condition, NpcID id, int interactionNumber);
    
    
    /**
     * Try to add an interaction in the map
     * @param id the Npc ID
     * @param interactionNumber the interaction Number
     * @param interaction a pointer to the interaction
     * @warning deletes the interaction if it can not bea added to the map
     */
    void tryAddInMap(NpcID id, int interactionNumber, Interaction* interaction);
    
    
    //=================// Private struct //==================//
    
    /**
     * A structure to identify Interactions
     */
    struct InteractionIdentifier{
        NpcID npc;
        int interaction;
        
        InteractionIdentifier(NpcID npcID, int num);
        
        // Operator for the Map storage
        bool operator<(const InteractionIdentifier& right) const;
    };
    
    
    //=================// Attributes //==================//

    // A fabric for the entity Movers
    MoverFabric m_moverFabric;
    
    
    // Vector of SFML Strings (data for dialogs and others)
    std::vector<sf::String*> m_strings;
    
    // Map of Interaction
    std::map<InteractionIdentifier, Interaction*> m_interactions;
    
    // Map for action strings
    std::map<InteractionIdentifier, std::string> m_actionsStrings;
    
    // Map for the Npc first interactions saved
    std::map<NpcID, int> m_firstInteractions;
    
    //=================// Static attributes //==================//
    
    // Map to convert strings to reactions
    static const std::map<std::string, ReactionType> reactionsStrings;
    
    // Map to convert Condition string to Enum
    static const std::map<std::string, InteractionCondition> conditionStrings;
};

#endif /* INTERACTIONHOLDER_HPP */

