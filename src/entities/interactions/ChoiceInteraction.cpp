#include "ChoiceInteraction.hpp"


ChoiceInteraction::ChoiceInteraction(NpcID npc, int interactionNumber, const std::string& dialog, const std::string& data) :
Interaction(npc, interactionNumber),
m_dialogLine(dialog),
m_nextInteraction(-1){
    createChoices(data);
}



ChoiceInteraction::~ChoiceInteraction() {
    // Delete each SFML String in the choices
    for(auto c : m_choices)
        delete c.str;
}



void ChoiceInteraction::startInteraction(StateStack* stack, Entity* e) const {
    // Create a vector for the entries
    std::vector<sf::String*>* entries = new std::vector<sf::String*>();
    
    // Push each entries
    for(const Choice& c : m_choices)
        entries->push_back(c.str);
    
    stack->requestStackPushChoice(m_dialogLine, entries);
}



int ChoiceInteraction::getNext() const {
    return m_nextInteraction;
}



void ChoiceInteraction::handleGameEvent(const GameEvent& event) {
    // Finished if a choice state was popped
    if(event.getType() == EventType::StatePopped && event.stateID == StateID::ChoiceS)
        m_isFinished = true;
    // Get the entry selected
    else if(event.getType() == EventType::ChoiceSelected){
        m_nextInteraction = m_choices[event.choice].nextInteraction;
        std::cout << "Selected entry : " << event.choice << ". Next : " << m_nextInteraction << std::endl;
    }
}



void ChoiceInteraction::createChoices(const std::string& data) {
    // Split for the different entries
    std::vector<std::string> entries;
    split(&entries, data, '+');
    
    // For each entry
    for(const std::string& str : entries){
        // Get the position of the splitter
        int posSep = str.find(':');
        
        // If the separator was found
        if(posSep != str.npos){
            // Create a choice
            Choice choice;
            choice.str = new sf::String(str.substr(0, posSep));
            
            // Extract the next interaction
            std::istringstream stream(str.substr(posSep+1));
            stream >> choice.nextInteraction;
            
            // Add it to the vector
            m_choices.push_back(choice);
        }
        else{
            std::cout << "Invalid choice, could not find ':'" << std::endl;
        }
    }
}
