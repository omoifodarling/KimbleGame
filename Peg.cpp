/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Peg.cpp
 * Author: omoif
 * 
 * Created on 23 July 2017, 18:55
 */

#include "Peg.h"

Peg::Peg() {
}


Color Peg::GetCol() const {
    return col;
}

Peg::Peg(const Peg& orig) {
    *this;
}

Cell* Peg::GetContCell(){
    return contCell;
}

Peg::~Peg() {
}

