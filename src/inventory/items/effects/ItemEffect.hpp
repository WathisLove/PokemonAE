/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ItemEffect.hpp
 * Author: Redbuzard
 *
 * Created on 10 février 2021, 17:13
 */

#ifndef ITEMEFFECT_HPP
#define ITEMEFFECT_HPP

#include <SFML/System/String.hpp>

class ItemEffect {
public:
    //=================// Enums //==================//
    
    enum class Type{
        HealHP,
        HealPP,
        HealConfusion,
        HealMainStatus,
        HealKO,
        
        Evolution,
        
        MoneyBoost
    };
    
    
    //=================// Constructors //==================//
    
    
    /**
     * Constructor with a specific Type
     */
    ItemEffect(ItemEffect::Type type);
    
    
    /**
     * Constructor with a string
     */
    ItemEffect(ItemEffect::Type type, sf::String* str);


    /**
     * Destructor
     */
    virtual ~ItemEffect();
    
    
    //=================// Public methods //==================//
    
    /**
     * GCheck if the ItemEffect has an assigned string
     * @return true if the pointer to a string was assigned
     */
    bool hasString() const;
    
    
    //=================// Getters //==================//
    
    
    /**
     * Get the Type of the ItemEffect
     * @return the item effect as an enum
     */
    ItemEffect::Type getType() const;
    
    
    /**
     * Get the string for the current effect
     * @return a const reference to the string
     */
    const sf::String& getString() const;
    

private:
    //=================// Attributes //==================//
    
    // The type of the ItemEffect
    ItemEffect::Type m_type;
    
    // A pointer to the String
    sf::String* m_str;
};

#endif /* ITEMEFFECT_HPP */

