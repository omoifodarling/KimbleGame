/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Die.cpp
 * Author: omoif
 * 
 * Created on 23 July 2017, 19:16
 */

#include "Die.h"
#include <typeinfo>

Die::Die() {
    this->value = 3;
    //std::cout <<"Die made at @"<< this<<std::endl;
}

Die::Die(const Die& orig) {
}

int Die::GetValue() {
    //this->throwIt();
    //std::cout << "Getter got "<<this->value<<" from GetValue()"<<std::endl;
    return abs(this->value);
}


int Die::throwIt() {
    //std::cout <<"Die thrown"<<std::endl;
    time_t seconds;
    srand((unsigned int) time(&seconds));
    //this->die.SetValue(0);
    int val  = abs(rand() % 6 + 1);
     //std::cout << "Die Value cast was: "<<val <<std::endl;
    this->SetValue(val);
   // std::cout << "Die Value is: "<<this->value <<std::endl;
    //std::cout << "getVal() Die Value is: "<<this->GetValue() <<std::endl;
    return val;
}

void Die::SetValue(int val) {
    //std::cout << "Die setter called " << val << std::endl;
    this->value = val;
    //std::cout << "Left setter " <<std::endl;
}


Die::~Die() {
}

