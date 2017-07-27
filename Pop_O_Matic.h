/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Pop_O_Matic.h
 * Author: omoif
 *
 * Created on 23 July 2017, 19:15
 */

#ifndef POP_O_MATIC_H
#define POP_O_MATIC_H

#include "Die.h"
#include <iostream>




class Pop_O_Matic {
public:
    Pop_O_Matic(Die * d);
 
    Pop_O_Matic();
    
    Pop_O_Matic(const Pop_O_Matic& orig);
    virtual ~Pop_O_Matic();
    Die  GetDie() {
        return this->die;
    }
    int castDieVal(){
        return this->die.throwIt();
    }
    
    int dieVal(){return this->die.GetValue();}

    void SetDie(Die * die) {
        this->die = *die;
    }
    
    Die  pressButton(){
        //std::cout<<"Button Pressed"<<std::endl;
        this->die.throwIt();
        //std::cout<<"Cast Die"<<std::endl;
        return this->die;
    }

private:
    Die  die;
};

#endif /* POP_O_MATIC_H */

