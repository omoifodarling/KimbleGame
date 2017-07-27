/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: omoif
 *
 * Created on 23 July 2017, 18:59
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <cstring>

#include "Cell.h"
#include "Color.h"
#include "Peg.h"
#include <iostream>

using namespace std;


class Player {
public:

    Player(Cell* start, Color col) :
    start(start), col(col) {
    }
    
    Player();

    virtual ~Player() {
    }

    Player(const Player& other) :
    home(other.home), start(other.start), fin(other.fin) {
    }

    Cell* GetFin(){return this->fin;}

    Cell* GetHome() {return this->home;};

    char* GetName() {
        return this->name;
    }

    Player  * addFinish(Cell * f,int ind){
        if(ind >= 0 && ind <5)
            this->fin[ind] = *f;
        std::cout<<"Added Finish\n"<<std::endl;
        return this;
    }
    
    Player *addHome(Cell * h,int ind){
        if(ind >= 0 && ind <5)
            this->home[ind] = *h;
        std::cout<<"Added Home\n"<<std::endl;
         return this;
    }

    Player * SetName(char* name) {
        std::strncpy(this->name, name, strlen(name) + 1);
         return this;
    }

    void SetStart(Cell* start) {
        this->start = start;
    }

    Cell* GetStart() const {
        return start;
    }

    Color GetCol() const {
        return col;
    }

    void SetCol(Color col) {
        this->col = col;
    }


    Peg*  GetPegs() { printf("Getting Pegs\n");return pegs;} 
    
    Player * addPeg(Peg * p, int id) {
        if(id >-1 && id < 5)this->pegs[id] = *p;
        return this;
    }


private:
    Cell home[4];
    Cell * start;
    Cell fin[4];
    Peg pegs[4]; 
    Color col;
    char name[20];
};

#endif /* PLAYER_H */

