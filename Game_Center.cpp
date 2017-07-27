/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game_Center.cpp
 * Author: omoif
 * 
 * Created on 24 July 2017, 13:52
 */

#include "Game_Center.h"
#include <stdio.h>
#include <conio.h> 
#include <cstdlib>
#include "State.h"
#include "Player.h"
#include "Cell.h"
#include "Color.h" 
#include <iostream>

Game_Center::Game_Center() {
    this->setBoard(NULL,NULL);
    this->start();

}
setBoard(char player[4][20], Player play[4],Cell  lanes[28], Color  cols[5], State st[4]) {

}

Board* Game_Center::setBoard(char player[4][20],Board *b) {
    printf("Players:\t\n%s\n%s\n%s\n%s\n", player[0], player[1], player[2], player[3]);
    printf("Setting board\n");
    
    Color r = RED, i = INDIGO, g = GREEN, p = PURPLE, plain = PLAIN;
    State h = HOME, s = START, m = MOVING, f = SAFE;
    State states[4] = {h, s, m, f};
    Cell * lanes[28];
    //this->getBoard()->SetLanes(lanes);
    Cell *playHome[4][4];
    Cell * playFinish[4][4];
    
    for (int i = 0; i < 28; i++) {
        //lanes[i] = Cell('S',Color->PLAIN);
       lanes[i] = new Cell(i, 'L', plain, 0, NULL, false);
        b->addLane(lanes[i],i);
        printf("Lanes ID:%d\n",lanes[i]->GetCellID());
        printf("Made first lane, about getting board\n");//Cell(0, 'L', plain, 0, NULL, false)
        //this->getBoard()->addLane(lanes[i],i);
    }
    
    printf("Players in Game center\n");
    for(int kk = 0; kk<28; kk++)
        printf("Lane: %d\n", b->getLanes()[kk]);
    printf("Made lanes\n");
    Color colors[5] = {r, g, i, p, plain};
    Peg * pegs[16];
    char name[20];
    Player *players[4];
    for (int i = 0; i < 4; i++) {
        Cell *lane = lanes[i*7+1];
        players[i] = new Player(lane, colors[i]);
        for (int j = 0; j < 4; j++) {
            playHome[i][j] = new Cell(0, 'H', colors[i], 0, NULL, true);
            pegs[i * 4 + j] = new Peg(0, j + 1, 0, colors[i], states[0], playHome[i][j], lanes[i * 7], NULL);
            playFinish[i][j] = new Cell(0, 'F', colors[i], 0, NULL, false);
            players[i] = (players[i]->addFinish(playFinish[i][j],j)->addHome(playHome[i][j],j));
        }
        
        snprintf(name, 12, "Player %d", i + 1);
        //std::cout<<"Name: "<< (player !=NULL ?player:name)<<std::endl;
        player[i] != NULL ? players[i] = (players[i]->SetName(player[i])) : players[i] = (players[i]->SetName(name));
        Peg * miP = NULL, * runner;
        int pCount = h, h = i * 4, end = h + 4;
        miP = pegs[h], runner = miP;
        //std::cout<<"About adding a player name"<<std::endl;
        for (h; h < end; h++) {
            pegs[h]->SetPlayName(players[i]->GetName());
            players[i] = (players[i]->addPeg(pegs[h],h%end));
        }
        std::cout << players[i]->GetName() << " Added." << std::endl;
       b->setPlayers(players[i],i);
        //players[i].SetPegs(runner);
        //std::cout<<"After adding player name"<<std::endl;
        memset(name, 0, strlen(name));   
    }
    //this->start();
    this->getBoard()->setStartPlayer(this->getStartPlayer());
    this->setStartPlayer(this->getStartPlayer());
    return b;
};

Game_Center::Game_Center(const Game_Center& orig) {
}

Game_Center::~Game_Center() {
}

