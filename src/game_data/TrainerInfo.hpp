/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TrainerInfo.hpp
 * Author: Redbuzard
 *
 * Created on 17 décembre 2019, 18:51
 */

#ifndef TRAINERINFO_HPP
#define TRAINERINFO_HPP

#include <string>

class TrainerInfo {
public:
    
    /**
     * Get the trainer name
     * @param trainerID the id of the trainer as an int;
     * @return the trainer name as a wstring
     */
    static std::wstring getTrainerName(int trainerID);
    
    
private:
    
    // Size of the trainerNames tab
    static const int nameSize;
    
    // Tab for the trainer names 
    static const std::wstring trainerNames [];
};

#endif /* TRAINERINFO_HPP */

