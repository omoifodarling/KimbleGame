/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Board.h
 * Author: omoif
 *
 * Created on 23 July 2017, 19:13
 */

#ifndef BOARD_H
#define BOARD_H
#include "Cell.h"
#include "Player.h"
#include "Pop_O_Matic.h"
#include "Peg.h"
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <ctype.h>
#include <cstdio>
#include <iostream>

using namespace std;

class Board {
public:

    Board(Pop_O_Matic * kimble) :
    kimble(kimble) {
        std::cout << "Made Board" << std::endl;
    }

    int getPos(Peg * p) {
        if (!p->GetLID()) return 0;
        if (p->GetPState() == SAFE) return p->GetFinID();
        return abs(p->GetLID() - p->GetStart()->GetCellID());
    }

    Player * getPlayerOnBoard(Color colName) {

        for (int k = 0; k < 4; k++) {
            if (this->GetPlayers()[k].GetCol() == colName)
                return &this->GetPlayers()[k];
        }
        return &this->GetPlayers()[0];
    }

    Peg * getPegOnPath(Cell * p) {
        if (!p->IsOccupied()) return NULL;
        Player * u = this->getPlayerOnBoard(*(p->GetOccCol()));
        Peg * n = u->GetPegs();
        while (n) {
            if (n->GetCol() == *p->GetOccCol() && p->GetOcchomeID() == n->GetHID())
                return n;
        }
    }

    Cell* GetLanes() {
        return lanes;
    }

    void SetLanes(Cell **cells) {
        //this->lanes = *cells;
        for (int i = 0; i < 28; i++)this->lanes[i] = *cells[i];
        std::cout << "Lanes set\n" << std::endl;
    }

    Player* GetPlayers() {
        return players;
    }

    void SetPlayers(Player * player) {
        *this->players = *player;
        std::cout << "Players set\n" << std::endl;
    }

    Board();
    Board(const Board& orig);

    Pop_O_Matic * GetKimble() {
        return this->kimble;
    }

    void SetKimble(Pop_O_Matic * kimble) {
        this->kimble = kimble;
    }

    Cell getBLane(int id) {
        return this->lanes[--id];
    }

    Board * mutate() {
        State w = WON;
        this->state = w;
        return this;
    }

    Pop_O_Matic getRoller() {
        return *this->kimble;
    }

    bool allSafe(Player * u) {
        bool safe = true;
        Peg *pegs = u->GetPegs();
        for (int k = 0; k < 4; k++) {
            safe &= pegs[k].GetPState();
        }
        return safe;
    }

    State isWon() {
        Player *f = this->GetPlayers();
        for (int k = 0; k < 4; k++) {
            if (allSafe(&f[k])) {
                this->mutate();
                return WON;
            }
        }
        return PLAYING;
    }

    Peg * maxDistPegChoice(Player *p) {
        int peg = 0;
        Peg * pp = p->GetPegs(), *last = pp;
        for (int j = 0; j < 4; j++) {
            if (getPos(&pp[j]) > peg) {
                peg = getPos(&pp[j]);
                last = &pp[j];
            }
        }
        return last;
    }

    Peg *choosePeg(Player *p, int pId) {
        printf("choosing peg()\n");
        return manuallyChoosePeg(p, pId);
    }

    Peg * manuallyChoosePeg(Player * p, int peg) {
        if (peg > 0 && peg < 5) return &p->GetPegs()[--peg];
        return maxDistPegChoice(p);
    }

    Board * playerPlay(char a, Player * p, Die d) {
        int pId = 0;
        Peg * mP = NULL;
        if (a != 'a' || a != 'A') {
            cout << "\nDo You Want to Choose a Peg?(type a number 1-4): " << ends;
            std::cin>> pId;
        }
        if (!pId || a == 'A' || a == 'a') {
            mP = maxDistPegChoice(p);
        } else {
            mP = choosePeg(p, pId);
        }
        //Die  kim = this->GetKimble()->pressButton();
        this->movePeg(mP, d.GetValue());
        std::cout << "\n" << p->GetName() << " Game State:\t\n" << std::ends;
        mP = p->GetPegs();
        for (int k = 0; k < 4; k++) {
            showPegState(&p->GetPegs()[k]);
        }
        return this;
    }

    bool onLane(int dieVal, Peg p) {
        return (getPos(&p) && (getPos(&p) + dieVal <= 28));
    }

    void moveToStart(Peg *p, Cell*st) {
        Player *u = this->getPlayerOnBoard(p->GetCol());
        Cell * l = u->GetStart(); //pointer to Peg's Start lane
        if (l->IsOccupied()) {
            Peg * op = this->getPegOnPath(st);
            op->SetContCell(NULL);
        }
        int value = p->GetHID();
        (u->GetHome()[--value]).SetOccupied(false);
        p->SetContCell(l);
        p->SetBoardLaneID(l->GetCellID());
        Color smart = p->GetCol();
        l->SetOccCol(&smart);
        l->SetOcchomeID(p->GetHID());
        p->changeState();
        l->SetOccupied(true); //We changed state from HOME to START
    }

    Peg * moveToCell(Peg * p, Cell* c) {
        Peg * oldP = this->getPegOnPath(c);
        Cell *oldC = p->GetContCell();
        oldC->reset();
        oldP->reset();
        p->SetContCell(c);
        c->SetOcchomeID(p->GetHID());
        Color smart = p->GetCol();
        c->SetOccCol(&smart);
        return p;
    }

