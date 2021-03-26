/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoMover.cpp
 * Author: Redbuzard
 * 
 * Created on 5 décembre 2018, 18:56
 */

#include "NoMover.hpp"


NoMover::NoMover() :
EntityMover(){

}



MovementType NoMover::getNextMovement() {
    return MovementType::NoMove;
}



EntityMover* NoMover::copy() {
    return new NoMover();
}



bool NoMover::isFinished() {
    return false;
}
