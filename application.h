//
// Created by Stephen Cushen on 29/10/2019.
//
#pragma once
#ifndef LAB4_APPLICATION_H
#define LAB4_APPLICATION_H

#include "board.h"
#include "move.h"

class application {
public:
    application();

    ~application();

    void run();

    int test();

private:
    char nextTurn(char turn);

    static void printMoves(move *firstMove);

    static void deleteList(move *firstMove);
};


#endif //LAB4_APPLICATION_H