    void addChangePeg(Cell * c, Peg * p) {
        if (!c->IsOccupied()) return;
        moveToCell(p, c);
    }

    bool movePeg(Peg * p, int dieVal) {
        Player *u = this->getPlayerOnBoard(p->GetCol());
        State test = p->GetPState();
        State h = HOME, s = START, m = MOVING, f = SAFE;
        switch (test) {
            case HOME:
                if (dieVal == 6) {
                    //handling a six thrown and leaving HOME State to START
                    Cell * l = u->GetStart(); //pointer to Peg's Start lane
                    moveToStart(p, l);
                    return true;
                }
                return false;
            case START:
                p->changeState();
                this->movePeg(p, dieVal); // transient state
                return true;
            case MOVING:
            {
                int onBoard = dieVal + getPos(p);
                if (this->onLane(dieVal, *p)) {
                    Cell t = this->getBLane(onBoard), *nL = &t;

                    if (nL->IsOccupied()) {
                        if (nL->GetCol() != p->GetCol()) {
                            addChangePeg(nL, p); // This handles swapping and resetting pegs to home state
                            return true;
                        }
                    }
                } else {
                    onBoard -= 28;
                    p->changeState(); //Need a new state(FINISH) to compute play
                    this->movePeg(p, onBoard); //the pointer is faster to compute
                    return true;
                }
            }
            case SAFE:
            {
                if (dieVal + getPos(p) > 4) return false;
                Cell *fin = u->GetFin(); //dieVal altered possibly below
                if (!fin[--dieVal].IsOccupied()) {
                    moveToCell(p, fin);
                    return true;
                }
                return false;
            }
            default:
                break;
        }
        return false;
    }

    int playerToStart() {
        return this->startPlayer;
    }

    char * giveState(State s) {
        switch (s) {
            case HOME: return "HOME";
            case START: return "START";
            case MOVING: return "MOVING";
            case SAFE: return "SAFE";
            case PLAYING: return "PLAYING";
            case WON: return "WON";
            default: return "HOME";
        }
    }

    char * giveColor(Color s) {
        switch (s) {
            case RED: return "RED";
            case INDIGO: return "INDIGO";
            case PURPLE: return "PURPLE";
            case GREEN: return "GREEN";
            case PLAIN: return "PLAIN";
            default: return "PLAIN";
        }
    }

    void showPegState(Peg * p) {
        char mini[60];
        snprintf(mini, 60, "%s, PEG %d \n\tPos:%d \n\t State:%s\n\tTeam:%s\n\t\t=======================+++++++++++++++===========================\n", p->GetPName(), p->GetHID(), p->GetLID(), giveState(p->GetPState()), giveColor(p->GetCol()));
        cout << mini << ends;
    }

    Pop_O_Matic getKimble() const {
        return *kimble;
    }

    void setKimble(Pop_O_Matic * kimble) {
        this->kimble = kimble;
    }

    Cell* getLanes() {
        return lanes;
    }

    Board * addLane(Cell *lane, int id) {
        //printf("Lane to be added to\n");
        if (id > 0 && id <= 28)
            //memmove((Cell*)&this->lanes[id],&lane,sizeof(Cell));
            this->lanes[id] = *lane;
        printf("Lane %d added to\n", lane->GetCellID());
        return this;
    }

    Player* getPlayers() {
        return this->players;
    }

    Board setPlayers(Player * player, int id) {
        cout << "Setting Player\n" << endl;
        if (id >= 0 && id < 4)this->players[id] = *player;
        cout << "Set Player\n" << endl;
        return *this;
    }

    State getState() {
        return this->state;
    }

    void setState(State state) {
        this->state = state;
    }

    void play(char dir, char aOrM) {
        printf("Started in Play!! %d\n", this->getStartPlayer());
        switch (toupper(dir)) {
            case 'N':
                this->counterClockwisePlay(aOrM, playerToStart());
                break;
            case 'C':
            default:
                this->clockwisePlay(aOrM, playerToStart());
                break;
        }
    }

    void clockwisePlay(char mode, int st) {
        int i = 0;
        do {
            char play;
            while (read(STDIN_FILENO, &play, 1) > 0) {
                this->playerPlay(mode, &this->players[((i++) + st - 1) % this->noPlayers], this->GetKimble()->pressButton());
                break;
            }
        } while (this->isWon() != WON);
    }

    void counterClockwisePlay(char mode, int st) {
        int i;
        do {
            char play;
            while (read(STDIN_FILENO, &play, 1) > 0) {
                this->playerPlay(mode, &this->players[abs(((i--) + st - 1) % this->noPlayers)], this->GetKimble()->pressButton());
                break;
            }
        } while (this->isWon() != WON);
    }

    virtual ~Board();

    Board(Pop_O_Matic *kimble, State state, int noPlayers) :
    kimble(kimble), state(state), noPlayers(noPlayers) {
        std::cout << "Multiple inputs called\n" << std::endl;
    }

    int getNoPlayers() const {
        return noPlayers;
    }

    void setNoPlayers(int noPlayers) {
        this->noPlayers = noPlayers;
    }

    int getStartPlayer() const {
        return startPlayer;
    }

    void setStartPlayer(int startPlayer) {
        this->startPlayer = startPlayer;
    }

    Player* getWinner() const {
        return winner;
    }

    void setWinner(Player* winner) {
        this->winner = winner;
    }

private:
    Player players[4];
    Player * winner = NULL;
    Cell lanes[28];
    Pop_O_Matic * kimble;
    State state;
    int noPlayers;
    int startPlayer;


};

#endif /* BOARD_H */

