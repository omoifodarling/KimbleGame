/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Peg.h
 * Author: omoif
 *
 * Created on 23 July 2017, 18:55
 */

#ifndef PEG_H
#define PEG_H
#include "Color.h"
#include "Cell.h"
#include <cstring>
#include "State.h"
class Peg {
public:
    Peg();
    
    Peg(int boardLaneID, int homeID, int finID, Color col, State pegState, Cell* contCell, Cell* start, char* playName) :
    boardLaneID(boardLaneID), homeID(homeID), finID(finID), col(col), pegState(pegState), contCell(contCell), start(start), playName(playName) {
    }


    Peg(const Peg& orig);
    
    virtual ~Peg();
    Color GetCol() const;

    void SetCol(Color col) {
        this->col = col;
    }

    Cell * GetContCell();

    void SetContCell(Cell *contCell) {
        this->contCell = contCell;
    }

    Peg(int id, Color col, Cell * contCell) :
    boardLaneID(id), col(col), contCell(contCell) {
    }

    
Peg *changeState() {
    switch(this->pegState){
        case HOME:
            this->pegState = START;
            return this;
         case START:
            this->pegState = MOVING;
            return this;
         case MOVING:
            this->pegState = SAFE;
            return this;
        default:
            break;
    }
    return this;
}

    int GetLID(){
         printf("Getting Board lane %d\n",this->boardLaneID);
        return this->boardLaneID;
    }

    void SetBoardLaneID(int boardLaneID) {
        this->boardLaneID = boardLaneID;
    }

    int GetFinID() const {
        return finID;
    }

    void SetFinID(int finID) {
        this->finID = finID;
    }

    int GetHID() const {
        return homeID;
    }

    void SetHomeID(int homeID) {
        this->homeID = homeID;
    }
    bool equals(Peg * p) {
    return this->GetHID() == p->GetHID()&& strcmp(this->GetPName(),this->GetPName())==0  &&
            this->GetLID() == p->GetLID();
} 

    State GetPState(){
        return pegState;
    }

    void SetPegState(State pegState) {
        this->pegState = pegState;
    }

    char* GetPName() const {
        return playName;
    }
    
    Peg(int boardLaneID, int homeID, int finID, Color col, State pegState, Cell * contCell, char* playName) :
    boardLaneID(boardLaneID), homeID(homeID), finID(finID), col(col), pegState(pegState), contCell(contCell), playName(playName) {
    }

    void SetPlayName(char* playName) {
        this->playName = playName;
    }    

    Cell* GetStart() const {
        return start;
    }
    
    void reset(){
        State h = HOME;
    this->pegState = h;
    this->SetBoardLaneID(0),this->SetFinID(0);
    this->SetContCell(NULL);
}

    void SetStart(Cell* start) {
        this->start = start;
    }

private:
    int boardLaneID,homeID,finID;
    Color col;
    State pegState;
    Cell * contCell;
    Cell * start;
    char * playName;
};

#endif /* PEG_H */

