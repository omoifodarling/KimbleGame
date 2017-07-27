/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pop_O_Matic.cpp
 * Author: omoif
 * 
 * Created on 23 July 2017, 19:15
 */

#include "Pop_O_Matic.h"

Pop_O_Matic::Pop_O_Matic() {
    //std::cout<<"POP Empty"<<std::endl;
}

Pop_O_Matic::Pop_O_Matic(Die  * d):die(*d) {
        std::cout<<"Made Board"<<std::endl;
    } 
    //std::cout << "Made POP" << std::endl;


Pop_O_Matic::Pop_O_Matic(const Pop_O_Matic& orig) {
}

Pop_O_Matic::~Pop_O_Matic() {
}

