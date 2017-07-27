/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Die.h
 * Author: omoif
 *
 * Created on 23 July 2017, 19:16
 */

#ifndef DIE_H
#define DIE_H

#include <cstdlib>
#include <sys/types.h>
#include <iostream>
#include <time.h>

class Die {
public:
    Die();
    Die(const Die& orig);
    int GetValue();
    virtual ~Die();
    int throwIt();
protected:
    int value;
    void SetValue(int d);
    
};

#endif /* DIE_H */

