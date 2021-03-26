/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Champion.hpp
 * Author: Redbuzard
 *
 * Created on 7 avril 2020, 14:48
 */

#ifndef CHAMPION_HPP
#define CHAMPION_HPP

#include "Trainer.hpp"


class Champion : public Trainer{
public:
    
//=================// Constructor //==================//
    
    /**
     * Default Constructor
     */
    Champion(const sf::String& name, const sf::Texture& texture, Context& context, sf::Vector2i pos, Zone* zone, NpcID id);
    
    
//=================// Public methods //==================//
    
    
    /**
     * Check if the trainer is a champion
     * @return true as we are in Champion Class
     */
    virtual bool isChampion() override;
    
    
private:
//=================// Private methods //==================//
    
    /**
     * Setup the NPC ID corresponding to this Champion
     */
    void setupChampionID();
};

#endif /* CHAMPION_HPP */

