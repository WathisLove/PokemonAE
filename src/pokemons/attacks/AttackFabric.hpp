/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AttackFabric.hpp
 * Author: Redbuzard
 *
 * Created on 29 septembre 2020, 10:11
 */

#ifndef ATTACKFABRIC_HPP
#define ATTACKFABRIC_HPP

#include <SFML/System/String.hpp>
#include <set>
#include <map>
#include <array>

#include "Attack.hpp"


/**
 * Class that creates Attacks
 */
class AttackFabric {
public:
//=================// Public methods //==================//
    
    
    /**
     * Create an attack from a Given ID
     * @param id
     * @return 
     */
    static Attack* createAttack(AttackID id);
    
    
private:
//=================// Structure for the possible Statuses //==================//
    
    struct PossibleStatus{
        MainStatusName status;
        float chance;
    };
    
    
//=================// Attack Data //==================//
    
    // Map for the Attack names
    static std::map<AttackID, sf::String> names;
    
    // Map for the Descriptions
    static std::map<AttackID, sf::String> descriptions;
    
    // Map for the Attack types
    static std::map<AttackID, Type> types;
    
    // Map for the Attack categories
    static std::map<AttackID, Attack::AttackCategory> categories;
    
    // Map for the Targets
    static std::map<AttackID, Attack::AttackTarget> targets;
    
    // Map for the damages
    static std::map<AttackID, int> damages;
    
    // Map for the precision
    static std::map<AttackID, int> accuracies;
    
    // Map for the precision
    static std::map<AttackID, int> ppMax;
    
    // Map for the MainStatus
    static std::map<AttackID, AttackFabric::PossibleStatus> mainStatuses;
    
    // Map for the priorities
    static std::map<AttackID, int> priorities;
    
    // Map for the critical levels
    static std::map<AttackID, int> critLevels;
    
    // Set for the Attack that double damages when hit before
    static std::map<AttackID, StatsChanger> statsChangers;
    
    // Map for the hits
    static std::map<AttackID, std::array<int, 2>> hits;
    
    // Map for the recoils percentages
    static std::map<AttackID, int> recoils;
    
    // Maps for the breaks
    static std::set<AttackID> breakBefore;
    static std::set<AttackID> breakAfter;
    
    
    // Set for the Attack that double damages when hit before
    static std::set<AttackID> doubleDamage;    
    
    // Map for the always critical attacks
    static std::set<AttackID> alwaysCriticals;
    
    // Map for the always critical attacks
    static std::set<AttackID> protects;
};

#endif /* ATTACKFABRIC_HPP */

