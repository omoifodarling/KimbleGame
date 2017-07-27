/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cell.h
 * Author: omoif
 *
 * Created on 23 July 2017, 18:48
 */

#ifndef CELL_H
#define CELL_H

#include <cstdlib>
#include "Color.h"
#include <stdio.h>

class Cell {
public:
    
    Cell();
    Cell(int cellID, char cellType, Color col, int OcchomeID, Color* occCol, bool occupied) :
    cellID(cellID), cellType(cellType), col(col), OcchomeID(OcchomeID), occCol(occCol), occupied(occupied) {
         printf("Cell made\n");
         this->SetHId(0),this->SetFId(0);
         //this->cellID = 0;
    }


    Cell(char cellType, Color col) :
    cellType(cellType), col(col) {
        this->cellID = 0;
    }
    int GetOcchomeID(){
        return OcchomeID;
    }

    void SetOcchomeID(int OcchomeID) {
        this->OcchomeID = OcchomeID;
    }

    Color * GetOccCol(){
        return occCol;
    }

    void SetOccCol(Color * occCol) {
        this->occCol = occCol;
    }


    Cell(const Cell& orig);
    virtual ~Cell();
    

    char GetCellType(){
        return this->cellType;
    }
    

    void SetCellType(char cellType) {
        this->cellType = cellType;
    }

    Color GetCol() const {
        return col;
    }

    void SetCol(Color col) {
        this->col = col;
    }

    bool IsOccupied(){
        return this->occupied;
    }

    void SetOccupied(bool occupied) {
        this->occupied = occupied;
    }

    int GetCellID(){
         printf("Getting Cell lane ID:%d\n",this->cellID);
        return this->cellID;
    }

    void SetCellID(int cellID) {
        this->cellID = cellID;
    }
    void reset(){
        this->OcchomeID = 0;
        this->occCol = NULL;
    }
    int GetFId(){
        return fId;
    }

    void SetFId(int fId) {
        this->fId = fId;
    }

    int GetHId() const {
        return hId;
    }

    void SetHId(int hId) {
        this->hId = hId;
    }

    Cell(int laneID, char cellType, Color col, int OcchomeID, int fId, int hId, Color* occCol, bool occupied) :
    cellID(laneID), cellType(cellType), col(col), OcchomeID(OcchomeID), fId(fId), hId(hId), occCol(occCol), occupied(occupied) {
    }

private:
    int cellID;
    char cellType;
    Color col;
    int OcchomeID, fId,hId;
    Color * occCol;
    bool occupied;
};

#endif /* CELL_H */

