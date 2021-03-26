/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EntityMover.cpp
 * Author: Redbuzard
 * 
 * Created on 28 novembre 2018, 06:14
 */

#include "EntityMover.hpp"

EntityMover::EntityMover() :
m_timeSinceLastMove(0){

}



void EntityMover::update(float elapsedTime) {
    m_timeSinceLastMove += elapsedTime;
}



void EntityMover::revertMovement() {

}



void EntityMover::setPosition(sf::Vector2i actualPos) {
    m_actualPos = actualPos;
}



float EntityMover::getSinceLastMove() const {
    return m_timeSinceLastMove;
}



void EntityMover::resetSinceLastMove() {
    m_timeSinceLastMove = 0;
}



MovementType EntityMover::goDirection(Direction dir) {
    switch(dir){
        case Direction::North: return MovementType::GoUp;
        case Direction::South: return MovementType::GoDown;
        case Direction::East: return MovementType::GoRight;
        case Direction::West: return MovementType::GoLeft;
        default: throw std::string("wrong movement type");
    }
}
