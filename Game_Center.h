/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game_Center.h
 * Author: omoif
 *
 * Created on 24 July 2017, 13:52
 */

#ifndef GAME_CENTER_H
#define GAME_CENTER_H

#include "Board.h"
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

class Game_Center {
public:
    Game_Center();
    Board * setBoard(char player[4][20], Board *b);

    Game_Center(const Game_Center& orig);
    virtual ~Game_Center();

    Board* getBoard() const {
        return board;
    }

    char *menu(char *men) {
        snprintf(men, 512, "=======WELCOME=======\n"
                "You can choose your Peg Colour\t\nRED,INDIGO, GREEN,PURPLE\n"
                " and Select your Peg to move.\n"
                "DEFAULT Settings\t\nPeg Select:'A'(Auto - farthest first) can Select 'M'(Manual select)\n\t"
                "Direction of Play: 'C'(clockwise- default) and 'N'(Anticlockwise)\n"
                "You can also choose a Player Name per unit of 4 Pegs(Not in this version 1.0)");
        return men;
    }

    char* help(char *men) {
        snprintf(men, 512, "=======WELCOME=======\n"
                "State - 5: HOME, START, MOVING(can be conquered) and SAFE(when home)\n"
                "When one moves to a cell with same player; a peg of one's player e.g. RED, move is denied\n"
                "Otherwise, the owner of the peg looses the accumulated move and Peg returns HOME(restarts it's journey of survival)\n"
                "The Pegs change their state as the progress from Home through SAFE\n"
                "When ALL Pegs are Safe in a Unit/Player, the player wins - Any first unit to turn all in safe state\n\t"
                "=========-------++++++++++++Now enjoy playing!-------+++++++++++===========\n"
                "Choose player? Options are 'Y' or 'L' some other time - later.\n");
        return men;
    }

    int playerToStart() {
        return this->startPlayer;
    }

    int flushTermBuffer(char *flushable, char * touse) {
        int rd, done = 0; // touse is a single character, I used the pointer to access / write the value to it's memory
        //char pos; flushable can also be local i actually used a local variable
        rd = read(STDIN_FILENO, flushable, 20);
        strncpy(touse, flushable, rd - 1);
        printf("Length was: %lu, read was:%d\n", strlen(touse), rd);
        touse[rd - 1] = 0;
        if (*flushable != 0) {
            memset(flushable, 0, 20);
            done = 1;
        }
        rd = 0;
        return done; //this is just an int value - safe to do
    }

    void playGame() {
        //return;
        char dir, mode, player[4][20], flushable[20];
        int playList = 0;
        player[0][0] = 0, player[1][0] = 0, player[2][0] = 0, player[3][0] = 0;
        bool sd = true, sm = true;
        std::cout << "==========********Type 'help' if you need any assistance.**********===============\n\t\t"
                "All Players MUST choose same Direction and or Mode to apply. Otherwise, the default applies."
                "\nPress ENTER when done in each case.\n" << std::endl;
        //FILE * file = fdopen(STDIN_FILENO, "r");
        //std::cout << "Select Play Direction:[C/N?]:" << std::ends;
        while (playList < 4) {
            std::cout << "\nPlayer " << playList + 1 << "\t\t" << std::endl;
            std::cout << "Select Play Direction:[C/N?]:" << std::ends;
            this->flushTermBuffer(flushable, &dir);
            sd = dir == 'N';
            std::cout << "Select Play Mode:[A/M?]:" << std::ends;
            this->flushTermBuffer(flushable, &mode);
            sm = mode == 'M';
            std::cout << "Choose Player Name(2-20 chars max)?:[name/L?]:" << std::ends;
            this->flushTermBuffer(flushable, player[playList++]);
            if (playList == 4)break;
        }
        if (player[0][0] != 0) {
            for (int k = 0; k < 4; k++) {
                this->getBoard()->getPlayers()[k].SetName(player[k]);
                for (int u = 0; u < 7; u++)cout << this->getBoard()->GetLanes()[k*7+u].GetCellID()<<endl;
            }

        };

        //this->start();
        this->getBoard()->setStartPlayer(this->getStartPlayer());
        this->getBoard()->play(sd==true?dir:'C', sm==true?mode:'A');

    }

    Board* updateBoard(Board * b) {
        this->board = b;
    }

    void showPegState(Peg * p, char *mini) {
        snprintf(mini, 60, "%s, PEG %d, Pos:%d,  State:%s", p->GetPName(), p->GetHID(), p->GetLID(), p->GetPState());
        std::cout << "%s" << mini << std::ends;
    }

    State getState() {
        return this->state;
    }

    Game_Center(Board* board, State state, bool loadable) :
    board(board), state(state), loadable(loadable) {
        this->start();
    }

    Game_Center(bool loadable) :
    loadable(loadable) {
        this->playGame();
    }

    int getStartPlayer() const {
        return startPlayer;
    }

    void setStartPlayer(int startPlayer) {
        this->startPlayer = startPlayer;
    }

    Player getThisWinner() const {
        return thisWinner;
    }

    void setThisWinner(Player thisWinner) {
        this->thisWinner = thisWinner;
    }

private:
    Player thisWinner;
    Board * board;
    int startPlayer;
    State state;
    bool loadable;

    void start() {
        for (int j = 0; j < 4; j++) {
            cout << "Home cell type: " << this->board->GetPlayers()[j].GetHome()->GetCellType() << endl;
            cout << "Fin cell type:" << this->board->GetPlayers()[j].GetFin()->GetCellType() << endl;
            cout << "Peg HID:" << this->board->GetPlayers()[j].GetPegs()->GetHID() << endl;
            cout << "Player Name: " << this->board->GetPlayers()[j].GetName() << endl;
        }
        std::cout << "Started()" << std::endl;
        //return;
        timespec tm = {2, 99000000};
        int max = 0, cur, round = 0, res[4], maxInd = 0;
        std::cout << "\n=============Choose Starting Player by Throwing the Die!"
                "=============\n\tPress any key to throw the die\n" << std::ends;
        Player * one = this->board->GetPlayers(), *p = one;
        int count = 0, tie = 1;
        char press, players[4][20];
        for (int h = 0; h< 4; h++) strcpy(players[h],one[h].GetName());
        do {
            while (read(STDIN_FILENO, &press, 1) > 0) {// I could use pselect but no call for that
                //std::cout << "count is:" << count << std::endl;
                this->getBoard()->GetKimble()->pressButton();
                cur = res[round] = this->getBoard()->GetKimble()->dieVal();
                std::cout << "Player " << count + 1 << " in GameUnit " << ++round <<
                        " got " << cur << ". Count is " << count + 1 << std::endl;
                if (max <= cur) {
                    tie = max == cur;
                    max = cur;
                    maxInd = round - 1;
                }
                press = 0;
                //system("cls");
                count++;
                if (max == 6 || count == 4)break;
                //nanosleep(&tm, NULL);
            }
            if (!tie) {
                printf("Results: \n\tP1:%d, P2:%d, P3:%d,P4:%d\n."
                        "=======HURRAY %s. Good job! =========\n\t Let's Play KIMBLE: You start the Game\n",res[0],res[1],res[2],res[3],players[maxInd]);
                this->startPlayer = maxInd;
                return;
            } else {
                round = count = 0;
                one = p;
            }

        } while (tie);
        this->startPlayer = maxInd;
        printf("Leaving start()\n");
    };
};
#endif /* GAME_CENTER_H */